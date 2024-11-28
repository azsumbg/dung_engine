#include "pch.h"
#include "dung_engine.h"

// RANDiT Class ********************

dll::RANDiT::RANDiT()
{
	vSeeds.clear();
	for (int i = 0; i < 650; ++i)vSeeds.push_back(rd());
	sq = new std::seed_seq(vSeeds.begin(), vSeeds.end());
	twister = new std::mt19937(*sq);
}
dll::RANDiT::~RANDiT()
{
	delete sq;
	delete twister;
}
int dll::RANDiT::operator ()(int min, int max)
{
	std::uniform_int_distribution random_eng(min, max);
	return random_eng(*twister);
}

///////////////////////////////////

// PROTON CLASS *******************

dll::PROTON::PROTON(float _x, float _y, float _width, float _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	ex = x + width;
	ey = y + height;
}

float dll::PROTON::GetWidth() const
{
	return width;
}
float dll::PROTON::GetHeight() const
{
	return height;
}

void dll::PROTON::SetWidth(float new_width)
{
	width = new_width;
	ex = x + width;
}
void dll::PROTON::SetHeight(float new_height)
{
	height = new_height;
	ey = y + height;
}

void dll::PROTON::SetEdges()
{
	ex = x + width;
	ey = y + height;
}
void dll::PROTON::NewDims(float new_width, float new_height)
{
	width = new_width;
	height = new_height;
	ex = x + width;
	ey = y + height;
}

///////////////////////////////////

// BASE_ASSETS_CLASS **************

dll::BASE_ASSETS_CLASS::BASE_ASSETS_CLASS(int16_t _type, float where_x, float _where_y) :PROTON(where_x, _where_y)
{
	type_flag = _type;

	switch (type_flag)
	{
	case axe_flag:
		NewDims(32.0f, 32.0f);
		break;

	case club_flag:
		NewDims(32.0f, 32.0f);
		break;

	case sword_flag:
		NewDims(32.0f, 32.0f);
		break;

	case potion_flag:
		NewDims(32.0f, 32.0f);
		break;

	case gold_flag:
		NewDims(32.0f, 32.0f);
		break;

	case mail_flag:
		NewDims(32.0f, 32.0f);
		break;

	case cloak_flag:
		NewDims(32.0f, 32.0f);
		break;

	case crystal_flag:
		NewDims(32.0f, 32.0f);
		break;

	case stone_brick_flag:
		NewDims(50.0f, 50.0f);
		break;

	case red_brick_flag:
		NewDims(50.0f, 50.0f);
		break;
	}
}

bool dll::BASE_ASSETS_CLASS::CheckFlag(int16_t which_flag) const
{
	return (type_flag & which_flag);
}
void dll::BASE_ASSETS_CLASS::SetFlag(int16_t which_flag)
{
	type_flag |= which_flag;
}
void dll::BASE_ASSETS_CLASS::NullFlag(int16_t which_flag)
{
	type_flag &= ~which_flag;
}

/////////////////////////////////////
