
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
	drawLine(10, 10, _mouseX, _mouseY);

	if(_pressedChar != 0)
	{
		char str[2] = {0};
		str[0] = _pressedChar;

		drawText(100, 100, str, 10);
	}

	char str[16] = {0};
	sprintf(str, "%d", _secondElapsed);

	drawText(100, 200, str, 10);
}

void keyDown(char character, int virtualKey)
{
	_pressedChar = character;
	
	repaintWindow();
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

