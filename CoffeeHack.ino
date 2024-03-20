#include "nfc.hpp"

SoftwareSerial SWSerial(3, 2); // RX, TX

PN532_SWHSU pn532swhsu(SWSerial);
PN532 nfc(pn532swhsu);

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing nfc reader...");

    uint32_t versiondata = 0;
    while (!versiondata)
    {
        nfc.begin();
        versiondata = nfc.getFirmwareVersion();
        if (!versiondata)
        {
            Serial.print(".");
            delay(1000);
        }
    }
    Serial.println("");
    

    Serial.print("Found chip PN5");
    Serial.println((versiondata >> 24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata >> 16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata >> 8) & 0xFF, DEC);

    nfc.SAMConfig();
}

void loop()
{
    Serial.println("Select operation:");
    Serial.println("1. Read NFC UID");
    Serial.println("2. Serial passthrough");

    while (Serial.available() == 0)
    {
        delay(100);
    }

    int operation = Serial.parseInt();
    switch (operation)
    {
    case 1:
        read_nfc_uid_frontend();
        break;
    case 2:
        serial_passthrough();
        break;
    default:
        Serial.println("Invalid operation");
        break;
    }
}

void read_nfc_uid_frontend()
{
    uint8_t uid[7] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t uidLength = 0;

    Serial.println("Place card on reader...");
    
    nfc_utils::read_nfc_uid(&nfc, uid, &uidLength);

    Serial.println("Found card with UID:");
    for (uint8_t i = 0; i < uidLength; i++)
    {
        Serial.print(" ");
        Serial.print(uid[i], HEX);
    }
    Serial.println("");
}

int serial_passthrough()
{
    while (1)
    {
        while (Serial.available() > 0)
        {
            SWSerial.write(Serial.read());
        }

        while (SWSerial.available() > 0)
        {
            Serial.write(SWSerial.read());
        }
    }
    return 0;
}

