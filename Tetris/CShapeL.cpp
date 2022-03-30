#include "pch.h"
#include "CShapeL.h"


int shapeL_blocks[4][4][2] = {

	//   #
	// ###
	//
	//
	{ {0, 2}, {1, 0}, {1, 1}, {1, 2} },

	// ##
	//  #
	//  #
	//
	{ {0, 0}, {0, 1}, {1, 1}, {2, 1} },

	// ###
	// #
	// 
	// 
	{ {0, 0}, {0, 1}, {0, 2}, {1, 0} },

	// #
	// #
	// ##
	// 
	{ {0, 0}, {1, 0}, {2, 0}, {2, 1} }
};


CShapeL::CShapeL(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeL::init()
{
	set_maps(shapeL_blocks[0], shapeL_blocks[1]);
	_rot_state = 0;
	_size_row = 2;
}

void CShapeL::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeL_blocks[1], shapeL_blocks[2]);
		_rot_state = 1;
		_size_row = 3;
	}
	else if (1 == _rot_state)
	{
		set_maps(shapeL_blocks[2], shapeL_blocks[3]);
		_rot_state = 2;
		_size_row = 2;
	}
	else if (2 == _rot_state)
	{
		set_maps(shapeL_blocks[3], shapeL_blocks[0]);
		_rot_state = 3;
		_size_row = 3;
	}
	else // if (3 == _rot_state)
	{
		set_maps(shapeL_blocks[0], shapeL_blocks[1]);
		_rot_state = 0;
		_size_row = 2;
	}
}
