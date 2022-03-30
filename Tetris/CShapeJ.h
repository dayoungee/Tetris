#pragma once
#include "CShape.h"
class CShapeJ :
	public CShape
{
public:
	CShapeJ(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeJ() {}

	virtual void rotate();

protected:
	void init();
};

