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
#include "libc/bits/pushpop.h"
#include "libc/calls/calls.h"
#include "libc/fmt/fmt.h"
#include "libc/log/internal.h"
#include "libc/log/log.h"
#include "libc/log/ubsan.h"
#include "libc/runtime/internal.h"
#include "libc/runtime/missioncritical.h"
#include "libc/runtime/runtime.h"
#include "libc/stdio/stdio.h"
#include "libc/str/str.h"
#include "libc/sysv/consts/fileno.h"

static char __ubsan_buf[256];

static const char kUbsanTypeCheckKinds[] = "load of\0"
                                           "store to\0"
                                           "reference binding to\0"
                                           "member access within\0"
                                           "member call on\0"
                                           "constructor call on\0"
                                           "downcast of\0"
                                           "downcast of\0"
                                           "upcast of\0"
                                           "cast to virtual base of\0"
                                           "\0";

void __ubsan_abort(const struct UbsanSourceLocation *loc,
                   const char *description) {
  static bool once;
  if (!once) {
    once = true;
  } else {
    abort();
  }
  g_runstate |= RUNSTATE_BROKEN;
  if (IsDebuggerPresent(false)) DebugBreak();
  startfatal(loc->file, loc->line);
  fprintf(stderr, "%s\n", description);
  die();
  unreachable;
}

void __ubsan_handle_out_of_bounds(struct UbsanOutOfBoundsInfo *info,
                                  uintptr_t index) {
  snprintf(__ubsan_buf, sizeof(__ubsan_buf),
           "%s index %,lu into %s out of bounds", info->index_type->name, index,
           info->array_type->name);
  __ubsan_abort(&info->location, __ubsan_buf);
  unreachable;
}

void __ubsan_handle_type_mismatch(struct UbsanTypeMismatchInfo *type_mismatch,
                                  uintptr_t pointer) {
  struct UbsanSourceLocation *loc = &type_mismatch->location;
  const char *description;
  const char *kind = indexdoublenulstring(kUbsanTypeCheckKinds,
                                          type_mismatch->type_check_kind);
  if (pointer == 0) {
    description = "null pointer access";
  } else if (type_mismatch->alignment != 0 &&
             (pointer & (type_mismatch->alignment - 1))) {
    description = __ubsan_buf;
    snprintf(__ubsan_buf, sizeof(__ubsan_buf), "%s %s %s @%p %s %d",
             "unaligned", kind, type_mismatch->type->name, pointer, "align",
             type_mismatch->alignment);
  } else {
    description = __ubsan_buf;
    snprintf(__ubsan_buf, sizeof(__ubsan_buf), "%s\n\t%s %s %p %s %s",
             "insufficient size", kind, "address", pointer,
             "with insufficient space for object of type",
             type_mismatch->type->name);
  }
  __ubsan_abort(loc, description);
  unreachable;
}

void ___ubsan_handle_type_mismatch_v1(
    struct UbsanTypeMismatchInfoClang *type_mismatch, uintptr_t pointer) {
  struct UbsanTypeMismatchInfo mm;
  mm.location = type_mismatch->location;
  mm.type = type_mismatch->type;
  mm.alignment = 1u << type_mismatch->log_alignment;
  mm.type_check_kind = type_mismatch->type_check_kind;
  __ubsan_handle_type_mismatch(&mm, pointer);
  unreachable;
}

void __ubsan_handle_float_cast_overflow(void *data_raw, void *from_raw) {
  struct UbsanFloatCastOverflowData *data =
      (struct UbsanFloatCastOverflowData *)data_raw;
#if __GNUC__ + 0 >= 6
  __ubsan_abort(&data->location, "float cast overflow");
#else
  const struct UbsanSourceLocation kUnknownLocation = {
      "<unknown file>",
      pushpop(0),
      pushpop(0),
  };
  __ubsan_abort(((void)data, &kUnknownLocation), "float cast overflow");
#endif
  unreachable;
}
