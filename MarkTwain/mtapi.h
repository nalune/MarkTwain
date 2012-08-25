#pragma once

void exitApplication();

void repaintWindow();

int getWindowWidth();
int getWindowHeight();

void setWindowWidth(int value);
void setWindowHeight(int value);

void drawLine(int x1, int y1, int x2, int y2);
void drawText(int x, int y, char* text, float sizeInPts);