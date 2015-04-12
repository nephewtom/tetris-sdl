#include "IO.h"
#include <SDL/SDL_ttf.h>

static TTF_Font* fntCourier;
static SDL_Surface *sText;
static SDL_Surface *mScreen;
static Uint32 mColors [COLOR_MAX] = {0x000000ff, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
                                     0x00ffffff, 0xff00ffff, 0xffff00ff, 0xffffffff};
/*
  ======================================
  Init
  ======================================
*/
IO::IO(int width, int height)
{
    this->width = width;
    this->height = height;

    init();

    // Alpha blending doesn't work well at 8-bit color
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    if ( info->vfmt->BitsPerPixel > 8 ) {
        video_bpp = info->vfmt->BitsPerPixel;
    } else {
        video_bpp = 16;
    }

    // Set 640x480 video mode
    videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
    if ( (mScreen=SDL_SetVideoMode(width, height, video_bpp, videoflags)) == NULL ) {
        fprintf(stderr, "Couldn't set %ix%i video mode: %s\n", width, height, SDL_GetError());
        return;
    }
    return;
}

void IO::init() {

    // Initialize SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
        return;
    }
    if (TTF_Init() == -1) {
        printf("Error in TTF_Init\n");

    }
    fntCourier = TTF_OpenFont( "cour.ttf", 12 );
    if (fntCourier == NULL) {
        printf("Bad font!\n");
    }

    atexit(SDL_Quit);
}

void IO::DrawFont() {

    SDL_Color clrFg = {0,255,255,0};
    sText = TTF_RenderText_Solid( fntCourier, "1234567890", clrFg );

    SDL_Rect rcDest = {30,30,0,0};
    SDL_BlitSurface(sText, NULL, mScreen, &rcDest);
    SDL_FreeSurface( sText );
    //boxColor (mScreen, 0, 0, 20, 20, mColors[YELLOW]);
}

void IO::toogleFs() {

}

/*
  ======================================
  Clear the screen to black
  ======================================
*/
void IO::ClearScreen()
{
    boxColor (mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
}

/*
  ======================================
  Draw a rectangle of a given color

  Parameters:
  >> pX1, pY1: 		Upper left corner of the rectangle
  >> pX2, pY2: 		Lower right corner of the rectangle
  >> pC				Rectangle color
  ======================================
*/
void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    boxColor (mScreen, pX1, pY1, pX2, pY2-1, mColors[pC]);
}


/*
  ======================================
  Return the screen height
  ======================================
*/
int IO::GetScreenHeight()
{
    return mScreen->h;
}


/*
  ======================================
  Update screen
  ======================================
*/
void IO::UpdateScreen()
{
    SDL_Flip(mScreen);
}


/*
  ======================================
  Keyboard Input
  ======================================
*/
int IO::Pollkey()
{
    SDL_Event event;
    while ( SDL_PollEvent(&event) ) {
        switch (event.type) {
        case SDL_KEYDOWN:
            return event.key.keysym.sym;
        case SDL_QUIT:
            exit(3);
        }
    }
    return -1;
}

/*
  ======================================
  Keyboard Input
  ======================================
*/
int IO::Getkey()
{
    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
        if (event.type == SDL_QUIT)
            exit(3);
    };
    return event.key.keysym.sym;
}

/*
  ======================================
  Keyboard Input
  ======================================
*/
int IO::IsKeyDown (int pKey)
{
    Uint8* mKeytable;
    int mNumkeys;
    SDL_PumpEvents();
    mKeytable = SDL_GetKeyState(&mNumkeys);
    return mKeytable[pKey];
}
