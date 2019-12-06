#pragma once
#include "T_Engine.h"
class GdiTest :
	public T_Engine
{
private:
	static const long T_LENGTH = 4500;
	int wnd_width, wnd_height;
	HBITMAP hbitmap;
	int cell_width, cell_height;
	int rows, cols;
	long startTime;
	POINT mousePT;
	int* randCell;
	int ratio;
	bool enlarge;

	Bitmap* HBITMAP_To_Bitmap(HBITMAP hbmp, HDC hdc);
	void PaintRegion(HDC destDC, int destX, int destY,
		int srcX, int srcY, int regionWidth, int regionHeight,
		float ratio, int rotType = 0, BYTE alpha = 255);
	void PaintText(HDC hdc, RectF fontRect, LPCTSTR text,
		REAL fontSize, LPCTSTR fontName,
		Color fontColor = Color::White,
		FontStyle style = FontStyleBold,
		StringAlignment align = StringAlignmentCenter);

	HBITMAP GetBmpHandle() { return hbitmap; }
	void GetRandomNum(int range, int* iArray);

public:
	virtual ~GdiTest(void);
	GdiTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = NULL, WORD sm_icon = NULL,
		int winwidth = 800, int winheight = 600, COLORREF bkColor = WIN_BKCLR);
	// 纯函数声明(具体游戏要重载这些函数并增加游戏功能代码)
	// 游戏初始化
	virtual void GameInit();
	// 游戏逻辑处理
	virtual void GameLogic();
	// 游戏结束处理
	virtual void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	virtual void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理按键行为
	virtual void GameKeyAction(int Action = KEY_SYS_NONE);
	// 根据KM_ACTION值处理鼠标行为
	virtual void GameMouseAction(int x, int y, int Action);
};

