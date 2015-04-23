#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"

#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>

using std::min;
using std::max;

using namespace rgb_matrix;

class GoBoard : public ThreadedCanvasManipulator {
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

class GoBoard2 : public ThreadedCanvasManipulator {
public:
  GoBoard2(Canvas *m)  : ThreadedCanvasManipulator(m) {}
  void Run() {
    const int board_size = 24;
    for (int i = 13; i < board_size; ++i) {
      canvas()->SetPixel(i, 0, 200, 100, 100);
      canvas()->SetPixel(0, i, 200, 100, 100);
      canvas()->SetPixel(board_size - 1, i, 200, 100, 100);
      canvas()->SetPixel(i, board_size - 1, 200, 100, 100);
    }
  }
};
 

int main(int argc, char *argv[]) {
  bool as_daemon = false; //run as daemon. Use this when starting in /etc/init.d or running without terminal
  int rows = 32;
  int chain = 1;
  int parallel = 1;
  bool do_luminance_correct = true;

  if (getuid() != 0) {
    //"Must run as root to be able to access /dev/mem
    //Prepend 'sudo' to the command
    return 1;
  }

  // Initialize GPIO pins. This might fail when we don't have permissions.
  GPIO io;
  if (!io.Init())
    return 1;

  // Start daemon before we start any threads.
  if (as_daemon) {
    if (fork() != 0)
      return 0;
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

  // The matrix, our 'frame buffer' and display updater.
  RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);
  matrix->set_luminance_correct(do_luminance_correct);

  Canvas *canvas = matrix;

  // The ThreadedCanvasManipulator objects are filling
  // the matrix continuously.
  ThreadedCanvasManipulator *image_gen = NULL;
  image_gen = new GoBoard(canvas);

  if (image_gen == NULL)
    return -1;

  // Image generating demo is crated. Now start the thread.
  image_gen->Start();
  getchar();
  canvas->Clear();
  delete image_gen;
  image_gen = new GoBoard2(canvas);
  image_gen->Start();

  // Now, the image generation runs in the background. We can do arbitrary
  // things here in parallel.
  if (as_daemon) {
    sleep(INT_MAX);
  } else {
    //press any key to exit
    getchar();
  }

  // Stop image generating thread.
  delete image_gen;
  delete canvas;

  return 0;
}
