#include "GraphTest.h"

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
	LPCTSTR WinTitle = L"实验六";
	GraphTest* test = new GraphTest(hInstance, WIN_CLASS, WinTitle, NULL, NULL, 800, 600);
	T_Engine::pEngine = test;
	test->SetFrame(20);
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

}

void GraphTest::GameLogic()
{
	vector<FISH>::iterator it;
	for (it = vecFish.begin(); it < vecFish.end(); it++)
	{
		if (it->fcount < fish_NUM)
		{
			it->fcount += 1;

			//
			it->x = rand() % wnd_width - 30;
			it->y = rand() % wnd_height - 30;
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
	LPCTSTR caption = L"位图模块绘图实验";
	T_Graph::PaintText(hdc, captionRec, caption, 24, L"微软雅黑", Color::White, FontStyleBold, StringAlignmentNear);

	RectF infoRec;
	infoRec.X = 0.00;
	infoRec.Y = (REAL)(wnd_height - 60);
	infoRec.Width = (float)wnd_width;
	infoRec.Height = 60;
	LPCTSTR info = L"班级：软件工程1702班；学号：8002117052；姓名：曾欢；时间：2019年11月1日";
	T_Graph::PaintText(hdc, infoRec, info, 14, L"微软雅黑", Color::White, FontStyleRegular, StringAlignmentCenter);


}

void GraphTest::GameKeyAction(int ActionType)
{


}

void GraphTest::GameMouseAction(int x, int y, int ActionType)
{
}

