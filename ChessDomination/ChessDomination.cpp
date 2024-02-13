/**
 * ChessDomination.cpp
 * @author: <Albert Tucci>
 */


#include <iostream>
#include <string>
#include <stdexcept>
#include "rng.cpp"


   using namespace std;


   /**
    * The purpose of this class is to simulate one cell on a chess board.
    */
   class Cell
   {
      public:
         int row, column;
   };


   /**
    * The purpose of this class is to model the domination of a chess board given a specific type of chess 
    * piece and a specific size of the chess board.
    */
   class ChessDomination
   {
      //Private member variables

      char **board;		//Two-dimensional array to hold simulate the chess board.  Size may dynamically change.
   
      Cell *cells;		//Array to simulate the cells in a given row of the chess board.
   
      Cell **storedCellCombinations;	//Two-dimensional array to store where chess pieces are on the chess board.
   
      string type;		//string representing the type of the chess piece chosen by the user.
   
      int height;			//int representing the height of the chess board.
	   int width;			//int representing the width of the chess board.
	   int min;				//int representing the minimum number of chess pieces to dominate the board as chosen by the user.
	   int placeHolder;	//int representing the exact cell on the chess board the solve algorithm is on at any given moment.
   
      bool totalDomination;	//bool chosen by the user that determines if the would like the chess board to be totally dominated.
   
      long combinations;		//long representing the number of combinations of domination given the dimensions of the chess board and the type of chess piece chosen by the user.
   
      char marker;				//char marking the type of chess piece chosen by the user.



	   //Private methods

      /**
       * The purpose of this method is to display the chess board on the screen with all occupied squares.
       * @param - none
       * @return - none
       */
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
   
      /**
       * The purpose of this method is to initialize all arrays to an empty, default value.
       * @param - none
       * @return - none
       */
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
   
      /**
       * The purpose of this method is to clear all Cells in the chess board.
       * @param - none
       * @return - none
       */
      void clearBoard()
      {
         for (int i = 0;i < height;i++)
            for (int j = 0;j < width;j++)
               board[i][j] = ' ';
      }
   
      /**
       * The purpose of this method is to determine the number of combinations of moves that can be made.
       * @param - ints representing the total number of Cells and the number of pieces selected
       * @return - long representing the total number of combinations
       */
      long choose(int total, int selection)
      {
         return (fact(total)/(fact(selection)*fact(total-selection)));
      }
   
      /**
       * The purpose of this method is to find the factorial of a desired number
       * @param - int representing the number to find the desired fatorial of
       * @return - long representing the factorial of the desired number
       */
      long fact(int num)
      {
         for (int i = num-1;i > 0;i--)
            num *= i;
      
         return static_cast<long>(num);
      }
   
      /**
       * The purpose of this method is to check if the chess board is currently dominated.
       * @param - none
       * @return - true or false
       */
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
   
      /**
       * The purpose of this method is to check whether or not a cell on the board dominates in all 8 directions by Kings.
       * @param - a Cell on the board where you are checking domination from
       * @return - none
       */
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
   
      /**
       * The purpose of this method is to check the horizontal path in the left direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void LeftForKings(Cell c)
      {
         if ((c.column-1) >= 0)
            board[c.row][c.column-1] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the up-left direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpLeftForKings(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column-1) >= 0)
            board[c.row-1][c.column-1] = marker;
      }
   
      /**
       * The purpose of this method is to check the vertical path in the left up for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpForKings(Cell c)
      {
         if ((c.row-1) >= 0)
            board[c.row-1][c.column] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the up-right direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpRightForKings(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column+1) < width)
            board[c.row-1][c.column+1] = marker;
      }
   
      /**
       * The purpose of this method is to check the horizontal path in the right direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void RightForKings(Cell c)
      {
         if ((c.column+1) < width)
            board[c.row][c.column+1] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the down-right direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownRightForKings(Cell c)
      {
         if ((c.row+1) < height && (c.column+1) < width)
            board[c.row+1][c.column+1] = marker;
      }
   
      /**
       * The purpose of this method is to check the vertical path in the down direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownForKings(Cell c)
      {
         if ((c.row+1) < height)
            board[c.row+1][c.column] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the down-left direction for domination by Kings.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownLeftForKings(Cell c)
      {
         if ((c.row+1) < height && (c.column-1) >= 0)
            board[c.row+1][c.column-1] = marker;
      }
   
      /**
       * The purpose of this method is to check whether or not a cell on the board dominates in all 8 directions by Knights.
       * @param - a Cell on the board where you are checking domination from
       * @return - none
       */
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
   
      /**
       * The purpose of this method is to check the path in the left-left-down direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void LeftDownForKnights(Cell c)
      {
         if ((c.row+1) < height && (c.column-2) >= 0)
            board[c.row+1][c.column-2] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the left-left-up direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void LeftUpForKnights(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column-2) >= 0)
            board[c.row-1][c.column-2] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the up-up-left direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpLeftForKnights(Cell c)
      {
         if ((c.row-2) >= 0 && (c.column-1) >= 0)
            board[c.row-2][c.column-1] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the up-up-right direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpRightForKnights(Cell c)
      {
         if ((c.row-2) >= 0 && (c.column+1) < width)
            board[c.row-2][c.column+1] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the right-right-up direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void RightUpForKnights(Cell c)
      {
         if ((c.row-1) >= 0 && (c.column+2) < width)
            board[c.row-1][c.column+2] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the right-right-down direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void RightDownForKnights(Cell c)
      {
         if ((c.row+1) < height && (c.column+2) < width)
            board[c.row+1][c.column+2] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the down-down-right direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownRightForKnights(Cell c)
      {
         if ((c.row+2) < height && (c.column+1) < width)
            board[c.row+2][c.column+1] = marker;
      }
   
      /**
       * The purpose of this method is to check the path in the down-down-left direction for domination by Knights.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownLeftForKnights(Cell c)
      {
         if ((c.row+2) < height && (c.column-1) >= 0)
            board[c.row+2][c.column-1] = marker;
      }
   
      /**
       * The purpose of this method is to check whether the board is dominated.
       * @param - a Cell on the board where you are checking domination from
       * @return - none
       */   
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
   
      /**
       * The purpose of this method is to check the horizontal path in the left direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void Left(Cell c)
      {
         for (int i = c.column-1;i >= 0;i--)
            board[c.row][i] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the up-left direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpLeft(Cell c)
      {
         for (int i = c.row-1, j = c.column-1;i >= 0 && j >= 0;i--,j--)
            board[i][j] = marker;
      }
   
      /**
       * The purpose of this method is to check the vertical path in the up direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void Up(Cell c)
      {
         for (int i = c.row-1;i >= 0;i--)
            board[i][c.column] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the up-right direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void UpRight(Cell c)
      {
         for (int i = c.row-1, j = c.column+1;i >= 0 && j < width;i--,j++)
            board[i][j] = marker;
      }
   
      /**
       * The purpose of this method is to check the horizontal path in the right direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void Right(Cell c)
      {
         for (int i = c.column+1;i < width;i++)
            board[c.row][i] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the down-right direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownRight(Cell c)
      {
         for (int i = c.row+1, j = c.column+1;i < height && j < width;i++,j++)
            board[i][j] = marker;
      }
   
      /**
       * The purpose of this method is to check the vertical path in the down direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void Down(Cell c)
      {
         for (int i = c.row+1;i < height;i++)
            board[i][c.column] = marker;
      }
   
      /**
       * The purpose of this method is to check the diagonal path in the down-left direction for domination.
       * @param - a Cell on the board where you are checking from
       * @return - none
       */
      void DownLeft(Cell c)
      {
         for (int i = c.row+1, j = c.column-1;i < height && j >= 0;i++,j--)
            board[i][j] = marker;
      }
   
      /**
       * The purpose of this method is to check if every square on the chess board can be moved to by a 
	    * any of the pieces currently occupying it.
       * @param - none
       * @return - true of false
       */
      bool EverySquareIsThreatened()
      {
         for (int i = 0;i < height;i++)
            for (int j = 0;j < width;j++)
               if (board[i][j] == ' ')
                  return false;		
      
         return true;
      }
   
      /**
       * The purpose of this method is to check if a potential move is equal to a preiviously stored move.
       * @param - none
       * @return - true or false
       */
      bool CellCombinationAlreadyTried()
      {
         for (int i = 0;i < placeHolder;i++)
            if (CellArraysAreEqual(i))
               return true;
      
         return false;				
      }
   
      /**
       * The purpose of this method is to check if two cells on the chess board on considered equal.
       * @param - int representing a previously occupied position on the chess board.
       * @return - true or false
       */
      bool CellArraysAreEqual(int pos)
      {
         for (int i = 0;i < min;i++)
            if (CellIsNotContained(i, pos))
               return false;
      
         return true;
      }
   
      /**
       * The purpose of this method is to check whether a spot on the chess board is empty.
       * @param - ints representing row and column on the chess board
       * @return - true or false
       */
      bool CellIsNotContained(int a, int b)
      {
         for (int i = 0;i < min;i++)
            if (cells[a].row == storedCellCombinations[b][i].row &&
               cells[a].column == storedCellCombinations[b][i].column)
               return false;
      
         return true;
      }
   
   public:
   
      /**
       * This is the default constructor.
	    * All private member variables are initialized to default values.
       * @param - none
       * @return - none
       */
      ChessDomination()
		{
			
		}

      /**
       * This is a constructor.
	    * All private member variables are initialized.
       * @param - board dimensions, minimum number of pieces desired, search type and total/normal domination
       * @return - none
       */
      ChessDomination(int len, int wid, int minimum, string searchType, string totalDom)
      {
         height = len;
         width = wid;
         min = minimum;
      
         type = searchType;
      
         totalDomination = false;
      
         if (totalDom == "Y")
            totalDomination = true;
      
         initializeArrays();
      }
   
      /**
       * The purpose of this method is to determine if and how a chess board of chosen dimensions can be 
	    * dominated by a chosen type of chess piece.
       * @param - none
       * @return - none
       */
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
            board[cells[i].row][cells[i].column] = type[0];//s[min-i-1];
      
         displayBoard();
      }
   };
