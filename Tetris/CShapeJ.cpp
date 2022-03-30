#include "pch.h"
#include "CShapeJ.h"


int shapeJ_blocks[4][4][2] = {

	// #
	// ###
	//
	//
	{ {0, 0}, {1, 0}, {1, 1}, {1, 2} },

	//  #
	//  #
	// ##
	//
	{ {0, 1}, {1, 1}, {2, 0}, {2, 1} },

	// ###
	//   #
	// 
	// 
	{ {0, 0}, {0, 1}, {0, 2}, {1, 2} },

	// ##
	// #
	// #
	// 
	{ {0, 0}, {0, 1}, {1, 0}, {2, 0} }
};

CShapeJ::CShapeJ(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeJ::init()
{
	set_maps(shapeJ_blocks[0], shapeJ_blocks[1]);
	_rot_state = 0;
	_size_row = 2;
}

void CShapeJ::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeJ_blocks[1], shapeJ_blocks[2]);
		_rot_state = 1;
		_size_row = 3;
	}
	else if (1 == _rot_state)
	{
		set_maps(shapeJ_blocks[2], shapeJ_blocks[3]);
		_rot_state = 2;
		_size_row = 2;
	}
	else if (2 == _rot_state)
	{
		set_maps(shapeJ_blocks[3], shapeJ_blocks[0]);
		_rot_state = 3;
		_size_row = 3;
	}
	else // if (3 == _rot_state)
	{
		set_maps(shapeJ_blocks[0], shapeJ_blocks[1]);
		_rot_state = 0;
		_size_row = 2;
	}
}
