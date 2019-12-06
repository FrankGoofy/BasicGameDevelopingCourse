#pragma once
#include "T_Engine.h"
#include "T_Menu.h"

#ifdef _GDI_PLUS_TEST_

class GdiPlusTest :
	public T_Engine
{
private:
	int wnd_width, wnd_height;
	T_Menu t_menu;
public:
	virtual ~GdiPlusTest(void);
	GdiPlusTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
		WORD icon = NULL, WORD sm_icon = NULL,
		int winwidth = 800, int winheight = 600);

	void GameInit();
	// 游戏逻辑处理
	void GameLogic();
	// 游戏结束处理
	void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理按键行为
	virtual void GameKeyAction(int ActionType = KEY_SYS_NONE);
	// 根据KM_ACTION值处理鼠标行为
	void GameMouseAction(int x, int y, int ActionType);
};

#endif // _GDI_PLUS_TEST_