#include "pch.h"
#include "EngineTest.h"

int WINAPI WinMain(
	HINSTANCE h_instance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	LPCTSTR WinTitle = L"T_Engine²âÊÔ³ÌÐò";
	EngineTest* test = new EngineTest(h_instance, WIN_CLASS, WinTitle, NULL, NULL, 800, 600);
	T_Engine::pEngine = test;
	test->SetFrame(10);
	//test->SetFullScreen(TRUE);
	test->StartEngine();
	return true;
}

EngineTest::~EngineTest(void)
{
}

EngineTest::EngineTest(
	HINSTANCE h_instance,
	LPCTSTR sz_winclass,
	LPCTSTR sz_title,
	WORD icon,
	WORD sm_icon,
	int winwidth,
	int winheight) :T_Engine(h_instance, sz_winclass, sz_title, icon, sm_icon, winwidth, winheight)
{
	wnd_width = winwidth;
	wnd_height = winheight;
}

void EngineTest::GameInit()
{
}

void EngineTest::GameLogic()
{
}

void EngineTest::GameEnd()
{
}

void EngineTest::GamePaint(HDC hdc)
{
	HGDIOBJ mbrush;
	HGDIOBJ oldbrush;
	HGDIOBJ mpen;
	HGDIOBJ oldpen;
	RECT mrect;
	int cell_width = wnd_width / 20;
	int cell_height = wnd_height / 20;
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			mpen = CreatePen(PS_SOLID, 0, RGB(240, 240, 240));
			oldpen = SelectObject(hdc, mpen);
			mbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			oldbrush = SelectObject(hdc, mbrush);
			mrect.left = c * cell_width;
			mrect.right = mrect.left + cell_width;
			mrect.top = r * cell_height;
			mrect.bottom = mrect.top + cell_height;
			FillRect(hdc, &mrect, (HBRUSH)mbrush);
			Rectangle(hdc, mrect.left, mrect.top, mrect.right, mrect.bottom);
			SelectObject(hdc, oldbrush);
			DeleteObject(mbrush);
			SelectObject(hdc, oldpen);
			DeleteObject(mpen);
		}
	}
}

void EngineTest::GameKeyAction(int Action)
{
}

void EngineTest::GameMouseAction(int x, int y, int Action)
{
}
