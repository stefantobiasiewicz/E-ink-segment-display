#include <stdio.h>
#include <Wire.h>
#include "EPD_1in9.h"

float temperature_value = 0.0;
float humidity_value = 0.0;
uint8_t digit_left[] = {0xbf, 0x00, 0xfd, 0xf5, 0x47, 0xf7, 0xff, 0x21, 0xff, 0xf7, 0x00};  
uint8_t digit_right[] = {0x1f, 0x1f, 0x17, 0x1f, 0x1f, 0x1d, 0x1d, 0x1f, 0x1f, 0x1f, 0x00};  
uint8_t eink_segments[15] = {0x00};  

void updateTemperatureDisplay(float temperature);
void updateHumidityDisplay(float humidity);
void updateTemperatureDisplay(float temperature);
void updateHumidityDisplay(float humidity);


void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);


	// put your setup code here, to run once:
  	Serial.begin(9600);
	Wire.begin(); 
	Serial.println("e-Paper init and clear");
	GPIOInit();
	EPD_1in9_init();
	

	EPD_1in9_lut_5S();




	
	EPD_1in9_Write_Screen(DSPNUM_1in9_off);
	delay(500);
	
	EPD_1in9_lut_GC();
	
	EPD_1in9_Write_Screen1(DSPNUM_1in9_on);
	delay(500);
	
	// EPD_1in9_Write_Screen(DSPNUM_1in9_off);
	// delay(500);
	
	EPD_1in9_lut_DU_WB();
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W0);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W1);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W2);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W3);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W4);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W5);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W6);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W7);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W8);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_W9);
	// delay(500);
	// EPD_1in9_Write_Screen(DSPNUM_1in9_WB);
	// delay(500);

	// EPD_1in9_sleep();
	// Serial.end();
	// Wire.end();
}

void loop()
{
	temperature_value += 4.1;
	humidity_value += 3.1;

	updateTemperatureDisplay(temperature_value);
	updateHumidityDisplay(humidity_value);

	EPD_1in9_Write_Screen(eink_segments);

	delay(1000);
}

void updateTemperatureDisplay(float temperature) {
  char temperature_digits[4];
  temperature_digits[0] = int(temperature / 100) % 10;
  temperature_digits[1] = int(temperature / 10) % 10;
  temperature_digits[2] = int(temperature) % 10;
  temperature_digits[3] = int(temperature * 10) % 10;

  if (temperature < 100) { temperature_digits[0] = 10; }
  if (temperature < 10) { temperature_digits[1] = 10; }

  eink_segments[0] = digit_right[temperature_digits[0]];
  eink_segments[1] = digit_left[temperature_digits[1]];
  eink_segments[2] = digit_right[temperature_digits[1]];
  eink_segments[3] = digit_left[temperature_digits[2]];
  eink_segments[4] = digit_right[temperature_digits[2]] | B00100000; // Decimal point
  eink_segments[11] = digit_left[temperature_digits[3]];
  eink_segments[12] = digit_right[temperature_digits[3]];

  eink_segments[13] = 0x05; // °C symbol
}

void updateHumidityDisplay(float humidity) {
  char humidity_digits[3];
  humidity_digits[0] = int(humidity / 10) % 10;
  humidity_digits[1] = int(humidity) % 10;
  humidity_digits[2] = int(humidity * 10) % 10;

  if (humidity < 10) { humidity_digits[0] = 10; }

  eink_segments[5] = digit_left[humidity_digits[0]];
  eink_segments[6] = digit_right[humidity_digits[0]];
  eink_segments[7] = digit_left[humidity_digits[1]];
  eink_segments[8] = digit_right[humidity_digits[1]] | B00100000; // Decimal point
  eink_segments[9] = digit_left[humidity_digits[2]];
  eink_segments[10] = digit_right[humidity_digits[2]] | B00100000; // Percentage sign
}