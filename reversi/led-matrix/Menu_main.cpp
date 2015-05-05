
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

<<<<<<< HEAD
	if ((pid = fork())< 0) { 
	    perror("fork");
	}
	else if (pid == 0) {
		while (mode == 1) {
				ThreadedCanvasManipulator *image_gen1 = NULL;
                if(players%2 == 1) {             
                    image_gen1 = new BoardTextfile(canvas, "players_1.txt");
                    if (image_gen1 == NULL) return -1;
                    image_gen1->Start();
                }
                else if (players%2 == 0) {
                    image_gen1 = new BoardTextfile(canvas, "players_2.txt");
                    if (image_gen1 == NULL) return -1;
                    image_gen1->Start();
                }
=======
	if ((pid = fork()) < 0) {
		perror("fork");
	}
	else if (pid == 0) {
		while (mode == 1) {
			ThreadedCanvasManipulator *image_gen1 = NULL;
            if(players%2 == 1) {             
                image_gen1 = new BoardTextfile(canvas, "players_1.txt");
                if (image_gen1 == NULL) return -1;
                image_gen1->Start();
            }
            else if (players%2 == 0) {
                image_gen1 = new BoardTextfile(canvas, "players_2.txt");
                if (image_gen1 == NULL) return -1;
                image_gen1->Start();
            }
>>>>>>> 62bad4feb6b423c397c3a10eee821070b4ff8941

			input = getchar();
			canvas->Clear();
		
			if (input == 'w') {
				players++;
				printf("players: %d\n", players);
			} 
			else if (input == 's') {
				players--;
				printf("players: %d\n", players);
			}
			else if (input == 'n') {
				if (players%2 == 1) { 
					mode++;
					child_args[1] = "1";
				}
				else if(players%2 == 0) { 
					child_args[0] = "2"; 
					mode = mode+2;
				}
			}
			//delete image_gen1;
		}
				
		while (mode == 2) {
            ThreadedCanvasManipulator *image_gen2 = NULL;
			if(difficulty%3 == 1) {
                image_gen2 = new BoardTextfile(canvas, "easy.txt");
                if (image_gen2 == NULL) return -1;
                image_gen2->Start();
			}
            else if (difficulty%3 == 2) {
                image_gen2 = new BoardTextfile(canvas, "medium.txt");
                if (image_gen2 == NULL) return -1;
                image_gen2->Start();
			}
            else if (difficulty%3 == 0) {
                image_gen2 = new BoardTextfile(canvas, "hard.txt");
                if (image_gen2 == NULL) return -1;
                image_gen2->Start();
			}
     		    input = getchar();
			    canvas->Clear();
				
				if (input == 'w') {
					difficulty++;
					printf("difficulty: %d\n", difficulty);
				}
				else if (input == 's') {
					difficulty--;
					printf("difficulty: %d\n", difficulty);
				}
				else if (input == 'n') {
					mode++;
					if(difficulty%3 == 1) {
						child_args[2] = "1";
					} 
					else if (difficulty%3 == 2) {
						child_args[2] = "2";
					}
					else if (difficulty%3 == 3) {
						child_args[2] = "0";
					}
				}
				//delete image_gen2;
			}
				
			while (mode == 3) {
				ThreadedCanvasManipulator *image_gen3 = NULL;
				if(size%2 == 1) {
					image_gen3 = new BoardTextfile(canvas, "8x8.txt");
					if (image_gen3 == NULL) return -1;
					image_gen3->Start();
				}
				else if (size%2 == 0) {
					image_gen3 = new BoardTextfile(canvas, "16x16.txt");
					if (image_gen3 == NULL) return -1;
					image_gen3->Start();
				}
				
				input = getchar();
			    canvas->Clear();
			    //delete image_gen;
				
				if (input == 'w') {
					size++;
					printf("size: %d\n", size);
				}
				else if (input == 's') {
					size--;
					printf("size: %d\n", size);
				}
				else if (input == 'n') {
					if(size%2 == 1) {
						child_args[0] = "./Othello_size8";
						execv("./Othello_size8 ",  child_args);
						puts("Uh oh! If this prints, execv() must have failed");
						exit(EXIT_FAILURE);
					} else if (size%2 == 0) {
						child_args[0] = "./Othello_size16";
						execv("./Othello_size16 ",  child_args);
						puts("Uh oh! If this prints, execv() must have failed");
						exit(EXIT_FAILURE);
					}
				}
<<<<<<< HEAD
		} else {
=======
				//delete image_gen3;
			}		
			if (mode > 3 || mode < 1) {
				std::cout << "menu failed in Menu_main.c" << std::endl;
			}
		}
		else {
>>>>>>> 62bad4feb6b423c397c3a10eee821070b4ff8941
			puts("End of fork\n");
		}

	canvas->Clear();
	delete image_gen;
    delete canvas;
	return 0; 
}
