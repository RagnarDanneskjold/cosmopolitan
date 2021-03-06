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
#include "libc/str/str.h"

/**
 * Extracts non-empty tokens from string.
 *
 * @param s is mutated and should be NULL on subsequent calls
 * @param sep is a NUL-terminated set of bytes to consider separators
 * @param state tracks progress between calls
 * @return pointer to next token or NULL for end
 * @see strsep() which is similar
 * @asyncsignalsafe
 */
char *strtok_r(char *s, const char *sep, char **state) {
  if (!s) {
    s = *state;
    if (!s) {
      return NULL;
    }
  }
  size_t leadingseps = strspn(s, sep);
  s += leadingseps;
  if (*s) {
    size_t tokenlen = strcspn(s, sep);
    if (s[tokenlen]) {
      s[tokenlen] = '\0';
      *state = &s[tokenlen + 1];
      return s;
    } else if (tokenlen) {
      s[tokenlen] = '\0';
      *state = NULL;
      return s;
    }
  }
  return (*state = NULL);
}
