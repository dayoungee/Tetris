#pragma once


#define PEN_COLOR_BLACK		RGB(0,0,0)
#define PEN_COLOR_WHITE		RGB(255,255,255)
#define PEN_COLOR_BLOCK		RGB(190, 190, 190)

#define BLOCK_BRUSH_COLOR0	RGB(65, 228, 82)
#define BLOCK_BRUSH_COLOR1	RGB(58, 98, 235)
#define BLOCK_BRUSH_COLOR2	RGB(128, 0, 64)
#define BLOCK_BRUSH_COLOR3	RGB(255, 35, 31)
#define BLOCK_BRUSH_COLOR4	RGB(68, 17, 111)
#define BLOCK_BRUSH_COLOR5	RGB(246, 118, 57)
#define BLOCK_BRUSH_COLOR6	RGB(224, 134, 4)

#define BACKGROUND_COLOR_BLUE	RGB(100, 149, 237)
#define BACKGROUND_COLOR_PINK	RGB(255, 192, 203)
#define BACKGROUND_COLOR_WHITE	RGB(255, 255, 255)


class CTetrisPalette
{
public:
	static CTetrisPalette* getInstance()
	{
		if (nullptr == _instance) // 포인터 변수는 nullptr로
			_instance = new CTetrisPalette;
		return _instance;
	}

	static void destroy()
	{
		if (_instance) delete _instance;
		_instance = nullptr;
	}

	typedef enum PENS 
	{
		BLACK, WHITE, BLOCK_LINE

	} pen_e;

	CPen* getPen(pen_e pen_index);

	typedef enum BRUSHES
	{
		BLOCK_0, BLOCK_1, BLOCK_2, BLOCK_3, BLOCK_4, BLOCK_5, BLOCK_6,
		BG_BLUE, BG_PINK, BG_WHITE

	} brush_e;

	CBrush* getBrush(brush_e brush_index);

private:
	CTetrisPalette() { init(); }
	~CTetrisPalette() {}

	static CTetrisPalette* _instance; // 전역

	void init();

	CPen _pens[3];

	CBrush _brushes[10];
};

