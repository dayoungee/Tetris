#include "pch.h"
#include "CShapeI.h"


int shapeI_blocks[2][4][2] = {

	//  #
	//  #
	//  #
	//  #
	{ {0, 1}, {1, 1}, {2, 1}, {3, 1} },

	// ####
	//
	//
	//
	{ {0, 0}, {0, 1}, {0, 2}, {0, 3} }
};


CShapeI::CShapeI(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeI::init()
{
	set_maps(shapeI_blocks[0], shapeI_blocks[1]);
	_rot_state = 0;
	_size_row = 4;
}

void CShapeI::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeI_blocks[1], shapeI_blocks[0]);
		_rot_state = 1;
		_size_row = 1;
	}
	else // if (1 == _rot_state)
	{
		set_maps(shapeI_blocks[0], shapeI_blocks[1]);
		_rot_state = 0;
		_size_row = 4;
	}
}
