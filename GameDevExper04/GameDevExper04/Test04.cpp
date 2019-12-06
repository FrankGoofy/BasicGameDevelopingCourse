#include "Test04.h"


int blend =0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LPCTSTR WinTitle = L"ÊµÑéËÄ";
	Test04* test = new Test04(hInstance, WIN_CLASS, WinTitle, NULL, NULL, 1024, 768);
	T_Engine::pEngine = test;
	test->SetFrame(30);
	test->StartEngine();
	return 0;
}

Test04::Test04(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,WORD Icon, WORD SmIcon, int iWidth, int iHeight, COLORREF bkColor):
	T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight, bkColor)
{
	w_width = iWidth;
	w_height = iHeight;
}

Test04::~Test04()
{
}

void Test04::GameInit()
{
}

void Test04::GameLogic()
{
}

void Test04::GameEnd()
{
}

void Test04::GamePaint(HDC hdc)
{
	blend++;
	if (blend > 255)
		blend = 0;
	testAlphaBlen(hdc);

	//testBitBlt(hdc);

	//testBitBlt2(hdc);
	//testStretchBlt(hdc);
}

void Test04::GameKeyAction(int ActionType)
{
}

void Test04::GameMouseAction(int x, int y, int ActionType)
{
}

void Test04::testAlphaBlen(HDC hdc)
{
	BLENDFUNCTION rBlendProps;
	rBlendProps.BlendOp = AC_SRC_OVER;
	rBlendProps.BlendFlags = 0;
	rBlendProps.AlphaFormat = 0;
	rBlendProps.SourceConstantAlpha = 255;

	HDC myhdc = CreateCompatibleDC(hdc);
	wchar_t t[] = L".\\res\\lighttower.bmp";
	LoadBmp(t);
	HBITMAP hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	AlphaBlend(hdc, 0, 0, bmpWidth, bmpHeight, myhdc, 0, 0, bmpWidth, bmpHeight, rBlendProps);
	

	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;

	rBlendProps.SourceConstantAlpha = blend;
	wchar_t t2[] = L".\\res\\fog.bmp";
	LoadBmp(t2);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	AlphaBlend(hdc, 0, 0, bmpWidth, bmpHeight, myhdc, 0, 0, bmpWidth, bmpHeight, rBlendProps);

	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;


	DeleteDC(myhdc);
}

void Test04::testBitBlt(HDC hdc)
{
	HDC myhdc = CreateCompatibleDC(hdc);
	wchar_t t[] = L".\\res\\drop.bmp";
	hBitmap = CreateBlankBMP(hdc, w_width, w_height, RGB(255, 255, 0));
	
	LoadBmp(t);
	HBITMAP hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, 0, 0, w_width/2, w_height/2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;
	DeleteObject(hBitmap);

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t2[] = L".\\res\\island.bmp";
	LoadBmp(t2);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, w_width / 2, 0, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t3[] = L".\\res\\sea.bmp";
	LoadBmp(t3);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, 0, w_height/2, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t4[] = L".\\res\\tulip.bmp";
	LoadBmp(t4);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);

	BitBlt(hdc, w_width/2, w_height / 2, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	DeleteObject(hBitmap);

}

void Test04::testBitBlt2(HDC hdc)
{

	HDC myhdc = CreateCompatibleDC(hdc);
	hBitmap = CreateBlankBMP(hdc, w_width, w_height, RGB(255, 255, 0));
	HBITMAP hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, 0, 0, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;

	hBitmap = CreateBlankBMP(hdc, w_width, w_height, RGB(255, 0, 255));
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, w_width / 2, 0, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;

	hBitmap = CreateBlankBMP(hdc, w_width, w_height, RGB(0, 255, 255));
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, 0, w_height / 2, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;


	hBitmap = CreateBlankBMP(hdc, w_width, w_height, RGB(0, 0, 255));
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	BitBlt(hdc, w_width / 2, w_height / 2, w_width / 2, w_height / 2, myhdc, 0, 0, SRCCOPY);
	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;

	DeleteDC(myhdc);
}

void Test04::testStretchBlt(HDC hdc)
{
	HDC myhdc = CreateCompatibleDC(hdc);
	wchar_t t[] = L".\\res\\drop.bmp";
	LoadBmp(t);
	HBITMAP hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	StretchBlt(hdc, 0, 0, w_width / 2, w_height / 2, myhdc, 0, 0, bmpWidth, bmpHeight, SRCCOPY);
	SelectObject(myhdc, hOld);
	DeleteObject(hBitmap);
	hBitmap = NULL;
	

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t2[] = L".\\res\\island.bmp";
	LoadBmp(t2);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	StretchBlt(hdc, w_width / 2, 0, w_width / 2, w_height / 2, myhdc, 0, 0, bmpWidth, bmpHeight, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t3[] = L".\\res\\sea.bmp";
	LoadBmp(t3);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);
	StretchBlt(hdc, 0, w_height / 2, w_width / 2, w_height / 2, myhdc, 0, 0, bmpWidth, bmpHeight, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	myhdc = CreateCompatibleDC(hdc);
	wchar_t t4[] = L".\\res\\tulip.bmp";
	LoadBmp(t4);
	hOld = (HBITMAP)SelectObject(myhdc, hBitmap);

	StretchBlt(hdc, w_width / 2, w_height / 2, w_width / 2, w_height / 2, myhdc, 0, 0, bmpWidth, bmpHeight, SRCCOPY);
	SelectObject(myhdc, hOld);
	hBitmap = NULL;

	DeleteObject(hBitmap);
}
