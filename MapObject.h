#pragma once
class MapObject
{
public:
	int type; //1= hero, 2 = door, 3 = glob = 4 = mimic, 5 = chest

	int x, y;//pos

	bool active = true; //when not active destroy

};

