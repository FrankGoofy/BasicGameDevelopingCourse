#pragma once
#include "T_Engine.h"
#include"T_Graph.h"
#include"T_Menu.h"

//云的结构体
struct Cloud
{
	int x;
	int y;

	int speed;
	T_Graph cloud;
};



struct NPC
{
	int x;
	int y;
	int dir;
	bool alive;
	int framCount;
	float ratio;
	int speed;
	T_Graph npc;
};

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
	int wnd_width;//窗口的宽
	int wnd_height;//窗口的高
	T_Graph bluesky;//背景海床

	static LPCTSTR cloud_files[8];//云的文件路径
	static int cloud_NUM;//绘制云的数量
	static int npc_NUM;//绘制敌机的数量

	vector<NPC> vcNpc;//npc容器
	vector<Cloud> vcCloud;//存放每只云的容器

	NPC player;//玩家
	NPC boss;//boss结构体
	T_Menu t_menu;//游戏菜单类的对象
	T_Menu about_menu;//游戏菜单类的对象

	Color normalClr, focuClr;//按钮正常颜色和焦点颜色
	int btn_width, btn_height;//按钮的宽高

};

