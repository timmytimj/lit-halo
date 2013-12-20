//	####################################################################
//
//	LED.cpp
//
//	####################################################################

#include "LED.h"

LED::LED()
{
	brightness		= 100;
	currentLayer	=   1;
	color.setColor(1,69,100);
}

LED::LED(Color newColor, byte newBrightness, byte newLayer)
{
	if (newLayer <  1)			newLayer =  1;
	if (newLayer > 10)			newLayer = 10;
	
	if (newBrightness <   0)	newBrightness =   0;
	if (newBrightness > 100)	newBrightness = 100;
	
	color			= newColor;
	brightness		= newBrightness;
	currentLayer	= newLayer;
}

void LED::adjustColor()
{
	// adjusts r,g,b values based on brightness
	
	float ratio = (float) brightness / maxBrightness;
		
	color.r *= ratio;
	color.g *= ratio;
	color.b *= ratio;
}

void LED::mixWith(LED aLED)
{
	adjustColor();
	aLED.adjustColor();
	
	if (aLED.brightness > brightness)
		brightness = aLED.brightness;

	
	color.mixWith(aLED.color);
}

void LED::setAttributes(LED aLED)
{
	color.setColor(aLED.color);
	brightness = aLED.brightness;
}

void LED::setAttributes(Color aColor,byte aBrightness)
{
	color.setColor(aColor);
	brightness = aBrightness;
}


void LED::printVitals()
{
	color.printVitals();
	Serial.print("Brightness:   ");
	if (brightness < 10) Serial.print("  ");
	else if (brightness < 100) Serial.print(" ");
	Serial.println(brightness);
	Serial.print("Current Layer:  ");
	Serial.println(currentLayer);
	Serial.println();	
}
