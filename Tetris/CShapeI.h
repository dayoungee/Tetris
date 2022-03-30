#pragma once
#include "CShape.h"
class CShapeI :
	public CShape
{
public:
	CShapeI(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeI() {}

	virtual void rotate();

protected:
	void init();
};

