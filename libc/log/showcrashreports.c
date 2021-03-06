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
#include "libc/bits/bits.h"
#include "libc/calls/calls.h"
#include "libc/calls/sigbits.h"
#include "libc/calls/typedef/sigaction_f.h"
#include "libc/dce.h"
#include "libc/log/internal.h"
#include "libc/log/log.h"
#include "libc/macros.h"
#include "libc/nt/signals.h"
#include "libc/str/str.h"
#include "libc/sysv/consts/sa.h"
#include "libc/sysv/consts/sig.h"

extern const unsigned char kOncrashThunks[7][11];

/**
 * Installs crash signal handlers.
 *
 * Normally, only functions calling die() will print backtraces. This
 * function may be called at program startup to install handlers that
 * will display similar information, for most types of crashes.
 *
 *   - Backtraces
 *   - CPU state printout
 *   - Automatic debugger attachment
 *
 * Another trick this function enables, is you can press CTRL+\ to open
 * the debugger GUI at any point while the program is running. It can be
 * useful, for example, if a program is caught in an infinite loop.
 *
 * @see callexitontermination()
 */
optimizesize void showcrashreports(void) {
  size_t i;
  struct sigaction sa;
  if (IsModeDbg()) STATIC_YOINK("__ubsan_abort");
  if (!NoDebug()) STATIC_YOINK("die");
  /* <SYNC-LIST>: oncrashthunks.S */
  kCrashSigs[0] = SIGQUIT; /* ctrl+\ aka ctrl+break */
  kCrashSigs[1] = SIGFPE;  /* 1 / 0 */
  kCrashSigs[2] = SIGILL;  /* illegal instruction */
  kCrashSigs[3] = SIGSEGV; /* bad memory access */
  kCrashSigs[4] = SIGTRAP; /* bad system call */
  kCrashSigs[5] = SIGABRT; /* abort() called */
  kCrashSigs[6] = SIGBUS;  /* misaligned, noncanonical ptr, etc. */
  /* </SYNC-LIST>: oncrashthunks.S */
  memset(&sa, 0, sizeof(sa));
  sa.sa_flags = SA_RESETHAND;
  sigfillset(&sa.sa_mask);
  for (i = 0; i < ARRAYLEN(kCrashSigs); ++i) {
    sigdelset(&sa.sa_mask, kCrashSigs[i]);
  }
  for (i = 0; i < ARRAYLEN(kCrashSigs); ++i) {
    if (kCrashSigs[i]) {
      sa.sa_sigaction = (sigaction_f)kOncrashThunks[i];
      sigaction(kCrashSigs[i], &sa, &g_oldcrashacts[i]);
    }
  }
}
