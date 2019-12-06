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
	// ����������(������ϷҪ������Щ������������Ϸ���ܴ���)
	// ��Ϸ��ʼ��
	virtual void GameInit();
	// ��Ϸ�߼�����
	virtual void GameLogic();
	// ��Ϸ��������
	virtual void GameEnd();
	// ����GAME_STATEֵ��ʾ��Ϸ����
	virtual void GamePaint(HDC hdc);
	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int Action = KEY_SYS_NONE);
	// ����KM_ACTIONֵ���������Ϊ
	virtual void GameMouseAction(int x, int y, int Action);
};

