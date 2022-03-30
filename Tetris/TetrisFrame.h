#pragma once

#include "CShape.h"


#define FRAME_BASIC_SIZE_ROW	23
#define FRAME_BASIC_SIZE_COL	12

class CTetrisFrame
{
public:
	CTetrisFrame(CTetrisPalette::brush_e bgColor = CTetrisPalette::BG_WHITE);
	CTetrisFrame(int row, int column, CTetrisPalette::brush_e bgColor = CTetrisPalette::BG_WHITE);
	virtual ~CTetrisFrame();

	void set_bgcolor(CTetrisPalette::brush_e color); // 배경화면 색
	void draw(CDC& dc, int start_x, int start_y);
	void initMap(void);
	bool insertBlock(CShape* block);

	void on_key_down(UINT nChar);

	void on_timer();

	bool no_moving_block() { return (nullptr == _current_block) ? true : false; }

	int takeDeletedLines() // 삭제 라인 0리셋 후 템프에 저장
	{
		int temp = _deleted_line_count;
		_deleted_line_count = 0;
		return temp;
	}

protected:
	void moveBlockLeft(void); // 왼쪽으로
	void moveBlockRight(void); // 오른쪽으로
	void turnBlock(void); // 블럭돌리기
	bool dropBlock(void); //떨어트리기
	void directDropBlock(void); //바로 떨어트리기

	void block_to_map();

	int deleteLines(void);

	int mapSizeRow;		// 테트리스판의 세로 크기
	int mapSizeColumn;	// 테트리스판의 가로 크기

	block_cell_t** _block_map;			// 게임판 색

	CPoint _current_block_pos;			// 맵 상에서의 current 블록의 왼쪽 상단의 위치.

	CShape* _current_block;				// 블럭

	int _deleted_line;

	CTetrisPalette::brush_e _background;	// 뒷배경 색깔

private:
	int _deleted_line_count;
};

