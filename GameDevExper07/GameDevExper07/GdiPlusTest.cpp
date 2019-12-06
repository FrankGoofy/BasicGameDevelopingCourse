#include "GdiPlusTest.h"

#ifdef _GDI_PLUS_TEST_

GdiPlusTest::GdiPlusTest(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title, WORD icon, WORD sm_icon, int winwidth, int winheight)
	:T_Engine(h_instance, sz_winclass, sz_title, icon, sm_icon, winwidth, winheight)
{
	wnd_width = winwidth;
	wnd_height = winheight;
}

void GdiPlusTest::GameInit()
{
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;
	Color normalClr, focusClr;
	wstring menuItems[] = { L"����Ϸ",L"����",L"����",L"�˳�" };
	t_menu.SetMenuBkg(L".\\res\\menubkg.jpg");

	btn_width = 250;
	btn_height = 70;
	normalClr = Color::Red;
	focusClr = Color::White;
	t_menu.SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);

	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.space = MENU_SPACE;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	menuInfo.fontName = L"����";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focusClr;

	t_menu.SetMenuInfo(menuInfo);
	for (int i = 0; i < 4; i++)
	{
		//��ֱ���в���
		x = (wndWidth - btn_width) / 2;
		y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;
		
		//ˮƽ����
		//x = i * (btn_width + MENU_SPACE) + (wndWidth - 4 * btn_width - 3 * MENU_SPACE) / 2;
		//y = wnd_height - 2 * btn_height;

		//���ݲ���
		//x = (wndWidth - btn_width / 2) - btn_width + i * (btn_width / 2);
		//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

		//2��2������
		//int col = i % 2;
		//int row = i / 2;
		//x = row * (btn_width + MENU_SPACE) + (wndWidth - 2 * btn_width - MENU_SPACE) / 2;
		//y = row * (btn_height + MENU_SPACE) + (wnd_height - 2 * btn_height - MENU_SPACE) / 2;

		//Բ�ΰ�ť�˵���
		btn_width = 120;
		btn_height = 120;
		normalClr = Color::White;
		focusClr = Color::Yellow;
		t_menu.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);
		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];
		t_menu.AddMenuItem(mItem);
	}
	GameState = GAME_START;
}

void GdiPlusTest::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		t_menu.DrawMenu(hdc);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = 0.00;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 4;
		T_Graph::PaintText(hdc, textRec, L"��Ϸ�˵�", 36, L"����",
			Color::White, FontStyleBold, StringAlignmentCenter);
	}
}

void GdiPlusTest::GameKeyAction(int ActionType)
{
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		t_menu.MenuKeyDown(VK_UP);
	}
	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		t_menu.MenuKeyDown(VK_DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		t_menu.MenuKeyDown(VK_LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0)
	{
		t_menu.MenuKeyDown(VK_RIGHT);
	}
	if (GetAsyncKeyState(VK_RETURN) < 0)
	{
		if (t_menu.GetMenuIndex() >= 0)
		{
			switch (t_menu.GetMenuIndex())
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				break;

			default:
				break;
			}
		}
	}
}

void GdiPlusTest::GameMouseAction(int x, int y, int ActionType)
{
	if (ActionType == MOUSE_MOVE && GameState != GAME_RUN)
	{
		t_menu.MenuMouseMove(x, y);
	}
	if (ActionType == MOUSE_LCLICK)
	{
		if (GameState == GAME_START)
		{
			int index = t_menu.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				default:
					break;
				}
			}
		}
	}
}

#endif // _GDI_PLUS_TEST_