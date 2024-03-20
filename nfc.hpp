#pragma once

#include <SoftwareSerial.h>
#include <PN532.h>
#include <PN532_SWHSU.h>

namespace nfc_utils
{
    void read_nfc_uid(PN532* nfc, uint8_t uid[], uint8_t* length);
}