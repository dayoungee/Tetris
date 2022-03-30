#pragma once
#include "CShape.h"
class CShapeT :
	public CShape
{
public:
	CShapeT(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeT() {}

	virtual void rotate();

protected:
	void init();
};

