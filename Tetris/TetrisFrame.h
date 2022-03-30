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

	void set_bgcolor(CTetrisPalette::brush_e color); // ���ȭ�� ��
	void draw(CDC& dc, int start_x, int start_y);
	void initMap(void);
	bool insertBlock(CShape* block);

	void on_key_down(UINT nChar);

	void on_timer();

	bool no_moving_block() { return (nullptr == _current_block) ? true : false; }

	int takeDeletedLines() // ���� ���� 0���� �� ������ ����
	{
		int temp = _deleted_line_count;
		_deleted_line_count = 0;
		return temp;
	}

protected:
	void moveBlockLeft(void); // ��������
	void moveBlockRight(void); // ����������
	void turnBlock(void); // ��������
	bool dropBlock(void); //����Ʈ����
	void directDropBlock(void); //�ٷ� ����Ʈ����

	void block_to_map();

	int deleteLines(void);

	int mapSizeRow;		// ��Ʈ�������� ���� ũ��
	int mapSizeColumn;	// ��Ʈ�������� ���� ũ��

	block_cell_t** _block_map;			// ������ ��

	CPoint _current_block_pos;			// �� �󿡼��� current ����� ���� ����� ��ġ.

	CShape* _current_block;				// ��

	int _deleted_line;

	CTetrisPalette::brush_e _background;	// �޹�� ����

private:
	int _deleted_line_count;
};

