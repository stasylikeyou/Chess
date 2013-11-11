#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include "Chessone.h"

int main()
{
	setlocale(0, "");
	bool black=true;
	bool white=false;
	TKing bKing(black,'c', 6);
	THorse bHorse1(black,'d', 3);
	THorse bHorse2(black,'b', 8);
	TQueen bQueen(black,'b', 5);
    TKing wKing(white,'a', 2);
    cout << TBoard::Instance();
    cout << endl << wKing.Result() << endl << endl;
	getch(); 
}