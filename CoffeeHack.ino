#include <SoftwareSerial.h>
#include <PN532_SWHSU.h>
#include <PN532.h>

SoftwareSerial SWSerial(2, 3); // RX, TX

PN532_SWHSU pn532swhsu(SWSerial);
PN532 nfc(pn532swhsu);

void setup()
{
    Serial.begin(19200);
    Serial.println("Initializing nfc reader...");
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
        Serial.print("Didn't find PN53x board");
        exit(0);
    }

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
    
}