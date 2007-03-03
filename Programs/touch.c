/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2007 by The BRLTTY Developers.
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

#include "prologue.h"

#include <stdio.h>

#include "misc.h"
#include "touch.h"

static int touchLeft;
static int touchRight;
static int touchTop;
static int touchBottom;

int
touchGetRegion (int *left, int *right, int *top, int *bottom) {
  if ((touchLeft > touchRight) || (touchTop > touchBottom)) return 0;

  *left = touchLeft;
  *right = touchRight;
  *top = touchTop;
  *bottom = touchBottom;
  return 1;
}

static inline int
touchCheckColumn (BrailleDisplay *brl, const unsigned char *pressure, int column) {
  int row;
  for (row=touchTop; row<=touchBottom; ++row) {
    if (pressure[(row * brl->x) + column]) return 1;
  }
  return 0;
}

static inline int
touchCheckRow (BrailleDisplay *brl, const unsigned char *pressure, int row) {
  int column;
  for (column=touchLeft; column<=touchRight; ++column) {
    if (pressure[(row * brl->x) + column]) return 1;
  }
  return 0;
}

static inline int
touchCropLeft (BrailleDisplay *brl, const unsigned char *pressure) {
  while (touchLeft <= touchRight) {
    if (touchCheckColumn(brl, pressure, touchLeft)) return 1;
    ++touchLeft;
  }
  return 0;
}

static inline int
touchCropRight (BrailleDisplay *brl, const unsigned char *pressure) {
  while (touchRight >= touchLeft) {
    if (touchCheckColumn(brl, pressure, touchRight)) return 1;
    --touchRight;
  }
  return 0;
}

static inline int
touchCropTop (BrailleDisplay *brl, const unsigned char *pressure) {
  while (touchTop <= touchBottom) {
    if (touchCheckRow(brl, pressure, touchTop)) return 1;
    ++touchTop;
  }
  return 0;
}

static inline int
touchCropBottom (BrailleDisplay *brl, const unsigned char *pressure) {
  while (touchBottom >= touchTop) {
    if (touchCheckRow(brl, pressure, touchBottom)) return 1;
    --touchBottom;
  }
  return 0;
}

static inline int
touchCropWindow (BrailleDisplay *brl, const unsigned char *pressure) {
  if (pressure) {
    if (touchCropRight(brl, pressure)) {
      touchCropLeft(brl, pressure);
      touchCropTop(brl, pressure);
      touchCropBottom(brl, pressure);
      return 1;
    }
  }

  touchBottom = touchTop - 1;
  return 0;
}

static inline void
touchUncropWindow (BrailleDisplay *brl) {
  touchLeft = 0;
  touchRight = brl->x;
  touchTop = 0;
  touchBottom = brl->y;
}

static inline int
touchRecropWindow (BrailleDisplay *brl, const unsigned char *pressure) {
  touchUncropWindow(brl);
  return touchCropWindow(brl, pressure);
}

int
touchAnalyzePressure (BrailleDisplay *brl, const unsigned char *pressure) {
  if (pressure) {
    LogBytes(LOG_DEBUG, "Touch Pressure", pressure, brl->x*brl->y);
  } else {
    LogPrint(LOG_DEBUG, "Touch Pressure off");
  }

  touchRecropWindow(brl, pressure);
  return EOF;
}

void
touchAnalyzeCells (BrailleDisplay *brl, const unsigned char *cells) {
}
