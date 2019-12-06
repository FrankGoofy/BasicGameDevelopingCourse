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
	LPCTSTR WinTitle = L"实验七-基于实验六";
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
	//主菜单初始化
	{
		int x = 0, y = 0;
		int btn_width = 0, btn_height = 0;
		Color normalClr, focusClr;
		wstring menuItems[] = { L"新游戏",L"关于",L"帮助",L"退出" };
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
		menuInfo.fontName = L"黑体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;

		t_menu.SetMenuInfo(menuInfo);
		for (int i = 0; i < 4; i++)
		{
			////圆形按钮菜单项
			//btn_width = 120;
			//btn_height = 120;
			//normalClr = Color::White;
			//focusClr = Color::Yellow;
			//t_menu.SetBtnBmp(L".\\res\\redroundbtn.png", btn_width, btn_height);

			//垂直居中布局
			x = (wndWidth - btn_width) / 2;
			y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//水平居中
			//x = i * (btn_width + MENU_SPACE) + (wndWidth - 4 * btn_width - 3 * MENU_SPACE) / 2;
			//y = wnd_height - 2 * btn_height;

			//阶梯布局
			//x = (wndWidth - btn_width / 2) - btn_width + i * (btn_width / 2);
			//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//2行2列坐标
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

	//关于界面初始化
	{
		int x = 0, y = 0;
		int btn_width = 0, btn_height = 0;
		Color normalClr, focusClr;
		wstring menuItems[] = { L"返回",L"开始",L"退出" };
		t_about.SetMenuBkg(L".\\res\\seafloor.jpg");

		//btn_width = 250;
		//btn_height = 70;
		//normalClr = Color::Red;
		//focusClr = Color::White;
		//t_about.SetBtnBmp(L".\\res\\button.png", btn_width, btn_height);

		//圆形按钮菜单项
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
		menuInfo.fontName = L"黑体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;

		t_about.SetMenuInfo(menuInfo);
		for (int i = 0; i < 3; i++)
		{
			//垂直居中布局
			//x = (wndWidth - btn_width) / 2;
			//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//水平居中
			x = i * (btn_width + MENU_SPACE) + (wndWidth - 4 * btn_width - 3 * MENU_SPACE) / 2;
			y = wnd_height - 2 * btn_height;

			//阶梯布局
			//x = (wndWidth - btn_width / 2) - btn_width + i * (btn_width / 2);
			//y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;

			//2行2列坐标
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

	//游戏主体初始化
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

			//瞎jb乱游
			//it->x = rand() % wnd_width - 30;
			//it->y = rand() % wnd_height - 30;

			//慢慢游
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
		T_Graph::PaintText(hdc, textRec, L"游戏菜单", 36, L"黑体",
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
		T_Graph::PaintText(hdc, textRec, L"关于", 36, L"黑体",
			Color::White, FontStyleBold, StringAlignmentCenter);

		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height * 0.2);
		infoRec.Width = (float)(wnd_width - 60);
		infoRec.Height = 400;
		LPCTSTR info = L"名称：菜单模块应用\n\
			班级：软件工程1702班\n\
			学号：8002117052\n\
			姓名：曾欢\n\
			时间：2019年11月8日";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"微软雅黑", Color::White, FontStyleRegular, StringAlignmentCenter);
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
		LPCTSTR caption = L"菜单实验";
		T_Graph::PaintText(hdc, captionRec, caption, 24, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentNear);

		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = (REAL)(wnd_height - 60);
		infoRec.Width = (float)wnd_width;
		infoRec.Height = 60;
		LPCTSTR info = L"班级：软件工程1702班；学号：8002117052；姓名：曾欢；时间：2019年11月1日";
		T_Graph::PaintText(hdc, infoRec, info, 14, L"微软雅黑", Color::White, FontStyleRegular, StringAlignmentCenter);
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

