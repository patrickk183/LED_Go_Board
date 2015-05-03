#include "led-matrix/include/led-matrix.h"
#include "led-matrix/include/threaded-canvas-manipulator.h"
#include "../engine/gnugo.h"

#include <string.h>
#include <fstream>

using namespace rgb_matrix;

class ShowGoBoard : public ThreadedCanvasManipulator {
public:
  GoBoard(Canvas *m, int a_boardSize, int a_cursx, int a_cursy)  : ThreadedCanvasManipulator(m) {
    cursx = a_cursx;
    cursy = a_cursy;
    boardSize = a_boardSize;
  }
  void Run() {

    if (boardSize == 19) {

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
      for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
          if (BOARD(i, j) == WHITE) {
            canvas()->SetPixel(i+5, j+5, 200, 200, 200);
          }
          else if (BOARD(i, j) == BLACK) {
            canvas()->SetPixel(i+5, j+5, 200, 50, 200);
          }
          if (i == cx && j == cy) {
            canvas()->SetPixel(i+5, j+5, 150, 0, 0);
          }
        }
      }
    }
    else if (boardSize == 9) {
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
          if (BOARD(i, j) == WHITE) {
            canvas()->SetPixel(3+3*i, 3+3*j, 200, 200, 200);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 200, 200, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 200, 200, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 200, 200, 200);
          }
          else if (BOARD(i, j) == BLACK) {
            canvas()->SetPixel(3+3*i, 3+3*j, 200, 50, 200);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 200, 50, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 200, 50, 200);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 200, 50, 200);
          }
          if (cx == i && cy == j) {
            canvas()->SetPixel(3+3*i, 3+3*j, 150, 0, 0);
            canvas()->SetPixel(3+3*i, 3+3*j+1, 150, 0, 0);
            canvas()->SetPixel(3+3*i+1, 3+3*j, 150, 0, 0);
            canvas()->SetPixel(3+3*i+1, 3+3*j+1, 150, 0, 0);
          }
        }
      }
    } 
    else { } //do nothing. Board_size not supported
  }
  int boardSize;
  int cursx;
  int cursy;
};

class Menu : public ThreadedCanvasManipulator { 
public: 
	Menu(Canvas *m, int a_mode, int a_players, int a_difficulty, a_size)  : ThreadedCanvasManipulator(m) {
		players = a_players;
		difficulty = a_difficulty;
		mode = a_mode;
		size = a_size;
	}
  	void Run() {
  		std::string filename = "../assets/";

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
