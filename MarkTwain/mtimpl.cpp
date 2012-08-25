
#include "stdafx.h"
#include "mtapi.h"
#include "mtapi_private.h"

static HDC _paintDC;

void setPaintDC(HDC dc)
{
	_paintDC = dc;
}

void repaintWindow()
{
	HWND hwnd = GetForegroundWindow();

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	InvalidateRect(hwnd, &clientRect, TRUE);

	UpdateWindow(hwnd);
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
	// hello

	RECT measureRect;
	DrawTextEx(_paintDC, text, strlen(text), &measureRect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE, NULL);


	RECT drawRect;
	drawRect.left = x;
	drawRect.top = y - (measureRect.bottom - measureRect.top);
	drawRect.right = x + (measureRect.right - measureRect.left);
	drawRect.bottom = y;

	DrawTextEx(_paintDC, text, strlen(text), &drawRect, DT_LEFT | DT_SINGLELINE, NULL);

}

