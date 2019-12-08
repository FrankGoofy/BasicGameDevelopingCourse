#pragma once
#include "T_Menu.h"
class myGameMenu :
	public T_Menu
{
public:
	int btn_width;
	int btn_height;
	int x;
	int y;

	myGameMenu() {};
	virtual ~myGameMenu();
	void DrawMenu(HDC hdc, int bkgX = 0, int bkgY = 0, BYTE btnTrans = 255, bool startState = true);
	void CleraTtems() { gm_menuItems.clear(); }
};

