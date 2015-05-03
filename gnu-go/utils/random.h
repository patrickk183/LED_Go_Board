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

#ifndef _RANDOM_H_
#define _RANDOM_H_
#include <limits.h>
#include <assert.h>
/* This random number generator produces 32 bit unsigned integers, no
 * more, no less. Internally in the algorithm and for storing the
 * state we need a type that is at least 32 bits wide. A longer type
 * doesn't hurt but means a waste of bits.
 *
 * ISO C guarantees that an unsigned long always is at least 32 bits.
 * It is not uncommon, however, that it is longer. An unsigned int is
 * not guaranteed to be more than 16 bits wide, but on modern
 * platforms we can be certain that this type too is 32 bits (or
 * more). Also the GNU Coding Standards explicitly state that the
 * possibility of ints shorter than 32 bits should be ignored.
 *
 * We could make a typedef here to choose exactly which type to use.
 * In order to avoid various complications in the interface to the
 * random number generator, however, we prefer to consistently use
 * unsigned int internally and we assume this type to be at least 32
 * bits wide.
 */

/* Internal state of the random number generator. */
static struct gg_rand_state {
  unsigned int x[25];   /* Internal state. */
  int k;                /* Word counter. */
};

/* Algorithm parameters. */
#define N 25
static const int m = 7;
static const int s = 7;
static const int t = 15;
static const unsigned int a = 0x8ebfd028U;
static const unsigned int b = 0x2b5b2500U;
static const unsigned int c = 0xdb8b0000U;


/* Global state for the random number generator. */
static unsigned int x[N];
static int k;


/* Set when properly seeded. */
static int rand_initialized = 0;

/* We use this to detect whether unsigned ints are bigger than 32
 * bits. If they are we need to clear higher order bits, otherwise we
 * can optimize by not doing the masking.
 */
#define BIG_UINT (UINT_MAX > 0xffffffffU)


/* Seed the random number generator. The first word of the internal
 * state is set by the (lower) 32 bits of seed. The remaining 24 words
 * are generated from the first one by a linear congruential pseudo
 * random generator.
 *
 * FIXME: The constants in this generator has not been checked, but
 * since they only are used to produce a very short sequence, which in
 * turn only is a seed to a stronger generator, it probably doesn't
 * matter much.
 */

static void
gg_srand(unsigned int seed)
{
  int i;
  for (i = 0; i < N; i++) {
#if BIG_UINT
    seed &= 0xffffffffU;
#endif
    x[i] = seed;
    seed *= 1313;
    seed += 88897;
  }
  k = N-1; /* Force an immediate iteration of the TGFSR. */
  rand_initialized = 1;
}

/* Iterate the TGFSR once to get a new state which can be used to
 * produce another 25 random numbers.
 */

static void
iterate_tgfsr(void)
{
  int i;
  for (i = 0; i < N - m; i++)
    x[i] = x[i + m]   ^  (x[i] >> 1)  ^  ((x[i] & 1) ? a : 0);
  for (; i < N; i++)
    x[i] = x[i + m - N] ^  (x[i] >> 1)  ^  ((x[i] & 1) ? a : 0);
}


/* Produce a random number from the next word of the internal state.
 */

static unsigned int
next_rand(void)
{
  int y;
  if (!rand_initialized) {
    assert(rand_initialized); /* Abort. */
    gg_srand(1);              /* Initialize silently if assertions disabled. */
  }
  if (++k == N) {
    iterate_tgfsr();
    k = 0;
  }
  y = x[k] ^ ((x[k] << s) & b);
  y ^= ((y << t) & c);
#if BIG_UINT
  y &= 0xffffffffU;
#endif
  return y;
}

/* Obtain one random integer value in the interval [0, 2^31-1].
 */

static int
gg_rand(void)
{
  return (int) (next_rand() & 0x7fffffff);
}


/* Obtain one random integer value in the interval [0, 2^32-1].
 */

static unsigned int
gg_urand(void)
{
  return next_rand();
}


/* Obtain one random floating point value in the half open interval
 * [0.0, 1.0).
 *
 * If the value is converted to a floating point type with less than
 * 32 bits mantissa (or if the double type should happen to be
 * unusually short), the value 1.0 may be attained.
 */

static double
gg_drand(void)
{
  return next_rand() * 2.328306436538696e-10;
}


/* Retrieve the internal state of the random generator.
 */

static void
gg_get_rand_state(struct gg_rand_state *state)
{
  int i;
  for (i = 0; i < N; i++)
    state->x[i] = x[i];
  state->k = k;
}


/* Set the internal state of the random number generator.
 */

static void
gg_set_rand_state(struct gg_rand_state *state)
{
  int i;
  for (i = 0; i < N; i++)
    x[i] = state->x[i];
  k = state->k;
}

#endif /* _RANDOM_H_ */

/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
