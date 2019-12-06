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
	// 游戏逻辑处理
	void GameLogic();
	// 游戏结束处理
	void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理按键行为
	virtual void GameKeyAction(int ActionType);
	// 根据KM_ACTION值处理鼠标行为
	void GameMouseAction(int x, int y, int ActionType);

	int w_width, w_height;

	void testAlphaBlen(HDC hdc);

	void testBitBlt(HDC hdc);

	void testBitBlt2(HDC hdc);

	void testStretchBlt(HDC hdc);
};

