

#include "ShowReversiBoard.h"
#include "include/led-matrix.h"
#include "include/threaded-canvas-manipulator.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
	//Go interface section of startup
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

	// The matrix, our 'frame buffer' and display updater.
	RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);
	matrix->set_luminance_correct(do_luminance_correct);

	Canvas *canvas = matrix;

	int players = 1;
	int mode = 1;
	int size = 1;
	int difficulty = 1;

	// The ThreadedCanvasManipulator objects are filling
	// the matrix continuously.
	ThreadedCanvasManipulator *image_gen = NULL;
	image_gen = new Menu(canvas, mode, players, difficulty, size);

	if (image_gen == NULL)
	return -1;

	// Image generating demo is created. Now start the thread.
	image_gen->Start();

	while(mode < 4) {
		char input = getchar();

		//change settings
		switch (mode) {
			case 1:
				if (input == 'w' && players == 1) {
					players++;
				}
				else if (input == 's' && players == 2) {
					players--;
				}
				else if (input == '\n') {
					if (players == 1) { mode = 2; }
					else { mode = 3; }
				}
				break;
			case 2:
				if (input == 'w' && difficulty < 3) {
					difficulty++;
				}
				else if (input == 's' && difficulty > 1) {
					difficulty--;
				}
				else if (input == '\n') {
					mode++;
				}
				break;
			case 3:
				if (input == 'w' && size == 1) {
					size++;
				}
				else if (input == 's' && size == 2) {
					size--;
				}
				else if (input == '\n') {
					mode++;
				}
				break;
			default:
				std::cout << "menu failed in main.c" << std::endl;
				break;
		}

		canvas->Clear();
		delete image_gen;
		image_gen = new Menu(canvas, mode, players, difficulty, size);
		image_gen->Start();
	}
	canvas->Clear();
	delete image_gen;

	image_gen = new ShowReversiBoard(canvas, size, 0, 0);
	getchar();

	// Stop image generating thread.
	delete image_gen;
	delete canvas;
}