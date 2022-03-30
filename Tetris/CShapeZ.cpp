#include "pch.h"
#include "CShapeZ.h"


int shapeZ_blocks[2][4][2] = {

	//  #
	// ##
	// #
	//
	{ {0, 1}, {1, 0}, {1, 1}, {2, 0} },

	//  ##
	//   ##
	//  
	//
	{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }
};


CShapeZ::CShapeZ(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeZ::init()
{
	set_maps(shapeZ_blocks[0], shapeZ_blocks[1]);
	_rot_state = 0;
	_size_row = 3;
}

void CShapeZ::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeZ_blocks[1], shapeZ_blocks[0]);
		_rot_state = 1;
		_size_row = 2;
	}
	else // if (1 == _rot_state)
	{
		set_maps(shapeZ_blocks[0], shapeZ_blocks[1]);
		_rot_state = 0;
		_size_row = 3;
	}
}
