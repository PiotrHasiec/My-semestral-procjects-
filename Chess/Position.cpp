#include "Position.h"
#include "Move.h"
#include <vector>
#include <iomanip>
#include <cmath>
#include <set>
#include <algorithm>
#include <limits>
#include "Snapshot.h"
#include "node.h"
#include "Constants.h"
#include "Positional_value.h"
#include <memory>

std::set<Move> Position::pawn_move_normal(int x, int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;
    
    if (color)
    {
        if (in((x - 1), y) and !pos[x - 1][y])
        {
            r.insert(Move(x, y, (x - 1), y, type::Normal));

        }
        if (in((x - 1), (y - 1)) and pos[x - 1][y - 1] and !p_color((x - 1), (y - 1)))
        {
            r.insert(Move(x, y, (x - 1), (y - 1), type::beats));
        }
        if (in((x - 1), (y + 1)) and pos[x - 1][y + 1] and !p_color((x - 1), (y + 1)))
        {
            r.insert(Move(x, y, (x - 1), (y + 1), type::beats));
        }

    }
    else
    {
        if (in((x + 1), y) and !pos[x + 1][y])
        {
            r.insert(Move(x, y, (x + 1), y, type::Normal));
            
        }
        if (in((x + 1), (y + 1)) and pos[x + 1][y + 1] and p_color((x + 1), (y + 1)))
        {
            r.insert(Move(x, y, (x + 1), (y + 1), type::beats));
        }
        if (in((x + 1), (y - 1)) and pos[x + 1][y - 1] and p_color((x + 1), (y - 1)))
        {
            r.insert(Move(x, y, (x + 1), (y - 1), type::beats));
        }

    }
    return r;
}

std::set<Move> Position::pawn_move_2(int x, int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;

    if (color)
    {
        if (in((x - 1), y) and !pos[x - 1][y])
        {
 
            if (in((x - 2), y) and x == 6 and !pos[x - 2][y])
                 r.insert(Move(x, y, (x - 2), y,type::by2));
        }


    }
    else
    {
        if (in((x + 1), y) and !pos[x + 1][y])
        {
           
            if (in((x + 2), y) and x == 1 and !pos[x + 2][y])
                r.insert(Move(x, y, (x + 2), y, type::by2));
        }


    }
    return r;
}

std::set<Move> Position::pawn_move_enpasse(int x, int y)
{
    if (not in(x, y) or enpasse == -1)
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;

    if (color)
    {
        if (( y == (enpasse + 1)or y == (enpasse -1) )and x == 3)
        {
            r.insert(Move(x, y, (x - 1), enpasse, type::Enpasse));

        }
       

    }
    else
    {
        if ((y == (enpasse + 1) or y == (enpasse - 1)) and x == 4)
        {
            r.insert(Move(x, y, (x + 1), enpasse, type::Enpasse));

        }

    }
    return r;
}

std::set<Move> Position::knight_move(int x , int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;

    if (in(x - 1, y - 2) and p_color(x - 1, y - 2) != color)
        r.insert(Move(x, y, (x - 1), (y - 2), type::beats));
    if(in(x - 1, y - 2) and !pos[x - 1][y - 2])
        r.insert(Move(x, y, (x - 1), (y - 2), type::Normal));

    if (in(x + 1, y - 2) and p_color(x + 1, y - 2) != color)
        r.insert(Move(x, y, (x + 1), (y - 2), type::beats));
    if (in(x + 1, y - 2) and !pos[x + 1][y - 2] )
        r.insert(Move(x, y, (x + 1), (y - 2), type::Normal));

    if (in(x - 1, y + 2) and  p_color(x - 1, y + 2) != color)
        r.insert(Move(x, y, (x - 1), (y + 2), type::beats));
    if (in(x - 1, y + 2) and !pos[x - 1][y + 2] )
        r.insert(Move(x, y, (x - 1), (y + 2), type::Normal));

    if (in(x + 1, y + 2) and  p_color(x + 1, y + 2) != color)
        r.insert(Move(x, y, (x + 1), (y + 2), type::beats));
    if (in(x + 1, y + 2) and !pos[x + 1][y + 2] )
        r.insert(Move(x, y, (x + 1), (y + 2), type::Normal));

    if (in(x - 2, y - 1) and (!pos[x - 2][y - 1] or p_color(x - 2, y - 1) != color))
        r.insert(Move(x, y, (x - 2), (y - 1), type::beats));
    if (in(x - 2, y - 1) and (!pos[x - 2][y - 1] or p_color(x - 2, y - 1) != color))
        r.insert(Move(x, y, (x - 2), (y - 1), type::Normal));

    if (in(x + 2, y - 1) and  p_color(x + 2, y - 1) != color)
        r.insert(Move(x, y, (x + 2), (y - 1), type::beats));
    if (in(x + 2, y - 1) and !pos[x + 2][y - 1] )
        r.insert(Move(x, y, (x + 2), (y - 1), type::Normal));

    if (in(x - 2, y + 1) and  p_color(x - 2, y + 1) != color)
        r.insert(Move(x, y, (x - 2), (y + 1), type::beats));
    if (in(x - 2, y + 1) and !pos[x - 2][y + 1] )
        r.insert(Move(x, y, (x - 2), (y + 1), type::Normal));

    if (in(x + 2, y + 1) and  p_color(x + 2, y + 1) != color)
        r.insert(Move(x, y, (x + 2), (y + 1), type::beats));
    if (in(x + 2, y + 1) and !pos[x + 2][y + 1] )
        r.insert(Move(x, y, (x + 2), (y + 1), type::Normal));
    return r;
}

std::set<Move> Position::bishop_move(int x , int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;

    for (int i = 1; in(x + i, y + i); i++)
        if (!pos[x + i][y + i] or p_color(x + i, y + i) != color)
        {
           
            if (pos[x + i][y + i] and p_color(x + i, y + i) != color)
            {
                r.insert(Move(x, y, (x + i), (y + i), type::beats));
                break;
            }
            else
                r.insert(Move(x, y, (x + i), (y + i), type::Normal));
        }
        else
            break;

    for (int i = 1; in(x - i, y + i); i++)
        if (!pos[x - i][y + i] or p_color(x - i, y + i) != color)
        {
            
            if (pos[x - i][y + i] and p_color(x - i, y + i) != color)
            {
                r.insert(Move(x, y, (x - i), (y + i), type::beats));
                break;
            }
            else
                r.insert(Move(x, y, (x - i), (y + i), type::Normal));
        }


        else
            break;

    for (int i = 1; in(x + i, y - i); i++)
        if (!pos[x + i][y - i] or p_color(x + i, y - i) != color)
        {
            
            if (pos[x + i][y - i] and p_color(x + i, y - i) != color)
            {
                r.insert(Move(x, y, (x + i), (y - i), type::beats));
                break;
            }
            r.insert(Move(x, y, (x + i), (y - i), type::Normal));
        }
        else
            break;

    for (int i = 1; in(x - i, y - i); i++)
        if (!pos[x - i][y - i] or p_color(x - i, y - i) != color)
        {
            
            if (pos[x - i][y - i] and p_color(x - i, y - i) != color)
            {
                r.insert(Move(x, y, (x - i), (y - i), type::beats));
                break;
            }
            r.insert(Move(x, y, (x - i), (y - i), type::Normal));
        }
        else
            break;
    
    return r;
}

std::set<Move> Position::rook_move(int x, int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;
    for (int i = 1; in(x + i, y); i++)
        if (!pos[x + i][y] or p_color(x + i, y) != color)
        {
            
            if (pos[x + i][y] and p_color(x + i, y) != color)
            {
                r.insert(Move(x, y, (x + i), (y), type::beats));
                break;
            }
            r.insert(Move(x, y, (x + i), (y), type::Normal));
        }
        else
            break;

    for (int i = 1; in(x - i, y); i++)
        if (!pos[x - i][y] or p_color(x - i, y) != color)
        {
           
            if (pos[x - i][y] and p_color(x - i, y) != color)
            {
                r.insert(Move(x, y, (x - i), (y), type::beats));
                break;
            }
            r.insert(Move(x, y, (x - i), (y), type::Normal));
        }
        else
            break;

    for (int i = 1; in(x, y - i); i++)
        if (!pos[x][y - i] or p_color(x, y - i) != color)
        {
            
            if (pos[x][y - i] and p_color(x, y - i) != color)
            {
                r.insert(Move(x, y, (x), (y - i), type::beats));
                break;
            }
            r.insert(Move(x, y, (x), (y - i), type::Normal));
        }
        else
            break;

    for (int i = 1; in(x, y + i); i++)
        if (!pos[x][y + i] or p_color(x, y + i) != color)
        {
            
            if (pos[x][y + i] and p_color(x, y + i) != color)
            {
                r.insert(Move(x, y, (x), (y + i), type::beats));
                break;
            }
            r.insert(Move(x, y, (x), (y + i), type::Normal));
        }
        else
            break;
    return r;
}

std::set<Move> Position::queen_move(int x , int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    std::set<Move> r = rook_move(x, y);
    std::set<Move> l = bishop_move(x, y);
    r.insert(l.begin(), l.end());
    return r;
   
}

std::set<Move> Position::king_move_normal(int x, int y)
{
    if (not in(x, y))
    {
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r;
    
    if (in(x + 1, y + 1) and !pos[x + 1][y + 1])
        r.insert(Move(x, y, (x + 1), (y + 1)));
    if (in(x + 1, y + 1) and p_color(x + 1, y + 1) != color)
        r.insert(Move(x, y, (x + 1), (y + 1), type::beats));


    if (in(x - 1, y + 1) and !pos[x - 1][y + 1])
        r.insert(Move(x, y, (x - 1), (y + 1)));
    if (in(x - 1, y + 1) and  p_color(x - 1, y + 1) != color)
        r.insert(Move(x, y, (x - 1), (y + 1), type::beats));

    if (in(x + 1, y - 1) and !pos[x + 1][y - 1] )
        r.insert(Move(x, y, (x + 1), (y - 1)));
    if (in(x + 1, y - 1) and  p_color(x + 1, y - 1) != color)
        r.insert(Move(x, y, (x + 1), (y - 1), type::beats));


    if (in(x - 1, y - 1) and !pos[x - 1][y - 1] )
        r.insert(Move(x, y, (x - 1), (y - 1)));
    if (in(x - 1, y - 1) and  p_color(x - 1, y - 1) != color)
        r.insert(Move(x, y, (x - 1), (y - 1), type::beats));


    if (in(x + 1, y) and !pos[x + 1][y] )
        r.insert(Move(x, y, (x + 1), (y)));
    if (in(x + 1, y) and p_color(x + 1, y) != color)
        r.insert(Move(x, y, (x + 1), (y), type::beats));


    if (in(x - 1, y) and !pos[x - 1][y] )
        r.insert(Move(x, y, (x - 1), (y)));
    if (in(x - 1, y) and  p_color(x - 1, y) != color)
        r.insert(Move(x, y, (x - 1), (y), type::beats));


    if (in(x, y - 1) and !pos[x][y - 1] )
        r.insert(Move(x, y, (x), (y - 1)));
    if (in(x, y - 1) and  p_color(x, y - 1) != color)
        r.insert(Move(x, y, (x), (y - 1), type::beats));



    if (in(x, y + 1) and !pos[x][y + 1] )
        r.insert(Move(x, y, (x), (y + 1)));
    if (in(x, y + 1) and  p_color(x, y + 1) != color)
        r.insert(Move(x, y, (x), (y + 1), type::beats));
    return r;
}

std::set<Move> Position::king_catling(int x, int y)
{
    if (not in(x, y) or y != 4 or (x != 0 and x != 7))
    {
        return std::set<Move>();
    }
    std::set<Move> r;
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);//wy³uskanie koloru bierki
    if (color == this->move)
    {
        if(( (OO and color) or (oo and not color) ) and !this->pos[x][y+1] and !this->pos[x][y + 2])
            r.insert(Move(x, y, x, (y + 2),type::Castling_oo));
        if (((OOO and color) or (ooo and not color)) and !this->pos[x][y - 1] and !this->pos[x][y - 2] and !this->pos[x][y - 3])
            r.insert(Move(x, y, x, (y - 2), type::Castling_ooo));
    }
   
    return r;
    
}

Position::Position()
{

    for (int i = 0; i < 8; i++)
    {
        std::vector<int> tmp;
        for (int j = 0; j < 8; j++)
        {
            tmp.push_back(start_poss[i][j]);
        }
        pos.push_back(tmp);
    }

}

Position::Position(Position& position)
{
    this->set_state(position.move, position.OO, position.OOO, position.oo, position.ooo, position.enpasse, position.pos, position.LastMove);
}
Position* Position::make_move(std::string move)
{
    char y1 = static_cast<char>(move[0] - 'a');
    char x1 = 7 - static_cast<char>(move[1] - '1');
    char y2 = static_cast<char>(move[2] - 'a');
    char x2 = 7 - static_cast<char>(move[3] - '1');
    auto tmp = this->pseudolegalmove(x1, y1);
    //bool tmp2 = tmp.count(Move{ x1,y1,x2,y2 });

        
        this->LastMove =  Move{ x1,y1,x2,y2 }.tonot(0);
            this->pos[x2][y2] = this->pos[x1][y1];
            this->pos[x1][y1] = 0;
        
            switch (tmp.find(Move{ x1,y1,x2,y2 })->move_type)
            {
            case type::by2:
                this->enpasse = y1;
                break;

            case  type::Enpasse:
                if (this->move)
                    this->pos[x2 + 1][y2] = 0;
                else
                    this->pos[x2 - 1][y2] = 0;
                break;

            case type::Castling_ooo:
                std::swap(this->pos[x2][y2 - 2], this->pos[x2][y2 + 1]);
                break;

            case type::Castling_oo:
                std::swap(this->pos[x2][y2 - 1], this->pos[x2][y2 + 1]);
                break;

            
            default:
                this->enpasse = -1;
                break;
            }
           
            switch (pos[x2][y2])
            {
            case W_KING:
                this->OOO = this->OO = 0;
                break;
            case B_KING:
                this->ooo = this->oo = 0;
                break;
            case W_PAWN:
                if(x2==0)
                    pos[x2][y2] = piece::W_QUEEN;
                break;
            case B_PAWN:
                if (x2 == 7)
                    pos[x2][y2] = piece::B_QUEEN;
                break;
            case W_ROOK:
                if (x1 == 7 and y1 == 0)
                    this->OOO = 0;
                if (x1 == 7 and y1 == 7)
                    this->OO = 0;
            case B_ROOK:
                if (x1 == 0 and y1 == 0)
                    this->ooo = 0;
                if (x1 == 0 and y1 == 7)
                    this->oo = 0;
            default:
                break;
            }
          

        this->move = !this->move;
        return this;
        

}

Position* Position::make_legal_move(std::string move)
{
    if (move.size() >= 4)
    {
        char y1 = static_cast<char>(move[0] - 'a');
        char x1 = 7 - static_cast<char>(move[1] - '1');
        char y2 = static_cast<char>(move[2] - 'a');
        char x2 = 7 - static_cast<char>(move[3] - '1');
        auto tmp = this->legalmove(x1, y1);
        bool tmp2 = tmp.count(Move{ x1,y1,x2,y2 });

        if (tmp2)
        {

            this->LastMove = Move{ x1,y1,x2,y2 }.tonot(0);
            this->pos[x2][y2] = this->pos[x1][y1];
            this->pos[x1][y1] = 0;

            switch (tmp.find(Move{ x1,y1,x2,y2 })->move_type)
            {
            case type::by2:
                this->enpasse = y1;
                break;

            case  type::Enpasse:
                if (this->move)
                    this->pos[x2 + 1][y2] = 0;
                else
                    this->pos[x2 - 1][y2] = 0;
                break;

            case type::Castling_ooo:
                std::swap(this->pos[x2][y2 - 2], this->pos[x2][y2 + 1]);
                break;

            case type::Castling_oo:
                std::swap(this->pos[x2][y2 - 1], this->pos[x2][y2 + 1]);
                break;


            default:
                this->enpasse = -1;
                break;
            }

            switch (pos[x2][y2])
            {
            case W_KING:
                this->OOO = this->OO = 0;
                break;
            case B_KING:
                this->ooo = this->oo = 0;
                break;
            case W_PAWN:
                if (x2 == 0)
                    pos[x2][y2] = piece::W_QUEEN;
                break;
            case B_PAWN:
                if (x2 == 7)
                    pos[x2][y2] = piece::B_QUEEN;
                break;
            case W_ROOK:
                if (x1 == 7 and y1 == 0)
                    this->OOO = 0;
                if (x1 == 7 and y1 == 7)
                    this->OO = 0;
            case B_ROOK:
                if (x1 == 0 and y1 == 0)
                    this->ooo = 0;
                if (x1 == 0 and y1 == 7)
                    this->oo = 0;
            default:
                break;
            }


            this->move = !this->move;
            return this;

        }
    }
    return nullptr;
}






Snapshot* Position::make_snapshot()
{

    return new Snapshot{ this,this->move, this->OO, this->OOO, this->oo, this->ooo, this->enpasse, this->pos, this->LastMove };

}

void Position::set_state(bool move, bool OO, bool OOO, bool oo, bool ooo, int enpasse, std::vector<std::vector <int>> pos, std::string LastMove)
{
   // mtx_all.lock();
    this->move = move;
    this->OO = OO;
    this->OOO = OOO;
    this->oo = oo;
    this->ooo = ooo;
    this->enpasse = enpasse;
    if(LastMove.size())
        this->LastMove = LastMove;
    this->pos.clear();
   
    for (int i = 0; i < 8; i++)
    {
        std::vector<int> tmp;
        for (int j = 0; j < 8; j++)
        {
            tmp.push_back(pos[i][j]);
        }
       this->pos.push_back(tmp);
    }
    //mtx_all.unlock();
}

void Position::print()
{
   
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << std::setw(3) << pos[i][j];
        }
        std::cout << std::endl;
    }
  
}

std::set<Move> Position::pseudolegalmove(int x, int y)
{
    
    if (not in(x, y))
    {
        
        return std::set<Move>();
    }
    char type = this->pos[x][y] % 8;
    bool color = !(this->pos[x][y] / 8);
    std::set<Move> r, l, s, q;

    if (color == this->move) {
        switch (type)
        {
        case PAWN:
            
            r = pawn_move_2(x, y);
            l = pawn_move_normal(x, y);
            s = pawn_move_enpasse(x, y);
            r.insert(l.begin(), l.end());
            r.insert(s.begin(), s.end());
            
            return r;
            break;
        case KNIGHT:
            return knight_move(x, y);
            
            break;
        case BISHOP:
            return bishop_move(x, y);
            
            break;

        case ROOK:
            return rook_move(x, y);
            
            break;

        case QUEEN:
            
            return queen_move(x, y);
            
            break;

        case KING:
            r = king_move_normal(x, y);
            l = king_catling(x, y);
            r.insert(l.begin(), l.end());
            
            return r;
            break;

        default:
            break;

        }

    }
   
        return r;
       
}

std::set<Move> Position::legalmove(int x, int y)
{
    Position testpos = *this;
    std::unique_ptr<Node> root = nullptr;
    std::vector <  std::set<Move>::iterator > toerase{};
    std::set<Move> legalmove = pseudolegalmove(x,y);
    for (auto i = legalmove.begin(); i != legalmove.end(); i++)
    {

        testpos = *this;
        auto move = *i;
        switch (move.move_type) {

        case(type::Castling_oo):
            if (this->move)
            {
                testpos.make_move("e1f1");
                root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                if (not root->is_legal())
                {
                    toerase.push_back(i);
                    //legalmove.erase(i);
                }
                else {
                    testpos = *this;
                    testpos.make_move("e1g1");
                    root = std::unique_ptr<Node> { new Node{ testpos,testpos.move } };

                    if (not root->is_legal())
                    {
                        toerase.push_back(i);
                        //legalmove.erase(i);
                    }
                }
            }
            else {
                testpos.make_move("e8f8");
                root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                if (not root->is_legal())
                {
                    toerase.push_back(i);
                    //legalmove.erase(i);
                }
                else {
                    testpos = *this;
                    testpos.make_move("e8g8");
                    root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                    if (not root->is_legal())
                    {
                        toerase.push_back(i);
                        //legalmove.erase(i);
                    }
                }
            }
            break;
        case(type::Castling_ooo):
            if (this->move)
            {
                testpos.make_move("e1d1");
                root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                if (not root->is_legal())
                {
                    toerase.push_back(i);
                    //legalmove.erase(i);
                }
                else {
                    testpos = *this;
                    testpos.make_move("e1c1");
                    root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                    if (not root->is_legal())
                    {
                        toerase.push_back(i);
                        //legalmove.erase(i);
                    }
                }
            }
            else {
                testpos.make_move("e8d8");
                root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                if (not root->is_legal())
                {
                    toerase.push_back(i);
                    //legalmove.erase(i);
                }
                else {
                    testpos = *this;
                    testpos.make_move("e8c8");
                    root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                    if (not root->is_legal())
                    {
                        toerase.push_back(i);
                        //legalmove.erase(i);
                    }
                }
            }
            break;
        default:
                testpos.make_move(move.tonot(0));
                root = std::unique_ptr<Node>{ new Node{ testpos,testpos.move } };

                if (not root->is_legal())
                {
                    toerase.push_back(i);
                    //legalmove.erase(i);
                }

                
                break;
        }
    }

    for (auto i = toerase.begin(); i != toerase.end(); i++)
    {
        legalmove.erase(*i);
    }
    return legalmove;
}

bool Position::p_color(int x, int y)
{
    
    if (!in(x, y))
    {
        throw(std::string("not in"));
        
        return 0;
       
    }

    
        return !(this->pos[x][y] / 8);
        
}

bool Position::in(int x, int y)
{
    
    if (x >= 0 and x < 8 and y >= 0 and y < 8)
    {
       
        return true;
    }
    else
    {
       
        return false;
    }
}

float Position::evaluation()
{
    
    float score = 0;
    int w_king = 0;
    int b_king = 0;
    for(int i = 0; i<8; i++)
        for (int j = 0; j < 8; j++)
        {
           int piece = this->pos[i][j];
           if (piece == W_KING)
               w_king = 1;
           if (piece == B_KING)
               b_king = 1;
           if (piece and (piece % 8 - 1) > 0 and (piece % 8 - 1) < 6 )
{
               if ( this->p_color(i,j) )
               {

                   float tmp = static_cast<float> (positional_value[(piece % 8 - 1)][i][j]);
                   score += (pieces_value[piece % 8 - 1] + positional_value[piece % 8 - 1][i][j] / 100);
                   
               }
               else
               {
                   float tmp = positional_value[piece % 8 - 1][8 - i - 1][j];
                   score -= (pieces_value[piece % 8 - 1] + positional_value[piece % 8 - 1][8 - i - 1][j]/100);
               }
           }
        }
    
    if (w_king and !b_king)
        return FLT_MAX;
    else if (!w_king and b_king)
        return -FLT_MAX;
    else if (!w_king and !b_king)
        return 0;
    return score;

}


float Position::gamephase()
{

    float score = 0;
    int w_king = 0;
    int b_king = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int piece = this->pos[i][j];
            if (piece)
            {
                

                    float tmp = static_cast<float> (positional_value[(piece % 8 - 1)][i][j]);
                    score += (pieces_value[piece % 8 - 1] + positional_value[piece % 8 - 1][i][j] / 100);

               
            }
        }

   
    return score;

}

std::vector<int> Position::operator[](int x)
{
   
    auto return_v = pos[x];
    
    return return_v;
}

Position& Position::operator=(const Position& position)
{
    if (&position != this)
    {
        this->set_state(position.move, position.OO, position.OOO, position.oo, position.ooo, position.enpasse, position.pos, position.LastMove);
    }
    return *this;
}

std::string Position::last_move()
{
    
    auto return_v = LastMove;
    
    return return_v;
}

bool Position::is_exist_legal_move()
{
    for(int i = 0; i< 8; i++)
        for(int j = 0; j<8; j++)
        {
            auto legalmoves = this->legalmove(i, j);
            if (legalmoves.begin() != legalmoves.end())
                 return true;

        }
    return false;
}











