#pragma once
#include "CShape.h"
class CShapeRect :
	public CShape
{
public:
	CShapeRect(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeRect() {}

protected:
	void init();
};

