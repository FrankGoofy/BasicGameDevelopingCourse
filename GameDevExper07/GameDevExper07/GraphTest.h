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

