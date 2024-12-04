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

void dll::BASE_ASSETS_CLASS::Release()
{
	delete this;
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

// CREATURE_BASE_CLASS *****************

dll::BASE_CREATURE_CLASS::BASE_CREATURE_CLASS(unsigned char my_type, float first_x, float first_y) :PROTON(first_x, first_y)
{
	type_flag = my_type;

	switch (my_type)
	{
	case hero_flag:
		NewDims(45.0f, 50.0f);
		dir = dirs::right;
		speed = 0.8f;
		lifes = 200;
		attack_delay = 200;
		max_frames = 3;
		frame_delay = 10;
		strenght = 10;
		break;

	case evil1_flag:
		NewDims(40.0f, 40.0f);
		dir = dirs::left;
		speed = 0.8f;
		lifes = 100;
		attack_delay = 300;
		max_frames = 15;
		frame_delay = 4;
		strenght = 10;
		break;

	case evil2_flag:
		NewDims(40.0f, 40.0f);
		dir = dirs::left;
		speed = 0.5f;
		lifes = 110;
		attack_delay = 350;
		max_frames = 36;
		frame_delay = 2;
		strenght = 12;
		break;

	case evil3_flag:
		NewDims(45.0f, 45.0f);
		dir = dirs::left;
		speed = 0.5f;
		lifes = 140;
		attack_delay = 320;
		max_frames = 31;
		frame_delay = 2;
		strenght = 14;
		break;

	case evil4_flag:
		NewDims(40.0f, 29.0f);
		dir = dirs::left;
		speed = 0.9f;
		lifes = 90;
		attack_delay = 200;
		max_frames = 28;
		frame_delay = 2;
		strenght = 6;
		break;

	case evil5_flag:
		NewDims(40.0f, 50.0f);
		dir = dirs::left;
		speed = 0.4f;
		lifes = 150;
		attack_delay = 400;
		max_frames = 35;
		frame_delay = 2;
		strenght = 15;
		break;
	}
}

int dll::BASE_CREATURE_CLASS::GetFrame()
{
	frame_delay--;
	if (frame_delay <= 0)
	{
		switch (type_flag)
		{
		case hero_flag:
			frame_delay = 10;
			break;

		case evil1_flag:
			frame_delay = 4;
			break;

		case evil2_flag:
			frame_delay = 2;
			break;

		case evil3_flag:
			frame_delay = 2;
			break;

		case evil4_flag:
			frame_delay = 2;
			break;

		case evil5_flag:
			frame_delay = 2;
			break;
		}
		++current_frame;
		if (current_frame > max_frames)current_frame = 0;
	}
	return current_frame;
}
int dll::BASE_CREATURE_CLASS::Attack()
{
	--attack_delay;
	if (attack_delay <= 0)
	{
		switch (type_flag)
		{
		case hero_flag:
			attack_delay = 200;
			break;

		case evil1_flag:
			attack_delay = 300;
			break;

		case evil2_flag:
			attack_delay = 350;
			break;

		case evil3_flag:
			attack_delay = 320;
			break;

		case evil4_flag:
			attack_delay = 200;
			break;

		case evil5_flag:
			attack_delay = 400;
			break;
		}
		return strenght;
	}
	return 0;
}
float dll::BASE_CREATURE_CLASS::Distance(POINT reference_point, POINT my_point)
{
	float a = static_cast<float>(pow((my_point.x - reference_point.x),2));
	float b = static_cast<float>(pow((my_point.y - reference_point.y), 2));
	return static_cast<float>(sqrt(a + b));
}

void dll::BASE_CREATURE_CLASS::SetLineInfo(float _end_x, float _end_y)
{
	hor_line = false;
	vert_line = false;
	
	start_x = x;
	start_y = y;
	end_x = _end_x;
	end_y = _end_y;
	
	if (end_x - start_x == 0)
	{
		vert_line = true;
		return;
	}
	if (end_y - start_y == 0)
	{
		hor_line = true;
		return;
	}

	slope = (end_y - start_y) / (end_x - start_x);

	intercept = start_y - slope * start_x;
}

bool dll::BASE_CREATURE_CLASS::CheckType(unsigned char which_type)
{
	return type_flag & which_type;
}
void dll::BASE_CREATURE_CLASS::SetObstacleFlag(unsigned char which_flag)
{
	obstacle_flag |= which_flag;
}
unsigned char dll::BASE_CREATURE_CLASS::GetObstacleFlag() const
{
	return obstacle_flag;
}

unsigned char dll::BASE_CREATURE_CLASS::Move(float gear, PROT_CONTAINER& Obstacles, bool need_new_path,
	float target_x, float target_y)
{
	float current_speed = speed + gear / 10;

	obstacle_flag = 0;

	if (need_new_path)SetLineInfo(target_x, target_y);

	if (Obstacles.is_valid())
	{
		if (start_x > end_x)  //CHECK LEFT COLLISION 
		{
			for (int i = 0; i < Obstacles.size(); ++i)
			{
				float temp_x = x - current_speed;
				float temp_ex = ex - current_speed;

				if (!(temp_x > Obstacles[i].ex || temp_ex < Obstacles[i].x
					|| y > Obstacles[i].ey || ey < Obstacles[i].y))
				{
					SetObstacleFlag(left_obst_flag);
					break;
				}
			}
			if (x - current_speed <= 0) SetObstacleFlag(left_obst_flag);
		}
		else if (start_x < end_x)  //CHECK RIGHT COLLISION 
		{
			for (int i = 0; i < Obstacles.size(); ++i)
			{
				float temp_x = x + current_speed;
				float temp_ex = ex + current_speed;

				if (!(temp_x > Obstacles[i].ex || temp_ex < Obstacles[i].x
					|| y > Obstacles[i].ey || ey < Obstacles[i].y))
				{
					SetObstacleFlag(right_obst_flag);
					break;
				}
			}
			if (ex + current_speed >= scr_width) SetObstacleFlag(right_obst_flag);
		}
		if (start_y > end_y)  //CHECK TOP COLLISION 
		{
			for (int i = 0; i < Obstacles.size(); ++i)
			{
				float temp_y = y - current_speed;
				float temp_ey = ey - current_speed;

				if (!(x > Obstacles[i].ex || ex < Obstacles[i].x
					|| temp_y > Obstacles[i].ey || temp_ey < Obstacles[i].y))
				{
					SetObstacleFlag(up_obst_flag);
					break;
				}
			}
			if (y - current_speed <= sky) SetObstacleFlag(up_obst_flag);
		}
		else if (start_y < end_y)  //CHECK BOTTOM COLLISION 
		{
			for (int i = 0; i < Obstacles.size(); ++i)
			{
				float temp_y = y + current_speed;
				float temp_ey = ey + current_speed;

				if (!(x > Obstacles[i].ex || ex < Obstacles[i].x
					|| temp_y > Obstacles[i].ey || temp_ey < Obstacles[i].y))
				{
					SetObstacleFlag(down_obst_flag);
					break;
				}
			}
			if (ey + current_speed >= ground) SetObstacleFlag(down_obst_flag);
		}
	}

	if (obstacle_flag)
	{
		switch (obstacle_flag)
		{
		case left_obst_flag:
			SetLineInfo(scr_width, y);
			break;

		case right_obst_flag:
			SetLineInfo(0, y);
			break;

		case up_obst_flag:
			SetLineInfo(x, ground);
			break;

		case down_obst_flag:
			SetLineInfo(x, sky);
			break;

		case up_left_obst_flag:
			SetLineInfo(scr_width, ground);
			break;

		case up_right_obst_flag:
			SetLineInfo(0, ground);
			break;

		case down_left_obst_flag:
			SetLineInfo(scr_width, sky);
			break;

		case down_right_obst_flag:
			SetLineInfo(0, sky);
			break;
		}
	}
	
	if(!hor_line && !vert_line)
	{
		if (start_x < end_x)
		{
			if (ex + current_speed <= scr_width - 50.0f)
			{
				x += current_speed;
				y = x * slope + intercept;
				SetEdges();
			}
		}
		else if (start_x > end_x)
		{
			if (x - current_speed >= 50.0f)
			{
				x -= current_speed;
				y = x * slope + intercept;
				SetEdges();
			}
		}
	}
	else
	{
		if (hor_line)
		{
			if (start_x > end_x)
			{
				dir = dirs::left;
				if (x - current_speed >= 50.0f)
				{
					x -= current_speed;
					SetEdges();
				}
			}
			else if (start_x < end_x)
			{
				dir = dirs::right;
				if (ex + current_speed <= scr_width - 50.0f)
				{
					x += current_speed;
					SetEdges();
				}
			}
		}
		if (vert_line)
		{
			if (start_y > end_y)
			{
				if (y - current_speed >= sky)
				{
					y -= current_speed;
					SetEdges();
				}
			}
			else if (start_y < end_y)
			{
				if (ey + current_speed <= ground - 50.0f)
				{
					y += current_speed;
					SetEdges();
				}
			}
		}
	}

	if (x < 50.0f)
	{
		x = 50.0f;
		SetEdges();
	}
	if (ex > scr_width)
	{
		x = scr_width - 50.0f;
		SetEdges();
	}
	if (y < sky)
	{
		y = sky;
		SetEdges();
	}
	if (ey > ground)
	{
		y = ground - 50.0f;
		SetEdges();
	}

	return obstacle_flag;
}

void dll::BASE_CREATURE_CLASS::Release()
{
	delete this;
}

void dll::BASE_CREATURE_CLASS::Transform(unsigned char to_what)
{
	if (type_flag != hero_flag && type_flag != hero_axe_flag && type_flag != hero_club_flag && type_flag != hero_sword_flag)
		return;

	type_flag = to_what;

	switch (type_flag)
	{
	case hero_flag:
		attack_delay = 200;
		strenght = 10;
		break;

	case hero_club_flag:
		attack_delay = 220;
		strenght = 15;
		break;

	case hero_axe_flag:
		attack_delay = 250;
		strenght = 20;
		break;

	case hero_sword_flag:
		attack_delay = 300;
		strenght = 30;
		break;
	}
}

////////////////////////////////////////

//FACTORIES ***************************

dll::creature_ptr dll::CreatureFactory(unsigned char what, float _start_x, float _start_y)
{
	creature_ptr ret = nullptr;

	ret = new BASE_CREATURE_CLASS(what, _start_x, _start_y);
	return ret;
}

dll::asset_ptr dll::AssetFactory(int16_t what, float _start_x, float _start_y)
{
	asset_ptr ret = nullptr;
	ret = new BASE_ASSETS_CLASS(what, _start_x, _start_y);
	return ret;
}