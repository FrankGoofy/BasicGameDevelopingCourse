#include "GraphTest.h"

float GraphTest::fish_size[5] = { 0.8f,0.9f,1.0f,1.1f,0.7f };
LPCTSTR GraphTest::fish_files[4] = { L".\\res\\blue.png",L".\\res\\green.png", L".\\res\\red.png", L".\\res\\yellow.png" };
LPCTSTR GraphTest::fish_name[4] = { L"blue",L"green", L"red", L"yellow" };
int GraphTest::fish_NUM = 10;
int GraphTest::fish_width = 143;
int GraphTest::fish_height = 84;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LPCTSTR WinTitle = L"ʵ����-����ʵ����";
	GraphTest* test = new GraphTest(hInstance, WIN_CLASS, WinTitle, NULL, NULL, 1024, 768);
	T_Engine::pEngine = test;
	test->SetFrame(10);
	//test->SetFullScreen(true);
	test->StartEngine();

	return 0;
}

GraphTest::GraphTest(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth, int iHeight, COLORREF bkColor) :
	T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight, bkColor)
{
	srand((unsigned)time(NULL));
	wnd_width = iWidth;
	wnd_height = iHeight;
}

GraphTest::~GraphTest()
{
}

void GraphTest::GameInit()
{
	//���˵���ʼ��
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
			////Բ�ΰ�ť�˵���
			//btn_width = 120;
			//btn_height = 120;
			//normalClr = Color::White;
			//focusClr = Color::Yellow;
			//t_menu.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);

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

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = menuItems[i];
			t_menu.AddMenuItem(mItem);
		}
		GameState = GAME_START;
	}
	///////////////////////////////////////////////////////

	//���ڽ����ʼ��
	{
		int x = 0, y = 0;
		int btn_width = 0, btn_height = 0;
		Color normalClr, focusClr;
		wstring menuItems[] = { L"����",L"��ʼ",L"�˳�" };
		t_about.SetMenuBkg(L".\\res\\seafloor.jpg");

		//btn_width = 250;
		//btn_height = 70;
		//normalClr = Color::Red;
		//focusClr = Color::White;
		//t_about.SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);

		//Բ�ΰ�ť�˵���
		btn_width = 120;
		btn_height = 120;
		normalClr = Color::White;
		focusClr = Color::Yellow;
		t_about.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);

		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = btn_width;
		menuInfo.height = btn_height;
		menuInfo.fontName = L"����";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;

		t_about.SetMenuInfo(menuInfo);
		for (int i = 0; i < 3; i++)
		{
			//��ֱ���в���
			//x = (wndWidth - btn_width) / 2;
			//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//ˮƽ����
			x = i * (btn_width + MENU_SPACE) + (wndWidth - 4 * btn_width - 3 * MENU_SPACE) / 2;
			y = wnd_height - 2 * btn_height;

			//���ݲ���
			//x = (wndWidth - btn_width / 2) - btn_width + i * (btn_width / 2);
			//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//2��2������
			//int col = i % 2;
			//int row = i / 2;
			//x = row * (btn_width + MENU_SPACE) + (wndWidth - 2 * btn_width - MENU_SPACE) / 2;
			//y = row * (btn_height + MENU_SPACE) + (wnd_height - 2 * btn_height - MENU_SPACE) / 2;

			MENUITEM mItem;
			mItem.pos.x = x;
			mItem.pos.y = y;
			mItem.ItemName = menuItems[i];
			t_about.AddMenuItem(mItem);
		}
		GameState = GAME_START;
	}
	///////////////////////////////////////////////////////

	//��Ϸ�����ʼ��
	seafloor.LoadImageFile(L".\\res\\seafloor.jpg");
	seabed.LoadImageFile(L".\\res\\seabed.jpg");
	msgFrame.LoadImageFile(L".\\res\\msg.png");

	for (int i = 0; i < fish_NUM; i++)
	{
		FISH tempFish;

		int s = rand() % 5;
		tempFish.ratio = fish_size[s];
		//int w = (int)(fish_size[s] * fish_width);
		//int h = (int)(fish_size[s] * fish_height);
		int w = int(tempFish.ratio * fish_width);
		int h = int(tempFish.ratio * fish_height);
		tempFish.x = rand() % (wnd_width - w);
		tempFish.y = rand() % (wnd_height - h);

		int d = rand() % 2;
		tempFish.dir = d;

		int f = rand() % 4;
		LPCTSTR str = fish_files[f];
		tempFish.fish.LoadImageFile(str);
		tempFish.name = fish_name[f];

		tempFish.fcount = 0;
		vecFish.push_back(tempFish);
	}
	///////////////////////////////////////////////////////
}

void GraphTest::GameLogic()
{
	vector<FISH>::iterator it;
	for (it = vecFish.begin(); it < vecFish.end(); it++)
	{
		if (it->fcount < fish_NUM)
		{
			it->fcount += 1;

			//Ϲjb����
			//it->x = rand() % wnd_width - 30;
			//it->y = rand() % wnd_height - 30;

			//������
			if (it->dir == 0)
			{
				it->x -= 2;
				if (it->x <= -40)
				{
					it->x = wnd_width;
				}
			}
			else
			{
				it->x += 2;
				if (it->x >= wnd_width)
				{
					it->x = 0;
				}
			}
		}
		if (it->fcount >= fish_NUM)
		{
			it->fcount = 0;
		}
	}
}

void GraphTest::GameEnd()
{
	seabed.Destroy();
	seafloor.Destroy();
	msgFrame.Destroy();
	vector<FISH>::iterator it;
	for (it = vecFish.begin(); it < vecFish.end(); it++)
	{
		it->fish.Destroy();
	}
}

void GraphTest::GamePaint(HDC hdc)
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

	if (GameState == GAME_ABOUT)
	{
		t_about.DrawMenu(hdc);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = 0.00;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 3;
		T_Graph::PaintText(hdc, textRec, L"����", 36, L"����",
			Color::White, FontStyleBold, StringAlignmentCenter);

		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height * 0.2);
		infoRec.Width = (float)(wnd_width - 60);
		infoRec.Height = 400;
		LPCTSTR info = L"���ƣ��˵�ģ��Ӧ��\n\
			�༶���������1702��\n\
			ѧ�ţ�8002117052\n\
			����������\n\
			ʱ�䣺2019��11��8��";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"΢���ź�", Color::White, FontStyleRegular, StringAlignmentCenter);
	}

	if (GameState == GAME_RUN)
	{
		seafloor.PaintImage(hdc, 0, 0, wnd_width, wnd_height, 255);
		seabed.PaintImage(hdc, 0, 0, wnd_width, wnd_height, 160);

		vector<FISH>::iterator it;
		for (it = vecFish.begin(); it < vecFish.end(); it++)
		{
			int rot = 0;
			if (it->dir == 0)
			{
				rot = 0;
			}
			else
			{
				rot = TRANS_HFLIP_NOROT;
			}

			RectF msgRect;
			msgRect.Width = (REAL)(msgFrame.GetImageWidth());
			msgRect.Height = (REAL)(msgFrame.GetImageHeight());
			msgRect.X = (REAL)(it->x + (it->ratio * fish_width - msgFrame.GetImageWidth()) / 2);
			msgRect.Y = (REAL)(it->y - msgFrame.GetImageHeight());
			msgFrame.PaintImage(hdc, (int)msgRect.X, (int)msgRect.Y, (int)msgRect.Width, (int)msgRect.Height, 255);
			T_Graph::PaintText(hdc, msgRect, it->name, 10, L"Arial", Color::White, FontStyleBold, StringAlignmentCenter);

			it->fish.PaintFrame(it->fish.GetBmpHandle(), hdc, it->x, it->y, it->fcount,
				20, fish_width, fish_height, it->ratio, rot);
		}

		RectF captionRec;
		captionRec.X = 0.00;
		captionRec.Y = 0.00;
		captionRec.Width = (float)wnd_width;
		captionRec.Height = 60.0f;
		LPCTSTR caption = L"�˵�ʵ��";
		T_Graph::PaintText(hdc, captionRec, caption, 24, L"΢���ź�", Color::White, FontStyleBold, StringAlignmentNear);

		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height - 60);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"�༶���������1702�ࣻѧ�ţ�8002117052��������������ʱ�䣺2019��11��1��";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"΢���ź�", Color::White, FontStyleRegular, StringAlignmentCenter);
	}
}

void GraphTest::GameKeyAction(int ActionType)
{
	if (GameState == GAME_START)
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
					GameState = GAME_RUN;
					break;
				case 1:
					GameState = GAME_ABOUT;
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
	if (GameState == GAME_ABOUT)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			t_about.MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			t_about.MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			t_about.MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			t_about.MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (t_about.GetMenuIndex() >= 0)
			{
				switch (t_about.GetMenuIndex())
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					GameState = GAME_RUN;
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

void GraphTest::GameMouseAction(int x, int y, int ActionType)
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
					GameState = GAME_RUN;
					break;
				case 1:
					GameState = GAME_ABOUT;
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

		if (GameState == GAME_ABOUT)
		{

			int index = t_about.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					GameState = GAME_RUN;
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

