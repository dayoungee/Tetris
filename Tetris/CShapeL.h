#pragma once
#include "CShape.h"
class CShapeL :
	public CShape
{
public:
	CShapeL(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeL() {}

	virtual void rotate();

protected:
	void init();
};

