#pragma once
#include "T_Engine.h"
#include "T_Graph.h"
#include "T_Menu.h"

struct FISH
{
	int x;
	int y;
	float ratio;
	int fcount;
	int dir;
	LPCTSTR name;
	T_Graph fish;
};

class GraphTest :
	public T_Engine
{
public:
	GraphTest(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	~GraphTest();

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

private:
	int wnd_width;
	int wnd_height;
	T_Graph seafloor;
	T_Graph seabed;
	T_Graph msgFrame;

	static float fish_size[5];
	static LPCTSTR fish_files[4];
	static LPCTSTR fish_name[4];
	static int fish_NUM;
	static int fish_width;
	static int fish_height;

	vector<FISH> vecFish;

	T_Menu t_menu;
	T_Menu t_about;
};

