#pragma once
#include "CShape.h"
class CShapeS :
	public CShape
{
public:
	CShapeS(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeS() {}

	virtual void rotate();

protected:
	void init();
};

