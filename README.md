# NINA-Arduino
Modifyed the NINA-FW to run with arduino. This supports esp32c3

# Burning Firmware
Try running the command `esptool.py` and see if the command is found, otherwie install the esptool.py at https://github.com/espressif/esptool


**Step 1.** Wipe Chip:
``` sh
esptool.py --chip esp32 --port <SERIAL PORT> erase_flash
```

**Step 2.** Install firmware:
``` sh
esptool.py --chip esp32 --port <SERIAL PORT> --baud 115200 write_flash 0 <FLASH FILE>.bin
```

<br />

# !NOTE!
This firmware is a simplified version of the ESP32-NINA firmware, modifyed to work with the ESP32c3 module.  
The original github repo can be found [here](https://github.com/adafruit/nina-fw).  

<br />

# Building a custom ESP32 firmware
The building itself is actually quite simple. All that is needed is the [Arduino-IDE](https://www.arduino.cc/en/software)  

As well as a few libraries:
- [ESP32Ping](https://github.com/marian-craciunescu/ESP32Ping)
- TODO: NTP

<br />

# Wiring
The connection between the ESP32c3 and the Pico is as follows:
```
PICO            ESP32c3
VSYS    <-->    VIN
GND     <-->    GND
GP7     <-->    IO7  (CS)
GP10    <-->    IO18 (_Ready)
GP11    <-->    EN   (_EN)
GP16    <-->    IO6  (MISO)
GP18    <-->    IO4  (SCK)
GP19    <-->    IO5  (MOSI)
```

<br />

# (OPTIONAL) Change pins
The pins for spi change depending on what board is used.  
The current pins are configured for the ESP32c3.  
The pins can be changed in `"NINA-Arduino/NINA-Simple/SPIS.cpp"`  
At the buttom, you will see:
``` cpp
SPISClass SPIS(SPI2_HOST, SPI_DMA_CH_AUTO, 5, 6, 4, 7, 18);
```
These are the pins, used for the SPI communication, and can be changed to fit your chip.  
The pin order can be found in the function definition:
``` cpp
SPISClass::SPISClass(spi_host_device_t hostDevice, int dmaChannel, int mosiPin, int misoPin, int sclkPin, int csPin, int readyPin)
```
NOTE: Do not change the `hostDevice` or `dmaChannel` unless the ESP gives an error.

<br />

# TODO:
There is a lot of TODO and NOTE tags in the source code that can give an inside on some changes that is needed, but here is a few.

## Add SSL
Since SSL made the compiler slow, as well as some libraries were missing, then I have chose to disable it for the time being.  
This should be enabled for later use.

<br />

# References
### ESP32 Toolcahin
https://docs.espressif.com/projects/esp-idf/en/v3.3.1/get-started/index.html#setup-toolchain
### NINA-FW
https://github.com/adafruit/nina-fw

https://www.youtube.com/watch?v=YjKEpQDj8S0
