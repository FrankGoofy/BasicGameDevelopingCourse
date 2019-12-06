#pragma once
#include "T_Engine.h"
class Test04 :public T_Engine
{
public:
	Test04(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	~Test04();

	void GameInit();
	// ��Ϸ�߼�����
	void GameLogic();
	// ��Ϸ��������
	void GameEnd();
	// ����GAME_STATEֵ��ʾ��Ϸ����
	void GamePaint(HDC hdc);
	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int ActionType);
	// ����KM_ACTIONֵ���������Ϊ
	void GameMouseAction(int x, int y, int ActionType);

	int w_width, w_height;

	void testAlphaBlen(HDC hdc);

	void testBitBlt(HDC hdc);

	void testBitBlt2(HDC hdc);

	void testStretchBlt(HDC hdc);
};

