
#include "stdafx.h"

#include "Program.h"
#include "mtapi.h"

void initialize()
{
}

static int _mouseX;
static int _mouseY;

static char _pressedChar;

static bool _mousePressed;

void paint()
{
	drawLine(10, 10, _mouseX, _mouseY);

	if(_pressedChar != 0)
	{
		char str[2] = {0};
		str[0] = _pressedChar;

		drawText(100, 100, str, 10);
	}
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

