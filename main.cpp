//Kaarthic Pulogarajah
//Battleship
#include <iostream>
#include <conio.h>
#include <string>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
using namespace std;
int keepCountPlayer(string a[10][10]);
int keepCountCpu(string a[10][10]);
int countA (string a[10][10]);
int countB (string a[10][10]);
int countC (string a[10][10]);
int countD (string a[10][10]);
int countS (string a[10][10]);
string guess (string player[10][10], string a[10][10]);
void ScreenSize ()
{
HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r); //stores the console's current dimensions

  //MoveWindow(window_handle, x, y, width, height, redraw_window);
  MoveWindow(console, r.left, r.top, 800, 600, TRUE);
}
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void print (string a[10][10])
{
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j <10 ; j++)
        {
            if (a[i][j] == "A")
            {
                SetConsoleTextAttribute(h,11);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == " X")
            {
                SetConsoleTextAttribute(h,12);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == "B")
            {
                SetConsoleTextAttribute(h,9);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == "C")
            {
                SetConsoleTextAttribute(h,14);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == "D")
            {
                SetConsoleTextAttribute(h,10);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == "S")
            {
                SetConsoleTextAttribute(h,13);
                cout << a[i][j] << "\t";
            }
            else if (a[i][j] == " O")
            {
                SetConsoleTextAttribute(h,15);
                cout << a[i][j] << "\t";
            }
            else
            {
                SetConsoleTextAttribute(h,7);
                cout << a[i][j] << "\t";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(h,7);
}

int check (string a[10][10], string x);

int main()
{
    ScreenSize();
    SetConsoleTitle("Battleship");

    string game[10][10] = {{"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10"},
    {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10"},
    {"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"},
    {"D1","D2","D3","D4","D5","D6","D7","D8","D9","D10"},
    {"E1","E2","E3","E4","E5","E6","E7","E8","E9","E10"},
    {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10"},
    {"G1","G2","G3","G4","G5","G6","G7","G8","G9","G10"},
    {"H1","H2","H3","H4","H5","H6","H7","H8","H9","H10"},
    {"I1","I2","I3","I4","I5","I6","I7","I8","I9","I10"},
    {"J1","J2","J3","J4","J5","J6","J7","J8","J9","J10"}};

    string player [10][10] = game;
    string startCoor;
    char orientation, redo;
    int occ = 0;

    cout << "YOU ARE PLAYING BATTLESHIP\n\nYou have 5 ships:\nAircraftCarrier\t 5 spaces\nBattleship\t 4 spaces\nSubmarine\t 3 spaces\nCruiser\t\t 3 spaces\nDestroyer\t 2 spaces\n\n";

    do
    {
        string game[10][10] =  {{"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10"},
                                {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10"},
                                {"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"},
                                {"D1","D2","D3","D4","D5","D6","D7","D8","D9","D10"},
                                {"E1","E2","E3","E4","E5","E6","E7","E8","E9","E10"},
                                {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10"},
                                {"G1","G2","G3","G4","G5","G6","G7","G8","G9","G10"},
                                {"H1","H2","H3","H4","H5","H6","H7","H8","H9","H10"},
                                {"I1","I2","I3","I4","I5","I6","I7","I8","I9","I10"},
                                {"J1","J2","J3","J4","J5","J6","J7","J8","J9","J10"}};
        print(game);
        cout <<"\n\nNote: Coordinates are case-sensitive\n\nWhere will you place the Aircraft Carrier? \nEnter starting coordinate: ";
        cin >> startCoor;
        while (check(game, startCoor) == -1)
        {
            cout << "\nIncorrect coordinate, try again: ";
            cin >> startCoor;
        }
        cout << "Place horizontally or vertically? Enter v/h: ";
        cin >> orientation;
        while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
        {
            cout << "Place horizontally or vertically? Enter v/h: ";
            cin >> orientation;
        }
        int z;
        z = 0;
        do{
            occ = 0;
            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                                if (j+3 > 9)
                                {
                                    occ++;
                                    break;
                                }
                        }
                    }
                }
            }

            else if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                            {
                                if (i+3 > 9)
                                {
                                    occ++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (occ > 0)
            {
                cout << "\nOut of Range, or path may be occupied";
                cout << "\nEnter different starting coordinate:";
                cin >> startCoor;
                while (check(game, startCoor) == -1)
                {
                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                    cin >> startCoor;
                }
                cout << "Place horizontally or vertically? Enter v/h: ";
                cin >> orientation;
                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                {
                    cout << "Place horizontally or vertically? Enter v/h: ";
                    cin >> orientation;
                }
            }
        }
        while (occ > 0);

        if (orientation == 'h' || orientation == 'H')
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                for (int j = 0 ; j <10 ; j++)
                {
                    if (game[i][j] == startCoor)
                    {
                        for (int k = 0 ; k < 5 ; k++)
                        {
                            game[i][j+k] = "A";

                        }
                    }
                }
            }
        }
        //aircraft carrier input

        else if (orientation == 'v' || orientation == 'V')
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                for (int j = 0 ; j <10 ; j++)
                {
                    if (game[i][j] == startCoor)
                    {
                        for (int k = 0 ; k < 5 ; k++)
                            game[i+k][j] = "A";
                    }
                }
            }
        }
        print(game);
        //battleship input
        cout <<"\n\nWhere will you place the Battleship? \nEnter starting coordinate:";
        cin >> startCoor;
        while (check(game, startCoor) == -1)
        {
            cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
            cin >> startCoor;
        }
        cout << "Place horizontally or vertically? Enter v/h: ";
        cin >> orientation;
        while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
        {
            cout << "Place horizontally or vertically? Enter v/h: ";
            cin >> orientation;
        }

        do{
            occ = 0;
            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                                if (j+3 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i][j+k].length () == 1)
                                    occ++;
                        }
                    }
                }
            }

            else if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                            {
                                if (i+3 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i+k][j].length () == 1)
                                    occ++;
                            }
                        }
                    }
                }
            }
            if (occ > 0)
            {
                cout << "\nOut of Range, or path may be occupied";
                cout << "\nEnter different starting coordinate:";
                cin >> startCoor;
                while (check(game, startCoor) == -1)
                {
                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                    cin >> startCoor;
                }
                cout << "Place horizontally or vertically? Enter v/h: ";
                cin >> orientation;
                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                {
                    cout << "Place horizontally or vertically? Enter v/h: ";
                    cin >> orientation;
                }
            }
        }
        while (occ > 0);

        if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                                game[i+k][j] = "B";

                        }
                    }
                }
            }
        else if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 4 ; k++)
                                game[i][j+k] = "B";

                        }
                    }
                }
            }
            print(game);
        //submarine input
        cout <<"\n\nWhere will you place the Submarine? \nEnter starting coordinate:";
        cin >> startCoor;
        while (check(game, startCoor) == -1)
        {
            cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
            cin >> startCoor;
        }
        cout << "Place horizontally or vertically? Enter v/h: ";
        cin >> orientation;
        while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
        {
            cout << "Place horizontally or vertically? Enter v/h: ";
            cin >> orientation;
        }

        do {occ = 0;
            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                if (j+2 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i][j+k].length () == 1)
                                    occ++;
                        }
                    }
                }
            }

            else if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                if (i+2 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i+k][j].length () == 1)
                                    occ++;
                        }
                    }
                }
            }
            if (occ > 0)
            {
                cout << "\nOut of range, or path is occupied";
                cout << "\nEnter different starting coordinate:";
                cin >> startCoor;
                while (check(game, startCoor) == -1)
                {
                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                    cin >> startCoor;
                }
                cout << "Place horizontally or vertically? Enter v/h: ";
                cin >> orientation;
                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                {
                    cout << "Place horizontally or vertically? Enter v/h: ";
                    cin >> orientation;
                }
            }
        }
        while (occ > 0 );

        if (orientation == 'v' || orientation == 'V')
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                for (int j = 0 ; j <10 ; j++)
                {
                    if (game[i][j] == startCoor)
                    {
                        for (int k = 0 ; k < 3 ; k++)
                            game[i+k][j] = "S";
                    }
                }
            }
        }
        else if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                game[i][j+k] = "S";
                        }
                    }
                }
            }
            print(game);
        //CRUISER INPUT
        cout <<"\n\nWhere will you place the Cruiser? \nEnter starting coordinate:";
        cin >> startCoor;
        while (check(game, startCoor) == -1)
        {
            cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
            cin >> startCoor;
        }
        cout << "Place horizontally or vertically? Enter v/h: ";
        cin >> orientation;
        while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
        {
            cout << "Place horizontally or vertically? Enter v/h: ";
            cin >> orientation;
        }

        do {occ = 0;
            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                if (j+2 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i][j+k].length () == 1)
                                    occ++;
                        }
                    }
                }
            }

            else if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                if (i+2 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i+k][j].length () == 1)
                                    occ++;
                        }
                    }
                }
            }
            if (occ > 0)
            {
                cout << "\nOut of range, or path is occupied";
                cout << "\nEnter different starting coordinate:";
                cin >> startCoor;
                while (check(game, startCoor) == -1)
                {
                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                    cin >> startCoor;
                }
                cout << "Place horizontally or vertically? Enter v/h: ";
                cin >> orientation;
                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                {
                    cout << "Place horizontally or vertically? Enter v/h: ";
                    cin >> orientation;
                }
            }
        }
        while (occ > 0);

        if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                game[i+k][j] = "C";
                        }
                    }
                }
            }
            else if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 3 ; k++)
                                game[i][j+k] = "C";

                        }
                    }
                }
            }
        print(game);
        //DESTROYER INPUT
        cout <<"\n\nWhere will you place the Destroyer? \nEnter starting coordinate:";
        cin >> startCoor;
        while (check(game, startCoor) == -1)
        {
            cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
            cin >> startCoor;
        }
        cout << "Place horizontally or vertically? Enter v/h: ";
        cin >> orientation;
        while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
        {
            cout << "Place horizontally or vertically? Enter v/h: ";
            cin >> orientation;
        }

        do {occ = 0;
            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 2 ; k++)
                                if (j+1 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i][j+k].length () == 1)
                                    occ++;
                        }
                    }
                }
            }

            else if (orientation == 'v' || orientation == 'V')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 2 ; k++)
                                if (i+1 > 9)
                                {
                                    occ++;
                                    break;
                                }
                                else if (game[i+k][j].length () == 1)
                                    occ++;
                        }
                    }
                }
            }
            if (occ > 0)
            {
                cout << "\nOut of Range, or path is occupied";
                cout << "\nEnter different starting coordinate:";
                cin >> startCoor;
                while (check(game, startCoor) == -1)
                {
                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                    cin >> startCoor;
                }
                cout << "Place horizontally or vertically? Enter v/h: ";
                cin >> orientation;
                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                {
                    cout << "Place horizontally or vertically? Enter v/h: ";
                    cin >> orientation;
                }
            }
        }
        while (occ > 0);

        z = 0;
        do{

            if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j < 10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            z = j;
                            if (z+1 > 9)
                            {
                                cout << "Invalid\nPick a different position: ";
                                cin >> startCoor;
                                while (check(game, startCoor) == -1)
                                {
                                    cout << "\nIncorrect coordinate (or the space may be occupied), try again: ";
                                    cin >> startCoor;
                                }
                                cout << "\nPlace horizontally or vertically? Enter v/h: ";
                                cin >> orientation;
                                while (orientation != 'h' && orientation != 'H' && orientation != 'V' && orientation != 'v' )
                                {
                                    cout << "Place horizontally or vertically? Enter v/h: ";
                                    cin >> orientation;
                                }
                            }
                        }
                    }
                }
            }

        }
        while (z+1 > 9 && (orientation == 'h' || orientation == 'H'));

        if (orientation == 'v' || orientation == 'V')
        {
            for (int i = 0 ; i < 10 ; i++)
            {
                for (int j = 0 ; j <10 ; j++)
                {
                    if (game[i][j] == startCoor)
                    {
                        for (int k = 0 ; k < 2 ; k++)
                            game[i+k][j] = "D";
                    }
                }
            }
        }
        else if (orientation == 'h' || orientation == 'H')
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0 ; j <10 ; j++)
                    {
                        if (game[i][j] == startCoor)
                        {
                            for (int k = 0 ; k < 2 ; k++)
                                game[i][j+k] = "D";
                        }
                    }
                }
            }
        print(game);
        cout << "\nIf you want to rearrange your ships, press 'r', or press any letter to continue\n";
        cin >> redo;

    if (redo != 'r' && redo != 'R')
    {
    // CPU ship placement
    string CPU[10][10] = {{"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10"},
                            {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10"},
                            {"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"},
                            {"D1","D2","D3","D4","D5","D6","D7","D8","D9","D10"},
                            {"E1","E2","E3","E4","E5","E6","E7","E8","E9","E10"},
                            {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10"},
                            {"G1","G2","G3","G4","G5","G6","G7","G8","G9","G10"},
                            {"H1","H2","H3","H4","H5","H6","H7","H8","H9","H10"},
                            {"I1","I2","I3","I4","I5","I6","I7","I8","I9","I10"},
                            {"J1","J2","J3","J4","J5","J6","J7","J8","J9","J10"}};
    srand(time(NULL));
    //aircraft carrier placement
    int oriCPU,rowCPU, colCPU;
    oriCPU = rand() % 2;
    // 0 is horizontal, 1 is vertical
    int xyz = 0, counter;

    if (oriCPU == 0)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
            for (int i = 0 ; i <=4 ; i++)
                if (colCPU+4 < 10)
                    CPU[rowCPU][colCPU+i] = "A";
        }
        while (colCPU + 4 > 9);
    }
    else if (oriCPU == 1)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
            for (int i = 0 ; i <=4 ; i++)
                if (rowCPU+4 < 10)
                    CPU[rowCPU+i][colCPU] = "A";
        }
        while (rowCPU + 4 > 9);
    }

    //battleship placment

    oriCPU = rand() % 2;

    if (oriCPU == 0)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;

            xyz = 0;
            counter = 0;

                if (colCPU + 3 < 10 && CPU[rowCPU][colCPU+1].length () != 1 && CPU[rowCPU][colCPU+2].length () != 1&& CPU[rowCPU][colCPU+3].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU][colCPU] = "B";
                    CPU[rowCPU][colCPU+1] = "B";
                    CPU[rowCPU][colCPU+2] = "B";
                    CPU[rowCPU][colCPU+3] = "B";
                }
                else
                    xyz++;


            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "B")
                        counter++;
        }
        while (colCPU + 3 > 9 || xyz > 0|| counter > 4);
    }
    else if (oriCPU == 1)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
             xyz = 0;
             counter = 0;

                if (rowCPU + 3 < 10 && CPU[rowCPU+1][colCPU].length () != 1 && CPU[rowCPU+2][colCPU].length () != 1&& CPU[rowCPU+3][colCPU].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU+1][colCPU] = "B";
                    CPU[rowCPU+2][colCPU] = "B";
                    CPU[rowCPU+3][colCPU] = "B";
                    CPU[rowCPU][colCPU] = "B";
                }
                else
                    xyz++;

            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "B")
                        counter++;
        }
        while (rowCPU + 3 > 9 || xyz > 0 || counter > 4);
    }

    //submarine placement
    oriCPU = rand() % 2;

    if (oriCPU == 0)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;

            xyz = 0;
            counter = 0;

                if (colCPU + 2 < 10 && CPU[rowCPU][colCPU+1].length () != 1 && CPU[rowCPU][colCPU+2].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU][colCPU] = "S";
                    CPU[rowCPU][colCPU+1] = "S";
                    CPU[rowCPU][colCPU+2] = "S";
                }
                else
                    xyz++;


            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "S")
                        counter++;
        }
        while (colCPU + 2 > 9 || xyz > 0|| counter > 3);
    }
    else if (oriCPU == 1)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
             xyz = 0;
             counter = 0;

                if (rowCPU + 2 < 10 && CPU[rowCPU+1][colCPU].length () != 1 && CPU[rowCPU+2][colCPU].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU+1][colCPU] = "S";
                    CPU[rowCPU+2][colCPU] = "S";
                    CPU[rowCPU][colCPU] = "S";
                }
                else
                    xyz++;

            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "S")
                        counter++;
        }
        while (rowCPU + 2 > 9 || xyz > 0 || counter > 3);
    }

    //cruiser placement
    oriCPU = rand() % 2;

    if (oriCPU == 0)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;

            xyz = 0;
            counter = 0;

                if (colCPU + 2 < 10 && CPU[rowCPU][colCPU+1].length () != 1 && CPU[rowCPU][colCPU+2].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU][colCPU] = "C";
                    CPU[rowCPU][colCPU+1] = "C";
                    CPU[rowCPU][colCPU+2] = "C";
                }
                else
                    xyz++;


            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "C")
                        counter++;
        }
        while (colCPU + 2 > 9 || xyz > 0|| counter > 3);
    }
    else if (oriCPU == 1)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
             xyz = 0;
             counter = 0;

                if (rowCPU + 2 < 10 && CPU[rowCPU+1][colCPU].length () != 1 && CPU[rowCPU+2][colCPU].length () != 1&& CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU+1][colCPU] = "C";
                    CPU[rowCPU+2][colCPU] = "C";
                    CPU[rowCPU][colCPU] = "C";
                }
                else
                    xyz++;

            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "C")
                        counter++;
        }
        while (rowCPU + 2 > 9 || xyz > 0 || counter > 3);
    }

    //destroyer placement
    oriCPU = rand() % 2;

    if (oriCPU == 0)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;

            xyz = 0;
            counter = 0;

                if (colCPU + 1 < 10 && CPU[rowCPU][colCPU+1].length () != 1 && CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU][colCPU] = "D";
                    CPU[rowCPU][colCPU+1] = "D";
                }
                else
                    xyz++;


            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "D")
                        counter++;
        }
        while (colCPU + 1 > 9 || xyz > 0|| counter > 2);
    }
    else if (oriCPU == 1)
    {
        do
        {
            rowCPU = rand() % 10;
            colCPU = rand() % 10;
             xyz = 0;
             counter = 0;

                if (rowCPU + 1 < 10 && CPU[rowCPU+1][colCPU].length () != 1 && CPU[rowCPU][colCPU].length () != 1)
                {
                    CPU[rowCPU+1][colCPU] = "D";
                    CPU[rowCPU][colCPU] = "D";
                }
                else
                    xyz++;

            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0; j < 10 ; j++)
                    if (CPU[i][j] == "D")
                        counter++;
        }
        while (rowCPU + 1 > 9 || xyz > 0 || counter > 2);
    }

    //let the player make guesses
    system("cls");
    string a;
    string temp = " ";
    cout << "\t\t\t    LET THE GAME BEGIN\n\n";
    print(player);
    int totalPlayer,totalCPU, heat = 0, totA = 0, totB = 0, totC = 0, totD = 0, totS = 0, cpuA = 0, cpuB = 0, cpuC = 0, cpuD = 0, cpuS = 0;
    do
    {
        //player's turn
        a = guess(player,CPU);
            for (int i = 0 ; i < 10 ; i++)
                for (int j = 0 ; j <10 ; j++)
                    if (player[i][j] == a)
                    {
                        if (CPU[i][j].length () == 1)
                        {
                            cout << "\nHit!";
                            player[i][j] = " X";
                            CPU[i][j] = "X";
                            if (totA == 0)
                                totA = countA(CPU);
                            if (totB == 0)
                                totB = countB(CPU);
                            if (totC == 0)
                                totC = countC(CPU);
                            if (totD == 0)
                                totD = countD(CPU);
                            if (totS == 0)
                                totS = countS(CPU);
                            totalPlayer = keepCountPlayer(CPU);
                        }
                        else
                        {
                            cout << "\nMiss!";
                            player[i][j] = " O";
                            totalPlayer = keepCountPlayer(CPU);
                        }
                    }
        Sleep(500);
        //CPU's turn

        int r,c;
        if (totalPlayer != 0)
        {
            cout <<"\nCPU's Target: ";
            if (heat == 0)
            {
                r = rand() % 10;
                c = rand() % 10;
                while (game[r][c] == " O" || game [r][c] == " X")
                {
                    r = rand() % 10;
                    c = rand() % 10;
                }
            }
            if (heat > 0)
            {
                for (int i = 0 ; i < 10 ; i++)
                {
                    for (int j = 0; j < 10 ; j++)
                    {
                        if (game[i][j] == temp)
                        {
                            r = i;
                            c = j;
                            j=9;
                            i=9;
                        }
                        else
                        {
                            r = rand() % 10;
                            c = rand() % 10;
                            while (game[r][c] == " O" || game [r][c] == " X")
                            {
                                r = rand() % 10;
                                c = rand() % 10;
                            }
                            heat = 0;
                        }
                    }
                }
            }

            if (r == 0)
                cout << "A" << c+1;
            else if (r == 1)
                cout << "B" << c+1;
            else if (r == 2)
                cout << "C" << c+1;
            else if (r == 3)
                cout << "D" << c+1;
            else if (r == 4)
                cout << "E" << c+1;
            else if (r == 5)
                cout << "F" << c+1;
            else if (r == 6)
                cout << "G" << c+1;
            else if (r == 7)
                cout << "H" << c+1;
            else if (r == 8)
                cout << "I" << c+1;
            else if (r == 9)
                cout << "J" << c+1;
            Sleep(1000);
            if (game[r][c].length () == 1)
            {
                cout << "\nHit!\n";
                Sleep(500);
                temp = game[r][c];

                game[r][c] = " X";
                print(game);
                 heat++;

                if (cpuA == 0)
                    cpuA = countA(game);
                if (cpuB == 0)
                    cpuB = countB(game);
                if (cpuC == 0)
                    cpuC = countC(game);
                if (cpuD == 0)
                    cpuD = countD(game);
                if (cpuS == 0)
                    cpuS = countS(game);
                totalCPU = keepCountCpu(game);
                cout << "\npress any key to continue...";
                getch();

            }
            else
            {
                cout << "\nMiss!\n";
                Sleep(500);
                game[r][c] = " O";
                print(game);

                cout << "\npress any key to continue...";
                getch();
                totalCPU = keepCountCpu(game);
            }

        }

        if (totalCPU != 0 && totalPlayer != 0)
        {
            system("cls");
            print(player);
        }
    }
    while (totalPlayer != 0 && totalCPU != 0);
    }
    }
    while (redo == 'r' || redo == 'R');

    getch ();
    return 0;
}

string guess (string player[10][10], string a[10][10])
{
    string target;
    int here;

    do
    {
        cout << "\nChoose a valid target: ";
        cin >> target;
        if (target == "!")
            print(a);
        here = 0;
        for (int i = 0 ; i < 10 ; i++)
            for (int j = 0 ; j <10 ; j++)
                if (player[i][j] == target)
                here++;
    }
    while (here == 0);
    return target;
}

int check (string a[10][10], string x)
{
    int temp = -1;
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j < 10 ; j++)
        {
            if (a[i][j] == x && a[i][j].length () > 1){
                temp++;
                break;
            }
        }
    }
    return temp;
}

int countA (string a[10][10])
{
    int num = 0;
    for (int i  = 0 ; i < 10 ; i++)
        for (int j = 0; j <10 ; j++)
            if (a[i][j] == "A")
                num++;
    if (num == 0)
    {
        cout << "\nACHEIVEMENT: Aircraft Carrier has been sunk!";
        num = 100;
        return num;
    }
    else
        return 0;
}

int countB (string a[10][10])
{
    int num = 0;
    for (int i  = 0 ; i < 10 ; i++)
        for (int j = 0; j <10 ; j++)
            if (a[i][j] == "B")
                num++;
    if (num == 0)
    {
        cout << "\nACHEIVEMENT: Battleship has been sunk!";
        num = 100;
        return num;
    }
    else
        return 0;
}

int countC (string a[10][10])
{
    int num = 0;
    for (int i  = 0 ; i < 10 ; i++)
        for (int j = 0; j <10 ; j++)
            if (a[i][j] == "C")
                num++;
    if (num == 0)
    {
        cout << "\nACHEIVEMENT: Cruiser has been sunk!";
        num = 100;
        return num;
    }
    else
        return 0;
}

int countD (string a[10][10])
{
    int num = 0;
    for (int i  = 0 ; i < 10 ; i++)
        for (int j = 0; j <10 ; j++)
            if (a[i][j] == "D")
                num++;
    if (num == 0)
    {
        cout << "\nACHEIVEMENT: Destroyer has been sunk!";
        num = 100;
        return num;
    }
    else
        return 0;
}

int countS (string a[10][10])
{
    int num = 0;
    for (int i  = 0 ; i < 10 ; i++)
        for (int j = 0; j <10 ; j++)
            if (a[i][j] == "S")
                num++;
    if (num == 0)
    {
        cout << "\nACHEIVEMENT: Submarine has been sunk!";
        num = 100;
        return num;
    }
    else
        return 0;
}


int keepCountPlayer (string a[10][10])
{
    int countA = 0, countB = 0, countC = 0, countD = 0, countS = 0;
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j <10 ; j++)
        {
            if (a[i][j] == "A")
                countA++;
            else if (a[i][j] == "B")
                countB++;
            else if (a[i][j] == "C")
                countC++;
            else if (a[i][j] == "D")
                countD++;
            else if (a[i][j] == "S")
                countS++;
        }
    }
    int total = countA+countB+countC+countD+countS;
    if (total == 0)
        cout << "\n\nYOU WIN!";
    Sleep(1000);
    return total;
}

int keepCountCpu (string a[10][10])
{
    int countA = 0, countB = 0, countC = 0, countD = 0, countS = 0;
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j <10 ; j++)
        {
            if (a[i][j] == "A")
                countA++;
            else if (a[i][j] == "B")
                countB++;
            else if (a[i][j] == "C")
                countC++;
            else if (a[i][j] == "D")
                countD++;
            else if (a[i][j] == "S")
                countS++;
        }
    }
    int total = countA+countB+countC+countD+countS;
    if (total == 0)
        cout << "\n\nYOU LOSE!";
    Sleep(1000);
    return total;
}

