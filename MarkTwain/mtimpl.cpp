
#include "stdafx.h"
#include "mtapi.h"
#include "mtapi_private.h"

static HDC _paintDC;
static HWND _hwnd;

void setHWND(HWND hwnd)
{
	_hwnd = hwnd;
}

void setPaintDC(HDC dc)
{
	_paintDC = dc;
}


void setTimer(int durationInMs)
{
	SetTimer(_hwnd, IDT_TIMER0, durationInMs, NULL);
}

void stopTimer()
{
	KillTimer(_hwnd, IDT_TIMER0);
}


void repaintWindow()
{
	RECT clientRect;
	GetClientRect(_hwnd, &clientRect);

	InvalidateRect(_hwnd, &clientRect, TRUE);

	UpdateWindow(_hwnd);
}

//---------------------------------------------------------------

void drawLine(int x1, int y1, int x2, int y2)
{
	POINT point[2];
	point[0].x = x1;
	point[0].y = y1;
	point[1].x = x2;
	point[1].y = y2;

	Polyline(_paintDC, point, 2);
}

void drawText(int x, int y, char* text, float sizeInPts)
{
	RECT measureRect;
	DrawTextEx(_paintDC, text, strlen(text), &measureRect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE, NULL);


	RECT drawRect;
	drawRect.left = x;
	drawRect.top = y - (measureRect.bottom - measureRect.top);
	drawRect.right = x + (measureRect.right - measureRect.left);
	drawRect.bottom = y;

	DrawTextEx(_paintDC, text, strlen(text), &drawRect, DT_LEFT | DT_SINGLELINE, NULL);

}

