#include "Game.h"

int main()
{
    // Class for drawing staff, it uses SDL for the rendering. Change the methods of this class
    // in order to use a different renderer

    int WAIT_TIME = 700;                   // Number of milliseconds that the piece remains before going 1 block down */
    bool pause=false;

    int w=640; int h=480;
    IO mIO(w, h);
    int mScreenHeight = mIO.GetScreenHeight();

    Pieces mPieces;
    Board mBoard (&mPieces, mScreenHeight);
    Game mGame (&mBoard, &mPieces, &mIO, mScreenHeight);

    // Get the actual clock milliseconds (SDL)
    unsigned long mTime1 = SDL_GetTicks();


    // ----- Main Loop -----
    while (!mIO.IsKeyDown (SDLK_ESCAPE)) {

        // ----- Draw -----
        mIO.ClearScreen (); 		// Clear screen
        mGame.DrawScene ();			// Draw staff
        mIO.UpdateScreen ();		// Put the graphic context in the screen

        // ----- Input -----
        int mKey = mIO.Pollkey();

        switch (mKey) {


        case (SDLK_p): {
            if (pause) {
                WAIT_TIME = 700;
            } else {
                WAIT_TIME = 120000;
            }
            pause = !pause;
            break;
        }

        case (SDLK_RIGHT): {
            if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
                mGame.mPosX++;
            }
            mGame.printPos();
            break;
        }

        case (SDLK_LEFT): {
            if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
                mGame.mPosX--;
            }
            mGame.printPos();
            break;
        }

        case (SDLK_DOWN): {
            if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
                mGame.mPosY++;
            }
            mGame.printPos();
            break;
        }

        case (SDLK_SPACE): {
            // Check collision from up to down
            while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
                mGame.mPosY++;
            }
            mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);
            mBoard.DeletePossibleLines ();

            if (mBoard.IsGameOver()) {
                mIO.Getkey();
                exit(0);
            }
            mGame.printPos();
            mGame.CreateNewPiece();

            break;
        }

        case (SDLK_UP): {
            if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
                mGame.mRotation = (mGame.mRotation + 1) % 4;

            break;
        }
        }

        // ----- Vertical movement -----

        unsigned long mTime2 = SDL_GetTicks();

        if ((mTime2 - mTime1) > WAIT_TIME) {
            if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
                mGame.mPosY++;
                mGame.printPos();
            }
            else {
                mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                mBoard.DeletePossibleLines ();

                if (mBoard.IsGameOver()) {
                    mIO.Getkey();
                    exit(0);
                }

                mGame.CreateNewPiece();
            }

            mTime1 = SDL_GetTicks();
        }
    }

    return 0;
}
