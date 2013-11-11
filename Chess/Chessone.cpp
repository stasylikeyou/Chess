#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Chessone.h"

TFigure::TFigure() 
{
	//constructor
}
TFigure::TFigure(bool black, char l, int n) 
{
    this->black = black;
    this->l = l;
    this->n = n;
}
TFigure::~TFigure() 
{
    //destructor
}

bool TBoard::isFree(char l, int n) const 
{
    if (!((l < 'a') || (l > 'h') || (n > 8) || (n < 1))) 
	{
        for (size_t i = 0; i < figures.size(); i++) 
            if ((figures[i]->l == l) && (figures[i]->n == n)) return false;
        return true;
    }
    else return false;

}
int TBoard::numFigures(bool black, string t) const 
{
    int num = 0;
    for (size_t i = 0; i < figures.size(); i++) 
        if ((figures[i]->black == black) && (figures[i]->t == t)) num++;
    return num;
}

ostream& operator << (ostream& output, const TBoard& other)
{
    bool bool1 = true;
    for (char i = 'a'; i < 'i'; i++) 
	{
        for (int j = 1; j < 9; j++) 
		{
            for (size_t k = 0; k < other.figures.size(); k++) 
			{
                if ((other.figures[k]->l == i) && (other.figures[k]->n == j)) 
				{
                    if (other.figures[k]->t == "Horse") output << "H ";
                    if (other.figures[k]->t == "Queen") output << "Q ";
                    if ((other.figures[k]->t == "King") && (other.figures[k]->black != true)) output << "K ";
                    if ((other.figures[k]->t == "King") && (other.figures[k]->black == true)) output << "k ";
                    bool1 = false;
                }
            }
            if ((bool1 == true) && ((i + j) % 2 == 0)) output << "+ ";
            else if ((bool1 == 1) && !((i + j) % 2 == 0)) output << "- ";
            bool1 = true;
        }
        output << endl;
    }
    return output;
}

THorse::THorse() 
{
    //constructor
}
THorse::THorse(bool black, char l, int n) 
{
    this->black = black;
    this->l = l;
    this->n = n;
    this->t = "Horse";
    if (TBoard::Instance().isFree(l, n) == false)
        throw logic_error("The cell is busy or does not exist");
    TBoard::Instance().figures.push_back(this);
    if (TBoard::Instance().numFigures(black, t) > 2)
        throw logic_error("Can't be more than two horses of the same color");
}
THorse::~THorse() 
{
    //destructor
}
bool THorse::canKill(char l, int n) 
{
     if ((this->l + 2 == l) && (this->n + 1 == n)) return true;
     if ((this->l + 2 == l) && (this->n - 1 == n)) return true;
     if ((this->l - 2 == l) && (this->n + 1 == n)) return true;
     if ((this->l - 2 == l) && (this->n - 1 == n)) return true;
     if ((this->l + 1 == l) && (this->n + 2 == n)) return true;
     if ((this->l + 1 == l) && (this->n - 2 == n)) return true;
     if ((this->l - 1 == l) && (this->n + 2 == n)) return true;
     if ((this->l - 1 == l) && (this->n - 2 == n)) return true;
     return false;
}

TKing::TKing() 
{
    //constructor
}
TKing::TKing(bool black, char l, int n) 
{
    this->black = black;
    this->l = l;
    this->n = n;
    this->t = "King";
    if (TBoard::Instance().numFigures(black, t) > 0)
        throw logic_error("Can't be more than one king of the same color");
    if (TBoard::Instance().isFree(l, n) == false)
        throw logic_error("The cell is busy or does not exist");
    TBoard::Instance().figures.push_back(this);
}
TKing::~TKing() 
{
    //destructor
}
bool TKing::canKill(char l, int n) 
{
     if ((this->l + 1 == l) && (this->n == n)) return true;
     if ((this->l - 1 == l) && (this->n == n)) return true;
     if ((this->l == l) && (this->n + 1 == n)) return true;
     if ((this->l == l) && (this->n - 1 == n)) return true;
     if ((this->l + 1 == l) && (this->n + 1 == n)) return true;
     if ((this->l - 1 == l) && (this->n + 1 == n)) return true;
     if ((this->l + 1 == l) && (this->n - 1 == n)) return true;
     if ((this->l - 1 == l) && (this->n - 1 == n)) return true;
    return false;
}
bool TKing::canMove(char l, int n)
{
    bool bool1;
    for (int i = -1; i < 2; i++) 
	{
        for (int j = -1; j < 2; j++) 
		{
            if ((i != 0) || (j != 0)) 
			{
                if (!((this->l + j < 'a') || (this->l + j > 'h') || (this->n + i > 8) || (this->n + i < 1))) 
				{
                        bool1 = true;
                        for (size_t k = 0; k < TBoard::Instance().figures.size(); k++)
                            if (TBoard::Instance().figures[k]->canKill(l + j, n + i)) bool1 = false;
                        if (bool1 == true) return true;
                }
            }
        }
    }
    return false;
}
bool TKing::check() 
{
    for (size_t i = 0; i < TBoard::Instance().figures.size(); i++)
        if (TBoard::Instance().figures[i]->canKill(this->l, this-> n)) return true;
    return false;
}
string TKing::Result() 
{
    string s;
    if ((this->check() == true) && (this->canMove(this->l, this->n) != true)) s = "It is checkmate";
    else if (this->check() == true) s = "It is check";
        else if (this->canMove(this->l, this->n) != true) s = "It is stalemate";
             else s = "White's king is not in danger";
    return s;
}

TQueen::TQueen() 
{
    //constructor
}
TQueen::TQueen(bool black, char l,int n)
{
    this->black = black;
    this->l = l;
    this->n = n;
    this->t = "Queen";
    if (TBoard::Instance().isFree(l,n) == false)
        throw logic_error("The cell is busy or does not exist");
    TBoard::Instance().figures.push_back(this);
    if (TBoard::Instance().numFigures(black,t) > 1)
        throw logic_error("Can't be more than one queen of the same color");
}
TQueen::~TQueen() 
{
    //destructor
}
bool TQueen::canKill(char l,int n) 
{
     for (int i = 1; i < 8; i++) 
	 {
        if ((this->l + i == l) && (this->n + i == n)) return true;
        if ((this->l + i == l) && (this->n - i == n)) return true;
        if ((this->l - i == l) && (this->n + i == n)) return true;
        if ((this->l - i == l) && (this->n - i == n)) return true;
        if ((this->l + i == l) && (this->n == n)) return true;
        if ((this->l - i == l) && (this->n == n)) return true;
        if ((this->l == l) && (this->n + i == n)) return true;
        if ((this->l == l) && (this->n - i == n)) return true;
     }
     return false;
}