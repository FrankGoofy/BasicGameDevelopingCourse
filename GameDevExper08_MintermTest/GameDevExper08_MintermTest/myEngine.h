#pragma once
#include "T_Engine.h"
#include"T_Graph.h"
#include"T_Menu.h"

//�ƵĽṹ��
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
	int wnd_width;//���ڵĿ�
	int wnd_height;//���ڵĸ�
	T_Graph bluesky;//��������

	static LPCTSTR cloud_files[8];//�Ƶ��ļ�·��
	static int cloud_NUM;//�����Ƶ�����
	static int npc_NUM;//���Ƶл�������

	vector<NPC> vcNpc;//npc����
	vector<Cloud> vcCloud;//���ÿֻ�Ƶ�����

	NPC player;//���
	NPC boss;//boss�ṹ��
	T_Menu t_menu;//��Ϸ�˵���Ķ���
	T_Menu about_menu;//��Ϸ�˵���Ķ���

	Color normalClr, focuClr;//��ť������ɫ�ͽ�����ɫ
	int btn_width, btn_height;//��ť�Ŀ��

};

