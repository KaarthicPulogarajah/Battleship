//Kaarthic Pulogarajah
//Battleship
#include <iostream>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <unordered_map>
#include <algorithm>
// #include <string>
// #define _WIN32_WINNT 0x0500
// #include <cstdlib>
// #include <time.h>
// #include <stdlib.h>
using namespace std;

class Ship {
	protected:
		int spaces, numHit;
		string name, letter;
		string startCoor;
		bool sunk;
	public:
		Ship (int spaces, string name){
			this-> spaces = spaces;
			this-> name = name;
			letter = name[0];
			sunk = false;
			numHit = 0;
		}

		int getSpaces(){return spaces;}
		string getName(){return name;}
		string getLetter(){return letter;}
		void sink(){sunk = true;}
		bool isSunk(){return sunk;}
		void hit(int numHit){this -> numHit = numHit;}
		int getHits(){return numHit;}
		
		virtual void setStart(string startCoor){};
		virtual void setStart(int i , int j){};	
		
};

class PlayerShip : public Ship
{
	private:
		string startCoor;
	public:
		PlayerShip (int spaces, string name): Ship(spaces, name){}
		void setStart (string startCoor){this -> startCoor = startCoor;}
		string getstartCoor(){return startCoor;}
};

class CpuShip : public Ship
{
	private:
		int startCoor[2];
	public:
		CpuShip (int spaces, string name): Ship(spaces, name){}
		void setStart(int i, int j){
			this -> startCoor[0] = i;
			this -> startCoor[1] = j;
		}
		int * getstartCoor(){return startCoor;}
};

static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void ScreenSize ();
void print (string grid[10][10]);
void restore (string grid[10][10]);
string getCoor();
string guess (string player[10][10], string grid[10][10]);
bool check (string grid[10][10], string x);
void randomCoor(string grid[10][10], int &r, int &c);
void count(string grid[10][10], Ship * ShipToCount);
int winCondition(string grid[10][10], int person);

int main()
{
	char replay;
	
	do{
		system("cls");
		ScreenSize();
		SetConsoleTitle("Battleship");

		PlayerShip AircraftCarrier(5,"Aircraft Carrier");
		PlayerShip Battleship(4,"Battleship");
		PlayerShip Submarine(3,"Submarine");
		PlayerShip Cruiser(3,"Cruiser");
		PlayerShip Destroyer(2,"Destroyer");
		PlayerShip ShipListPlayer[5] = {AircraftCarrier, Battleship, Submarine, Cruiser, Destroyer};

		//map spaces to coordinate
		unordered_map<string, string> gameMap;
		for (int i = 0 ; i < 10 ; i++){
			for (int j = 0 ; j < 10 ; j++){	
				char lett = i+65;
				string letter(1,lett);
				gameMap.insert({letter+to_string(j+1), to_string(i)+to_string(j)});		
			}
		}
		
		string game[10][10];
		string player[10][10];
		
		restore(game);
		restore(player);
		
		string startCoor;
		char orientation, redo = 'R';
		bool occupied = false;

		cout << "YOU ARE PLAYING BATTLESHIP\n\nYou have 5 ships:\nAircraftCarrier\t 5 spaces\nBattleship\t "<<
		"4 spaces\nSubmarine\t 3 spaces\nCruiser\t\t 3 spaces\nDestroyer\t 2 spaces\n\n\n";
	// goto cpugo;

		// player input to place ships
		do 
		{
			int i,j;
			restore(game);
			print(game);
			
			for (int q = 0 ; q < 5 ; q++)
			{
				cout << "\n\nWhere will you place the ";
				cout << ShipListPlayer[q].getName() << "? " << ShipListPlayer[q].getSpaces()<<" spaces \nEnter starting coordinate: ";
				
				// loop until valid placement is chosen
				do{

					if (occupied)
					{
						cout << "\nNot enough space";
						cout << "\nEnter starting coordinate: ";
					}
					// cin >> startCoor;
					startCoor = getCoor();

					while (!check(game, startCoor))
					{
						cout << "\nIncorrect coordinate, try again: ";
						// cin >> startCoor;
						startCoor = getCoor();
					}
					
					do
					{
						cout << "\nPlace horizontally or vertically? Enter V/H: ";
						cin >> orientation;
					}
					while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v');
					
					i = gameMap.at(startCoor)[0] -'0';
					j = gameMap.at(startCoor)[1] -'0';
					occupied = false;
					
					//check if other ships or board edge is in the way
					if (orientation == 'h' || orientation == 'H')
					{
						for (int k = 0 ; k < ShipListPlayer[q].getSpaces() ; k++)
						{   
							if (j+ShipListPlayer[q].getSpaces()-1 > 9 && !occupied)
								occupied = true;
							else if (game[i][j+k].length () == 1) occupied = true;
						}       
					}

					else if (orientation == 'v' || orientation == 'V')
					{
						for (int k = 0 ; k < ShipListPlayer[q].getSpaces() ; k++)
						{
							if (i+ShipListPlayer[q].getSpaces()-1 > 9 && !occupied)
								occupied = true;
							else if (game[i+k][j].length () == 1) occupied = true;
						}
					}
				}
				while (occupied);

				// place ships if no problems encountered
				if (orientation == 'h' || orientation == 'H')
					for (int k = 0 ; k < ShipListPlayer[q].getSpaces() ; k++)
						game[i][j+k] = ShipListPlayer[q].getLetter();
				else if (orientation == 'v' || orientation == 'V')
					for (int k = 0 ; k < ShipListPlayer[q].getSpaces() ; k++)
						game[i+k][j] = ShipListPlayer[q].getLetter();

				Ship *CurrentShip;
				CurrentShip = &ShipListPlayer[q];
				CurrentShip->setStart(startCoor); 
				
				print(game);
			}
			
			cout << "\nIf you want to rearrange your ships, press 'r', or press any letter to continue\n";
			cin >> redo;
			
		}
		while (redo == 'r' || redo == 'R');
		
	cpugo:

		// CPU ship placement
		string CPU[10][10];
		restore(CPU);
		srand(time(NULL));
		
		cout << "\nCPU setting up ships...\n";
		CpuShip AircraftCarrierCPU(5,"Aircraft Carrier");
		CpuShip BattleshipCPU(4,"Battleship");
		CpuShip SubmarineCPU(3,"Submarine");
		CpuShip CruiserCPU(3,"Cruiser");
		CpuShip DestroyerCPU(2,"Destroyer");
		CpuShip ShipListCpu[5] = {AircraftCarrierCPU, BattleshipCPU, SubmarineCPU, CruiserCPU, DestroyerCPU};

		int oriCPU,rowCPU, colCPU;
		int *coor;
		oriCPU = rand() % 2; // 0 is horizontal, 1 is vertical
		
		bool f, xyz;
		for (int q = 0 ; q < 5 ; q++){
			
			// generate orientation for ship
			oriCPU = rand() % 2;

			if (oriCPU == 0)
			{
				do
				{
					randomCoor(CPU, rowCPU, colCPU);
					f = true;
					xyz = false;
					
					// make sure no other ships are in the way
					for (int i = 0 ; i < ShipListCpu[q].getSpaces() ; i++)
						if (CPU[rowCPU][colCPU+i].length () == 1)
							f = false;
					
					// make sure ship stays in board
					if (colCPU + ShipListCpu[q].getSpaces()-1 < 10 && f)
					{
						for (int j = 0 ; j < ShipListCpu[q].getSpaces() ; j++)
							CPU[rowCPU][colCPU+j] = ShipListCpu[q].getLetter();
					}
					else
						xyz = true;

				}
				while (colCPU + ShipListCpu[q].getSpaces()-1 > 9 || xyz);
				
			}
			else if (oriCPU == 1)
			{
				do
				{
					randomCoor(CPU, rowCPU, colCPU);
					f = true;
					xyz = false;
					
					for (int i = 0 ; i < ShipListCpu[q].getSpaces() ; i++)
						if (CPU[rowCPU+i][colCPU].length () == 1)
							f = false;
					
					if (rowCPU + ShipListCpu[q].getSpaces()-1 < 10 && f)
					{
						for (int j = 0 ; j < ShipListCpu[q].getSpaces() ; j++)
							CPU[rowCPU+j][colCPU] = ShipListCpu[q].getLetter();
					}
					else
						xyz = true;
				}
				while (rowCPU + ShipListCpu[q].getSpaces()-1 > 9 || xyz);
			}
			
			Ship * CurrentShip;
			CurrentShip = &ShipListCpu[q];
			CurrentShip->setStart(rowCPU,colCPU);

			coor = ShipListCpu[q].getstartCoor();
		} 
		
		//let the player make guesses
		system("cls");
		string playerGuess;
		string temp = " ";
		cout << "\t\t\t    LET THE GAME BEGIN\n\n";
		print(player);
		int totalPlayer,totalCPU, totA = 0, totB = 0, totC = 0, totD = 0, totS = 0;
		int cpuA = 0, cpuB = 0, cpuC = 0, cpuD = 0, cpuS = 0;
		bool heat = false;
		
		do
		{
			//player's turn
			playerGuess = guess(player,CPU);
			int i = gameMap.at(playerGuess)[0] -'0';
			int j = gameMap.at(playerGuess)[1] -'0';
			if (CPU[i][j].length () == 1)
			{
				cout << "\nHit!";
				player[i][j] = " X";
				CPU[i][j] = "X";
				for (int q = 0 ; q < 5 ; q++)
					count(CPU, &ShipListCpu[q]);
			}
			else
			{
				cout << "\nMiss!";
				player[i][j] = " O";
			}
			totalPlayer = winCondition(CPU,1);
			
			Sleep(100);
			
			//CPU's turn
			int r,c;
			bool lock = false;
			if (totalPlayer != 0)
			{
				cout <<"\nCPU's Target: ";
				if (!heat)
					randomCoor(game, r, c);
				else
				{
					for (int i = 0 ; i < 10 ; i++)
					{
						for (int j = 0; j < 10 ; j++)
						{
							if (game[i][j] == temp && !lock)
							{
								r = i;
								c = j;
								lock = true;
							}
							else if (!lock)
							{
								randomCoor(game, r, c);
								heat = false;
							}
						}
					}
				}
				
				// display CPU target
				string value = to_string(r)+to_string(c);
				auto it = find_if(gameMap.begin(), gameMap.end(),[&value](const pair<string, string> &p) {return p.second == value;});
				cout << it -> first;
				
				Sleep(500);
				if (game[r][c].length () == 1)
				{
					cout << "\nHit!";
					temp = game[r][c];
					game[r][c] = " X";
					heat = true;
					for (int q = 0 ; q < 5 ; q++)
						count(game, &ShipListPlayer[q]);
				}
				else
				{
					cout << "\nMiss!";
					game[r][c] = " O";
				}
				
				Sleep(100);
				cout << endl;
				cout << endl;
				print(game);
				cout << endl;
				totalCPU = winCondition(game,2);
				if (totalCPU != 0)
					system("pause");
			}
			
			// continue game if both player and CPU have ships left
			if (totalCPU != 0 && totalPlayer != 0)
			{
				system("cls");
				print(player);
			}
		}
		while (totalPlayer != 0 && totalCPU != 0);
	
		cout << "\n\nPress 'r' to play again, or press any letter to quit\n";
		cin >> replay;
	}
	while(replay == 'r' || replay == 'R');
	
    return 0;
}

// set screen size
void ScreenSize (){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, 20, 700, 900, TRUE);
}

// print board with appropriate colour
void print (string grid[10][10]){
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j <10 ; j++)
        {
			string coor = grid[i][j];
			
            if (coor == "A")
            {
                SetConsoleTextAttribute(h,11);
                cout << coor << "\t";
            }
            else if (coor == " X")
            {
                SetConsoleTextAttribute(h,12);
                cout << coor << "\t";
            }
            else if (coor == "B")
            {
                SetConsoleTextAttribute(h,9);
                cout << coor << "\t";
            }
            else if (coor == "C")
            {
                SetConsoleTextAttribute(h,14);
                cout << coor << "\t";
            }
            else if (coor == "D")
            {
                SetConsoleTextAttribute(h,10);
                cout << coor << "\t";
            }
            else if (coor == "S")
            {
                SetConsoleTextAttribute(h,13);
                cout << coor << "\t";
            }
            else if (coor == " O")
            {
                SetConsoleTextAttribute(h,15);
                cout << coor << "\t";
            }
            else
            {
                SetConsoleTextAttribute(h,7);
                cout << coor << "\t";
            }
        }
        cout << endl << endl;;
    }
    SetConsoleTextAttribute(h,7);
}

// reset board
void restore (string grid[10][10]){
	for (int i = 0 ; i < 10 ; i++){
		for (int j = 0 ; j < 10 ; j++){	
			char lett = i+65;
			string letter(1,lett);
			grid[i][j] = letter+to_string(j+1);
		}
	} 
}

// get user coordinates
string getCoor()
{
	string startCoor = "";
	char charOne,charTwo,charThree;
	
	charOne = getch();
	cout << charOne;
	charTwo = getch();
	cout << charTwo;
	charThree = getch();
	if (int(charThree) > 47)
	{
		cout << charThree;
		getch();
	}
	
	if(int(charOne) > 96)
		startCoor.push_back(char(charOne-32));
	else
		startCoor.push_back(char(charOne));
	startCoor.push_back(charTwo);
	startCoor.push_back(charThree);
	
	if (int(charThree) < 48)
		startCoor.pop_back();
	if (int(charOne) == 3 || int(charTwo) == 3 || int(charThree) == 3)
		exit(EXIT_FAILURE);

	return startCoor;
}

// ensure valid input from user
string guess (string player[10][10], string grid[10][10]){
    string target;
    bool here;

    do
    {
        cout << "\nChoose a valid target: ";
        target = getCoor();
		// cin >> target;
        if (target == "!!")
		{
			cout << endl;
            print(grid);
		}
        here = false;
        for (int i = 0 ; i < 10 ; i++)
            for (int j = 0 ; j <10 ; j++)
                if (player[i][j] == target)
					here = true;
    }
    while (!here);
    return target;
}

// check if string is in board
bool check (string grid[10][10], string x){
    bool temp = false;
    for (int i = 0 ; i < 10 ; i++)
        for (int j = 0 ; j < 10 ; j++)
            if (grid[i][j] == x && grid[i][j].length () > 1)
                temp = true;
	
    return temp;
}

// generate random coordinate for cpu 
void randomCoor(string grid[10][10], int &r, int &c){
	srand(time(NULL));
	do
	{
		r = rand() % 10;
		c = rand() % 10;
	}
	while (grid[r][c] == " O" || grid [r][c] == " X");
}

// determine if ship has been sunk
void count(string CPU[10][10], Ship * ShipToCount){
	int num = 0;
	// bool flag = true;
	for (int i = 0 ; i < 10 ; i++)
		for (int j = 0; j <10 ; j++)
			if (CPU[i][j] == ShipToCount->getLetter() && !ShipToCount->isSunk())
				num++;
		
	ShipToCount->hit(ShipToCount->getSpaces()-num);
	if(ShipToCount->getSpaces() == ShipToCount->getHits() && !ShipToCount->isSunk())
	{
		ShipToCount->sink();
		cout << "\nACHEIVEMENT: " << ShipToCount->getName() << " has been sunk!";
	}
}

// check if there is a winner
int winCondition (string grid[10][10], int person){
    int countA = 0, countB = 0, countC = 0, countD = 0, countS = 0;
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j <10 ; j++)
        {
            if (grid[i][j] == "A")			countA++;
            else if (grid[i][j] == "B")		countB++;
            else if (grid[i][j] == "C")		countC++;
            else if (grid[i][j] == "D")		countD++;
            else if (grid[i][j] == "S")		countS++;
        }
    }
    int total = countA+countB+countC+countD+countS;
    if (total == 0)
	{
		if (person == 1)	cout << "\n\nYOU WIN!";
		else cout << "\n\nYOU LOSE!";
	}
    Sleep(500);
    return total;
}
