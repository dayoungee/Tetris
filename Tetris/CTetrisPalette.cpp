#include "pch.h"
#include "CTetrisPalette.h"

CTetrisPalette* CTetrisPalette::_instance = nullptr;

void CTetrisPalette::init()
{
	_pens[0].CreatePen(PS_SOLID, 1, PEN_COLOR_BLACK);
	_pens[1].CreatePen(PS_SOLID, 1, PEN_COLOR_WHITE);
	_pens[2].CreatePen(PS_SOLID, 1, PEN_COLOR_BLOCK);

	_brushes[0].CreateSolidBrush(BLOCK_BRUSH_COLOR0);
	_brushes[1].CreateSolidBrush(BLOCK_BRUSH_COLOR1);
	_brushes[2].CreateSolidBrush(BLOCK_BRUSH_COLOR2);
	_brushes[3].CreateSolidBrush(BLOCK_BRUSH_COLOR3);
	_brushes[4].CreateSolidBrush(BLOCK_BRUSH_COLOR4);
	_brushes[5].CreateSolidBrush(BLOCK_BRUSH_COLOR5);
	_brushes[6].CreateSolidBrush(BLOCK_BRUSH_COLOR6);
	_brushes[7].CreateSolidBrush(BACKGROUND_COLOR_BLUE);
	_brushes[8].CreateSolidBrush(BACKGROUND_COLOR_PINK);
	_brushes[9].CreateSolidBrush(BACKGROUND_COLOR_WHITE);
}

CPen* CTetrisPalette::getPen(pen_e pen_index)
{
	return &_pens[pen_index];
}

CBrush* CTetrisPalette::getBrush(brush_e brush_index)
{
	return &_brushes[brush_index];
}
