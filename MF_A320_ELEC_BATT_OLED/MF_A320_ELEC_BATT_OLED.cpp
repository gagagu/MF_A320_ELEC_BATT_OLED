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
{
	_initialised = false;
}



void MF_A320_ELEC_BATT_OLED::attach(uint8_t addrI2C)
{
    _addrI2C = addrI2C;
    Wire.begin();
    Wire.setClock(400000);
    if (!FitInMemory(sizeof(OLEDInterface))) {
        // Error Message to Connector
        cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
        return;
    }
    if (_addrI2C & 0x01) {
        oled = new (allocateMemory(sizeof(OLEDInterface))) OLEDInterface(SSD1306);
    } else {
        oled = new (allocateMemory(sizeof(OLEDInterface))) OLEDInterface(SH1106);
    }
    _initialised = true;
}



void MF_A320_ELEC_BATT_OLED::begin()
{
	if (!_initialised)
		return;
	
    //**************************
    // // BATT left
    // //**************************
    setTCAChannel(TCA9548A_CHANNEL_BATT_LEFT);
    oled->begin(SCREEN_ADDRESS, true); // Address 0x3C default
    oled->display();
    updateDisplayBattLeft();	
	
	//**************************
    // // BATT right
    // //**************************
    setTCAChannel(TCA9548A_CHANNEL_BATT_RIGHT);
    oled->begin(SCREEN_ADDRESS, true); // Address 0x3C default
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
    /* **********************************************************************************
        Each messageID has it's own value
        check for the messageID and define what to do.
        Important Remark!
        MessageID == -2 will be send from the board when PowerSavingMode is set
            Message will be "0" for leaving and "1" for entering PowerSavingMode
        MessageID == -1 will be send from the connector when Connector stops running
        Put in your code to enter this mode (e.g. clear a display)

    ********************************************************************************** */
    switch (messageID) {
    case 0:
        // Efis Left Baro Select
        // inHg=0, hPa=1
        elecPanelBattLeftValue = message;
        updateDisplayBattLeft();
        break;

    case 1:
        // Efis Right Baro Value Hpa
        elecPanelBattRightValue = message;
        updateDisplayBattRight();
        break;

    default:
        break;
    }
}

void MF_A320_ELEC_BATT_OLED::update()
{
    // Do something which is required regulary
	updateDisplayBattLeft();
    updateDisplayBattRight();
}

/*
  switch multiplexer channel
*/
void MF_A320_ELEC_BATT_OLED::setTCAChannel(byte i)
{
    Wire.beginTransmission(_addrI2C);
    Wire.write(1 << i);
    Wire.endTransmission();
    delay(5); // Pause
}


void MF_A320_ELEC_BATT_OLED::updateDisplayBattLeft(void)
{
	setTCAChannel(TCA9548A_CHANNEL_BATT_LEFT);
    // Clear the buffer
    oled->clearDisplay();
    oled->setTextColor(SSD1306_WHITE);
	oled->setFont(&DSEG7Classic_Regular_High28pt7b);
    
	//code
	oled->setCursor(0, 60);
    if(elecPanelBattLeftValue.length()==2)
    {
        oled->print("0"); 
    }
    else if (elecPanelBattLeftValue.length()==1){
        oled->print("00"); 
    }	
    oled->print(elecPanelBattLeftValue);

    if (elecPanelBattLeftValue.length()>0){
    	oled->println("-");
    	oled->fillCircle(60, 58, 2, SSD1306_WHITE);  
    }    
	// show
	oled->display();
}

void MF_A320_ELEC_BATT_OLED::updateDisplayBattRight(void)
{
	setTCAChannel(TCA9548A_CHANNEL_BATT_RIGHT);
    // Clear the buffer
    oled->clearDisplay();
    oled->setTextColor(SSD1306_WHITE);
	oled->setFont(&DSEG7Classic_Regular_High28pt7b);

	//code
	oled->setCursor(0, 60);
    if(elecPanelBattRightValue.length()==2)
    {
        oled->print("0"); 
    }
    else if (elecPanelBattRightValue.length()==1){
        oled->print("00"); 
    }
    oled->print(elecPanelBattRightValue);
    
    if (elecPanelBattRightValue.length()>0){
    	oled->println("-");
    	oled->fillCircle(60, 58, 2, SSD1306_WHITE);  
    }

	// show
	oled->display();
}