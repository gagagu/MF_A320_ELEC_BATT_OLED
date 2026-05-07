#include "MF_A320_ELEC_BATT_OLED.h"
#include "allocateMem.h"
#include "commandmessenger.h"
#include "Fonts/DSEG7Classic_Regular_High28pt7b.h"

/* **********************************************************************************
    This is just the basic code to set up your custom device.
    Change/add your code as needed.
********************************************************************************** */

String  elecPanelBattLeftValue = "";
String  elecPanelBattRightValue  = "";

MF_A320_ELEC_BATT_OLED::MF_A320_ELEC_BATT_OLED()
    : _initialised(false)
    , _addrI2C(0)
    , oled(nullptr)
    , _battLeftValue("")
    , _battRightValue("")
    , _battLeftDirty(false)
    , _battRightDirty(false)
{
}


void MF_A320_ELEC_BATT_OLED::attach(uint8_t addrI2C)
{
    _addrI2C = addrI2C;
    Wire.begin();
    Wire.setClock(400000);
 
    if (!FitInMemory(sizeof(OLEDInterface))) {
        cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
        return;
    }
 
    // Odd address → SSD1306, even address → SH1106
    OLEDType type = (_addrI2C & 0x01) ? SSD1306 : SH1106;
    oled = new (allocateMemory(sizeof(OLEDInterface))) OLEDInterface(type);
 
    _initialised = true;
}



void MF_A320_ELEC_BATT_OLED::begin()
{
    if (!_initialised)
        return;
 
    setTCAChannel(TCA9548A_CHANNEL_BATT_LEFT);
    oled->begin(SCREEN_ADDRESS, true);
    oled->display();
    updateDisplayBattLeft();
 
    setTCAChannel(TCA9548A_CHANNEL_BATT_RIGHT);
    oled->begin(SCREEN_ADDRESS, true);
    oled->display();
    updateDisplayBattRight();
}

void MF_A320_ELEC_BATT_OLED::detach()
{
    if (!_initialised)
        return;
    _initialised = false;
}

void MF_A320_ELEC_BATT_OLED::set(int16_t messageID, char *message)
{
    /* MessageID == -2: PowerSavingMode ("0" = verlassen, "1" = betreten)
       MessageID == -1: Connector gestoppt → Display leeren               */
    switch (messageID) {
    case 0:
        // if (_battLeftValue != message) {
        //     _battLeftValue  = message;
        //     _battLeftDirty  = true;
        // }
        _battLeftValue  = message;
        updateDisplayBattLeft();
        break;
 
    case 1:
        // if (_battRightValue != message) {
        //     _battRightValue = message;
        //     _battRightDirty = true;
        // }
        _battRightValue = message;
        updateDisplayBattRight();
        break;
 
    default:
        break;
    }
}

void MF_A320_ELEC_BATT_OLED::update()
{
     updateDisplayBattLeft();
    // Nur neu zeichnen, wenn sich der Wert tatsächlich geändert hat
    //if (_battLeftDirty) {
        updateDisplayBattLeft();
     //   _battLeftDirty = false;
   // }
   // if (_battRightDirty) {
        updateDisplayBattRight();
   //     _battRightDirty = false;
   // }
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------
 
void MF_A320_ELEC_BATT_OLED::setTCAChannel(byte channel)
{
    Wire.beginTransmission(_addrI2C);
    Wire.write(1 << channel);
    Wire.endTransmission();
    delay(5);
}

/**
 * Gemeinsame Render-Logik für beide Batteriedisplays.
 * @param channel  TCA9548A-Kanal (BATT_LEFT oder BATT_RIGHT)
 * @param value    Aktueller Anzeigewert als String
 */
void MF_A320_ELEC_BATT_OLED::updateDisplay(byte channel, const String &value)
{
        String displayStr = "";
    setTCAChannel(channel);
    oled->clearDisplay();
    oled->setTextColor(SSD1306_WHITE);
    oled->setFont(&DSEG7Classic_Regular_High28pt7b);
    oled->setCursor(BATT_CURSOR_X, BATT_CURSOR_Y);
 
    if (value.length() == 0 || value == BATT_VALUE_INVALID) {
        // Kein gültiger Wert → leeres Display
        oled->print(displayStr);
        oled->display();
        return;
    }
 
    // Führende Nullen so dass immer 3 Stellen angezeigt werden
    float fValue = value.toFloat();

    if (fValue < 10.0f)       displayStr = "00";
    else if (fValue < 100.0f) displayStr = "0";
    displayStr += value;
 
    oled->print(displayStr);
    oled->println("-");
    oled->fillCircle(BATT_DOT_X, BATT_DOT_Y, BATT_DOT_RADIUS, SSD1306_WHITE);
    oled->display();
}
 
void MF_A320_ELEC_BATT_OLED::updateDisplayBattLeft()
{
    updateDisplay(TCA9548A_CHANNEL_BATT_LEFT, _battLeftValue);
}
 
void MF_A320_ELEC_BATT_OLED::updateDisplayBattRight()
{
    updateDisplay(TCA9548A_CHANNEL_BATT_RIGHT, _battRightValue);
}