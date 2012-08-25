
#include "stdafx.h"
#include "mtapi.h"
#include "mtapi_private.h"

static HDC _paintDC;
static HWND _hwnd;

static HPEN _currentPen;
static HBRUSH _currentBrush;

void exitApplication()
{
	DestroyWindow(_hwnd);
}


int getWindowWidth()
{
	RECT r;
	GetClientRect(_hwnd, &r);
	return r.right - r.left;
}

int getWindowHeight()
{
	RECT r;
	GetClientRect(_hwnd, &r);
	return r.bottom - r.top;
}


void setHWND(HWND hwnd)
{
	_hwnd = hwnd;
}

void setPaintDC(HDC dc)
{
	if(dc == NULL)
	{
		if(_currentPen != NULL)
		{
			DeleteObject(_currentPen);
			_currentPen = NULL;
		}

		if(_currentBrush != NULL)
		{
			DeleteObject(_currentBrush);
			_currentBrush = NULL;
		}
	}

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

	InvalidateRect(_hwnd, &clientRect, FALSE);

	UpdateWindow(_hwnd);
}

//---------------------------------------------------------------




void setStroke(color c, int thickness)
{
	if(_currentPen != NULL)
		DeleteObject(_currentPen);

	_currentPen = CreatePen(PS_SOLID, thickness, c);

	SelectObject(_paintDC, _currentPen);
}

void setFill(color c)
{
	if(_currentBrush != NULL)
		DeleteObject(_currentBrush);

	_currentBrush = CreateSolidBrush(c);

	SelectObject(_paintDC, _currentBrush);
}

void drawLine(int x1, int y1, int x2, int y2)
{
	POINT point[2];
	point[0].x = x1;
	point[0].y = y1;
	point[1].x = x2;
	point[1].y = y2;

	Polyline(_paintDC, point, 2);
}

void drawRectangle(int x, int y, int width, int height)
{
	POINT point[5];
	point[0].x = x;
	point[0].y = y;

	point[1].x = x + width;
	point[1].y = y;

	point[2].x = x + width;
	point[2].y = y + height;

	point[3].x = x;
	point[3].y = y + height;

	point[4].x = x;
	point[4].y = y;

	Polyline(_paintDC, point, 5);
}

void ensureBrushCreated()
{
	if(_currentBrush == NULL)
		setFill(colorBlack);
}

void fillRectangle(int x, int y, int width, int height)
{
	RECT r;
	r.left = x;
	r.top = y;
	r.right = x + width;
	r.bottom = y + height;

	ensureBrushCreated();
	FillRect(_paintDC, &r, _currentBrush);
}

void drawEllipse(int x, int y, int width, int height)
{
	Arc(_paintDC, x, y, x + width, y + height, x + width / 2, y, x + width / 2, y);
}

void fillEllipse(int x, int y, int width, int height)
{
	ensureBrushCreated();

	LOGBRUSH logBrush;
	GetObject(_currentBrush, sizeof(LOGBRUSH), &logBrush);
	COLORREF brushColor = logBrush.lbColor;

	HPEN p = CreatePen(PS_SOLID, 1, brushColor);

	HPEN old = (HPEN)SelectObject(_paintDC, p);

	Ellipse(_paintDC, x, y, x + width, y + height);

	SelectObject(_paintDC, old);
	DeleteObject(p);
}

void drawCircle(int xCenter, int yCenter, int radius)
{
	drawEllipse(xCenter - radius, yCenter - radius, radius * 2, radius * 2);
}

void fillCircle(int xCenter, int yCenter, int radius)
{
	fillEllipse(xCenter - radius, yCenter - radius, radius * 2, radius * 2);
}

void drawText(int x, int y, char* text, int sizeInPts, color backgroundColor, color textColor)
{
	int h = -MulDiv(sizeInPts, GetDeviceCaps(_paintDC, LOGPIXELSY), 72);

	HFONT font = CreateFont(h,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
									CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Terminal"));
    
	HFONT oldFont = (HFONT)SelectObject(_paintDC, font);

	SetBkColor(_paintDC, backgroundColor);
	SetTextColor(_paintDC, textColor);

	RECT measureRect;
	DrawTextEx(_paintDC, text, strlen(text), &measureRect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE, NULL);


	RECT drawRect;
	drawRect.left = x;
	drawRect.top = y - (measureRect.bottom - measureRect.top);
	drawRect.right = x + (measureRect.right - measureRect.left);
	drawRect.bottom = y;

	DrawTextEx(_paintDC, text, strlen(text), &drawRect, DT_LEFT | DT_SINGLELINE, NULL);

	SelectObject(_paintDC, oldFont);
	DeleteObject(font);

}

