//	########################################################################

//  ChristmasFoos.cpp

//	1/24/14

//	########################################################################

#include "ChristmasFoos.h"

RedGreenMover::RedGreenMover()
{
	for (int n=0;n<8;n++)
	{
		addLEDs(LITColor.red, maxBrightness, 4*n, 4*n);
		addLEDs(LITColor.green, maxBrightness, 4*n+2, 4*n+2);
	}
	
	addStepWithFunction(&MovingFoo::move, 3);
}

RedGreenPulser::RedGreenPulser()
{
	for (int n=0;n<16;n++)
	{
		addLEDs(LITColor.red, 0, 2*n,2*n);
	}
	
	for (int n=0;n<16;n++)
	{
		addLEDs(LITColor.green, maxBrightness, 2*n+1, 2*n+1);
	}
	
	pulseCounter = 0;
	
	addStepWithFunction(&RedGreenPulser::redUpGreenDown, 1, 50);
	addStepWithFunction(&RedGreenPulser::redDownGreenUp, 1, 50);
}

void RedGreenPulser::redUpGreenDown()
{
	for (int r=0;r<16;r++)
	{
		fLEDs.entry(r)->me->brightness += 2;
	}
	
	for (int g=16;g<32;g++)
	{
		fLEDs.entry(g)->me->brightness -= 2;
	}
}

void RedGreenPulser::redDownGreenUp()
{
	for (int r=0;r<16;r++)
	{
		fLEDs.entry(r)->me->brightness -= 2;
	}
	
	for (int g=16;g<32;g++)
	{
		fLEDs.entry(g)->me->brightness += 2;
	}
}



RedGreenAlternater::RedGreenAlternater()
{
	for (int n=0;n<4;n++)
	{
		addLEDs(LITColor.red, maxBrightness, 8*n, 8*n);
	}
	
	for (int n=0;n<4;n++)
	{
		addLEDs(LITColor.green, 0, 8*n+1, 8*n+1);
	}
	
	add1 = 0;
	add2 = 1;
	
	addStepWithFunction(&RedGreenAlternater::aUp, 1, 20);
	addStepWithFunction(&RedGreenAlternater::add1Up, 1, 1);
	addStepWithFunction(&RedGreenAlternater::bUp, 1, 20);
	addStepWithFunction(&RedGreenAlternater::add2Up, 1, 1);
}

void RedGreenAlternater::aUp()
{
	for (int r=0;r<4;r++)
	{
		fLEDs.entry(r)->me->brightness -= 5;
	}
	
	for (int g=4;g<8;g++)
	{
		fLEDs.entry(g)->me->brightness += 5;
	}
	
	Serial.println("aUp");
	Serial.print("r: ");
	Serial.println(fLEDs.entry(0)->me->brightness);
	Serial.print("g: ");
	Serial.println(fLEDs.entry(4)->me->brightness);
}

void RedGreenAlternater::bUp()
{
	for (int r=0;r<4;r++)
	{
		fLEDs.entry(r)->me->brightness += 5;
	}
	
	for (int g=4;g<8;g++)
	{
		fLEDs.entry(g)->me->brightness -= 5;
	}
}

void RedGreenAlternater::add1Up()
{
	add1 = updateValue(add1, up, 0, 7, cycles);
	add1 = updateValue(add1, up, 0, 7, cycles);
	
	for (int n=0;n<4;n++)
	{
		fLEDs.entry(n)->me->address = 8*n + add1;
	}
}

void RedGreenAlternater::add2Up()
{
	add2 = updateValue(add2, up, 0, 7, cycles);
	add2 = updateValue(add2, up, 0, 7, cycles);
	
	for (int n=0;n<4;n++)
	{
		fLEDs.entry(4+n)->me->address = 8*n + add2;
	}
}

ChristmasSnakes::ChristmasSnakes()
{
	addStepWithFunction(&ChristmasSnakes::checkForNoSnakes, 1);
	
	baseCycler = 0;
}

void ChristmasSnakes::checkForNoSnakes()
{
	if (!hasFoos())
	{
		EphemeralSnake* aSnake = new EphemeralSnake(0,16,1,&LITColor.red);
		addFoo(aSnake);
		
		EphemeralSnake* bSnake = new EphemeralSnake(16,16,1,&LITColor.green);
		addFoo(bSnake);
	}
}

ChristmasSparkler::ChristmasSparkler()
{
	rgw[0].setColor(LITColor.red);
	rgw[1].setColor(LITColor.green);
	rgw[2].setColor(LITColor.white);
	
	totalSparkles = 12;
	colorCount = 0;
	
	addStepWithFunction(&ChristmasSparkler::newSparkle, 1, 1);
	addStepWithFunction(&ChristmasSparkler::stall, 1, 10);
}

void ChristmasSparkler::newSparkle()
{
	int addr = rand()%32;
	
	while (!checkAddresses(addr))
	{
		addr = rand()%32;
	}
	
	InAndOutFader* x = new InAndOutFader(rgw[colorCount],addr);
	addFoo(x);
	
	colorCount = updateValue(colorCount, up, 0, 2, cycles);
}

void ChristmasSparkler::stall()
{
	// wait to create a new one
}

bool ChristmasSparkler::checkAddresses(int x)
{
	bool check = true;
	
	for (int n=0;n<countFoos();n++)
	{
		int z = foos.entry(n)->me->fLEDs.entry(0)->me->address;
		
		if (z == x)
		{
			check = false;
		}
	}
	
	return check;
}







