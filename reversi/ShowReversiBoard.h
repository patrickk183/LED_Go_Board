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

bool pcolor_set = false;
bool splash_done;
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
          canvas()->SetPixel(4*j, 4*i, 75, 25, 75);
          canvas()->SetPixel(4*j, 4*i+1, 75, 25, 75);
          canvas()->SetPixel(4*j, 4*i+2, 75, 25, 75);
          canvas()->SetPixel(4*j, 4*i+3, 75, 25, 75);
          canvas()->SetPixel(4*j+1, 4*i, 75, 25, 75);
          canvas()->SetPixel(4*j+1, 4*i+1, 75, 25, 75);
          canvas()->SetPixel(4*j+1, 4*i+2, 75, 25, 75);
          canvas()->SetPixel(4*j+1, 4*i+3, 75, 25, 75);
          canvas()->SetPixel(4*j+2, 4*i, 75, 25, 75);
          canvas()->SetPixel(4*j+2, 4*i+1, 75, 25, 75);
          canvas()->SetPixel(4*j+2, 4*i+2, 75, 25, 75);
          canvas()->SetPixel(4*j+2, 4*i+3, 75, 25, 75);
          canvas()->SetPixel(4*j+3, 4*i, 75, 25, 75);
          canvas()->SetPixel(4*j+3, 4*i+1, 75, 25, 75);
          canvas()->SetPixel(4*j+3, 4*i+2, 75, 25, 75);
          canvas()->SetPixel(4*j+3, 4*i+3, 75, 25, 75);
          

        }
        else {
        switch (board[i][j]) {
          case '@':
            canvas()->SetPixel(4*j, 4*i, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j, 4*i+1, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j, 4*i+2, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j, 4*i+3, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+1, 4*i, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+1, 4*i+1, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+1, 4*i+2, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+1, 4*i+3, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+2, 4*i, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+2, 4*i+1, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+2, 4*i+2, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+2, 4*i+3, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+3, 4*i, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+3, 4*i+1, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+3, 4*i+2, p1color.R, p1color.G, p1color.B);
            canvas()->SetPixel(4*j+3, 4*i+3, p1color.R, p1color.G, p1color.B);
            break;
          case 'O':
            canvas()->SetPixel(4*j, 4*i, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j, 4*i+1, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j, 4*i+2, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j, 4*i+3, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+1, 4*i, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+1, 4*i+1, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+1, 4*i+2, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+1, 4*i+3, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+2, 4*i, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+2, 4*i+1, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+2, 4*i+2, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+2, 4*i+3, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+3, 4*i, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+3, 4*i+1, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+3, 4*i+2, p2color.R, p2color.G, p2color.B);
            canvas()->SetPixel(4*j+3, 4*i+3, p2color.R, p2color.G, p2color.B);
            break;
          default:
            canvas()->SetPixel(4*j, 4*i, 30, 30, 30);
            canvas()->SetPixel(4*j, 4*i+1, 30, 30, 30);
            canvas()->SetPixel(4*j, 4*i+2, 30, 30, 30);
            canvas()->SetPixel(4*j, 4*i+3, 30, 30, 30);
            canvas()->SetPixel(4*j+1, 4*i, 30, 30, 30);
            canvas()->SetPixel(4*j+1, 4*i+1, 30, 30, 30);
            canvas()->SetPixel(4*j+1, 4*i+2, 30, 30, 30);
            canvas()->SetPixel(4*j+1, 4*i+3, 30, 30, 30);
            canvas()->SetPixel(4*j+2, 4*i, 30, 30, 30);
            canvas()->SetPixel(4*j+2, 4*i+1, 30, 30, 30);
            canvas()->SetPixel(4*j+2, 4*i+2, 30, 30, 30);
            canvas()->SetPixel(4*j+2, 4*i+3, 30, 30, 30);
            canvas()->SetPixel(4*j+3, 4*i, 30, 30, 30);
            canvas()->SetPixel(4*j+3, 4*i+1, 30, 30, 30);
            canvas()->SetPixel(4*j+3, 4*i+2, 30, 30, 30);
            canvas()->SetPixel(4*j+3, 4*i+3, 30, 30, 30);
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
    filename = "../assets/" + f;
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
            canvas()->SetPixel(j, i, 50, 0, 0);
            break;
          case 2:
            canvas()->SetPixel(j, i, 50, 50, 50);
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
  ChooseColorMenu(Canvas *m, std::string arg, int a_player)  : ThreadedCanvasManipulator(m) {
    filename = "../assets/" + arg;
    player = a_player;
  }

  void Run() {
    int percentage = 0;
    int value = 0;
    Color c1 = {70, 0, 0};
    Color c2 = {0, 70, 0};
    Color c3 = {0, 0, 70};
    Color display = {0, 0, 0};
    Color former = c1;
    Color latter = c2;
    std::fstream fs(filename.c_str(), std::ios_base::in);

    while (true) {
      if (former.R == c1.R && former.G == c1.G && former.B == c1.B) {former = c2; latter = c3;}
      else if (former.R == c2.R && former.G == c2.G && former.B == c2.B) {former = c3; latter = c1;}
      else if (former.R == c3.R && former.G == c3.G && former.B == c3.B) {former = c1; latter = c2;}
      while(percentage != 100) {
        display = interpolate(former, latter, percentage);
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
              fs >> value;
              if ((i < 12 || i > 20) || (j < 12 || j > 20)) {
                if (fs.good()) {
                  switch (value) {
                    case 1:
                      canvas()->SetPixel(j, i, 50, 0, 0);
                      break;
                    case 2:
                      canvas()->SetPixel(j, i, 50, 50, 50);
                      break;
                    default:
                      canvas()->SetPixel(j, i, 0, 0, 0);
                      break;
                  }
                }
              }
              else {
                canvas()->SetPixel(j, i, display.R, display.G, display.B);
              }
            }
        }
        percentage++;
        usleep(10000);
        if (/*isSelected(1)*/ pcolor_set == true) {
          pcolor_set = true;
          if (player == 1) { p1color = display; }
          else { p2color = display; }
          break;
        }
      }
      percentage = 0;
      fs.clear();
      fs.seekg(0, std::ios::beg);
      if (pcolor_set == true) {
        break;
      }
    }

   fs.close();

   }

private:
  std::string filename;
  int player;
};

class SplashScreen : public ThreadedCanvasManipulator { 
public: 
  SplashScreen(Canvas *m)  : ThreadedCanvasManipulator(m) {
  }

  void Run() {
    int percentage = 0;
    int percentage2 = 0;
    int value = 0;
    Color c1 = {50, 0, 0};
    Color c2 = {0, 50, 0};
    Color c3 = {0, 0, 50};
    Color display = {0, 0, 0};
    Color former = c1;
    Color latter = c2;
    Color other = c3;
    Color interp1 = {0, 0, 0};
    Color interp2 = {0, 0, 0};
    std::string filename = "../assets/reversi.txt";
    std::fstream fs(filename.c_str(), std::ios_base::in);

    while (true) {
      if (former.R == c1.R && former.G == c1.G && former.B == c1.B) {former = c2; latter = c3; other = c1;}
      else if (former.R == c2.R && former.G == c2.G && former.B == c2.B) {former = c3; latter = c1; other = c2;}
      else if (former.R == c3.R && former.G == c3.G && former.B == c3.B) {former = c1; latter = c2; other = c3;}
      while(percentage != 100) {
        interp1 = interpolate(former, latter, percentage);
        interp2 = interpolate(latter, other, percentage);
        //display = interpolate(former, latter, percentage);
        for (int i = 0; i < MATRIX_SIZE; i++) {
          display = interpolate(interp1, interp2, percentage2);
          for (int j = 0; j < MATRIX_SIZE; j++) {
            fs >> value;
            if (fs.good()) {
              switch (value) {
                case 1:
                  canvas()->SetPixel(j, i, 100, 100, 100);
                  break;
                default:
                  canvas()->SetPixel(j, i, display.R, display.G, display.B);
                  break;
              }
            }
          }
          percentage2++;
        }
        percentage2 = 0;
        percentage++;
        fs.clear();
        fs.seekg(0, std::ios::beg);
        usleep(7500);
        if (splash_done == true) {
          break;
        }
      }
      percentage = 0;
      if (splash_done == true) {
          break;
      }
    }

   fs.close();

   }

private:
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
          if (value == 1) canvas()->SetPixel(j, i, 75, 0, 0);
          if (value == 2) canvas()->SetPixel(j, i, 50, 50, 50);
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

class TransitionDisplay : public ThreadedCanvasManipulator { 
public: 
  //In this case, b is an array of pieces to transition from c1 to c2
  TransitionDisplay(Canvas *m, bool b[SIZE][SIZE], Color a_c1, Color a_c2) : ThreadedCanvasManipulator(m)
  {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = b[i][j];
        }
    } 
    c1 = a_c1;
    c2 = a_c2;
  }
  void Run() {

    int percentage = 0;
    Color display = {0, 0, 0};

    while (percentage != 100) {
      display = interpolate(c1, c2, percentage);
      for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
          if (board[i][j] == true) {
              canvas()->SetPixel(4*j, 4*i, display.R, display.G, display.B);
              canvas()->SetPixel(4*j, 4*i+1, display.R, display.G, display.B);
              canvas()->SetPixel(4*j, 4*i+2, display.R, display.G, display.B);
              canvas()->SetPixel(4*j, 4*i+3, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+1, 4*i, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+1, 4*i+1, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+1, 4*i+2, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+1, 4*i+3, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+2, 4*i, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+2, 4*i+1, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+2, 4*i+2, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+2, 4*i+3, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+3, 4*i, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+3, 4*i+1, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+3, 4*i+2, display.R, display.G, display.B);
              canvas()->SetPixel(4*j+3, 4*i+3, display.R, display.G, display.B);
          }
        }
      }
      usleep(10000);
      percentage++;
    }
  }

  private:
    char board[SIZE][SIZE];
    Color c1;
    Color c2;
};
