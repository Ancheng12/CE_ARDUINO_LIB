/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        ADS1114
        This code is designed to work with the ADS1114_I2CADC I2C Mini Module available from ControlEverything.com.
        https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1114_I2CADC#tabs-0-product_tabset-2
*/
/**************************************************************************/

#include <Wire.h>
#include <ADS1114.h>

ADS1114 ads;

void setup(void)
{
    Serial.begin(9600);

    // The address can be changed making the option of connecting multiple devices
    ads.getAddr_ADS1114(ADS1114_DEFAULT_ADDRESS);   // 0x48, 1001 000 (ADDR = GND)
    // ads.getAddr_ADS1114(ADS1114_VDD_ADDRESS);    // 0x49, 1001 001 (ADDR = VDD)
    // ads.getAddr_ADS1114(ADS1114_SDA_ADDRESS);    // 0x4A, 1001 010 (ADDR = SDA)
    // ads.getAddr_ADS1114(ADS1114_SCL_ADDRESS);    // 0x4B, 1001 011 (ADDR = SCL)

    // The ADC gain (PGA), Device operating mode, Data rate
    // Comparator mode, Comparator polarity, Latching comparator
    // Comparator queue can be changed via the following functions

    ads.setGain(GAIN_TWO);          // 2x gain   +/- 2.048V  1 bit = 0.0625mV (default)
    //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV
    // ads.setGain(GAIN_ONE);       // 1x gain   +/- 4.096V  1 bit = 0.125mV
    // ads.setGain(GAIN_FOUR);      // 4x gain   +/- 1.024V  1 bit = 0.03125mV
    // ads.setGain(GAIN_EIGHT);     // 8x gain   +/- 0.512V  1 bit = 0.015625mV
    // ads.setGain(GAIN_SIXTEEN);   // 16x gain  +/- 0.256V  1 bit = 0.0078125mV

    ads.setMode(MODE_CONTIN);       // Continuous conversion mode
    // ads.setMode(MODE_SINGLE);    // Power-down single-shot mode (default)

    ads.setRate(RATE_128);          // 128SPS (default)
    // ads.setRate(RATE_8);         // 8SPS
    // ads.setRate(RATE_16);        // 16SPS
    // ads.setRate(RATE_32);        // 32SPS
    // ads.setRate(RATE_64);        // 64SPS
    // ads.setRate(RATE_250);       // 250SPS
    // ads.setRate(RATE_475);       // 475SPS
    // ads.setRate(RATE_860);       // 860SPS

    ads.setOSMode(OSMODE_SINGLE);   // Start a single-conversion (default)

    ads.setCompMode(COMPMODE_TRAD);     // Traditional comparator with hysteresis (default)
    // ads.setCompMode(COMPMODE_WINDOW);// Window comparator

    ads.setCompPol(COMPPOL_LOW);        // Comparator polarity: Active low (default)
    // ads.setCompPol(COMPPOL_HIGH);    // Comparator polarity: Active high

    ads.setCompLat(COMPLAT_LATCH);   // Latching comparator
    // ads.setCompLat(COMPLAT_NONLAT);     // Non-latching comparator (default)


    ads.setCompQue(COMPQUE_ONE);        // Comparator queue: Assert after one conversion
    // ads.setCompQue(COMPQUE_TWO);     // Comparator queue: Assert after two conversion
    // ads.setCompQue(COMPQUE_FOUR);    // Comparator queue: Assert after four conversion
    // ads.setCompQue(COMPQUE_NONE);    // Disable comparator (default)

    // Be careful never to exceed VDD +0.3V max, or the upper and lower limits
    // Setting these values incorrectly may destroy your ADC
    // ADC Range: +/- 2.048V (1 bit = 0.0625mV)");
    // Serial.println("Comparator High Threshold: 32000 (2.000V)");
    ads.setHighThreshold(32000);
    // ads.setLowThreshold(0);

    ads.begin();

    delay(1000);
}

void loop(void)
{
    byte error;
    int8_t address;

    address = ads.ads_i2cAddress;
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        int16_t result01;

        Serial.println("Getting Comparator Differential Reading from AIN01");
        result01 = ads.Comparator_Differential(01);
        Serial.print("Digital Value of Analog Input between Channel 0 and 1: ");
        Serial.println(result01);
        Serial.println(" ");
        Serial.println("        ***************************        ");
        Serial.println(" ");
    }
    else
    {
        Serial.println("ADS1114 Disconnected!");
        Serial.println(" ");
        Serial.println("        ************        ");
        Serial.println(" ");
    }

    delay(1000);
}
