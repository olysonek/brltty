/*
 * BRLTTY - A background process providing access to the Linux console (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2001 by The BRLTTY Team. All rights reserved.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation.  Please see the file COPYING for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

/* BrailleLite/bindings.h - key bindings for BLazie Engineering's Braille Lite
 * N. Nair, 5 September 1998
 */

#ifndef _BINDINGS_H
#define _BINDINGS_H

#include "../brl.h"		/* for CMD_* codes */

/* When the Braille Lite sends braille key information, bits 0-5 represent
 * dots 1-6 and bit 6 represents the space bar.  For now, we mask out bit 6
 * and just use 64-byte tables.
 */

/* The static arrays must only be in brl.c, so just in case ... */
#ifdef BRL_C
#undef BRL_C

static unsigned char brltrans[64] =
{
  ' ', 'a', '1', 'b', '\'', 'k', '2', 'l',
  '`', 'c', 'i', 'f', '/', 'm', 's', 'p',
  '"', 'e', '3', 'h', '9', 'o', '6', 'r',
  '~', 'd', 'j', 'g', '>', 'n', 't', 'q',
  ',', '*', '5', '<', '-', 'u', '8', 'v',
  '.', '%', '{', '$', '+', 'x', '!', '&',
  ';', ':', '4', '|', '0', 'z', '7', '(',
  '_', '?', 'w', '}', '#', 'y', ')', '='
};

#ifdef USE_TEXTTRANS
/* Map from key representations (bits 0-5 for dots 1-6) to BRLTTY dot
   pattern representation (dot 1 bit 0, dot 4 bit 1, dot 2 bit 2, etc) */
static unsigned char keys_to_dots[64] =
{
  0x0, 0x1, 0x4, 0x5, 0x10, 0x11, 0x14, 0x15,
  0x2, 0x3, 0x6, 0x7, 0x12, 0x13, 0x16, 0x17,
  0x8, 0x9, 0xc, 0xd, 0x18, 0x19, 0x1c, 0x1d,
  0xa, 0xb, 0xe, 0xf, 0x1a, 0x1b, 0x1e, 0x1f,
  0x20, 0x21, 0x24, 0x25, 0x30, 0x31, 0x34, 0x35,
  0x22, 0x23, 0x26, 0x27, 0x32, 0x33, 0x36, 0x37,
  0x28, 0x29, 0x2c, 0x2d, 0x38, 0x39, 0x3c, 0x3d,
  0x2a, 0x2b, 0x2e, 0x2f, 0x3a, 0x3b, 0x3e, 0x3f
};
#endif

/* This table is for global BRLTTY commands, to be passed straight back to
 * the main module.  If keyboard emulation is off, they will work with or
 * without a chord, unless they are marked as dangerous in dangcmd[] below.
 *
 * Note that key combinations used to initiate internal commands should be
 * left as 0 here.
 */

static unsigned char cmdtrans[64] =
{
  0, CMD_LNUP, CMD_KEY_LEFT, 0, CMD_CHRLT, 0, CMD_KEY_UP, CMD_TOP_LEFT,
  CMD_LNDN, CMD_CSRTRK, CMD_DISPMD, CMD_FREEZE, CMD_INFO, CMD_MUTE, CMD_NXSEARCH, CMD_PASTE,
  CMD_KEY_RIGHT, 0, 0, CMD_HOME, 0, 0, CMD_LNBEG, CMD_RESTARTBRL,
  CMD_CSRJMP_VERT, 0, CMD_CSRJMP, 0, 0, CMD_NXBLNKLN, 0, 0,
  CMD_CHRRT, 0, 0, 0, CMD_SAY, 0, CMD_CUT_BEG, CMD_SWITCHVT_NEXT,
  0, 0, 0, CMD_PRBLNKLN, 0, 0, 0, 0,
  CMD_KEY_DOWN, CMD_PRSEARCH, CMD_LNEND, 0, CMD_CUT_END, 0, 0, 0,
  CMD_BOT_LEFT, CMD_HELP, 0, 0, CMD_SWITCHVT_PREV, 0, 0, 0
};

/* Dangerous commands; 1 bit per command, order as cmdtrans[], set if
 * the corresponding command is dangerous.
 */

static unsigned char dangcmd[8] =
{ 0x00, 0x88, 0x80, 0x05, 0x40, 0x00, 0x10, 0x00 };

#endif /* defined(BRL_C) */


/*
 * Functions for the advance bar.  Currently, these are passed straight
 * back to the main module, so have to be global commands.
 */

/* BrailleLite 18 */
#define BLT_BARLT CMD_FWINLT
#define BLT_BARRT CMD_FWINRT

/* BrailleLite 40 (patterned after other screen readers) */
/* Left-hand advance bar: left=pan left, right=line up */
#define BLT_BARLT1 CMD_FWINLT
#define BLT_BARRT1 CMD_LNUP
/* Right-hand advance bar: left=line down, right=pan right */
#define BLT_BARLT2 CMD_LNDN
#define BLT_BARRT2 CMD_FWINRT


/* Internal commands.  The definitions use the ASCII codes from brltrans[]
 * above.  All must be chorded.
 */

#define BLT_KBEMU 'k'
#define BLT_ROTATE '7'
#define BLT_POSITN 'g'
#define BLT_REPEAT 'o'
#define BLT_CONFIG '3'
#define BLT_ENDCMD 'e'
#define BLT_ABORT 'z'
#define SWITCHVT_NEXT 's'
#define SWITCHVT_PREV ':'


/* For keyboard emulation mode: */
#define BLT_UPCASE 'u'
#define BLT_UPCOFF 'q'
#define BLT_CTRL 'x'
#ifdef USE_TEXTTRANS
#define BLT_DOT8SHIFT '5'
#endif
#define BLT_META '9'
#define BLT_BACKSP 'b'
#define BLT_DELETE 'd'
#define BLT_TAB 't'
#define BLT_ESCAPE '{'
#define BLT_ENTER '.'
/* Console - incr, decr, spawn.  Cursor keys? */

#endif /* !defined(_BINDINGS_H) */