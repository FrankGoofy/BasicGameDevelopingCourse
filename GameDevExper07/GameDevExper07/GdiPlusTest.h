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
	// ��Ϸ�߼�����
	void GameLogic();
	// ��Ϸ��������
	void GameEnd();
	// ����GAME_STATEֵ��ʾ��Ϸ����
	void GamePaint(HDC hdc);
	// ����KM_ACTIONֵ��������Ϊ
	virtual void GameKeyAction(int ActionType = KEY_SYS_NONE);
	// ����KM_ACTIONֵ���������Ϊ
	void GameMouseAction(int x, int y, int ActionType);
};

#endif // _GDI_PLUS_TEST_