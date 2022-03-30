#include "pch.h"
#include "CShapeS.h"


int shapeS_blocks[2][4][2] = {

	//  #
	//  ##
	//   #
	//
	{ {0, 0}, {1, 0}, {1, 1}, {2, 1} },

	//   ##
	//  ##
	//  
	//
	{ {0, 1}, {0, 2}, {1, 0}, {1, 1} }
};


CShapeS::CShapeS(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeS::init()
{
	set_maps(shapeS_blocks[0], shapeS_blocks[1]);
	_rot_state = 0;
	_size_row = 3;
}

void CShapeS::rotate()
{
	clear_maps();

	if (0 == _rot_state)
	{
		set_maps(shapeS_blocks[1], shapeS_blocks[0]);
		_rot_state = 1;
		_size_row = 2;
	}
	else // if (1 == _rot_state)
	{
		set_maps(shapeS_blocks[0], shapeS_blocks[1]);
		_rot_state = 0;
		_size_row = 3;
	}
}
