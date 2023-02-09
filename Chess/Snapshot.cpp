#include "Snapshot.h"
#include "Position.h"
Snapshot::Snapshot(Position* p_pos, bool move, bool OO, bool OOO, bool oo, bool ooo, int enpasse, std::vector<std::vector <int>> pos, std:: string LastMove)
{

    this->move = move;
    this->OO = OO;
    this->OOO = OOO;
    this->oo = oo;
    this->ooo = ooo;
    this->enpasse = enpasse;
    this->position = p_pos;
    this->LastMove = LastMove;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            this->pos[i][j] = pos[i][j];
}


void Snapshot::restore()
{
    if (this)
    {
         this->position->set_state(this->move, this->OO, this->OOO, this->oo, this->ooo, this->enpasse, this->pos, this->LastMove);
       
    }
}