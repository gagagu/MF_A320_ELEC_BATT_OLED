# MF_A320_ELEC_BATT_OLED
This ist the Mobiflight firmware for a DIY 3d printed A320 Elec Panel

![alt_text](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/Bild1.jpg)

# ToDo
* Power on/off functionality
  
# General
This is a firmware for using two OLED 1,3" i2c Displays for an A320 Elect Panel with Mobiflight. 

I am using the following two Displays for my Project: [Aliexpress](https://de.aliexpress.com/item/1005003484018034.html) and one TCA9548A I2C Multiplexer.

# 3d files
[here](https://cults3d.com/de/modell-3d/spiel/a320-elec-panel)

# Schematic
![alt_text](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/Schematic.jpg)

# Install
Download the ZIP file from the Releases and extract it into the community folder within your Mobiflight folder. It should look like this:
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install1.jpg" width=80% height=80%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install1.jpg)

Start Mobiflight and open the "Mobiflight Modules Settings" page. If your device is not shown as "Compatible" than make a right click and choose "Reset Board" on the menu.
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install2.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install2.jpg)

Than make a right click on "Compatible" and choose "Update Firmaware / Community / gagagu MF_A320_ELEC_BATT_OLED Mega" from Menu.
The device will now get the newest firmware.
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install3.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install3.jpg)
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install4.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install4.jpg)

Make an another right mouse click on the device and choose "Add device / Custom Devices / gagagu's MF_A320_ELEC_BATT_OLED" from  Menu
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install5.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install5.jpg)
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install6.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install6.jpg)


With the Address setting you can select the OLED Display Device Type:
* 0x70 = SSD1306 
* 0x71 = SH1106

Than upload the config
[<img src="https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install7.jpg" width=50% height=50%>](https://github.com/gagagu/MF_A320_ELEC_BATT_OLED/blob/main/images/install7.jpg)

