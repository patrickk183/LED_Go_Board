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

#ifndef _GG_UTILS_H_
#define _GG_UTILS_H_

#include <stdarg.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef __MINGW32__
#include <windows.h>
#include <winsock.h>
#include <io.h>
#endif

#ifdef HAVE_WINSOCK_IO_H
#include <winsock.h>
#include <io.h>
#endif

void gg_init_color(void);
void write_color_char(int c, int x);
void write_color_string(int c, const char *str);


/*
 * A wrapper around vsnprintf.
 */

static void
gg_vsnprintf(char *dest, unsigned long len, const char *fmt, va_list args)
{
    
#ifdef HAVE_VSNPRINTF
  vsnprintf(dest, len, fmt, args);
#elif HAVE_G_VSNPRINTF
  g_vsnprintf(dest, len, fmt, args);
#elif HAVE__VSNPRINTF
  _vsnprintf(dest, len, fmt, args);
#else
  UNUSED(len);
  vsprintf(dest, fmt, args);
#endif

}

static void
gg_snprintf(char *dest, unsigned long len, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  gg_vsnprintf(dest, len, fmt, args);
  va_end(args);
}

double gg_gettimeofday(void);
double gg_cputime(void);

float gg_normalize_float(float x, float a);
int gg_normalize_float2int(float x, float a);

/* A sorting algorithm, call-compatible with the libc qsort() function.
 *
 * The reason to prefer this to standard qsort() is that quicksort is
 * an unstable sorting algorithm, i.e. the relative ordering of
 * elements with the same comparison value may change. Exactly how the
 * ordering changes depends on implementation specific details like
 * the strategy for choosing the pivot element. Thus a list with
 * "equal" values may be sorted differently between platforms, which
 * potentially can lead to significant differences in the move
 * generation.
 *
 * This is an implementation of the combsort algorithm.
 *
 * Testing shows that it is faster than the GNU libc qsort() function
 * on small data sets and within a factor of two slower for large
 * random data sets. Its performance does not degenerate for common
 * special cases (i.e. sorted or reversed data) but it seems to be
 * susceptible to O(N^2) behavior for repetitive data with specific
 * cycle lengths.
 *
 * Like qsort() this algorithm is unstable, but since the same
 * implementation (this one) is used on all platforms, the reordering
 * of equal elements will be consistent.
 */
static void
gg_sort(void *base, size_t nel, size_t width,
	int (*cmp)(const void *, const void *))
{
  int gap = nel;
  int swap_made;
  char *end = (char *) base + width * (nel - 1);
  do {
    char *a, *b;
    swap_made = 0;
    gap = (10 * gap + 3) / 13;
    for (a = (char*) base, b = a + gap * width; b <= end; a += width, b += width) {
      if (cmp((void *) a, (void *) b) > 0) {
	char *c = a;
	char *d = b;
	size_t size = width;
	while (size-- > 0) {
	  char tmp = *c;
	  *c++ = *d;
	  *d++ = tmp;
	}
	swap_made = 1;
      }
    }
  } while (gap > 1 || swap_made);
}


#define MAX_INTERPOLATION_STEPS 20
struct interpolation_data
{
  int sections;
  float range_lowerbound;
  float range_upperbound;
  float values[MAX_INTERPOLATION_STEPS + 1];
};

float gg_interpolate(struct interpolation_data *f, float x);
float soft_cap(float a, float b);

const char *gg_version(void);

/* prototypes for basic reorientation functions */

void rotate(int i, int j, int *ri, int *rj, int bs, int rot);
void inv_rotate(int i, int j, int *ri, int *rj, int bs, int rot);

void update_random_seed(void);
extern void set_random_seed(unsigned int seed);
unsigned int get_random_seed(void);
void reuse_random_seed(void);


#endif /* _GG_UTILS_H_ */


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
