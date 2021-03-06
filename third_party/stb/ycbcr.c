/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/limits.h"
#include "libc/log/check.h"
#include "libc/log/log.h"
#include "libc/macros.h"
#include "libc/str/str.h"
#include "third_party/stb/internal.h"

/* this is a reduced-precision calculation of YCbCr-to-RGB introduced
   to make sure the code produces the same results in both SIMD and scalar */
#define FLOAT2FIXED(x) (((int)((x)*4096.0f + 0.5f)) << 8)

void stbi__YCbCr_to_RGB_row(unsigned char *out, const unsigned char *y,
                            const unsigned char *pcb, const unsigned char *pcr,
                            unsigned count, unsigned step) {
  unsigned i;
  unsigned char b4[4];
  int y_fixed, r, g, b, cr, cb;
  CHECK(step == 3 || step == 4);
  CHECK_LE(count, INT_MAX / 4 - 4);
  for (i = step == 4 ? stbi__YCbCr_to_RGB_row$sse2(out, y, pcb, pcr, count) : 0;
       i < count; ++i) {
    y_fixed = (y[i] << 20) + (1 << 19); /* rounding */
    cr = pcr[i] - 128;
    cb = pcb[i] - 128;
    r = y_fixed + cr * FLOAT2FIXED(1.40200f);
    g = y_fixed + (cr * -FLOAT2FIXED(0.71414f)) +
        ((cb * -FLOAT2FIXED(0.34414f)) & 0xffff0000);
    b = y_fixed + cb * FLOAT2FIXED(1.77200f);
    r /= 1048576;
    g /= 1048576;
    b /= 1048576;
    b4[0] = MIN(255, MAX(0, r));
    b4[1] = MIN(255, MAX(0, g));
    b4[2] = MIN(255, MAX(0, b));
    b4[3] = 255;
    memcpy(out + i * step, b4, 4);
  }
}
