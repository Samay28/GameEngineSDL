#include "Glob.h"



Glob::Glob()
{
	hp = 10;
	hpMax = 10;
	str = 4;
	def = 2;
	agi = 5;
}


Glob::~Glob()
{
}

string Glob::getName() {
	return "Glob";
}

void Glob::makeDumbNoise()
{
	cout << getName() << " makes a shrieking sound at you!" << endl;
}
