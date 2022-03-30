#pragma once

#include "pch.h"
#include "CTetrisPalette.h"

#define BLOCK_MAP_SIZE_X	4
#define BLOCK_MAP_SIZE_Y	4
#define BLOCK_PIXEL_SIZE	15


typedef struct BLOCKCELL
{
	bool _is_block;
	CTetrisPalette::brush_e _color;

	BLOCKCELL() : _is_block(false), _color((CTetrisPalette::brush_e)-1) {}

	void init() { _is_block = false; _color = (CTetrisPalette::brush_e) - 1; }

} block_cell_t;


class CShape
{
public:
	CShape(CTetrisPalette::brush_e brush_index = CTetrisPalette::BLOCK_0);
	virtual ~CShape();

	bool check_left(block_cell_t** bgmap, int width, int height, CPoint pt);
	bool check_right(block_cell_t** bgmap, int width, int height, CPoint pt);
	bool check_drop(block_cell_t** bgmap, int width, int height, CPoint pt);
	bool check_rotate(block_cell_t** bgmap, int width, int height, CPoint pt);

	virtual void rotate() {}

	void draw(CDC& dc, int x, int y);

	CTetrisPalette::brush_e getColorIndex() { return _brush; }

	void print_to(block_cell_t** bgmap, CPoint pt);

	int getSizeRow() { return _size_row; }

protected:
	void clear_maps();

	inline void set_map(block_cell_t** map, int block_map[4][2])
	{
		for (int i = 0; i < 4; ++i)
		{
			int row = block_map[i][0];
			int col = block_map[i][1];
			map[row][col]._is_block = true;
			map[row][col]._color = _brush;
		}
	}

	inline void set_maps(int current[4][2], int next[4][2])
	{
		set_map(_current_map, current);
		set_map(_next_map, next);
	}

	inline void set_map(block_cell_t** to, block_cell_t** from)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				to[i][j] = from[i][j];
			}
		}
	}

	//inline void set_map(int block_map[4][2])
	//{
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		int row = block_map[i][0];
	//		int col = block_map[i][1];
	//		_current_map[row][col]._is_block = true;
	//		_current_map[row][col]._color = _brush;
	//	}
	//}

	block_cell_t** _current_map;
	block_cell_t** _next_map;
	int _rot_state;

	CTetrisPalette::brush_e _brush;
	int _size_row;
};

