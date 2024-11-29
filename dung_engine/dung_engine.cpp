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

// PROT_CONTAINER_CLASS **************

dll::PROT_CONTAINER::PROT_CONTAINER(size_t lenght) :max_size{ lenght }, m_ptr{ new PROTON[lenght] }
{
	next_element = 0;
}
dll::PROT_CONTAINER::~PROT_CONTAINER()
{
	if (m_ptr)delete[] m_ptr;
}
void dll::PROT_CONTAINER::push_back(PROTON& element)
{
	if (next_element < max_size)
	{
		*(m_ptr + next_element) = element;
		++next_element;
	}
}
void dll::PROT_CONTAINER::push_front(PROTON& element)
{
	*m_ptr = element;
}
bool dll::PROT_CONTAINER::is_valid() const
{
	return(max_size > 0);
}
size_t dll::PROT_CONTAINER::size() const
{
	return max_size;
}
dll::PROTON dll::PROT_CONTAINER::operator[](size_t index) const
{
	if (index < max_size)return *(m_ptr + index);
	return PROTON{};
}
void dll::PROT_CONTAINER::operator()(size_t index, PROTON& element)
{
	if (index < max_size) *(m_ptr + index) = element;
}

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
