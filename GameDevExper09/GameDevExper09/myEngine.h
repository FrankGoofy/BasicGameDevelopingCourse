#pragma once
#include "T_Engine.h"
#include"T_Graph.h"
#include"T_Menu.h"
#include"T_Sprite.h"
#include"myGameMenu.h"


class myEngine :public T_Engine
{
public:
	myEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	~myEngine();

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

	bool toSenceA;//从b移到a场景
	bool toSenceB;//从a移到b场景
	bool updateNpcPos;//是否 更新NPC位置
	int wnd_width;//窗口的宽
	int wnd_height;//窗口的高
	static float fish_size[5];//鱼的大小
	static  LPCTSTR fishPath[6];//鱼的文件路径
	static const int fishNum = 10;//NPC鱼的数量
	T_Graph sea_left;//左边背景
	T_Graph sea_right;//右边背景

	vector<T_Sprite*> vcNpc;//NPC容器
	T_Sprite* myplayer;//玩家

	myGameMenu* myMenu;//菜单


	void loadMenu();//载入菜单
	void loadNpc();//载入NPC

	void updatePlay();//更新玩家
	void updateNpc();//更新NPC
};

