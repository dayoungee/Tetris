#include "pch.h"
#include "CShapeT.h"



int shapeT_blocks[4][4][2] = {

	//  #
	// ###
	//
	//
		{ {0, 1}, {1, 0}, {1, 1}, {1, 2} },

	//  #
	// ##
	//  #
	//
	{ {0, 1}, {1, 0}, {1, 1}, {2, 1} },

	//  
	// ###
	//  #
	//
	{ {1, 0}, {1, 1}, {1, 2}, {2, 1} },

	//  #
	//  ##
	//  #
	//
	{ {0, 1}, {1, 1}, {1, 2}, {2, 1} }
};


CShapeT::CShapeT(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeT::init()
{
	set_maps(shapeT_blocks[0], shapeT_blocks[1]);
	_rot_state = 0;
	_size_row = 2;
}

void CShapeT::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeT_blocks[1], shapeT_blocks[2]);
		_rot_state = 1;
		_size_row = 3;
	}
	else if (1 == _rot_state)
	{
		set_maps(shapeT_blocks[2], shapeT_blocks[3]);
		_rot_state = 2;
		_size_row = 2;
	}
	else if (2 == _rot_state)
	{
		set_maps(shapeT_blocks[3], shapeT_blocks[0]);
		_rot_state = 3;
		_size_row = 3;
	}
	else // if (3 == _rot_state)
	{
		set_maps(shapeT_blocks[0], shapeT_blocks[1]);
		_rot_state = 0;
		_size_row = 2;
	}
}
