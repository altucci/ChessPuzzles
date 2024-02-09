#include "ChessDomination.cpp"

   int main()
   {
      while (true){
         try{
            string type, totalDom;
            int height, width, minimum;
            cout << "\n";
            cout << "Enter the type of chess piece\nRook = R , Bishop = B , Queen = Q , Knight = N , King = K: ";
            cin >> type;
            cout << "\n";
            cout << "Would you like total domination?\nYes = Y , No = N: ";
            cin >> totalDom;
            cout << "\n";
            cout << "Enter the height of the board: ";
            cin >> height;
            cout << "\n";
            cout << "Enter the width of the board: ";
            cin >> width;
            cout << "\n";
            cout << "Enter the minimum number of pieces required: ";
            cin >> minimumChess;
            cout << "\n";
            ChessDomination *cd = new ChessDomination(height, width, minimum, type, totalDom);
            (*cd).Solve();
         }
            catch (exception e){
            }
      }
      return 0;
   }
