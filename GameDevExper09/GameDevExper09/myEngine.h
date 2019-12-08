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

	bool toSenceA;//��b�Ƶ�a����
	bool toSenceB;//��a�Ƶ�b����
	bool updateNpcPos;//�Ƿ� ����NPCλ��
	int wnd_width;//���ڵĿ�
	int wnd_height;//���ڵĸ�
	static float fish_size[5];//��Ĵ�С
	static  LPCTSTR fishPath[6];//����ļ�·��
	static const int fishNum = 10;//NPC�������
	T_Graph sea_left;//��߱���
	T_Graph sea_right;//�ұ߱���

	vector<T_Sprite*> vcNpc;//NPC����
	T_Sprite* myplayer;//���

	myGameMenu* myMenu;//�˵�


	void loadMenu();//����˵�
	void loadNpc();//����NPC

	void updatePlay();//�������
	void updateNpc();//����NPC
};

