#include "pch.h"
#include "CShape.h"

CShape::CShape(CTetrisPalette::brush_e brush_index)
	: _rot_state(0), _current_map(nullptr), _next_map(nullptr), _size_row(0)
{
	_brush = brush_index;

	_current_map = new block_cell_t * [4];
	for (int i = 0; i < 4; ++i)
	{
		_current_map[i] = new block_cell_t[4];;
	}

	_next_map = new block_cell_t * [4];
	for (int i = 0; i < 4; ++i)
	{
		_next_map[i] = new block_cell_t[4];;
	}
}

CShape::~CShape()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _current_map[i];
	}
	delete _current_map;
	_current_map = nullptr;

	for (int i = 0; i < 4; ++i)
	{
		delete _next_map[i];
	}
	delete _next_map;
	_next_map = nullptr;
}

void CShape::clear_maps()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			_current_map[i][j].init();
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			_next_map[i][j].init();
		}
	}
}

//void CShape::set_map(int* block_map[2])
//{
//	for (int i = 0; i < 4; ++i)
//	{
//		int row = block_map[i][0];
//		int col = block_map[i][1];
//		_map[row][col]._is_block = true;
//		_map[row][col]._color = _brush;
//	}
//}
//
//void CShape::set_map(block_cell_t** map)
//{
//	for (int i = 0; i < 4; ++i)
//	{
//		for (int j = 0; j < 4; ++j)
//		{
//			_map[i][j] = map[i][j];
//		}
//	}
//}

bool CShape::check_left(block_cell_t** bgmap, int width, int height, CPoint pt)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (_current_map[i][j]._is_block)
			{
				if (pt.x + j - 1 < 0) return false;

				if (0 > pt.y + i) continue;

				// 현재 보다 왼쪽에 이미 블록이 있다면
				if (bgmap[pt.y + i][pt.x + j - 1]._is_block) return false;
			}
		}
	}

	return true;
}

bool CShape::check_right(block_cell_t** bgmap, int width, int height, CPoint pt)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 3; j >= 0; --j)
		{
			if (_current_map[i][j]._is_block)
			{
				if (width <= pt.x + j + 1) return false;

				if (0 > pt.y + i) continue;

				// 현재보다 오른쪽에 이미 블록이 있다면
				if (bgmap[pt.y + i][pt.x + j + 1]._is_block) return false;
			}
		}
	}

	return true;
}

bool CShape::check_drop(block_cell_t** bgmap, int width, int height, CPoint pt)
{
	for (int i = 3; i >= 0; --i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (_current_map[i][j]._is_block)
			{
				if (0 > pt.y + i + 1) return true;

				if (height <= pt.y + i + 1) return false;

				// 현재보다 아랫줄에 이미 블록이 있다면
				if (bgmap[pt.y + i + 1][pt.x + j]._is_block) return false;
			}
		}
	}

	return true;
}

bool CShape::check_rotate(block_cell_t** bgmap, int width, int height, CPoint pt)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (0 > pt.y + i) continue;

			if (bgmap[pt.y + i][pt.x + j]._is_block && _next_map[i][j]._is_block) return false;
		}
	}

	return true;
}

void CShape::draw(CDC& dc, int start_x, int start_y)
{
	dc.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLOCK_LINE));
	dc.SelectObject(CTetrisPalette::getInstance()->getBrush(_brush));
	for (int i = 0; i < BLOCK_MAP_SIZE_Y; ++i)
	{
		for (int j = 0; j < BLOCK_MAP_SIZE_X; ++j)
		{
			if (_current_map[i][j]._is_block)
			{
				dc.Rectangle(start_x + j * BLOCK_PIXEL_SIZE, start_y + i * BLOCK_PIXEL_SIZE,
					start_x + (j + 1) * BLOCK_PIXEL_SIZE, start_y + (i + 1) * BLOCK_PIXEL_SIZE);
			}
		}
	}
}

void CShape::print_to(block_cell_t** bgmap, CPoint pt)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (_current_map[i][j]._is_block)
			{
				if(0 <= pt.y + i)
					bgmap[pt.y + i][pt.x + j] = _current_map[i][j];
			}
		}
	}
}
