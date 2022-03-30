#include "pch.h"
#include "CShapeRect.h"


// ##
// ##
//
//
int shapeRect[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};


CShapeRect::CShapeRect(CTetrisPalette::brush_e brush_index)
	: CShape(brush_index)
{
	init();
}

void CShapeRect::init()
{
	set_maps(shapeRect, shapeRect);
}
