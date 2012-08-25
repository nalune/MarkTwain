#pragma once

void initialize();
void finalize();

void timerTick();

void paint();

void keyDown(char character, int virtualKey);
void keyUp(char character, int virtualKey);

void mouseDown();
void mouseUp();
void mouseMove(int x, int y);
