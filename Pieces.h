#ifndef _PIECES_
#define _PIECES_

enum BlockType { NO_BLOCK = 0, NORMAL_BLOCK = 1, PIVOT_BLOCK = 2 };

class Pieces
{
public:

    int GetBlockType(int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition (int pPiece, int pRotation);
    int GetYInitialPosition (int pPiece, int pRotation);
};

#endif // _PIECES_
