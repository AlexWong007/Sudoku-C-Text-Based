#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cctype>

class Board
{
    private:
    
    int GeneratedNumber;
    int GeneratedGridNum1 = 0;
    int GeneratedGridNum2 = 0;
    int max = 9;
    int max2 = 22;
    int Draw_Line = 1;
    int GeneratedNum;
    int grid[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0} ,{0, 0, 0, 0, 0, 0, 0, 0, 0} };
    int ReadOnly_grid[22][2];

    public:

    int Generated_Num()
    {
        //Generates a number between 1 - 9
        while (GeneratedNum < 1 || GeneratedNum > 9)
        {
            srand(time(0));
            GeneratedNum = 1 + (rand() % 11);
        }
    }

    void Display_Board()
    {
          for (int r = 0; r < 9; r++)
          {
            if (Draw_Line == 3)
            {
                for (int c = 0; c < 3; c++)
                {
                    std:: cout << grid[r][c];
                }
                std:: cout << "|";
                for (int c = 3; c < 6; c++)
                {
                    std:: cout << grid[r][c];
                }
                std:: cout << "|";
                for (int c = 6; c < 9; c++)
                {
                    std:: cout << grid[r][c];
                }
                std:: cout << "\n";
                if (r < 7)
                {
                    std:: cout << "-----------" << std:: endl;
                }
                Draw_Line = 1;
            }
            else
            {
                for (int c = 0; c < 3; c++)
                {
                    std:: cout << grid[r][c];
                }
                std:: cout << "|";
                for (int c = 3; c < 6; c++)
                {
                    std:: cout << grid[r][c];
                }
                std:: cout << "|";
                for (int c = 6; c < 9; c++)
                {
                    std:: cout << grid[r][c];
                }
                Draw_Line++;
                std:: cout << "\n";
            }
          }

    }

    void Generate_Board()
    {
        srand(time(0));
        int Num_Of_Set_Nums = 0;
        while (Num_Of_Set_Nums < 17 || Num_Of_Set_Nums > 22)
        {
            srand(time(0));
            Num_Of_Set_Nums = 1 + (rand() % 24);
        }
        
        for (int i = 0; i < (Num_Of_Set_Nums * 2) - 6; i++)
        {
            GeneratedGridNum1 = rand()%max;
            GeneratedGridNum2 = rand()%max;
            GeneratedNumber = rand()%max;
            ReadOnly_grid[i][0] = GeneratedGridNum1;
            ReadOnly_grid[i][1] = GeneratedGridNum2;
            Input_Generated_Board(GeneratedGridNum1, GeneratedGridNum2, GeneratedNumber);
        }
    }

    void Input_Generated_Board(int Row, int Col, int InputNumber)
    {
        grid[Row][Col] = InputNumber;
        for (int r = 0; r < 9; r++)
        {
            if (grid[r][Col] == InputNumber && r != Row)
            {
                grid[Row][Col] = 0;
            }
        }
        for (int c = 0; c < 9; c++)
        {
            if (grid[Row][c] == InputNumber && c != Col)
            {
                grid[Row][Col] = 0;
            }
        }
    }

    void Input_Into_Board()
    {
        int row;
        int col;
        int input;

        do
        {
            std:: cout << "Enter the row of the number you would like to move (left to right starting 1 - 9):" << std:: endl;
            std:: cin >> row;
            std:: cout << "Enter the column of the number you would like to move (up to down starting 1 - 9):" << std:: endl;
            std:: cin >> col;
            std :: cout << "Enter the number you would like to input:" << std:: endl;
            std:: cin >> input;
            Input_Generated_Board(row - 1, col - 1, input);
            Display_Board();
        }
        while (grid[row - 1][col - 1] == 0);
    }
    
    void Remove_From_Board()
    {
        int row;
        int col;
        bool error = false;

        std:: cout << "Enter the row of the number you would like to remove (left to right starting 1 - 9):" << std:: endl;
        std:: cin >> row;
        std:: cout << "Enter the column of the number you would like to remove (up to down starting 1 - 9):" << std:: endl;
        std:: cin >> col;
        
        for (int i = 0; i < 22; i++)
        {
            if (ReadOnly_grid[i][0] == (row - 1) && ReadOnly_grid[i][1] == (col - 1))
            error = true;
        }

        if (error)
        std:: cout << "Unable to remove number in grid because it was generated initally." << std:: endl;
        else if (!error)
        grid[row - 1][col - 1] = 0;

        Display_Board();
    }

    void CheckGameOver(bool &GameOver)
    {
        bool win = true;


        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
                if (grid[r][c] == 0)
                {
                    win = false;
                }
            }
        }

        if (win)
        GameOver = true;
        else if (!win)
        GameOver = false;
    }
};

int main()
{
    char UserInput;
    bool GameOver = false;
    Board board;

    std:: cout << "Welcome to Sudoku." << std:: endl;
    board.Display_Board();
    std:: cout << "Loading Grid..." << std:: endl;
    board.Generate_Board();
    std:: cout << std:: endl;
    board.Display_Board();
    
    while (!GameOver)
    {
        std:: cout << "If you want to Input a number type (y), if you would like to remove a number press (n):" << std:: endl;
        std:: cin >> UserInput;
        if (tolower(UserInput) == 'y')
        board.Input_Into_Board();
        else if (tolower(UserInput) == 'n')
        {
            board.Remove_From_Board();
        }
        board.CheckGameOver(GameOver);
    }
    std:: cout << "Game Over, You have beaten Sudoku!" << std:: endl;
}


