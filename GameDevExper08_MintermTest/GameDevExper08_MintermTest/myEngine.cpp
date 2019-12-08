#include "myEngine.h"

LPCTSTR myEngine::cloud_files[8] = { L".\\res\\cloud01.png",L".\\res\\cloud02.png",
								L".\\res\\cloud03.png", L".\\res\\cloud04.png", L".\\res\\cloud05.png",
L".\\res\\cloud06.png", L".\\res\\cloud07.png", L".\\res\\cloud07.png" };

int myEngine::cloud_NUM = 8;
int myEngine::npc_NUM = 4;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LPCTSTR WinTitle = L"����ʵ��";
	myEngine* test = new myEngine(hInstance, WIN_CLASS, WinTitle, NULL, NULL, 1024, 768);
	T_Engine::pEngine = test;
	test->SetFrame(30);
	//test->SetFullScreen(true);
	test->StartEngine();

	return 0;
}

myEngine::myEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth, int iHeight, COLORREF bkColor) :
	T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight, bkColor)
{
	srand((unsigned)time(NULL));
	wnd_width = iWidth;
	wnd_height = iHeight;
}

myEngine::~myEngine()
{
	t_menu.DestroyAll();
	about_menu.DestroyAll();
}

void myEngine::GameInit()
{
	GameState = GAME_START;
	bluesky.LoadImageFile(L".\\res\\bluesky.png");

	////////////////////////////////////////////////////////////////////////
	//��
	for (int i = 0; i < cloud_NUM; i++)
	{
		Cloud tempCloud;
		int s = rand() % 5;

		int f = rand() % 8;
		LPCTSTR str = cloud_files[f];
		tempCloud.cloud.LoadImageFile(str);
		tempCloud.x = rand() % (wnd_width - tempCloud.cloud.GetImageWidth());
		tempCloud.y = 0;
		tempCloud.speed = rand() % 3 + 2;
		vcCloud.push_back(tempCloud);
	}

	////////////////////////////////////////////////////////////////////////
	//Ŀ¼
	MENUITEM mItem;
	int x = 0, y = 0;
	btn_width = 200;
	btn_height = 60;
	normalClr = Color::Red;
	focuClr = Color::White;
	wstring menuItems[] = { L"����Ϸ",L"����", L"�˳���Ϸ" };
	t_menu.SetMenuBkg(L".\\res\\menubck.png", 210);
	t_menu.SetBtnBmp(L".\\res\\blueButton200x120.png", btn_width, btn_height);
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.space = MENU_SPACE;
	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	menuInfo.fontName = L"����";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focuClr;
	t_menu.SetMenuInfo(menuInfo);


	about_menu.SetMenuBkg(L".\\res\\menubck.png", 210);
	about_menu.SetBtnBmp(L".\\res\\blueButton200x120.png", btn_width, btn_height);
	menuInfo.normalTextColor = Color::Yellow;


	menuInfo.width = btn_width;
	menuInfo.height = btn_height;
	about_menu.SetMenuInfo(menuInfo);

	wstring menuItems2[] = { L"����",L"��ʼ", L"�˳�" };
	for (int i = 0; i < 3; i++)
	{

		////��ֱ��������
		x = (wnd_width - btn_width) / 2 - 210;
		y = i * (btn_height + MENU_SPACE) + (wnd_height - 4 * btn_height - 3 * MENU_SPACE) / 2;


		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];
		t_menu.AddMenuItem(mItem);
	}

	for (int i = 0; i < 3; i++)
	{
		//ˮƽ���в��ֵ�����
		x = i * (btn_width + MENU_SPACE) + wnd_width / 2 - 300;
		y = wnd_height / 5 * 3;

		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems2[i];
		about_menu.AddMenuItem(mItem);
	}

	////////////////////////////////////////////////////////////////////////
	//���������
	for (int i = 0; i < npc_NUM; i++)
	{
		NPC tempNpc;
		tempNpc.x = rand() % (wnd_width - 114);
		tempNpc.y = 0;
		tempNpc.speed = rand() % 3 + 2;
		tempNpc.npc.LoadImageFile(L".\\res\\npc.png");
		tempNpc.framCount = 0;
		vcNpc.push_back(tempNpc);
	}

	player.npc.LoadImageFile(L".\\res\\player.png");
	player.x = (wnd_width - player.npc.GetImageWidth()) / 2;
	player.y = wnd_height - 2 * player.npc.GetImageHeight();
	player.speed = 5;
	player.alive = false;

	boss.npc.LoadImageFile(L".\\res\\npc_boss.png");
	boss.x = rand() % (wnd_width - player.npc.GetImageWidth());
	boss.y = -wnd_height;
	boss.speed = 3;
}

void myEngine::GameLogic()
{
	vector<Cloud>::iterator it;
	for (it = vcCloud.begin(); it < vcCloud.end(); it++)
	{
		it->y += it->speed;
		if (it->y >= wnd_height)
		{
			it->x = rand() % (wnd_width - it->cloud.GetImageWidth());
			it->y = 0;
			it->speed = rand() % 6 + 2;
		}
	}

	//����NPC
	boss.x += 4;
	if (boss.x + boss.npc.GetImageWidth() > wnd_width)
	{
		boss.x -= 4;

	}
	boss.y += 3;
	if (boss.y > 2 * wnd_height)
	{
		boss.y = 0 - boss.npc.GetImageHeight();
		boss.x = rand() % (wnd_width - player.npc.GetImageWidth());
	}
	vector<NPC>::iterator it2;
	for (it2 = vcNpc.begin(); it2 < vcNpc.end(); it2++)
	{
		if (it2->framCount < 4)
		{
			it2->framCount += 1;
		}
		if (it2->framCount >= 4)
		{
			it2->framCount = 0;
		}
		it2->y += it2->speed;
		if (it2->y >= wnd_height)
		{
			it2->x = rand() % (wnd_width - 114);
			it2->y = 0;
			it2->speed = rand() % 4 + 1;
		}
	}
	if (player.alive == true)
	{
		if (player.dir == DIR_UP)
		{
			player.y -= player.speed;
			if (player.y < 0)
			{
				player.y = 0;
			}
		}
		if (player.dir == DIR_DOWN)
		{
			player.y += player.speed;
			if (player.y > wnd_height - player.npc.GetImageHeight())
			{
				player.y = wnd_height - player.npc.GetImageHeight();
			}
		}
		if (player.dir == DIR_LEFT)
		{
			player.x -= player.speed;
			if (player.x < 0)
			{
				player.x = 0;
			}
		}
		if (player.dir == DIR_RIGHT)
		{
			player.x += player.speed;
			if (player.x > wnd_width - player.npc.GetImageWidth())
			{
				player.x = wnd_width - player.npc.GetImageWidth();
			}
		}
	}
}

void myEngine::GameEnd()
{

	bluesky.Destroy();

	vector<Cloud>::iterator it;
	for (it = vcCloud.begin(); it < vcCloud.end(); it++)
	{
		it->cloud.Destroy();
	}
	player.npc.Destroy();
	boss.npc.Destroy();
}

void myEngine::GamePaint(HDC hdc)
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
		about_menu.DrawMenu(hdc);
		T_Graph::PaintBlank(hdc, wnd_width / 4, wnd_height / 12, wnd_width / 2, wnd_height / 2, Color::Blue, 200);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = (float)wnd_height / 10;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 10;
		wstring m_about = L"����:�˵�ģ��Ӧ��\n";
		m_about.append(L"�༶:�������172��\n");
		m_about.append(L"ѧ��: 8002117052\n");
		m_about.append(L"����:����\n");
		m_about.append(L"ʱ��: 2019��11��9��");
		T_Graph::PaintText(hdc, textRec, L"����", 36, L"΢���ź�",
			Color::White, FontStyleBold, StringAlignmentCenter);
		RectF aboutRec;
		aboutRec.X = wnd_width / 2 - 100;
		aboutRec.Y = (float)wnd_height / 5;
		aboutRec.Width = (float)wnd_width / 2 + 100;
		aboutRec.Height = (float)wnd_height / 5;
		T_Graph::PaintText(hdc, aboutRec, m_about.c_str(), 18, L"΢���ź�",
			Color::White, FontStyleBold, StringAlignmentNear);
	}

	if (GameState == GAME_RUN)
	{
		bluesky.PaintImage(hdc, 0, 0, wnd_width, wnd_height, 255);

		vector<Cloud>::iterator it;
		for (it = vcCloud.begin(); it < vcCloud.end(); it++)
		{
			it->cloud.PaintFrame(it->cloud.GetBmpHandle(), hdc, it->x, it->y, 0, 1, it->cloud.GetImageWidth(), it->cloud.GetImageHeight());
		}
		player.npc.PaintFrame(player.npc.GetBmpHandle(), hdc, 
			player.x, player.y, 0, 1, player.npc.GetImageWidth(), player.npc.GetImageHeight());
		//player.npc.PaintImage(hdc, player.x , player.y, player.npc.GetImageWidth(), player.npc.GetImageHeight(), 255);

		boss.npc.PaintFrame(boss.npc.GetBmpHandle(), hdc, 
			boss.x, boss.y, 0, 1, boss.npc.GetImageWidth(), boss.npc.GetImageHeight());
		RectF titleRect;
		titleRect.Width = (REAL)(300);
		titleRect.Height = (REAL)(50);
		titleRect.X = (REAL)0;
		titleRect.Y = (REAL)0;
		RectF infoRect;
		infoRect.Width = (REAL)(800);
		infoRect.Height = (REAL)(50);
		infoRect.X = (REAL)0;
		infoRect.Y = (REAL)(wnd_height - 40);
		T_Graph::PaintText(hdc, titleRect, L"����ʵ��", 20, L"΢���ź�", Color::White);
		T_Graph::PaintText(hdc, infoRect, L"�༶:�������172��      ѧ��: 8002117052     \
						����: ����    ʱ��: 2019��11��9��",
			14, L"΢���ź�", Color::White);

		vector<NPC>::iterator it2;
		for (it2 = vcNpc.begin(); it2 < vcNpc.end(); it2++)
		{
			it2->npc.PaintFrame(it2->npc.GetBmpHandle(), hdc, it2->x, it2->y, it2->framCount, 20, 114, 82);
		}
	}
}

void myEngine::GameKeyAction(int ActionType)
{
	if (GameState == GAME_START)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			t_menu.MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			t_menu.MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			t_menu.MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			t_menu.MenuKeyDown(VK_RIGHT);
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
				}
			}
		}
	}

	if (GameState == GAME_ABOUT || GameState == GAME_HELP)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			about_menu.MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			about_menu.MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			about_menu.MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			about_menu.MenuKeyDown(VK_RIGHT);
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (about_menu.GetMenuIndex() >= 0)
			{
				switch (about_menu.GetMenuIndex())
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					GameState = GAME_RUN;
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;

				}
			}
		}
	}
	if (GameState == GAME_RUN)
	{
		if (ActionType == KEY_DOWN)
		{
			if (GetAsyncKeyState(VK_UP) < 0)
			{
				player.alive = true;
				player.dir = DIR_UP;
			}

			if (GetAsyncKeyState(VK_DOWN) < 0)
			{
				player.alive = true;
				player.dir = DIR_DOWN;
			}

			if (GetAsyncKeyState(VK_LEFT) < 0)
			{
				player.alive = true;
				player.dir = DIR_LEFT;
			}

			if (GetAsyncKeyState(VK_RIGHT) < 0)
			{
				player.alive = true;
				player.dir = DIR_RIGHT;
			}

		}
		if (ActionType == KEY_UP)
		{
			if (GetAsyncKeyState(VK_RIGHT) == 0 || GetAsyncKeyState(VK_LEFT) == 0 || GetAsyncKeyState(VK_DOWN) == 0 || GetAsyncKeyState(VK_UP) == 0)
			{
				player.alive = false;
			}
		}
	}
}

void myEngine::GameMouseAction(int x, int y, int ActionType)
{
	if (GameState == GAME_START)
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
						ActionType = KEY_SYS_NONE;
						break;
					case 1:
						GameState = GAME_ABOUT;
						ActionType = KEY_SYS_NONE;
						break;
					case 2:
						GameState = GAME_HELP;
						ActionType = KEY_SYS_NONE;
						break;
					case 3:
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						break;
					}
				}
			}
		}
	}

	if (GameState == GAME_ABOUT || GameState == GAME_HELP)
	{
		if (ActionType == MOUSE_MOVE && GameState != GAME_RUN)
		{
			about_menu.MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			if (GameState == GAME_ABOUT || GameState == GAME_HELP)
			{
				int index = about_menu.MenuMouseClick(x, y);
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
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						break;
					}
				}
			}
		}
	}
}
