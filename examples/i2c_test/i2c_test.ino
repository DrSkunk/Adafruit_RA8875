/******************************************************************
 This is an I2C example for the Adafruit RA8875 Driver board for TFT
 displays. The RA8875 is a TFT driver for up to 800x480 dotclock'd
 displays.

 Some RA8875 modules (e.g. the EastRising / buydisplay.com ER-TFTM050-3)
 can be driven over I2C instead of SPI. To use I2C:

   * Set the module's interface jumpers to I2C mode (see the module's
     datasheet - on the ER-TFTM050-3 short J6, J10, J11, J14, J16).
   * Wire SCLK -> I2C SCL, SDI -> I2C SDA (bidirectional), leave SDO
     floating (NC), and connect RST to the pin below.

 IMPORTANT: the I2C slave address depends on the module's hardwired IICA
 strap pins. The RA8875_DEFAULT_I2CADDR used here is only a placeholder.
 Run an I2C scanner sketch to find the real address, then pass it to the
 constructor: Adafruit_RA8875(RA8875_RESET, &Wire, 0xNN);

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!

 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

#define RA8875_RESET 9

// Construct over I2C: reset pin, I2C bus, (optional) 7-bit address.
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_RESET, &Wire);

// Scan the I2C bus and print every device address found. Use this to confirm
// the RA8875's actual address before relying on RA8875_DEFAULT_I2CADDR.
void i2cScan() {
  Serial.println("Scanning I2C bus...");
  uint8_t count = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("  found device at 0x");
      Serial.println(addr, HEX);
      count++;
    }
  }
  if (count == 0)
    Serial.println("  no I2C devices found");
}

void setup() {
  Serial.begin(9600);
  Serial.println("RA8875 start (I2C)");

  Wire.begin();
  i2cScan();

  /* Initialize using 'RA8875_480x80', 'RA8875_480x128',
     'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_800x480)) {
    Serial.println("RA8875 Not Found!");
    Serial.println("Check wiring, I2C jumpers, and the slave address.");
    while (1)
      ;
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);                              // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);

  tft.fillScreen(RA8875_BLACK);
  tft.fillScreen(RA8875_RED);
  tft.drawCircle(400, 240, 100, RA8875_WHITE);
  tft.fillRect(100, 100, 80, 60, RA8875_BLUE);
}

void loop() {}
