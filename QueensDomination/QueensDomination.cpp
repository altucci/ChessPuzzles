#include <iostream>
#include <string>
#include <stdexcept>
#include "rng.cpp"

   using namespace std;

   class Cell
   {
   public:
      int row, column;
   };

   class ChessDomination
   {
      char **board;
   
      Cell *cells;
   
      Cell **storedCellCombinations;
   
      string type;
   
      int height, width, min, placeHolder;
   
      bool totalDomination;
   
      long combinations;
   
      char marker;
   
      void displayBoard()
      {
         cout << "\n";
         for (int i = 0;i < width;i++){
            if (width > 19)
               cout << "--";
            else
               cout << "----";
         }
         cout << "-\n";
         for (int i = 0;i < height;i++){
            for (int j = 0;j < width;j++){
               if (width > 19)
                  cout << "|" << board[i][j];
               else
                  cout << "| " << board[i][j] << " ";
            }
            cout << "|\n";
            for (int j = 0;j < width;j++){
               if (width > 19)
                  cout << "--";
               else
                  cout << "----";
            }
            cout << "-\n";
         }
         cout << "\n";
      }
   
      void initializeArrays()
      {
         board = new char*[height];
      
         for (int i = 0;i < height;i++)
            board[i] = new char[width];
      
         for (int i = 0;i < height;i++)
            for (int j = 0;j < width;j++)
               board[i][j] = ' ';
      
         cells = new Cell[min];
      }
   
      void clearBoard()
      {
         for (int i = 0;i < height;i++)
            for (int j = 0;j < width;j++)
               board[i][j] = ' ';
      }
   
      long choose(int total, int selection)
      {
         return (fact(total)/(fact(selection)*fact(total-selection)));
      }
   
      long fact(int num)
      {
         for (int i = num-1;i > 0;i--)
            num *= i;
      
         return static_cast<long>(num);
      }
   
      bool DominatesBoard()
      {
         string s = "123456789ABCDEFGHIJKLMNOP";
      
         for (int i = 0;i < min;i++)
         {
            marker = s[min-i-1];
            DominationCheck(cells[i]);
         }
      
         if (EverySquareIsThreatened())
            return true;
      
         return false;
      }
   
      void DominationCheckForKings(Cell c)
      {
         LeftForKings(c);
         UpForKings(c);
         RightForKings(c);
         DownForKings(c);
         UpLeftForKings(c);
         UpRightForKings(c);
         DownRightForKings(c);
         DownLeftForKings(c);
      }   
   
      void LeftForKings(Cell c)
      {
         if ((c.column-1) >= 0)
            board[c.row][c.column-1] = marker;
      }
   
      void UpLeftForKings(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column-1) >= 0)
            board[c.row-1][c.column-1] = marker;
      }
   
      void UpForKings(Cell c)
      {
         if ((c.row-1) >= 0)
            board[c.row-1][c.column] = marker;
      }
   
      void UpRightForKings(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column+1) < width)
            board[c.row-1][c.column+1] = marker;
      }
   
      void RightForKings(Cell c)
      {
         if ((c.column+1) < width)
            board[c.row][c.column+1] = marker;
      }
   
      void DownRightForKings(Cell c)
      {
         if ((c.row+1) < height && (c.column+1) < width)
            board[c.row+1][c.column+1] = marker;
      }
   
      void DownForKings(Cell c)
      {
         if ((c.row+1) < height)
            board[c.row+1][c.column] = marker;
      }
   
      void DownLeftForKings(Cell c)
      {
         if ((c.row+1) < height && (c.column-1) >= 0)
            board[c.row+1][c.column-1] = marker;
      }
   
      void DominationCheckForKnights(Cell c)
      {
         LeftDownForKnights(c);
         LeftUpForKnights(c);
         UpLeftForKnights(c);
         UpRightForKnights(c);
         RightUpForKnights(c);
         RightDownForKnights(c);
         DownRightForKnights(c);
         DownLeftForKnights(c);
      }
   
      void LeftDownForKnights(Cell c)
      {
         if ((c.row+1) < height && (c.column-2) >= 0)
            board[c.row+1][c.column-2] = marker;
      }
   
      void LeftUpForKnights(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column-2) >= 0)
            board[c.row-1][c.column-2] = marker;
      }
   
      void UpLeftForKnights(Cell c)
      {
         if ((c.row-2) >= 0 && (c.column-1) >= 0)
            board[c.row-2][c.column-1] = marker;
      }
   
      void UpRightForKnights(Cell c)
      {
         if ((c.row-2) >= 0 && (c.column+1) < width)
            board[c.row-2][c.column+1] = marker;
      }
   
      void RightUpForKnights(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column+2) < width)
            board[c.row-1][c.column+2] = marker;
      }
   
      void RightDownForKnights(Cell c)
      {
         if ((c.row+1) < height && (c.column+2) < width)
            board[c.row+1][c.column+2] = marker;
      }
   
      void DownRightForKnights(Cell c)
      {
         if ((c.row+2) < height && (c.column+1) < width)
            board[c.row+2][c.column+1] = marker;
      }
   
      void DownLeftForKnights(Cell c)
      {
         if ((c.row+2) < height && (c.column-1) >= 0)
            board[c.row+2][c.column-1] = marker;
      }
   
      void DominationCheck(Cell c)
      {
         if (totalDomination == false)
         {
            board[c.row][c.column] = type[0];
         }
      
         if (type == "K" || type == "k")
         {
            DominationCheckForKings(c);
         }
         else if (type == "N" || type == "n")
         {
            DominationCheckForKnights(c);
         }
         else if (type == "B" || type == "b")
         {         
            UpLeft(c);
            UpRight(c);
            DownRight(c);
            DownLeft(c);
         }
			else if ( type == "R" || type == "r")
			{
				Left(c);
				Up(c);
				Right(c);
				Down(c);
			}
         else
         {
            Left(c);
            Up(c);
            Right(c);
            Down(c);
            UpLeft(c);
            UpRight(c);
            DownRight(c);
            DownLeft(c);
         }
      }   
   
      void Left(Cell c)
      {
         for (int i = c.column-1;i >= 0;i--)
            board[c.row][i] = marker;
      }
   
      void UpLeft(Cell c)
      {
         for (int i = c.row-1, j = c.column-1;i >= 0 && j >= 0;i--,j--)
            board[i][j] = marker;
      }
   
      void Up(Cell c)
      {
         for (int i = c.row-1;i >= 0;i--)
            board[i][c.column] = marker;
      }
   
      void UpRight(Cell c)
      {
         for (int i = c.row-1, j = c.column+1;i >= 0 && j < width;i--,j++)
            board[i][j] = marker;
      }
   
      void Right(Cell c)
      {
         for (int i = c.column+1;i < width;i++)
            board[c.row][i] = marker;
      }
   
      void DownRight(Cell c)
      {
         for (int i = c.row+1, j = c.column+1;i < height && j < width;i++,j++)
            board[i][j] = marker;
      }
   
      void Down(Cell c)
      {
         for (int i = c.row+1;i < height;i++)
            board[i][c.column] = marker;
      }
   
      void DownLeft(Cell c)
      {
         for (int i = c.row+1, j = c.column-1;i < height && j >= 0;i++,j--)
            board[i][j] = marker;
      }
   
      bool EverySquareIsThreatened()
      {
         for (int i = 0;i < height;i++)
            for (int j = 0;j < width;j++)
               if (board[i][j] == ' ')
                  return false;		
      
         return true;
      }
   
      bool CellCombinationAlreadyTried()
      {
         for (int i = 0;i < placeHolder;i++)
            if (CellArraysAreEqual(i))
               return true;
      
         return false;				
      }
   
      bool CellArraysAreEqual(int pos)
      {
         for (int i = 0;i < min;i++)
            if (CellIsNotContained(i, pos))
               return false;
      
         return true;
      }
   
      bool CellIsNotContained(int a, int b)
      {
         for (int i = 0;i < min;i++)
            if (cells[a].row == storedCellCombinations[b][i].row &&
               cells[a].column == storedCellCombinations[b][i].column)
               return false;
      
         return true;
      }
   
   public:
   
      ChessDomination(int len, int wid, int minQ, string searchType, string totalDom)
      {
         height = len;
         width = wid;
         min = minQ;
      
         type = searchType;
      
         totalDomination = false;
      
         if (totalDom == "Y" || totalDom == "y")
            totalDomination = true;
      
         initializeArrays();
      }
   
      void Solve()
      {
         do{         
            clearBoard();
         
         	for (int i = 0;i < min;i++)
            {
               cells[i].row = rand_int(0, height-1);
               cells[i].column = rand_int(0, width-1);
            }
         
         }while (!DominatesBoard());
      
         clearBoard();
      
         string s = "abcdefghijklmnopqrstuvwxy";
      
         for (int i = 0;i < min;i++)
            board[cells[i].row][cells[i].column] = type[0];
      
         displayBoard();
      }
   };
