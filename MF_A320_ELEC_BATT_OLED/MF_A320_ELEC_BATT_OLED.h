#pragma once

#include "Arduino.h"
#include "OLEDInterface.h"

// address of the multiplexer to change the channels
#define TCA9548A_I2C_ADDRESS  0x70
#define TCA9548A_CHANNEL_BATT_LEFT  0
#define TCA9548A_CHANNEL_BATT_RIGHT 1
#define TCA9548A_CHANNEL_UNUSED_1   2
#define TCA9548A_CHANNEL_UNUSED_2   3
#define TCA9548A_CHANNEL_UNUSED_3   4
#define TCA9548A_CHANNEL_UNUSED_4   5
#define TCA9548A_CHANNEL_UNUSED_5   6
#define TCA9548A_CHANNEL_UNUSED_6   7

class MF_A320_ELEC_BATT_OLED
{
public:
    MF_A320_ELEC_BATT_OLED();
    void begin();
    void attach(uint8_t addrI2C);
    void detach();
    void set(int16_t messageID, char *message);
    void update();

private:
    bool    _initialised;
    uint8_t       _addrI2C;
    OLEDInterface *oled;
	
    void setTCAChannel(byte i);
    void updateDisplayBattLeft(void);
    void updateDisplayBattRight(void);	
};