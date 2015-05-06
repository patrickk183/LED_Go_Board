#include "include/led-matrix.h"
#include "include/threaded-canvas-manipulator.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "Color.h"
#include "ControllerInput.h"

#define SIZE 8
#define MATRIX_SIZE 32

using namespace rgb_matrix;

class Cursor {
  int x, y;
public:
  Cursor() {
    x = 0;
    y = 0;
  }
  int getx() {
    return x;
  }
  int gety() {
    return y;
  }
  void setX(int a) {
    x = a;
  }
  void setY(int a) {
    y = a;
  }
};

bool p1color_set = false, p2color_set = false;
Color p1color = {0, 0, 0}, p2color = {0, 0, 0};

class BoardArray : public ThreadedCanvasManipulator { 
public: 
  BoardArray(Canvas *m, char b[SIZE][SIZE], Cursor a_curs)  : ThreadedCanvasManipulator(m)
  {
    curs = a_curs;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = b[i][j];
        }
    } 
  }
  void Run() {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; j++) {
        if (j == curs.getx() && i == curs.gety()) {
          canvas()->SetPixel(2*j+ 8, 2*i+ 8, 200, 50, 200);
          canvas()->SetPixel(2*j+ 8, 2*i+1+ 8, 200, 50, 200);
          canvas()->SetPixel(2*j+1+ 8, 2*i+ 8, 200, 50, 200);
          canvas()->SetPixel(2*j+1+ 8, 2*i+1+ 8, 200, 50, 200);
        }
        else {
        switch (board[i][j]) {
          case '@':
            canvas()->SetPixel(2*j+ 8, 2*i+ 8, 200, 0, 0);
            canvas()->SetPixel(2*j+ 8, 2*i+1+ 8, 200, 0, 0);
            canvas()->SetPixel(2*j+1+ 8, 2*i+ 8, 200, 0, 0);
            canvas()->SetPixel(2*j+1+ 8, 2*i+1+ 8, 200, 0, 0);
            break;
          case 'O':
            canvas()->SetPixel(2*j + 8, 2*i + 8, 0, 0, 200);
            canvas()->SetPixel(2*j+ 8, 2*i+1+ 8, 0, 0, 200);
            canvas()->SetPixel(2*j+1+ 8, 2*i+ 8, 0, 0, 200);
            canvas()->SetPixel(2*j+1+ 8, 2*i+1+ 8, 0, 0, 200);
            break;
          default:
            canvas()->SetPixel(2*j+ 8, 2*i+ 8, 100, 100, 100);
            canvas()->SetPixel(2*j+ 8, 2*i+1+ 8, 100, 100, 100);
            canvas()->SetPixel(2*j+1+ 8, 2*i+ 8, 100, 100, 100);
            canvas()->SetPixel(2*j+1+ 8, 2*i+1+ 8, 100, 100, 100);
            break;
        }
       }
      }
    }
  }

  private:
    char board[SIZE][SIZE];
    Cursor curs;
};

class BoardTextfile : public ThreadedCanvasManipulator { 
public: 
  BoardTextfile(Canvas *m, std::string f)  : ThreadedCanvasManipulator(m)
  {
    filename = "../../assets/" + f;
  }
  void Run() {
    std::fstream fs(filename.c_str(), std::ios_base::in);
    int value = 0;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; j++) {
        fs >> value;
        if (!fs.good()) break;
        switch (value) {
          case 1:
            canvas()->SetPixel(j, i, 200, 0, 0);
            break;
          case 2:
            canvas()->SetPixel(j, i, 200, 200, 200);
            break;
          default:
            canvas()->SetPixel(j, i, 0, 0, 0);
            break;
        }
      }
    }
    fs.close();
  }

private:
  std::string filename;
};

class ChooseColorMenu : public ThreadedCanvasManipulator { 
public: 
  ChooseColorMenu(Canvas *m, std::string arg)  : ThreadedCanvasManipulator(m) {
    filename = "../../assets/" + arg;
  }

  void Run() {
    int percentage = 0;
    int value = 0;
    Color c1 = {200, 0, 0};
    Color c2 = {0, 200, 0};
    Color c3 = {0, 0, 200};
    Color display = {0, 0, 0};
    Color former = c1;
    Color latter = c2;
    std::fstream fs(filename.c_str(), std::ios_base::in);

    while (true) {
      if (former.R == c1.R && former.G == c1.G && former.B == c1.B) {former = c2; latter = c3;}
      if (former.R == c2.R && former.G == c2.G && former.B == c2.B) {former = c3; latter = c1;}
      if (former.R == c3.R && former.G == c3.G && former.B == c3.B) {former = c1; latter = c2;}
      while(percentage != 100) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
              fs >> value;
              if ((i < 12 || i > 20) || (j < 12 || j > 20)) {
                if (!fs.good()) break;
                switch (value) {
                  case 1:
                    canvas()->SetPixel(j, i, 200, 0, 0);
                    break;
                  case 2:
                    canvas()->SetPixel(j, i, 200, 200, 200);
                    break;
                  default:
                    canvas()->SetPixel(j, i, 0, 0, 0);
                    break;
                }
              }
              else {
                display = interpolate(former, latter, percentage);
                std::cout << percentage << " " << display.R << " " << display.G << " " << display.B << std::endl;
                canvas()->SetPixel(j, i, display.R, display.G, display.B);
              }
            }
        }
        percentage++;
        std::cout << "incrementing percentage" << std::endl;
        usleep(1000);
        if (/*isSelected(1)*/ getchar() == '\n') {
          p1color_set = true;
          p1color = display; 
          canvas()->Clear();
          break;
        }
      }
      percentage = 0;
      fs.clear();
      fs.seekg(0, std::ios::beg);

      if (p1color_set == true) {
        break;
      }
  }

  fs.close();

  }

private:
  std::string filename;
};

class Menu : public ThreadedCanvasManipulator { 
public: 
  Menu(Canvas *m, int a_mode, int a_players, int a_difficulty, int a_size)  : ThreadedCanvasManipulator(m) {
    players = a_players;
    difficulty = a_difficulty;
    mode = a_mode;
    size = a_size;
  }
    void Run() {
      std::string filename = "../../assets/";

      switch (mode) {
        case 1:
          if (players == 1) {
            filename += "players_1.txt";
          }
          else {
            filename += "players_2.txt";
          }
          break;
        case 2:
          if (difficulty == 1) {
            filename += "easy.txt";
          }
          else if (difficulty == 2) {
            filename += "medium.txt";
          }
          else {
            filename += "hard.txt";
          }
          break;
        case 3:
          if (size == 1) {
            filename += "9x9.txt";
          }
          else {
            filename += "19x19.txt";
          }
          break;
        default:
            filename += "hard.txt";
          break;
      }

      std::fstream fs(filename.c_str(), std::ios_base::in);

      const int size = 32;
      int value = 0;
      for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j++) {
          fs >> value;
          if (!fs.good()) break;
          if (value == 1) canvas()->SetPixel(j, i, 200, 0, 0);
          if (value == 2) canvas()->SetPixel(j, i, 200, 200, 200);
        }
      }
      fs.close();
    }

private:
  //players and difficulty signal what image to display within a set of images
  int players, difficulty, size;
  //mode indicates which set of images to check
  int mode;
};

class ShowReversiBoard : public ThreadedCanvasManipulator {
public:
  ShowReversiBoard(Canvas *m, int a_boardSize, int a_cursx, int a_cursy)  : ThreadedCanvasManipulator(m) {
    cursx = a_cursx;
    cursy = a_cursy;
    boardSize = a_boardSize;
  }
  void Run() {
	
    if (boardSize == 32) { //change pixels to 32

      //draw borders. Borders are on pixel 5 and 34 in both x and y directions
      for (int i = 0; i < 32; i++) {
        canvas()->SetPixel(i, 4, 100, 100, 200);
        canvas()->SetPixel(i, 5, 100, 100, 200);

        canvas()->SetPixel(i, 24, 100, 100, 200);
        canvas()->SetPixel(i, 25, 100, 100, 200);

        canvas()->SetPixel(4, i, 100, 100, 200);
        canvas()->SetPixel(5, i, 100, 100, 200);

        canvas()->SetPixel(24, i, 100, 100, 200); 
        canvas()->SetPixel(25, i, 100, 100, 200);      
      } 
      
      //Draw board state
      /*
      for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
          if (BOARD(i, j) == WHITE) {
            canvas()->SetPixel(i+5, j+5, 200, 200, 200);
          }
          else if (BOARD(i, j) == BLACK) {
            canvas()->SetPixel(i+5, j+5, 200, 50, 200);
          }
          if (i == cursx && j == cursy) {
            canvas()->SetPixel(i+5, j+5, 150, 0, 0);
          }
        }
      }*/

	  }
	  
	  if (boardSize == 16) { //change pixels to 16

      //draw borders. Borders are on pixel 5 and 34 in both x and y directions
      for (int i = 0; i < 32; i++) {
        canvas()->SetPixel(i, 4, 100, 100, 200);
        canvas()->SetPixel(i, 5, 100, 100, 200);

        canvas()->SetPixel(i, 24, 100, 100, 200);
        canvas()->SetPixel(i, 25, 100, 100, 200);

        canvas()->SetPixel(4, i, 100, 100, 200);
        canvas()->SetPixel(5, i, 100, 100, 200);

        canvas()->SetPixel(24, i, 100, 100, 200); 
        canvas()->SetPixel(25, i, 100, 100, 200);      
      } 

      //Draw board state
     /* 
     for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
          if (BOARD(i, j) == WHITE) {
            canvas()->SetPixel(i+5, j+5, 200, 200, 200);
          }
          else if (BOARD(i, j) == BLACK) {
            canvas()->SetPixel(i+5, j+5, 200, 50, 200);
          }
          if (i == cursx && j == cursy) {
            canvas()->SetPixel(i+5, j+5, 150, 0, 0);
          }
        }
      }
*/
	}

    else if (boardSize == 8) { //change pixels to 8
      //Draw borders
      for (int i = 0; i < 32; i++) {
        canvas()->SetPixel(i, 1, 100, 100, 200);

        canvas()->SetPixel(i, 2, 100, 100, 200);
        canvas()->SetPixel(i, 5, 100, 100, 200);
        canvas()->SetPixel(i, 8, 100, 100, 200);
        canvas()->SetPixel(i, 11, 100, 100, 200);
        canvas()->SetPixel(i, 14, 100, 100, 200);
        canvas()->SetPixel(i, 17, 100, 100, 200);
        canvas()->SetPixel(i, 20, 100, 100, 200);
        canvas()->SetPixel(i, 23, 100, 100, 200);
        canvas()->SetPixel(i, 26, 100, 100, 200);
        canvas()->SetPixel(i, 29, 100, 100, 200);

        canvas()->SetPixel(i, 30, 100, 100, 200);

        canvas()->SetPixel(1, i, 100, 100, 200);

        canvas()->SetPixel(2, i, 100, 100, 200);
        canvas()->SetPixel(5, i, 100, 100, 200);
        canvas()->SetPixel(8, i, 100, 100, 200);
        canvas()->SetPixel(11, i, 100, 100, 200);
        canvas()->SetPixel(14, i, 100, 100, 200);
        canvas()->SetPixel(17, i, 100, 100, 200);
        canvas()->SetPixel(20, i, 100, 100, 200);
        canvas()->SetPixel(23, i, 100, 100, 200);
        canvas()->SetPixel(26, i, 100, 100, 200);
        canvas()->SetPixel(29, i, 100, 100, 200);

        canvas()->SetPixel(30, i, 100, 100, 200); 
      }

      //Draw board state
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          //if (BOARD(i, j) == WHITE) {
            canvas()->SetPixel(3+3*i, 3+3*j, 200, 200, 200);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 200, 200, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 200, 200, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 200, 200, 200);
         // }
          //else if (BOARD(i, j) == BLACK) {
            canvas()->SetPixel(3+3*i, 3+3*j, 200, 50, 200);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 200, 50, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 200, 50, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 200, 50, 200);
         // }
          if (cursx == i && cursy == j) {
            canvas()->SetPixel(3+3*i, 3+3*j, 150, 0, 0);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 150, 0, 0);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 150, 0, 0);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 150, 0, 0);
          }
        }
      }
    } 
    else { ; } //do nothing. Board_size not supported
  }
  private:
	//players and difficulty signal what image to display within a set of images
	int cursx, cursy, boardSize;
};

