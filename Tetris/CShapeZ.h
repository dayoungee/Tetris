#pragma once

#include "CShape.h"

class CShapeZ : public CShape
{
public:
	CShapeZ(CTetrisPalette::brush_e brush_index);
	virtual ~CShapeZ() {}

	virtual void rotate();

protected:
	void init();
};

