//	########################################################################

//  PatternB.cpp

//	5/3/13

//	########################################################################

#include "PatternB.h"


PatternB::PatternB()
{
	createThingsArray();
	things[0] = new RainbowThing();
}

void PatternB::update()
{
	genericUpdate();
}