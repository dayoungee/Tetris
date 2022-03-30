#include "pch.h"
#include "TetrisFrame.h"

CTetrisFrame::CTetrisFrame(CTetrisPalette::brush_e bgColor)
	: mapSizeRow(FRAME_BASIC_SIZE_ROW), mapSizeColumn(FRAME_BASIC_SIZE_COL), _current_block(nullptr), _block_map(nullptr), _background(bgColor)
{
	initMap();
}

CTetrisFrame::CTetrisFrame(int row, int column, CTetrisPalette::brush_e bgColor)
	: mapSizeRow(row), mapSizeColumn(column), _current_block(nullptr), _block_map(nullptr), _background(bgColor)
{
	initMap();
}

CTetrisFrame::~CTetrisFrame()//소멸자
{
	if (_block_map)
	{
		for (int i = 0; i < mapSizeRow; i++)
		{
			delete _block_map[i];
		}
		delete _block_map;
	}

	if (_current_block) delete _current_block;
}

bool CTetrisFrame::dropBlock()
{
	if (nullptr == _current_block) return false;

	if (_current_block->check_drop(_block_map, mapSizeColumn, mapSizeRow, _current_block_pos))
	{
		++_current_block_pos.y;
		return true;
	}
	return false;
}

int CTetrisFrame::deleteLines()
{
	int countLine = 0;

	for (int i = 0; i < mapSizeRow; ++i)
	{
		bool delOk = true;
		for (int j = 0; j < mapSizeColumn; ++j)
		{
			if (!_block_map[i][j]._is_block)
			{
				delOk = false;
				break;
			}
		}

		if (delOk)
		{
			delete _block_map[i];
			_block_map[i] = nullptr;

			++countLine;
		}
	}

	if (countLine)
	{
		for (int i = (mapSizeRow - 1); i >= countLine; --i)
		{
			if (nullptr == _block_map[i])
			{
				// 상위에 비어 있지 않은 라인을 찾는다.
				int idx = i - 1;
				while (nullptr == _block_map[idx] && 0 < idx) --idx;

				_block_map[i] = _block_map[idx];
				_block_map[idx] = nullptr;

				if (0 == idx) break;
			}
		}

		for (int i = 0; i < countLine; ++i)
		{
			_block_map[i] = new block_cell_t[mapSizeColumn];

			for (int j = 0; j < countLine; ++j)
			{
				_block_map[i][j]._is_block = false;
				_block_map[i][j]._color = _background;
			}
		}
	}

	return countLine;
}

void CTetrisFrame::turnBlock()
{
	if (nullptr == _current_block) return;

	if (_current_block->check_rotate(_block_map, mapSizeColumn, mapSizeRow, _current_block_pos))
	{
		_current_block->rotate();
	}
}

void CTetrisFrame::moveBlockLeft(void)
{
	if (nullptr == _current_block) return;

	// 프레임을 벗어나는가 또는 왼쪽에 다른 오브젝트가 있는가
	if (_current_block->check_left(_block_map, mapSizeColumn, mapSizeRow, _current_block_pos))
	{
		--_current_block_pos.x;
	}
}

void CTetrisFrame::moveBlockRight(void)
{
	if (nullptr == _current_block) return;

	if (_current_block->check_right(_block_map, mapSizeColumn, mapSizeRow, _current_block_pos))
		++_current_block_pos.x;
}

bool CTetrisFrame::insertBlock(CShape* block)
{
	CPoint pt(5, block->getSizeRow() * -1);

	if (!block->check_drop(_block_map, mapSizeColumn, mapSizeRow, pt)) return false;

	_current_block_pos.x = 5;
	_current_block_pos.y = block->getSizeRow() * -1;

	if (_current_block) delete _current_block;
	_current_block = block;

	return true;
}

void CTetrisFrame::directDropBlock()
{
	if (nullptr == _current_block) return;

	while (_current_block->check_drop(_block_map, mapSizeColumn, mapSizeRow, _current_block_pos))
	{
		++_current_block_pos.y;
	}
}

void CTetrisFrame::initMap()
{
	if (nullptr == _block_map)
	{
		_block_map = new block_cell_t*[mapSizeRow];
		for (int i = 0; i < mapSizeRow; ++i)
		{
			_block_map[i] = new block_cell_t[mapSizeColumn];

			for (int j = 0; j < mapSizeColumn; ++j)
			{
				_block_map[i][j]._is_block = false;
				_block_map[i][j]._color = _background;
			}
		}
	}
	else
	{
		for (int i = 0; i < mapSizeRow; i++)
		{
			for (int j = 0; j < mapSizeColumn; j++)
			{
				_block_map[i][j]._is_block = false;
				_block_map[i][j]._color = _background;
			}
		}
	}
}

void CTetrisFrame::set_bgcolor(CTetrisPalette::brush_e color)
{
	_background = color;

	for (int i = 0; i < mapSizeRow; ++i)
	{
		for (int j = 0; j < mapSizeColumn; ++j)
		{
			if(!_block_map[i][j]._is_block) _block_map[i][j]._color = color; //블럭이 없는 곳 색 변경
		}
	}
}

void CTetrisFrame::draw(CDC& dc, int start_x, int start_y)
{
	// 맵을 그린다.
	dc.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLACK));
	dc.SelectObject(CTetrisPalette::getInstance()->getBrush(_background));

	int end_x = start_x + BLOCK_PIXEL_SIZE * mapSizeColumn + 1;
	int end_y = start_y + BLOCK_PIXEL_SIZE * mapSizeRow + 1;

	dc.Rectangle(start_x, start_y, end_x, end_y);
	dc.Rectangle(start_x + 236, start_y, end_x + 236, end_y);

	int map_start_x = start_x + 1;
	int map_start_y = start_y + 1;

	dc.SelectObject(CTetrisPalette::getInstance()->getPen(CTetrisPalette::BLOCK_LINE));
	for (int i = 0; i < mapSizeRow; ++i)
	{
		for (int j = 0; j < mapSizeColumn; ++j)
		{
			if (_block_map[i][j]._is_block)
			{
				dc.SelectObject(CTetrisPalette::getInstance()->getBrush(_block_map[i][j]._color));
				dc.Rectangle(map_start_x + j * BLOCK_PIXEL_SIZE, map_start_y + i * BLOCK_PIXEL_SIZE,
					map_start_x + (j + 1) * BLOCK_PIXEL_SIZE, map_start_y + (i + 1) * BLOCK_PIXEL_SIZE);
			}
		}
	}

	// 현재 block 을 그린다.

	int block_start_x = map_start_x + _current_block_pos.x * BLOCK_PIXEL_SIZE;
	int block_start_y = map_start_y + _current_block_pos.y * BLOCK_PIXEL_SIZE;
	
	if(_current_block) _current_block->draw(dc, block_start_x, block_start_y);
}

void CTetrisFrame::block_to_map()
{
	if (nullptr == _current_block) return;

	_current_block->print_to(_block_map, _current_block_pos);

	delete _current_block;
	_current_block = nullptr;
}

void CTetrisFrame::on_key_down(UINT nChar)
{
	switch (nChar)
	{
	case VK_DOWN:
		dropBlock();
		break;
	case VK_LEFT:
		moveBlockLeft();
		break;
	case VK_RIGHT:
		moveBlockRight();
		break;
	case VK_UP:
		turnBlock();
		break;
	case VK_SPACE:
		directDropBlock();
		break;
	default:
		break;
	}
}

void CTetrisFrame::on_timer()
{
	if (!dropBlock())
	{
		block_to_map();
		_deleted_line_count += deleteLines();
	}
}
