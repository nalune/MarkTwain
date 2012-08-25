
#include "stdafx.h"

#include "Program.h"
#include "mtapi.h"

void initialize()
{
	setTimer(1000);
}

void finalize()
{
	stopTimer();
}


static int _mouseX;
static int _mouseY;

static char _pressedChar;

static bool _mousePressed;

static int _secondElapsed;

void timerTick()
{
	_secondElapsed++;
	repaintWindow();
}


void paint()
{
	int width = getWindowWidth();
	int height = getWindowHeight();

	int radius = min(width, height) / 2;

	setFill(colorYellow);
	fillCircle(width / 2, height / 2, radius);
	setStroke(colorGreen, 10);
	drawCircle(width / 2, height / 2, radius);

	setFill(colorYellow);
	fillEllipse(200, 200, 350, 250);
	setStroke(colorGreen, 10);
	drawEllipse(200, 200, 350, 250);

	setStroke(colorBlue, 2);

	drawLine(10, 10, _mouseX, _mouseY);

	if(_pressedChar != 0)
	{
		char str[2] = {0};
		str[0] = _pressedChar;

		drawText(100, 100, str, 10, colorWhite, colorBlue);
	}

	char str[256] = {0};
	sprintf(str, "%d - HELLO COMPUTER", _secondElapsed);

	drawText(100, 200, str, 70, colorYellow, colorBlue);

	setFill((_secondElapsed % 2) == 0 ? colorBlue : colorRed);
	fillRectangle(200, 200, 100, 100);
	setStroke(colorGreen, 2);
	drawRectangle(200, 200, 100, 100);
}

void keyDown(char character, int virtualKey)
{
	_pressedChar = character;

	repaintWindow();

	if(virtualKey == VK_END)
		exitApplication();
}

void keyUp(char character, int virtualKey)
{
	_pressedChar = 0;

	repaintWindow();
}

void mouseDown()
{
	_mousePressed = true;
}

void mouseUp()
{
	_mousePressed = false;
}

void mouseMove(int x, int y)
{
	if(_mousePressed)
	{
		_mouseX = x;
		_mouseY = y;

		repaintWindow();
	}
}

