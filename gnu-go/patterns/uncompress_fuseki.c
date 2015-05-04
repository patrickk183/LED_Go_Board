/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This is GNU Go, a Go program. Contact gnugo@gnu.org, or see       *
 * http://www.gnu.org/software/gnugo/ for more information.          *
 *                                                                   *
 * Copyright 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,   *
 * 2008 and 2009 by the Free Software Foundation.                    *
 *                                                                   *
 * This program is free software; you can redistribute it and/or     *
 * modify it under the terms of the GNU General Public License as    *
 * published by the Free Software Foundation - version 3 or          *
 * (at your option) any later version.                               *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * GNU General Public License in file COPYING for more details.      *
 *                                                                   *
 * You should have received a copy of the GNU General Public         *
 * License along with this program; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA 02111, USA.                                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "board.h"
#include "liberty.h"
#include "hash.h"
#include "gg_utils.h"

#define BUFSIZE 160

#include <stdio.h>
#include "liberty.h"
#include "patterns.h"
  

static const char *const db_output_strings[3] =
  {"Preamble", "Header", "Footer"};
static const char *const c_output_strings[3] =
  {"Preamble", "Header", "Footer"};

#define PREAMBLE 	0
#define HEADER 		1
#define FOOTER 	 	2


/* Place a stone (or move mark) on the internal board. The board point
 * is sgf encoded.
 */
static int
set_boards(char board[MAX_BOARD + 2][MAX_BOARD + 2],
	   Intersection board1d[BOARDSIZE],
	   char *stones, char color, int boardsize)
{
  int i = stones[1] - 'a' + 1;
  int j = stones[0] - 'a' + 1;
  if (stones[0] != 't') {
    assert(i > 0 && i < boardsize + 2);
    board[i][j] = color;
    if (color == 'O')
      board1d[POS(i - 1, j - 1)] = WHITE;
    else if (color == 'X')
      board1d[POS(i - 1, j - 1)] = BLACK;
    return POS(i - 1, j - 1);
  }
  else 
    return NO_MOVE;
}

static void
write_pattern(char *name, char board[MAX_BOARD + 2][MAX_BOARD + 2],
	      int value, int boardsize)
{
  int i, j;
  /* Output the uncompressed pattern. */
  printf("Pattern %s\n\n", name);
  for (i = 0; i <= boardsize + 1; i++) {
    for (j = 0; j <= boardsize + 1; j++)
      printf("%c", board[i][j]);
    printf("\n");
  }
  printf("\n:8,-,value(%d)\n\n\n", value);
}


static void
write_pattern_c_code(char *name, Intersection board1d[BOARDSIZE],
		     int move_pos, int value, int boardsize, int patlen)
{
  int k;
  Hash_data pattern_hash;

  /* Compute hash. */
  hashdata_recalc(&pattern_hash, board1d, NO_MOVE);
  printf("  {{{");
  for (k = 0; k < NUM_HASHVALUES; k++) {
    printf("0x%lx", pattern_hash.hashval[k]);
    if (k < NUM_HASHVALUES - 1)
      printf(",");
  }
  if (name)
    printf("}},%d,\"%s\",%d,%d},\n", patlen, name,
	   OFFSET(I(move_pos) - (boardsize-1)/2,
		  J(move_pos) - (boardsize-1)/2),
	   value);
  else
    printf("}},-1,NULL,0,0},\n");
}



#define DB_OUTPUT 	1
#define C_OUTPUT 	2


int
main(int argc, char *argv[])
{
  const char *filename;
  FILE *input_FILE;
  const char *const *output_strings;
  int mode;
  int move_pos;
  char line[BUFSIZE];
  char name[BUFSIZE];
  char stones[BUFSIZE];
  int value;
  char board[MAX_BOARD + 2][MAX_BOARD + 2];
  Intersection board1d[BOARDSIZE];
  int boardsize;
  int i, j, k;
  int pos;
  char color;

  /* Check number of arguments. */
  if (argc != 4) {
    return EXIT_FAILURE;
  }

  boardsize = atoi(argv[1]);
  filename = argv[2];
  if (strncmp(argv[3], "c", 2) == 0) {
    mode = C_OUTPUT;
    output_strings = c_output_strings;
    set_random_seed(HASH_RANDOM_SEED);
    hash_init();
  }
  else if (strncmp(argv[3], "db", 3) == 0) {
    mode = DB_OUTPUT;
    output_strings = db_output_strings;
  }
  else {
    return EXIT_FAILURE;
  }

  assert(boardsize > 0);
  if (boardsize > MAX_BOARD) {
    printf(output_strings[PREAMBLE]);
    printf(output_strings[HEADER], boardsize);
    printf(output_strings[FOOTER]);
    return EXIT_SUCCESS;
  }
  
  
  input_FILE = fopen(filename, "r");
  if (!input_FILE) {
    fprintf(stderr, "uncompress_fuseki: Cannot open file %s\n", filename);
    return EXIT_FAILURE;
  }
  
  /* Initialize the corners of the internal board description. */
  board[0][0] = '+';
  board[0][boardsize + 1] = '+';
  board[boardsize + 1][0] = '+';
  board[boardsize + 1][boardsize + 1] = '+';

  /* Initialize the sides of the internal board description. */
  for (k = 1; k <= boardsize; k++) {
    board[0][k] = '-';
    board[boardsize + 1][k] = '-';
    board[k][0] = '|';
    board[k][boardsize + 1] = '|';
  }

  printf(output_strings[PREAMBLE]);
  printf(output_strings[HEADER], boardsize);
  

  /* Loop over the lines of the compressed database.
   * Each line is one pattern.
   */
  while (fgets(line, BUFSIZE, input_FILE)) {
    int num_stones = 0;
    /* Clear the internal board. */
    for (i = 1; i <= boardsize; i++)
      for (j = 1; j <= boardsize; j++)
	board[i][j] = '.';

    /* Initialize private 1D-board. */
    for (pos = 0; pos < BOARDSIZE; pos++)
      if (I(pos) >= 0 && I(pos) < boardsize
          && J(pos) >= 0 && J(pos) < boardsize)
	board1d[pos] = EMPTY;
      else
	board1d[pos] = GRAY;

    /* Assume a line from copyright notice if misformed and
     * silently ignore it.
     */
    if (sscanf(line, "%s %d %s", name, &value, stones) != 3)
      continue;

    /* The first point in the stones list is the move to be played. */
    move_pos = set_boards(board, board1d, stones, '*', boardsize);

    /* Then follows alternating X and O stones. */
    color = 'X';
    for (k = 2; k < (int) strlen(stones); k += 2) {
      pos = set_boards(board, board1d, stones + k, color, boardsize);
      if (I(pos) >= 0 && I(pos) < boardsize
          && J(pos) >= 0 && J(pos) < boardsize)
	num_stones++;
      if (color == 'X')
	color = 'O';
      else
	color = 'X';
    }

    if (mode == DB_OUTPUT)
      write_pattern(name, board, value, boardsize);
    else
      write_pattern_c_code(name, board1d, move_pos, value, boardsize,
		           num_stones);
  }

  /* Add a dummy pattern to mark the end of the array. This can't be
   * done statically in the footer since NUM_HASHVALUES may vary.
   */
  if (mode == C_OUTPUT)
    write_pattern_c_code(NULL, board1d, NO_MOVE, 0, boardsize, -1);
  
  printf(output_strings[FOOTER]);

  return EXIT_SUCCESS;
}


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
