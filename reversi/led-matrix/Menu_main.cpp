
#include <exception>  // terminate()
#include <cstdlib>    // abort()


#include "ShowReversiBoard.h"
#include "include/led-matrix.h"
#include "include/threaded-canvas-manipulator.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <exception>


int main(int argc, char **argv) {
	//Go interface section of startup
	int rows = 32;
	int chain = 1;
	int parallel = 1;
	bool do_luminance_correct = true;
	char input;
	
	pid_t pid;
	char *child_args[5];
	child_args[1] = "1";
	child_args[2] = "3";
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
	//image_gen = new Menu(canvas, mode, players, difficulty, size);
        
        image_gen = new BoardTextfile(canvas, "reversi.txt");
	if (image_gen == NULL) return -1;
        image_gen->Start();
	getchar();
        canvas->Clear();
        //delete image_gen;

	/*switch (pid = fork()) {
		case -1: 
			perror("fork");
			break;
		case 0:*/
			while (mode == 1) {
                                if(players == 1) {
                                        ThreadedCanvasManipulator *image_gen1 = NULL;
                                        image_gen1 = new BoardTextfile(canvas, "players_1.txt");
                                        if (image_gen == NULL) return -1;
                                        image_gen->Start();
                                }
                                else if (players == 2) {
                                        image_gen = new BoardTextfile(canvas, "players_2.txt");
                                        if (image_gen == NULL) return -1;
                                        image_gen->Start();
                                }

				input = getchar();
				canvas->Clear();
				//delete image_gen;
				
				if (input == 'w' && players == 1) {
						players++;
				} 
				else if (input == 's' && players == 2) {
					players--;
				}
				else if (input == '\n') {
					if (players == 1) { 
						mode++;
						child_args[1] = "1";
					}
					else { 
						child_args[0] = "2"; 
						mode = mode+2;
					}
				}
				
			}
					
			while (mode == 2) {
                                        if(difficulty == 1) {
                                                image_gen = new BoardTextfile(canvas, "easy.txt");
                                                if (image_gen == NULL) return -1;
                                                image_gen->Start();

                                        }
                                        else if (difficulty == 2) {
                                                image_gen = new BoardTextfile(canvas, "medium.txt");
                                                if (image_gen == NULL) return -1;
                                                image_gen->Start();

                                        }
                                        else if (difficulty == 3) {
                                                image_gen = new BoardTextfile(canvas, "hard.txt");
                                                if (image_gen == NULL) return -1;
                                                image_gen->Start();

                                        }
		

	       			input = getchar();
				    canvas->Clear();
				   // delete image_gen;
					
					if (input == 'w' && difficulty < 3) {
						difficulty++;
					}
					else if (input == 's' && difficulty > 1) {
						difficulty--;
					}
					else if (input == '\n') {
						mode++;
						if(difficulty == 1) {
							child_args[2] = "1";
						} 
						else if (difficulty == 2) {
							child_args[2] = "2";
						}
						else if (difficulty == 3) {
							child_args[2] = "4";
						}
					}
					
				}
					
				if (mode == 3) {
					input = getchar();
				    canvas->Clear();
				    delete image_gen;
					
					if (input == 'w' && size == 1) {
						size++;
					}
					else if (input == 's' && size == 2) {
						size--;
					}
					else if (input == '\n') {
						if(size == 1) {
							/*child_args[0] = "./Othello_size8";
							execv("./Othello_size8 ",  child_args);
							puts("Uh oh! If this prints, execv() must have failed");
							exit(EXIT_FAILURE);*/
						} else {
							/*child_args[0] = "./Othello_size16";
							execv("./Othello_size16 ",  child_args);
							puts("Uh oh! If this prints, execv() must have failed");
							exit(EXIT_FAILURE);*/
						}
					}
					if(size == 1) {
						image_gen = new BoardTextfile(canvas, "8x8.txt");
						if (image_gen == NULL) return -1;
						image_gen->Start();
					}
					else {
						image_gen = new BoardTextfile(canvas, "16x16.txt");
						if (image_gen == NULL) return -1;
						image_gen->Start();
					}
			        
				}		
				if (mode > 3 || mode < 1) {
					std::cout << "menu failed in Menu_main.c" << std::endl;
				}
		/*default:
			puts("End of fork\n");
			break;
	}*/

	canvas->Clear();
	delete image_gen;
    delete canvas;
	return 0; 
}
