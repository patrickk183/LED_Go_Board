/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h> /* for NULL */
#include "liberty.h"
#include "patterns.h"

static struct patval defpat0[] = {
  {684,2}
};

static struct patval defpat1[] = {
  {684,2},	{685,2},	{758,0},	{759,0}
};

static struct patval defpat2[] = {
  {721,2},	{648,2},	{684,2},	{649,2},
  {759,0},	{686,0},	{723,0},	{687,0}
};

static struct patval defpat3[] = {
  {684,2},	{685,2},	{795,2},	{758,4},
  {759,0},	{796,0},	{686,0},	{723,0},
  {760,0},	{797,0}
};

static struct patval defpat4[] = {
  {758,1},	{684,2},	{795,2},	{685,2},
  {759,0},	{796,0},	{686,0},	{723,0},
  {760,0},	{797,0}
};

static struct patval defpat5[] = {
  {759,1},	{684,2},	{795,2},	{722,2},
  {758,0}
};

static struct patval defpat6[] = {
  {684,2},	{722,2},	{686,0}
};

static struct patval defpat7[] = {
  {760,1},	{758,1},	{686,2},	{759,2},
  {684,2},	{723,0}
};

static struct patval defpat8[] = {
  {650,1},	{686,1},	{613,1},	{575,1},
  {722,2},	{648,2},	{612,2},	{684,2},
  {611,0},	{574,0},	{649,0},	{610,0},
  {573,0}
};

static struct patval defpat9[] = {
  {686,1},	{723,1},	{722,2},	{684,2},
  {759,2},	{758,4},	{796,4},	{794,4},
  {757,4}
};

static struct patval defpat10[] = {
  {723,1},	{687,1},	{686,2},	{684,2},
  {688,2},	{721,2},	{724,2},	{650,0},
  {649,0},	{651,0}
};

static struct patval defpat11[] = {
  {648,2},	{684,2},	{650,2},	{649,0},
  {686,0},	{612,0},	{687,0}
};

static struct patval defpat12[] = {
  {684,2},	{685,2},	{758,2},	{759,0}
};

static struct patval defpat13[] = {
  {684,2},	{648,2},	{686,2}
};

static struct patval defpat14[] = {
  {684,2},	{649,0},	{686,0},	{723,0},
  {687,0}
};

static struct patval defpat15[] = {
  {685,2},	{684,2},	{686,4},	{758,0},
  {794,0},	{832,0},	{759,0},	{796,0},
  {833,0},	{795,0},	{723,0},	{760,0},
  {797,0},	{834,0}
};

static struct patval defpat16[] = {
  {610,1},	{648,2},	{684,2},	{611,2},
  {758,0},	{759,0},	{612,0},	{649,0},
  {686,0},	{723,0},	{760,0}
};

static struct patval defpat17[] = {
  {795,1},	{758,1},	{721,2},	{759,2},
  {684,2},	{796,0},	{686,0},	{723,0},
  {760,0},	{797,0}
};

static struct patval defpat18[] = {
  {757,1},	{796,1},	{795,1},	{684,2},
  {759,2},	{758,0},	{686,0},	{723,0},
  {760,0},	{797,0}
};

static struct patval defpat19[] = {
  {684,2},	{722,2},	{758,0},	{759,0}
};

static struct patval defpat20[] = {
  {684,2},	{721,2},	{573,0},	{610,0},
  {572,0},	{609,0},	{574,0},	{611,0}
};

static struct patval defpat21[] = {
  {759,1},	{758,2},	{684,2},	{757,4}
};

static struct patval defpat22[] = {
  {611,1},	{684,2},	{648,2},	{610,3},
  {612,0},	{649,0},	{686,0},	{613,0},
  {650,0},	{687,0}
};

static struct patval defpat23[] = {
  {686,2},	{684,2},	{611,4},	{610,0},
  {612,0},	{649,0}
};

static struct patval defpat24[] = {
  {686,1},	{684,2},	{757,0},	{794,0},
  {758,0},	{795,0},	{759,0},	{796,0},
  {723,0},	{760,0},	{797,0}
};

static struct patval defpat25[] = {
  {686,1},	{760,1},	{684,2},	{794,0},
  {758,0},	{795,0},	{759,0},	{796,0},
  {723,0},	{757,0},	{797,0}
};

static struct patval defpat26[] = {
  {684,2},	{758,2},	{759,0},	{723,0}
};

static struct patval defpat27[] = {
  {649,1},	{686,2},	{684,2},	{682,0}
};

static struct patval defpat28[] = {
  {723,1},	{684,2},	{649,0},	{686,0},
  {760,0},	{650,0},	{687,0},	{724,0}
};

static struct patval defpat29[] = {
  {723,1},	{686,1},	{797,2},	{758,2},
  {722,2},	{684,2},	{795,4},	{796,0},
  {760,0},	{759,0}
};

static struct patval defpat30[] = {
  {757,1},	{795,2},	{684,2},	{758,0},
  {759,0},	{796,0}
};

static struct patval defpat31[] = {
  {684,2},	{722,2},	{758,0},	{759,0}
};

static struct patval defpat32[] = {
  {686,1},	{721,2},	{684,2},	{795,2},
  {758,2},	{685,2},	{723,2},	{796,0},
  {833,0},	{832,0},	{759,0},	{760,0},
  {797,0},	{834,0}
};

static struct pattern defpat[34];

static int
autohelperdefpat0(int trans, int move, int color, int action)
{
  UNUSED(trans);
  UNUSED(color);
  UNUSED(action);

  UNUSED(move);

  return accuratelib(move, color, MAX_LIBERTIES, NULL)>1;
}

static int
autohelperdefpat1(int trans, int move, int color, int action)
{
  int a, b;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(610, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);

  return ATTACK_MACRO(a) && play_attack_defend_n(color, 0, 2, move, b, a);
}

static int
autohelperdefpat10(int trans, int move, int color, int action)
{
  int a;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(718, trans, move);

  return countlib(a)>2;
}

static int
autohelperdefpat31(int trans, int move, int color, int action)
{
  int a, b, C;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(610, trans, move);
  b = AFFINE_TRANSFORM(648, trans, move);
  C = AFFINE_TRANSFORM(647, trans, move);

  return countlib(a)>1 && countlib(b)>1 && countlib(C)<=2 && accuratelib(move, color, MAX_LIBERTIES, NULL)>1;
}

static struct pattern defpat[] = {
  {defpat0,1,8, "Def1",-1,0,0,1,1,1,0x0,720,
    { 0x3c340000, 0x003c1c00, 0x0070f000, 0xd0f00000, 0x1c3c0000, 0x00343c00, 0x00f0d000, 0xf0700000},
    { 0x20100000, 0x00180000, 0x00102000, 0x00900000, 0x00180000, 0x00102000, 0x00900000, 0x20100000}
   , 0x40,0.000000,NULL,1,NULL,autohelperdefpat0,0,0.050000},
  {defpat1,4,8, "Def2",0,0,1,2,1,2,0x0,758,
    { 0x003f3f00, 0x00f0f0f0, 0xf0f00000, 0x3c3c0000, 0xf0f00000, 0x3f3f0000, 0x003c3c3c, 0x00f0f000},
    { 0x00101000, 0x00500000, 0x10100000, 0x00140000, 0x00500000, 0x10100000, 0x00140000, 0x00101000}
   , 0x40,0.000000,NULL,1,NULL,autohelperdefpat1,0,1.600000},
  {defpat2,8,8, "Def4",0,-1,3,2,3,3,0x0,723,
    { 0x00fcfffc, 0xf0f0f0c0, 0xfcfc0000, 0x3f3f3f00, 0xf0f0f000, 0xfffc0000, 0x3f3f3f0c, 0x00fcfcfc},
    { 0x00946040, 0x60901000, 0x24580000, 0x10182500, 0x10906000, 0x60940000, 0x25181000, 0x00582404}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat3,10,8, "Def5",0,0,2,3,2,3,0x2,722,
    { 0x003e3f3f, 0x00f0f0e0, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3e0000, 0x003f3f2f, 0x00f0f0f0},
    { 0x00181000, 0x00502000, 0x10900000, 0x20140000, 0x20500000, 0x10180000, 0x00142000, 0x00901000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat4,10,8, "Def6",0,0,2,3,2,3,0x2,759,
    { 0x003f3f3f, 0x00f0f0f0, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3f0000, 0x003f3f3f, 0x00f0f0f0},
    { 0x001a1000, 0x00502020, 0x10900000, 0x20140000, 0x20500000, 0x101a0000, 0x00142020, 0x00901000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat5,5,8, "Def9",0,0,1,3,1,3,0x0,758,
    { 0x003f3f00, 0x00f0f0f0, 0xf0f00000, 0x3c3c0000, 0xf0f00000, 0x3f3f0000, 0x003c3c3c, 0x00f0f000},
    { 0x00180600, 0x00106080, 0x40900000, 0x24100000, 0x60100000, 0x06180000, 0x00102408, 0x00904000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat6,3,8, "Def10",0,-1,2,1,2,2,0x0,648,
    { 0x00f0fc30, 0xf0f0c000, 0xfc3c0000, 0x0c3f3c00, 0xc0f0f000, 0xfcf00000, 0x3c3f0c00, 0x003cfc30},
    { 0x00900400, 0x20104000, 0x40180000, 0x04102000, 0x40102000, 0x04900000, 0x20100400, 0x00184000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat7,6,8, "Def12",0,-1,2,2,2,3,0x0,721,
    { 0x003fbf3f, 0x80f0f0f0, 0xf8f00000, 0x3f3f0800, 0xf0f08000, 0xbf3f0000, 0x083f3f3f, 0x00f0f8f0},
    { 0x00120912, 0x00108060, 0x80100000, 0x08110000, 0x80100000, 0x09120000, 0x00110826, 0x00108010}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat8,13,8, "Def16",0,-3,3,1,3,4,0x1,574,
    { 0x00f0fcf0, 0xf0f0c000, 0xff3f0000, 0x0c3f3f3f, 0xc0f0f0f0, 0xfcf00000, 0x3f3f0c00, 0x003fff3f},
    { 0x00106420, 0x40904000, 0x64100000, 0x041a0401, 0x40904000, 0x64100000, 0x041a0400, 0x00106421}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat9,9,8, "Def17",-1,0,2,3,3,3,0x9,720,
    { 0x3e3e3f3c, 0x00fcfce8, 0xf0f0f000, 0xffff0000, 0xfcfc0000, 0x3f3e3e00, 0x00ffffac, 0xf0f0f0f0},
    { 0x00102528, 0x00904040, 0x60100000, 0x061a0000, 0x40900000, 0x25100000, 0x001a0604, 0x001060a0}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat10,10,8, "Def21",0,-1,4,1,4,2,0x8,650,
    { 0x00bcfcfc, 0xe0f0f000, 0xfcf80000, 0x3f3f2f00, 0xf0f0e000, 0xfcbc0000, 0x2f3f3f00, 0x00f8fcfc},
    { 0x00142018, 0x00901000, 0x20500000, 0x12190000, 0x10900000, 0x20140000, 0x00191200, 0x00502090}
   , 0x40,0.000000,NULL,1,NULL,autohelperdefpat10,0,0.010000},
  {defpat11,7,8, "Def25",0,-2,3,0,3,2,0x0,686,
    { 0x00f0f0f0, 0xf0f00000, 0x3c3c0000, 0x003f3f03, 0x00f0f000, 0xf0f00000, 0x3f3f0000, 0x003c3c3f},
    { 0x00906000, 0x60900000, 0x24180000, 0x00182400, 0x00906000, 0x60900000, 0x24180000, 0x00182400}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat12,4,8, "Def26",0,0,1,3,1,3,0x0,759,
    { 0x003f3f00, 0x00f0f0f0, 0xf0f00000, 0x3c3c0000, 0xf0f00000, 0x3f3f0000, 0x003c3c3c, 0x00f0f000},
    { 0x00111000, 0x00500010, 0x10100000, 0x00140000, 0x00500000, 0x10110000, 0x00140010, 0x00101000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat13,3,4, "Def28",0,-1,2,1,2,2,0x0,722,
    { 0x0030dc30, 0xc070c000, 0xdc300000, 0x0c370c00, 0xc070c000, 0xdc300000, 0x0c370c00, 0x0030dc30},
    { 0x00104010, 0x40100000, 0x04100000, 0x00110400, 0x00104000, 0x40100000, 0x04110000, 0x00100410}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat14,5,4, "Def29",-1,-1,3,1,4,2,0x0,686,
    { 0x30fcfcfc, 0xf0fcf000, 0xfcfc3000, 0x3fff3f00, 0xf0fcf000, 0xfcfc3000, 0x3fff3f00, 0x30fcfcfc},
    { 0x20100000, 0x00180000, 0x00102000, 0x00900000, 0x00180000, 0x00102000, 0x00900000, 0x20100000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat15,14,8, "Def39",-1,0,2,5,3,5,0x2,795,
    { 0x0c3f3f2f, 0x00f0fcf0, 0xf0f0c000, 0xff3e0000, 0xfcf00000, 0x3f3f0c00, 0x003eff3f, 0xc0f0f0e0},
    { 0x08101000, 0x00500800, 0x10108000, 0x80140000, 0x08500000, 0x10100800, 0x00148000, 0x80101000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat16,11,8, "Def44",-1,-2,2,2,3,4,0x2,721,
    { 0x34ffffff, 0xf0fcf4f0, 0xffff7000, 0x7fff3f3f, 0xf4fcf0f0, 0xffff3400, 0x3fff7f3f, 0x70ffffff},
    { 0x20904000, 0x60180000, 0x051a2000, 0x00902424, 0x00186060, 0x40902000, 0x24900000, 0x201a0500}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat17,10,8, "Def45",0,0,2,3,2,3,0x2,796,
    { 0x003f3f3f, 0x00f0f0f0, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3f0000, 0x003f3f3f, 0x00f0f0f0},
    { 0x00160900, 0x00109060, 0x80500000, 0x18100000, 0x90100000, 0x09160000, 0x00101824, 0x00508000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat18,10,8, "Def49",-1,0,2,3,3,3,0x2,721,
    { 0x033f3f3f, 0x00f0f0fc, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3f0300, 0x003f3fff, 0x00f0f0f0},
    { 0x02100100, 0x00100048, 0x00100000, 0x00100000, 0x00100000, 0x01100200, 0x00100084, 0x00100000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat19,4,8, "Def50",-1,-1,1,2,2,3,0x2,758,
    { 0x083fff00, 0xc0f0f8f0, 0xfcf08000, 0xbc3c0c00, 0xf8f0c000, 0xff3f0800, 0x0c3cbc3c, 0x80f0fc00},
    { 0x0010a400, 0x80904000, 0x68100000, 0x04180800, 0x40908000, 0xa4100000, 0x08180400, 0x00106800}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat20,8,8, "Def52",-2,-4,2,1,4,5,0x0,610,
    { 0xf4fcf400, 0xfcfc7400, 0x7fff7f00, 0x74fcfcfc, 0x74fcfcfc, 0xf4fcf400, 0xfcfc7400, 0x7fff7f00},
    { 0x00140000, 0x00101000, 0x00500000, 0x10100000, 0x10100000, 0x00140000, 0x00101000, 0x00500000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat21,4,8, "Def55",-1,0,1,2,2,2,0x0,722,
    { 0x2a3f3f00, 0x00f8f8f8, 0xf0f0a000, 0xbcbc0000, 0xf8f80000, 0x3f3f2a00, 0x00bcbcbc, 0xa0f0f000},
    { 0x00110200, 0x00100090, 0x00100000, 0x00100000, 0x00100000, 0x02110000, 0x00100018, 0x00100000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat22,10,8, "Def56",0,-2,3,0,3,2,0x0,649,
    { 0x00f0f0f0, 0xf0f00000, 0x3f3d0000, 0x003f3f1f, 0x00f0f0d0, 0xf0f00000, 0x3f3f0000, 0x003d3f3f},
    { 0x00904000, 0x60100000, 0x06180000, 0x00102408, 0x00106080, 0x40900000, 0x24100000, 0x00180600}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat23,6,4, "Def57",0,-2,2,0,2,2,0x0,648,
    { 0x00f0f0f0, 0xf0f00000, 0x3e3f0000, 0x003f3f3b, 0x00f0f0b0, 0xf0f00000, 0x3f3f0000, 0x003f3e3f},
    { 0x00102010, 0x00900000, 0x20100000, 0x00190000, 0x00900000, 0x20100000, 0x00190000, 0x00102010}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat24,11,8, "Def58",-2,0,2,4,4,4,0x0,758,
    { 0x3f3f3f3f, 0x00fcfcfc, 0xf0f0f000, 0xffff0000, 0xfcfc0000, 0x3f3f3f00, 0x00ffffff, 0xf0f0f0f0},
    { 0x00100020, 0x00100000, 0x00100000, 0x00120000, 0x00100000, 0x00100000, 0x00120000, 0x00100020}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat25,11,8, "Def59",-1,0,2,3,3,3,0x0,758,
    { 0x3f3f3f3f, 0x00fcfcfc, 0xf0f0f000, 0xffff0000, 0xfcfc0000, 0x3f3f3f00, 0x00ffffff, 0xf0f0f0f0},
    { 0x00100022, 0x00100000, 0x00100000, 0x00120000, 0x00100000, 0x00100000, 0x00120002, 0x00100020}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat26,4,4, "Def60",0,0,2,2,2,2,0x0,722,
    { 0x003f3f0c, 0x00f0f0f0, 0xf0f00000, 0x3f3c0000, 0xf0f00000, 0x3f3f0000, 0x003c3f3c, 0x00f0f0c0},
    { 0x00190000, 0x00102010, 0x00900000, 0x20100000, 0x20100000, 0x00190000, 0x00102010, 0x00900000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat27,4,8, "Def61",-2,-1,2,1,4,2,0x0,683,
    { 0xfcf0f0f0, 0xfcff0c00, 0x3c3cfc30, 0xc0ffff00, 0x0cfffc00, 0xf0f0fc30, 0xffffc000, 0xfc3c3c3c},
    { 0x00908090, 0xa0100000, 0x08180000, 0x00112a00, 0x0010a000, 0x80900000, 0x2a110000, 0x00180818}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat28,8,8, "Def62",0,-1,3,2,3,3,0x0,686,
    { 0x00b8fcff, 0xe0f0e000, 0xfcb80000, 0x2f3f2f00, 0xe0f0e000, 0xfcb80000, 0x2f3f2f03, 0x00b8fcfc},
    { 0x00100008, 0x00100000, 0x00100000, 0x02100000, 0x00100000, 0x00100000, 0x00100200, 0x00100080}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat29,10,8, "Def63",0,0,2,3,2,3,0x0,760,
    { 0x003f3f3f, 0x00f0f0f0, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3f0000, 0x003f3f3f, 0x00f0f0f0},
    { 0x00112428, 0x00904010, 0x60100000, 0x061a0000, 0x40900000, 0x24110000, 0x001a0610, 0x001060a0}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat30,6,8, "Def68",-1,0,1,3,2,3,0x2,758,
    { 0x2f3f3f00, 0x00f8fcfc, 0xf0f0e000, 0xfcbc0000, 0xfcf80000, 0x3f3f2f00, 0x00bcfcfc, 0xe0f0f000},
    { 0x02180000, 0x00102008, 0x00900000, 0x20100000, 0x20100000, 0x00180200, 0x00102080, 0x00900000}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {defpat31,4,8, "Def69",0,0,1,2,1,2,0x0,758,
    { 0x003f0f00, 0x0030f0f0, 0xc0f00000, 0x3c300000, 0xf0300000, 0x0f3f0000, 0x00303c3c, 0x00f0c000},
    { 0x00180400, 0x00106000, 0x40900000, 0x24100000, 0x60100000, 0x04180000, 0x00102400, 0x00904000}
   , 0x40,0.000000,NULL,1,NULL,autohelperdefpat31,0,0.030400},
  {defpat32,14,8, "Def70",0,0,2,4,2,4,0x2,832,
    { 0x003f3f3f, 0x00f0f0f0, 0xf0f00000, 0x3f3f0000, 0xf0f00000, 0x3f3f0000, 0x003f3f3f, 0x00f0f0f0},
    { 0x00151024, 0x00501010, 0x10500000, 0x11160000, 0x10500000, 0x10150000, 0x00161110, 0x00501060}
   , 0x40,0.000000,NULL,0,NULL,NULL,0,0.000000},
  {NULL, 0,0,NULL,0,0,0,0,0,0,0,0,{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},0,0.0,NULL,0,NULL,NULL,0,0.0}
};

struct pattern_db defpat_db = {
  -1,
  0,
  defpat
 , NULL
};
