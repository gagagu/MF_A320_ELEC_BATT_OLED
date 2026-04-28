#pragma once

#include <Arduino.h>
#include "MF_A320_ELEC_BATT_OLED.h"

// only one entry required if you have only one custom device
enum {
    ELEC_BATT_DEVICE = 1
};
class MFCustomDevice
{
public:
    MFCustomDevice();
    void attach(uint16_t adrPin, uint16_t adrType, uint16_t adrConfig, bool configFromFlash = false);
    void detach();
    void update();
    void set(int16_t messageID, char *setPoint);

private:
    bool           getStringFromMem(uint16_t addreeprom, char *buffer, bool configFromFlash);
    bool           _initialized = false;
    MF_A320_ELEC_BATT_OLED *_mydevice;
    uint8_t        _customType = 0;
};
