#pragma once


void exitApplication();

void setTimer(int durationInMs);
void stopTimer();

void repaintWindow();

int getWindowWidth();
int getWindowHeight();

enum color
{
	colorBlack = RGB(0,0,0),
	colorBlue = RGB(0,0,255),
	colorGreen = RGB(0,255,0),
	colorRed = RGB(255,0,0),
	colorWhite = RGB(255,255,255),
	colorMagenta = RGB(255,0,255),
	colorYellow = RGB(255,255,0),
	colorCyan = RGB(0,255,255)
};

void setStroke(color c, int thickness);
void setFill(color c);

void drawLine(int x1, int y1, int x2, int y2);

void drawRectangle(int x, int y, int width, int height);
void fillRectangle(int x, int y, int width, int height);

void drawEllipse(int x, int y, int width, int height);
void fillEllipse(int x, int y, int width, int height);

void drawCircle(int xCenter, int yCenter, int radius);
void fillCircle(int xCenter, int yCenter, int radius);

void drawText(int x, int y, char* text, int sizeInPts, color backgroundColor, color textColor);
