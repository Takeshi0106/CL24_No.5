#pragma once
#include "Character.h"

class Goll: public Character
{
private:
	int Cnt = 0;

public:
	Goll();
	
	void Update();
	void Draw();
	void Overlap();

	void Animation();

	bool Arrival();
};

