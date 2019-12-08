#include "myEngine.h"


LPCTSTR myEngine::fishPath[6] = { L".\\res\\blue.png",L".\\res\\green.png", L".\\res\\red.png",
L".\\res\\yellow.png", L".\\res\\orange.png",  L".\\res\\pink.png" };
float myEngine::fish_size[5] = { 0.8f,0.9f,1.0f,1.1f,0.7f };
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LPCTSTR WinTitle = L"实验九";
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

}

void myEngine::GameInit()
{
	sea_left.LoadImageFile(L".\\res\\sea_left.jpg");
	sea_right.LoadImageFile(L".\\res\\sea_right.jpg");
	GameState = GAME_START;
	toSenceA = false;
	toSenceB = false;
	updateNpcPos = false;
	myMenu = new myGameMenu();
	loadMenu();
	loadNpc();
}

void myEngine::GameLogic()
{
	if (GameState == GAME_RUN)
	{
		updatePlay();
		updateNpc();
	}

}

void myEngine::GameEnd()
{
	vector<T_Sprite*>::iterator it;
	for (it = vcNpc.begin(); it < vcNpc.end(); it++)
	{
		(*it)->GetImage()->Destroy();
	}
	myplayer->GetImage()->Destroy();
	delete(myplayer);
	sea_left.Destroy();
	sea_right.Destroy();
}

void myEngine::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		myMenu->T_Menu::DrawMenu(hdc);

	}
	if (GameState == GAME_ABOUT)
	{
		myMenu->T_Menu::DrawMenu(hdc);
		T_Graph::PaintBlank(hdc, wnd_width / 4, wnd_height / 12, wnd_width / 2, wnd_height / 2, Color::Blue, 100);
		RectF textRec;
		textRec.X = 0.00;
		textRec.Y = (float)wnd_height / 10;
		textRec.Width = (float)wnd_width;
		textRec.Height = (float)wnd_height / 10;
		wstring m_about = L"名称:多角色绘制与控制\n";
		m_about.append(L"班级:软件工程1702班\n");
		m_about.append(L"学号: 8002117052\n");
		m_about.append(L"姓名:曾欢\n");
		m_about.append(L"时间: 2019年11月22日");
		T_Graph::PaintText(hdc, textRec, L"关于", 36, L"微软雅黑",
			Color::White, FontStyleBold, StringAlignmentCenter);
		RectF aboutRec;
		aboutRec.X = wnd_width / 2 - 100;
		aboutRec.Y = (float)wnd_height / 5;
		aboutRec.Width = (float)wnd_width / 2 + 100;
		aboutRec.Height = (float)wnd_height / 5;
		T_Graph::PaintText(hdc, aboutRec, m_about.c_str(), 18, L"微软雅黑",
			Color::White, FontStyleBold, StringAlignmentNear);
	}

	if (GameState == GAME_PAUSE)
	{
		myMenu->DrawMenu(hdc);
	}
	if (GameState == GAME_RUN)
	{
		if (toSenceA == false && toSenceB == false || toSenceA == true)
		{
			sea_left.PaintImage(hdc, 0, 0, wnd_width, wnd_height);
		}

		if (toSenceB == true)
		{
			sea_right.PaintImage(hdc, 0, 0, wnd_width, wnd_height);
		}


		if (myplayer->GetDir() == DIR_RIGHT)
		{
			myplayer->SetRotation(TRANS_HFLIP_NOROT);

		}
		if (myplayer->GetDir() == DIR_LEFT)
		{
			myplayer->SetRotation(TRANS_NONE);
		}
		myplayer->SetAlpha(255);
		myplayer->Draw(hdc);
		vector<T_Sprite*>::iterator it;
		for (it = vcNpc.begin(); it < vcNpc.end(); it++)
		{
			(*it)->SetAlpha(255);
			(*it)->Draw(hdc);
			if ((*it)->GetDir() == DIR_RIGHT)
			{
				(*it)->SetRotation(TRANS_HFLIP_NOROT);

			}
			if ((*it)->GetDir() == DIR_LEFT)
			{
				(*it)->SetRotation(TRANS_NONE);
			}
		}
	}
}

void myEngine::GameKeyAction(int ActionType)
{
	if (GameState == GAME_START)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			myMenu->MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			myMenu->MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			myMenu->MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			myMenu->MenuKeyDown(VK_RIGHT);
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (myMenu->GetMenuIndex() >= 0)
			{
				switch (myMenu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_RUN;
					break;
				case 1:
					GameState = GAME_ABOUT;
					loadMenu();
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
	}
	if (GameState == GAME_ABOUT || GameState == GAME_PAUSE)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			myMenu->MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			myMenu->MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			myMenu->MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			myMenu->MenuKeyDown(VK_RIGHT);
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (myMenu->GetMenuIndex() >= 0)
			{
				switch (myMenu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_START;
					loadMenu();
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

				myplayer->SetActive(true);
				myplayer->SetDir(DIR_UP);
			}

			if (GetAsyncKeyState(VK_DOWN) < 0)
			{
				myplayer->SetActive(true);
				myplayer->SetDir(DIR_DOWN);
			}

			if (GetAsyncKeyState(VK_LEFT) < 0)
			{
				myplayer->SetActive(true);
				myplayer->SetDir(DIR_LEFT);
			}

			if (GetAsyncKeyState(VK_RIGHT) < 0)
			{
				myplayer->SetActive(true);
				myplayer->SetDir(DIR_RIGHT);
			}

		}
		if (ActionType == KEY_UP)
		{
			if (GetAsyncKeyState(VK_RIGHT) == 0 || GetAsyncKeyState(VK_LEFT) == 0 ||
				GetAsyncKeyState(VK_DOWN) == 0 || GetAsyncKeyState(VK_UP) == 0)
			{
				myplayer->SetActive(false);
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
			myMenu->MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			if (GameState == GAME_START)
			{
				int index = myMenu->MenuMouseClick(x, y);
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
						loadMenu();
						ActionType = KEY_SYS_NONE;
						break;
					case 2:
						SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
						ActionType = KEY_SYS_NONE;
						break;

					}
				}
			}
		}
	}


	if (GameState == GAME_ABOUT || GameState == GAME_PAUSE)
	{
		if (ActionType == MOUSE_MOVE && GameState != GAME_RUN)
		{
			myMenu->MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			if (GameState == GAME_ABOUT || GameState == GAME_HELP || GameState == GAME_PAUSE)
			{
				int index = myMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (index)
					{
					case 0:
						GameState = GAME_START;
						loadMenu();
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

	if (GameState == GAME_RUN)
	{
		RECT myRect;
		myRect.right = wnd_width;
		myRect.top = 0;
		myRect.bottom = 30;
		myRect.left = wnd_width - 100;
		POINT mPt;
		mPt.x = x;
		mPt.y = y;
		if (PtInRect(&myRect, mPt) == true)
		{
			GameState = GAME_PAUSE;
			loadMenu();
		}
	}

}

void myEngine::loadMenu()
{
	if (GameState == GAME_START)
	{
		MENUITEM mItem;
		myMenu->CleraTtems();
		myMenu->btn_width = 125;
		myMenu->btn_height = 125;

		wstring menuItems[] = { L"开始游戏",L"关于游戏", L"退出游戏" };
		myMenu->SetMenuBkg(L".\\res\\menubkg.jpg", 210);
		myMenu->SetBtnBmp(L".\\res\\blue_round_125x125.png", myMenu->btn_width, myMenu->btn_height);
		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = myMenu->btn_width;
		menuInfo.height = myMenu->btn_height;
		menuInfo.fontName = L"新宋体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = Color::Black;
		menuInfo.focusTextColor = Color::White;
		myMenu->SetMenuInfo(menuInfo);
		for (int i = 0; i < 3; i++)
		{
			////垂直居中排列
			myMenu->x = (wnd_width - myMenu->btn_width) / 2;
			myMenu->y = i * (myMenu->btn_height + MENU_SPACE) + (wnd_height - 4 * myMenu->btn_height - 3 * MENU_SPACE) / 2;

			mItem.pos.x = myMenu->x;
			mItem.pos.y = myMenu->y;
			mItem.ItemName = menuItems[i];
			myMenu->AddMenuItem(mItem);
		}
	}

	if (GameState == GAME_ABOUT)
	{
		MENUITEM mItem;
		myMenu->CleraTtems();
		myMenu->btn_width = 180;
		myMenu->btn_height = 57;

		wstring menuItems[] = { L"返回主菜单", L"开始游戏", L"退出游戏" };
		myMenu->SetMenuBkg(L".\\res\\menubkg.jpg", 210);
		myMenu->SetBtnBmp(L".\\res\\recround_180x57.png", myMenu->btn_width, myMenu->btn_height);
		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = myMenu->btn_width;
		menuInfo.height = myMenu->btn_height;
		menuInfo.fontName = L"新宋体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = Color::Yellow;
		menuInfo.focusTextColor = Color::White;
		myMenu->SetMenuInfo(menuInfo);
		for (int i = 0; i < 3; i++)
		{
			//水平居中布局的坐标
			myMenu->x = i * (myMenu->btn_width + MENU_SPACE) + wnd_width / 2 - 280;
			myMenu->y = wnd_height / 5 * 3;

			mItem.pos.x = myMenu->x;
			mItem.pos.y = myMenu->y;
			mItem.ItemName = menuItems[i];
			myMenu->AddMenuItem(mItem);
		}
	}

	if (GameState == GAME_PAUSE)
	{
		MENUITEM mItem;
		myMenu->CleraTtems();
		myMenu->btn_width = 180;
		myMenu->btn_height = 57;

		wstring menuItems[] = { L"返回主菜单", L"继续游戏", L"退出游戏" };
		myMenu->SetMenuBkg(L".\\res\\menubkg.jpg", 210);
		myMenu->SetBtnBmp(L".\\res\\recround_180x57.png", myMenu->btn_width, myMenu->btn_height);
		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = myMenu->btn_width;
		menuInfo.height = myMenu->btn_height;
		menuInfo.fontName = L"新宋体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = Color::Yellow;
		menuInfo.focusTextColor = Color::White;
		myMenu->SetMenuInfo(menuInfo);
		for (int i = 0; i < 3; i++)
		{
			//水平居中布局的坐标
			myMenu->x = i * (myMenu->btn_width + MENU_SPACE) + wnd_width / 2 - 280;
			myMenu->y = wnd_height / 5 * 3;

			mItem.pos.x = myMenu->x;
			mItem.pos.y = myMenu->y;
			mItem.ItemName = menuItems[i];
			myMenu->AddMenuItem(mItem);
		}
	}
}

void myEngine::loadNpc()
{
	int wFrame = 143;
	int hFrame = 84;
	myplayer = new T_Sprite(fishPath[rand() % 6], wFrame, hFrame);

	SPRITEINFO playInfo;
	playInfo.Speed = 8;
	playInfo.X = (wnd_width - wFrame) / 2;
	playInfo.Y = (wnd_height - hFrame) / 2;
	playInfo.Dir = DIR_LEFT;
	playInfo.Ratio = 1.0f;
	playInfo.Visible = true;

	myplayer->Initiate(playInfo);

	for (int i = 0; i < fishNum; i++)
	{
		T_Sprite* npc = new T_Sprite(fishPath[rand() % 6], wFrame, hFrame);
		SPRITEINFO npcInfo;
		npcInfo.Speed = rand() % 4 + 2;
		npcInfo.X = rand() % (wnd_width - wFrame);
		npcInfo.Y = rand() % (wnd_height - hFrame);
		npcInfo.Dir = rand() % 4;
		npcInfo.Ratio = fish_size[rand() % 5];
		npcInfo.Visible = true;

		npc->Initiate(npcInfo);
		vcNpc.push_back(npc);
	}
}

void myEngine::updatePlay()
{
	myplayer->LoopFrame();
	if (myplayer->IsActive() == true)
	{
		int dir = myplayer->GetDir();
		if (dir == DIR_LEFT)
		{
			myplayer->SetPosition(myplayer->GetX() - myplayer->GetSpeed(), myplayer->GetY());
			if (myplayer->GetX() < 0 - myplayer->GetWidth() / 2)
			{
				if (toSenceA == true || (toSenceA == false && toSenceB == false))
				{
					myplayer->SetPosition(0 - myplayer->GetWidth() / 2, myplayer->GetY());
				}
				else
				{
					toSenceB = false;
					if (toSenceA == false)
					{
						toSenceA = true;
						myplayer->SetPosition(wnd_width - myplayer->GetWidth() / 2, myplayer->GetY());
						updateNpcPos = true;
					}
				}

			}
		}
		if (dir == DIR_RIGHT)
		{
			myplayer->SetPosition(myplayer->GetX() + myplayer->GetSpeed(), myplayer->GetY());
			if (myplayer->GetX() > wnd_width - myplayer->GetWidth() / 2)
			{
				if (toSenceB == true)
				{
					myplayer->SetPosition(wnd_width - myplayer->GetWidth() / 2, myplayer->GetY());
				}
				else
				{
					toSenceA = false;
					if (toSenceB == false)
					{
						toSenceB = true;
						updateNpcPos = true;
						myplayer->SetPosition(0 - myplayer->GetWidth() / 2, myplayer->GetY());
					}
				}
			}
		}
		if (dir == DIR_UP)
		{
			myplayer->SetPosition(myplayer->GetX(), myplayer->GetY() - myplayer->GetSpeed());
			if (myplayer->GetY() < 0)
			{
				myplayer->SetPosition(myplayer->GetX(), 0);
			}
		}
		if (dir == DIR_DOWN)
		{
			myplayer->SetPosition(myplayer->GetX(), myplayer->GetY() + myplayer->GetSpeed());
			if (myplayer->GetY() > wnd_height - myplayer->GetHeight())
			{
				myplayer->SetPosition(myplayer->GetX(), wnd_height - myplayer->GetHeight());
			}
		}
	}
}

void myEngine::updateNpc()
{
	vector<T_Sprite*>::iterator it;
	for (it = vcNpc.begin(); it < vcNpc.end(); it++)
	{
		(*it)->LoopFrame();
		if (updateNpcPos == true)
		{
			if (toSenceA == true)
			{
				(*it)->SetPosition((*it)->GetX() + wnd_width, (*it)->GetY());
			}
			if (toSenceB == true)
			{
				(*it)->SetPosition((*it)->GetX() - wnd_width, (*it)->GetY());
			}
			updateNpcPos = false;
		}
		int dir = (*it)->GetDir();
		if (GetTickCount() % 200 == 0)
		{
			(*it)->SetDir(rand() % 4);

		}
		if (dir == DIR_LEFT)
		{
			(*it)->SetPosition((*it)->GetX() - (*it)->GetSpeed(), (*it)->GetY());
			if ((*it)->GetX() < 0)
			{
				(*it)->SetPosition(0, (*it)->GetY());
				(*it)->SetDir(rand() % 4);
			}
		}
		if (dir == DIR_RIGHT)
		{
			(*it)->SetPosition((*it)->GetX() + (*it)->GetSpeed(), (*it)->GetY());
			if ((*it)->GetX() > (2 * wnd_width - ((*it)->GetWidth() / 2)))
			{
				(*it)->SetPosition((2 * wnd_width - ((*it)->GetWidth() / 2)), (*it)->GetY());
				(*it)->SetDir(rand() % 4);
			}
		}
		if (dir == DIR_UP)
		{
			(*it)->SetPosition((*it)->GetX(), (*it)->GetY() - (*it)->GetSpeed());
			if ((*it)->GetY() < 0)
			{
				(*it)->SetPosition((*it)->GetX(), 0);
				(*it)->SetDir(rand() % 4);
			}
		}
		if (dir == DIR_DOWN)
		{
			(*it)->SetPosition((*it)->GetX(), (*it)->GetY() + (*it)->GetSpeed());
			if ((*it)->GetY() > wnd_height - (*it)->GetHeight())
			{
				(*it)->SetPosition((*it)->GetX(), wnd_height - (*it)->GetHeight());
				(*it)->SetDir(rand() % 4);
			}
		}
	}
}

