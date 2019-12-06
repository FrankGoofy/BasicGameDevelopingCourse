#pragma once

#include "T_Engine.h"
class EngineTest :
	public T_Engine
{
public:
	virtual ~EngineTest(void);
	EngineTest(
		HINSTANCE h_instance,
		LPCTSTR sz_winclass,
		LPCTSTR sz_title,
		WORD icon = NULL,
		WORD sm_icon = NULL,
		int winwidth = WIN_WIDTH,
		int winheight = WIN_HEIGHT);

	void GameInit();
	void GameLogic();
	void GameEnd();
	void GamePaint(HDC hdc);
	void GameKeyAction(int Action = KEY_SYS_NONE);
	void GameMouseAction(int x, int y, int Action);

private:
	int wnd_width;
	int wnd_height;

};

