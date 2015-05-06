
#include <exception>  // terminate()
#include <cstdlib>    // abort()
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <exception>

#include "ShowReversiBoard.h"
#include "include/led-matrix.h"
#include "include/threaded-canvas-manipulator.h"

void display(char board[SIZE][SIZE]);
void transition(int player) ;
int valid_moves(char board[][SIZE], int moves[][SIZE], char player); 
void make_move(char board[][SIZE], int row, int col, char player);  
void computer_move(char board[][SIZE], int moves[][SIZE], char player, int deptha);  
int best_move(char board[][SIZE], int moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);
int reversi_main8(int player_count, int depth);

RGBMatrix *matrix;
Canvas *canvas;
ThreadedCanvasManipulator* image_gen;
Cursor curs;
GPIO io;

bool transition_tiles[SIZE][SIZE];
Color transArg1;
Color transArg2;

int main(int argc, char **argv) {

  //Go interface section of startup
  int rows = 32;
  int chain = 1;
  int parallel = 1;
  bool do_luminance_correct = true;
  char input;
  
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
  matrix = new RGBMatrix(&io, rows, chain, parallel);
  matrix->set_luminance_correct(do_luminance_correct);
  canvas = matrix;

  int players = 1;
  int mode = 1;
  int size = 1;
  int difficulty = 31;

  // The ThreadedCanvasManipulator objects are filling
  // the matrix continuously.
  
  delete image_gen;
  image_gen = new SplashScreen(canvas);
  if (image_gen == NULL) { return -1; }
  image_gen->Start();
  while (isNotSelected(1) && isNotSelected(2)) {usleep(1000); }
  //debug
  //getchar();
  sleep(1);
  splash_done = true;
  canvas->Clear();

  //player 1 color select
  delete image_gen;
  image_gen = new ChooseColorMenu(canvas, "color_1.txt", 1);
  if (image_gen == NULL) return -1;
  image_gen->Start();
  while (isNotSelected(1)) { usleep(10000); }
  pcolor_set = true;
  sleep(1);
  delete image_gen;
  image_gen = NULL;
  pcolor_set = false;

  //player 2 color select
  delete image_gen;
  image_gen = new ChooseColorMenu(canvas, "color_2.txt", 2);
  if (image_gen == NULL) return -1;
  image_gen->Start();
  while (isNotSelected(2)) { usleep(10000); }
  pcolor_set = true;
  sleep(1);
  delete image_gen;
  image_gen = NULL;
  pcolor_set = false;

  while (mode == 1) {
    delete image_gen;
    if(abs(players)%2 == 1) { 
        image_gen = new BoardTextfile(canvas, "players_1.txt");
        if (image_gen == NULL) return -1;
        image_gen->Start();
    }
    else if (abs(players)%2 == 0) {
        image_gen = new BoardTextfile(canvas, "players_2.txt");
        if (image_gen == NULL) return -1;
        image_gen->Start();
    }

    if (isDown(1) || isDown(2)) {
      players--;
    } 
    else if (isUp(1) || isUp(2)) {
      players++;
    }
    else if (isSelected(1) || isSelected(2)) {
      if (abs(players)%2 == 1) { 
        players = 1;
        mode = 2;
      }
      else if(abs(players)%2 == 0) { 
        players = 2;
        mode = 3;
      }
      usleep(500000);
    }
    usleep(200000);
    canvas->Clear();
    // delete image_gen;
  }
    
  while (mode == 2) {
    image_gen = NULL;
    delete image_gen;    
    if(abs(difficulty)%3 == 1) {
      image_gen = new BoardTextfile(canvas, "easy.txt");
      if (image_gen == NULL) { return -1; }
      image_gen->Start();
    }
    else if (abs(difficulty)%3 == 2) {
        image_gen = new BoardTextfile(canvas, "medium.txt");
        if (image_gen == NULL) return -1;
        image_gen->Start();
    }
    else if (abs(difficulty)%3 == 0) {
        image_gen = new BoardTextfile(canvas, "hard.txt");
        if (image_gen == NULL) { return -1; }
        image_gen->Start();
    }  
    
    canvas->Clear();
      
    if (isDown(1) || isDown(2)) {
      difficulty++;
    }
    else if (isUp(1) || isUp(2)) {
      difficulty--;
    }
    else if (isSelected(1) || isSelected(2) ) {
      if (abs(difficulty)%3 == 1) { difficulty = 2;}
      if (abs(difficulty)%3 == 2) { difficulty = 3;}
      if (abs(difficulty)%3 == 0) { difficulty = 4;}
      mode = 3;
      usleep(500000);
    }
    usleep(200000);
    // delete image_gen;
  }
  
  reversi_main8(players, difficulty);
      
  canvas->Clear();
  delete image_gen;
  delete canvas;
  return 0; 
}

int reversi_main8(int player_count, int depth)
{
  
  char board [SIZE][SIZE] = {0};  /* The board           */
  int moves[SIZE][SIZE] = { 0 };    /* Valid moves         */
  int row = 0;                      /* Board row index     */
  int col = 0;                      /* Board column index  */
  int no_of_games = 0;              /* Number of games     */
  int no_of_moves = 0;              /* Count of moves      */
  int invalid_moves = 0;            /* Invalid move count  */
  int comp_score = 0;               /* Computer score      */
  int user_score = 0;               /* Player score        */
  char y = 0;                       /* Column letter       */
  int x = 0;                        /* Row number          */
  char again = 0;                   /* Replay choice input */
  int player = 0;                   /* Player indicator    */

   /* The main game loop */
  do {
    /* On even games the player starts; */
    /* on odd games the computer starts */
    player = ++no_of_games % 2; 
    no_of_moves = 4;                /* Starts with four counters */

    /* Blank all the board squares */    
    for(row = 0; row < SIZE; row++) {
      for(col = 0; col < SIZE; col++) {
        board[row][col] = ' ';
      }
    }
    /* Place the initial four counters in the center */
    board[SIZE/2 - 1][SIZE/2 - 1] = board[SIZE/2][SIZE/2] = 'O';
    board[SIZE/2 - 1][SIZE/2] = board[SIZE/2][SIZE/2 - 1] = '@';

    /* The game play loop */
    do {

      display(board);             /* Display the board  */
      
      if(player++ % 2) { /*   It is the player's turn                    */
        if(valid_moves(board, moves, 'O')) {
          /* Read player moves until a valid move is entered */
          for(;;)  {
            // fflush(stdin);              /* Flush the keyboard buffer */
            // printf("Please enter your move (row column): "); 
            // scanf("%d%c", &x, &y);              /* Read input        */
            // y = tolower(y) - 'a';         /* Convert to column index */
            // x--;                           //Convert to row index    

            while (isNotSelected(1)) {
              if (isUp(1)) {
                if (curs.gety()-1 >= 0) {
                  curs.setY(curs.gety()-1);
                  canvas->Clear();
                  display(board);
                }
              }
              if (isDown(1)) {
                if (curs.gety()+1 < SIZE) {
                  curs.setY(curs.gety()+1);
                  canvas->Clear();
                  display(board);;
                }
              }
              if (isLeft(1)) {
                if (curs.getx()-1 >= 0) {
                  curs.setX(curs.getx()-1);
                  canvas->Clear();
                  display(board);
                }
              }
              if (isRight(1)) {
                if (curs.getx()+1 < SIZE) {
                  curs.setX(curs.getx()+1);
                  canvas->Clear();
                  display(board);
                }
              }
              usleep(100000);
            }
            if(moves[curs.gety()][curs.getx()]) {
              make_move(board, curs.gety(), curs.getx(), 'O');
              no_of_moves++;              /* Increment move count */
              transition(1);
              display(board);
              break;
            }
            else {
              delete image_gen;
              image_gen = new BoardTextfile(canvas, "illegal.txt");
              image_gen->Start();
              sleep(1);
              canvas->Clear();
              display(board);
            }
          }
        }
        else {                         /* No valid moves */
          ++invalid_moves;
        }
      }
      else if(player_count == 1) {
        /* It is the computer's turn                    */
        if(valid_moves(board, moves, '@')) /* Check for valid moves */
        {
          invalid_moves = 0;               /* Reset invalid count   */
          computer_move(board, moves, '@', depth);
          transition(2);
          no_of_moves++;                   /* Increment move count  */
        }
        else {
          ++invalid_moves;
        }
      } 
      else if(player_count == 2) {
        display(board);             /* Display the board  */
        //if(player++ % 2) { /*   It is the player's turn                    */
        if(valid_moves(board, moves, '@')) {
          /* Read player moves until a valid move is entered */
          for(;;) {

            fflush(stdin);
            char input;
            //while (input != 'w' || input != 's' || input != 'a' ||;input != 'd' || input != '\n') { input = getchar(); }

            while (isNotSelected(2)) {
              if (isUp(2)) {
                if (curs.gety()-1 >= 0) {
                  curs.setY(curs.gety()-1);
                  canvas->Clear();
                  display(board);
                }
              }
              if (isDown(2)) {
                if (curs.gety()+1 < SIZE) {
                  curs.setY(curs.gety()+1);
                  canvas->Clear();
                  display(board);;
                }
              }
              if (isLeft(2)) {
                if (curs.getx()-1 >= 0) {
                  curs.setX(curs.getx()-1);
                  canvas->Clear();
                  display(board);
                }
              }
              if (isRight(2)) {
                if (curs.getx()+1 < SIZE) {
                  curs.setX(curs.getx()+1);
                  canvas->Clear();
                  display(board);
                }
              }
              usleep(100000);
            }
            if(/* curs.getx() >= 0 && curs.gety() >= 0 && curs.getx() < SIZE && curs.gety() < SIZE && */moves[curs.gety()][curs.getx()]) {
              make_move(board, curs.gety(), curs.getx(), '@');
              no_of_moves++;              /* Increment move count */
              transition(2);
              display(board);
              break;
            }
            else {
              delete image_gen;
              image_gen = new BoardTextfile(canvas, "illegal.txt");
              image_gen->Start();
              sleep(1);
              canvas->Clear();
              display(board);
            }
          }
        }
        else {                           /* No valid moves */
          ++invalid_moves;
        }
      }
    }
    while(no_of_moves < SIZE*SIZE && invalid_moves<2);

    /* Game is over */
    display(board);  /* Show final board */

    /* Get final scores and display them */
    comp_score = user_score = 0; 
    for(row = 0; row < SIZE; row++) {
      for(col = 0; col < SIZE; col++) {
        comp_score += board[row][col] == '@';
        user_score += board[row][col] == 'O';
      }
    }
    // printf("The final score is:\n");
    // printf("Computer %d\n    User %d\n\n", comp_score, user_score);
  
    // fflush(stdin);                Flush the input buffer 
    // printf("Do you want to play again (y/n): ");
    // scanf("%c", &again);         /* Get y or n             */
    delete image_gen;
    image_gen = new BoardTextfile(canvas, "gameover.txt");
    image_gen->Start();
    sleep(1);
    display(board);
  }
  while(tolower(again) == 'y'); /* Go again on y          */

  return 0;
}

void transition(int player) 
{
  if (player == 1) { transArg1 = p1color; transArg2 = p2color; }
  else { transArg1 = p2color; transArg2 = p1color; }

  image_gen = new TransitionDisplay(canvas, transition_tiles, transArg1, transArg2);
  // image_gen = new TransitionDisplay(canvas, transition_tiles, transArg1, transArg2);
  if (image_gen == NULL) { return; }
  image_gen->Start();
  sleep(.5);
}

/***********************************************
 * Function to display the board in it's       *
 * current state with row numbers and column   *
 * letters to identify squares.                *
 * Parameter is the board array.               *
 ***********************************************/
void display(char board[SIZE][SIZE])
{
  // int row  = 0;          /* Row index      */
  // int col = 0;           /* Column index   */
  // char col_label = 'a';  /* Column label   */

  // printf("\n ");          //Start top line 
  // for(col = 0 ; col<SIZE ;col++)
  // printf("   %c", col_label+col); /* Display the top line */
  // printf("\n");                     /* End the top line     */

  delete image_gen;
  image_gen = new BoardArray(canvas, board, curs);
  if (image_gen == NULL) {
    printf("Image gen error.\n");
  }
  image_gen->Start();

  /* Display the intermediate rows */  
  // for(row = 0; row < SIZE; row++) {
  //  printf("  +");
  //  for(col = 0; col<SIZE; col++)
  //    printf("---+");
  //  printf("\n%2d|",row + 1); 

  //  for(col = 0; col<SIZE; col++)
  //    printf(" %c |", board[row][col]);  /* Display counters in row */
  //  printf("\n");    
  // }
  // delete image_gen;
  // printf("  +");                  /* Start the bottom line   */
  // for(col = 0 ; col<SIZE ;col++)
  //  printf("---+");               /* Display the bottom line */
  // printf("\n");                   /* End the bottom  line    */
}

/***********************************************
 * Calculates which squares are valid moves    *
 * for player. Valid moves are recorded in the *
 * moves array - 1 indicates a valid move,     *
 * 0 indicates an invalid move.                *
 * First parameter is the board array          *
 * Second parameter is the moves array         *
 * Third parameter identifies the player       *
 * to make the move.                           *
 * Returns valid move count.                   *
 ***********************************************/
int valid_moves(char board[][SIZE], int moves[][SIZE], char player)
{
   int rowdelta = 0;     /* Row increment around a square    */
   int coldelta = 0;     /* Column increment around a square */
   int row = 0;          /* Row index                        */
   int col = 0;          /* Column index                     */
   int x = 0;            /* Row index when searching         */
   int y = 0;            /* Column index when searching      */
   int no_of_moves = 0;  /* Number of valid moves            */

   /* Set the opponent            */
   char opponent1 = (player == 'O')? '@' : 'O';    

   /* Initialize moves array to zero */
   for(row = 0; row < SIZE; row++)
     for(col = 0; col < SIZE; col++)
       moves[row][col] = 0;

   /* Find squares for valid moves.                           */
   /* A valid move must be on a blank square and must enclose */
   /* at least one opponent square between two player squares */
   for(row = 0; row < SIZE; row++)
     for(col = 0; col < SIZE; col++)
     {
       if(board[row][col] != ' ')   /* Is it a blank square?  */
         continue;                  /* No - so on to the next */

       /* Check all the squares around the blank square  */ 
       /* for the opponents counter                      */
       for(rowdelta = -1; rowdelta <= 1; rowdelta++)
         for(coldelta = -1; coldelta <= 1; coldelta++)
         { 
           /* Don't check outside the array, or the current square */
           if(row + rowdelta < 0 || row + rowdelta >= SIZE ||
              col + coldelta < 0 || col + coldelta >= SIZE || 
                                       (rowdelta==0 && coldelta==0))
             continue;

           /* Now check the square */
           if(board[row + rowdelta][col + coldelta] == opponent1)
           {
             /* If we find the opponent, move in the delta direction  */
             /* over opponent counters searching for a player counter */
             x = row + rowdelta;                /* Move to          */
             y = col + coldelta;                /* opponent square  */

             /* Look for a player square in the delta direction */
             for(;;)
             {
               x += rowdelta;                  /* Go to next square */
               y += coldelta;                  /* in delta direction*/

               /* If we move outside the array, give up */
               if(x < 0 || x >= SIZE || y < 0 || y >= SIZE)
                 break;

               /* If we find a blank square, give up */ 
               if(board[x][y] == ' ')
                 break;
                /*  If the square has a player counter */
                /*  then we have a valid move          */
               if(board[x][y] == player)
               {
                 moves[row][col] = 1;   /* Mark as valid */
                 no_of_moves++;         /* Increase valid moves count */
                 break;                 /* Go check another square    */
               }
             } 
           } 
         }  
     }
   return no_of_moves; 
}


/************
 * Finds the best move for the computer. This is the move for      *
 * which the opponent's best possible move score is a minimum.     *
 * First parameter is the board array.                             *
 * Second parameter is the moves array containing valid moves.     *
 * Third parameter identifies the computer.                        *
 ************/
void computer_move(char board[][SIZE], int moves[][SIZE], char player, int depth)
{
   int row = 0;                          /* Row index               */
   int col = 0;                          /* Column index            */
   int best_row = 0;                     /* Best row index          */
   int best_col = 0;                     /* Best column index       */
   int i = 0;                            /* Loop index              */
   int j = 0;                            /* Loop index              */
   int new_score = 0;                    /* Score for current move  */
   int score = 100;                      /* Minimum opponent score  */
   char temp_board[SIZE][SIZE];          /* Local copy of board     */
   int temp_moves[SIZE][SIZE];           /* Local valid moves array */
   char opponent = (player == 'O')? '@' : 'O'; /* Identify opponent */
   /* Go through all valid moves */
   for(row = 0; row < SIZE; row++)
     for(col = 0; col < SIZE; col++)
     {
       if(moves[row][col] == 0)
         continue;
 
       /* First make copies of the board and moves arrays */
       for(i = 0; i < SIZE; i++)
         for(j = 0; j < SIZE; j++)
           temp_board[i][j] = board[i][j];
   
    /* Now make this move on the temporary board */
    make_move(temp_board, row, col, player); 
    
    if(depth > 0) 
      computer_move(temp_board,moves, player, depth-1); //goes through again to make sure it is the best possible move.
      //higher the depth the longer it takes
      
       /* find valid moves for the opponent after this move */
       valid_moves(temp_board, temp_moves, opponent);

       /* Now find the score for the opponents best move */
       new_score = best_move(temp_board, temp_moves, opponent);

       if(new_score<score) {                      /* Yes, so save this move */
         score = new_score;   /* Record new lowest opponent score */
         best_row = row;  /* Record best move row             */
         best_col = col;  /* and column                       */
         }
    }
    
    
   /* Make the best move */
   make_move(board, best_row, best_col, player); 
}

/************
 * Calculates the score for the current board position for the     *
 * player. player counters score +1, opponent counters score -1    *
 * First parameter is the board array                              *
 * Second parameter identifies the player                          *
 * Return value is the score.                                      *
 ************/
int get_score(char board[][SIZE], char player)
{
   int score = 0;      /* Score for current position */
   int row = 0;        /* Row index                  */    
   int col = 0;        /* Column index               */
   char opponent = player == 'O' ? '@' : 'O';  /* Identify opponent */

   /* Check all board squares */
   for(row = 0; row < SIZE; row++)
     for(col = 0; col < SIZE; col++)
   { 
     score -= board[row][col] == opponent; /* Decrement for opponent */
     score += board[row][col] == player;   /* Increment for player   */
   }
   return score;     
}

/************
 * Calculates the score for the best move out of the valid moves   *
 * for player in the current position.                             *
 * First parameter is the board array                              *
 * Second parameter is the moves array defining valid moves.       *
 * Third parameter identifies the player                           *
 * The score for the best move is returned                         *
 ************/
int best_move(char board[][SIZE], int moves[][SIZE], char player)
{
   int row = 0;     /* Row index    */
   int col = 0;     /* Column index */
   int i = 0;       /* Loop index   */
   int j = 0;       /* Loop index   */

   char opponent1 = (player == 'O')? '@' : 'O';  /* Identify opponent */

   char new_board[SIZE][SIZE] = { 0 };  /* Local copy of board    */
   int score = 0;                       /* Best score             */
   int new_score = 0;                   /* Score for current move */

   /* Check all valid moves to find the best */
   for(row = 0 ; row<SIZE ; row++)
     for(col = 0 ; col<SIZE ; col++)
     {
       if(!moves[row][col])             /* Not a valid move?      */
         continue;                      /* Go to the next         */
 
       /* Copy the board */
       for(i = 0 ; i<SIZE ; i++)
         for(j = 0 ; j<SIZE ; j++)
           new_board[i][j] = board[i][j];

       /* Make move on the board copy */
       make_move(new_board, row, col, player);  

       /* Get score for move */
       new_score = get_score(new_board, player);  

       if(score<new_score)         /* Is it better?               */
               score = new_score;  /* Yes, save it as best score  */
     }
   return score;                   /* Return best score           */
}

/*************
 * Makes a move. This places the counter on a square,and reverses   *
 * all the opponent's counters affected by the move.                *
 * First parameter is the board array.                              *
 * Second and third parameters are the row and column indices.      *
 * Fourth parameter identifies the player.                          *
 *************/
void make_move(char board[][SIZE], int row, int col, char player)
{
   int rowdelta = 0;                   /* Row increment              */
   int coldelta = 0;                   /* Column increment           */
   int x = 0;                          /* Row index for searching    */
   int y = 0;                          /* Column index for searching */
   char opponent1 = (player == 'O')? '@' : 'O';  /* Identify opponent */
   char opponent2 = (player == '@')? 'O' : '@'; 
   
   board[row][col] = player;           /* Place the player counter   */

  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      transition_tiles[i][j] = false;

   /* Check all the squares around this square */
   /* for the opponents counter                */
   for(rowdelta = -1; rowdelta <= 1; rowdelta++)
     for(coldelta = -1; coldelta <= 1; coldelta++)
     { 
       /* Don't check off the board, or the current square */
       if(row + rowdelta < 0 || row + rowdelta >= SIZE ||
          col + coldelta < 0 || col + coldelta >= SIZE || 
                               (rowdelta==0 && coldelta== 0))
         continue;

       /* Now check the square */
       if((board[row + rowdelta][col + coldelta] == opponent1) || (board[row + rowdelta][col + coldelta] == opponent2))
       {
         /* If we find the opponent, search in the same direction */
         /* for a player counter                                  */
         x = row + rowdelta;        /* Move to opponent */
         y = col + coldelta;        /* square           */

         for(;;)
         {
           x += rowdelta;           /* Move to the      */
           y += coldelta;           /* next square      */ 

           /* If we are off the board give up */
           if(x < 0 || x >= SIZE || y < 0 || y >= SIZE)
             break;
 
           /* If the square is blank give up */
           if(board[x][y] == ' ')
             break;

           /* If we find the player counter, go backwards from here */
           /* changing all the opponents counters to player         */
           if(board[x][y] == player)
           {
             while((board[x-=rowdelta][y-=coldelta]==opponent1) || (board[row + rowdelta][col + coldelta] == opponent2)) {/* Opponent? */
               board[x][y] = player;    /* Yes, change it */
               transition_tiles[x][y] = true;
             }
             break;                     /* We are done    */
           } 
         }
       }
     }
}
