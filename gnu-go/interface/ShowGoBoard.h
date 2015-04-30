#include "led-matrix/include/led-matrix.h"
#include "led-matrix/include/threaded-canvas-manipulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace rgb_matrix;

class ShowGoBoard : public ThreadedCanvasManipulator {
public:
  GoBoard(Canvas *m)  : ThreadedCanvasManipulator(m) {}
  void Run() {
    const int board_size = 11;
    for (int i = 0; i < board_size; ++i) {
      canvas()->SetPixel(i, 0, 100, 100, 200);
      canvas()->SetPixel(0, i, 100, 100, 200);
      canvas()->SetPixel(board_size - 1, i, 100, 100, 200);
      canvas()->SetPixel(i, board_size - 1, 100, 100, 200);
    }
  }
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
  		string filename = "../assets/";

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

	    const int board_size = 32;
	    int value = 0;
	    for (int i = 0; i < board_size; ++i) {
	     	for (int j = 0; j < board_size; j++) {
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