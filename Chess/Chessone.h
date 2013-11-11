#include <string>
#include <vector>
using namespace std;

class TFigure {
	public:
		TFigure();
		TFigure(bool, char, int);
		~TFigure();
		string t;
		bool black;
		char l;
		int n;
		virtual bool canKill(char, int) = 0;
};

class TBoard {
public:
        static TBoard& Instance() {
                static TBoard theSingleInstance;
                return theSingleInstance;
        }
        vector <TFigure*> figures;
        bool isFree(char, int) const;
        int numFigures(bool, string) const;
        friend ostream& operator << (ostream& output, const TBoard& other);
private:
        TBoard() {};
        TBoard(const TBoard& root);
        TBoard& operator = (const TBoard&);
};

class THorse : public TFigure {
    public:
        THorse();
        THorse(bool, char, int);
        virtual ~THorse();
        virtual bool canKill(char, int);
};

class TKing : public TFigure {
    public:
        TKing();
        TKing(bool, char, int);
        virtual ~TKing();
        virtual bool canKill(char, int);
        bool canMove(char, int);
        bool check();
        string Result();
};

class TQueen : public TFigure {
    public:
        TQueen();
        TQueen(bool, char, int);
        virtual ~TQueen();
        virtual bool canKill(char, int);
};