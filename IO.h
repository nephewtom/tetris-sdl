#ifndef _IO_
#define _IO_

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors

class IO
{
    int width;
    int height;
    Uint8  video_bpp;
    Uint32 videoflags;

public:

    IO(int width, int height);
    void init();
    void toogleFs();

    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void ClearScreen();
    int GetScreenHeight();
    int InitGraph();
    int Pollkey();
    int Getkey();
    int IsKeyDown(int pKey);
    void UpdateScreen();

    void DrawFont();
};

#endif // _IO_
