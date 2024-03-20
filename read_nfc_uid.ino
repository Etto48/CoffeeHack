#include "nfc.hpp"

namespace nfc_utils
{
    void read_nfc_uid(PN532* nfc, uint8_t uid[], uint8_t* length)
    {
        bool success = false;
        while (!success)
        {
            success = (*nfc).readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, length);
            if(success)
            {
                return;
            }
            else
            {
                delay(1000);
            }
        }
        return;
    }
}