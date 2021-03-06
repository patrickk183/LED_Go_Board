#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <climits>
#include <unistd.h>

extern FILE *stderr, *stdin, *stdout;

using std::min;
using std::max;

using namespace rgb_matrix;

class ShowReversiBoard : public ThreadedCanvasManipulator {
public:
  ShowReversiBoard(Canvas *m)  : ThreadedCanvasManipulator(m) {}
  void Run() {
    
   const int board_size = 32;
    for (int i = 0; i < board_size; ++i) {
   //   canvas()->SetPixel(i, 0, 100, 100, 200);
   //   canvas()->SetPixel(0, i, 100, 100, 200);
   //   canvas()->SetPixel(board_size - 1, i, 100, 100, 200);
   //   canvas()->SetPixel(i, board_size - 1, 100, 100, 200);
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
  }
};

class Menu : public ThreadedCanvasManipulator { 
public: 
  Menu(Canvas *m)  : ThreadedCanvasManipulator(m) {}
    void Run() {
  std::string filename = "../../assets/reversi.txt";
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
};
 
// Example code
 // int main(int argc, char *argv[]) {
   // bool as_daemon = false; //run as daemon. Use this when starting in /etc/init.d or running without terminal
   // int rows = 32;
   // int chain = 1;
   // int parallel = 1;
   // bool do_luminance_correct = true;

   // if (getuid() != 0) {
     // //"Must run as root to be able to access /dev/mem
     // //Prepend 'sudo' to the command
     // return 1;
   // }

   // // Initialize GPIO pins. This might fail when we don't have permissions.
   // GPIO io;
   // if (!io.Init())
     // return 1;

   // // Start daemon before we start any threads.
   // if (as_daemon) {
     // if (fork() != 0)
       // return 0;
     // close(STDIN_FILENO);
     // close(STDOUT_FILENO);
     // close(STDERR_FILENO);
   // }

   // // The matrix, our 'frame buffer' and display updater.
   // RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);
   // matrix->set_luminance_correct(do_luminance_correct);

   // Canvas *canvas = matrix;

   // // The ThreadedCanvasManipulator objects are filling
   // // the matrix continuously.
   // ThreadedCanvasManipulator *image_gen = NULL;
   // //image_gen = new Menu(canvas);
  // image_gen = new ShowReversiBoard(canvas);
   // if (image_gen == NULL)
     // return -1;

   // // Image generating demo is created. Now start the thread.
   // image_gen->Start();
   // getchar();
   // canvas->Clear();
   // delete image_gen;

   // // Now, the image generation runs in the background. We can do arbitrary
   // // things here in parallel.
   // if (as_daemon) {
     // sleep(INT_MAX);
   // } else {
     // //press any key to exit
     // getchar();
   // }

   // // Stop image generating thread.
   // delete image_gen;
   // delete canvas;

   // return 0;
 // }
