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
#include "libc/runtime/runtime.h"
#include "libc/testlib/testlib.h"

/**
 * @fileoverview Tests for arithmetic overflow traps.
 *
 * This module assumes -ftrapv, but not -fsanitize=undefined; since
 * Ubsan provides a superset trapping functionality, and therefore
 * overrides the prior. The nice thing about -ftrapv is that it doesn't
 * leak huge amounts of information into the binary. So it's appropriate
 * to enable in a release build.
 *
 * @note LLVM's implementation of the runtime for this crashes due to
 *     relying on undefined behavior lool, the very thing the flag was
 *     meant to help prevent, so we don't get punked by the compiler
 * @see __addvsi3, __mulvsi3, etc.
 */

bool overflowed_;

void __on_arithmetic_overflow(void) {
  overflowed_ = true;
}

void SetUp(void) {
  overflowed_ = false;
}

/* 32-BIT SIGNED NEGATION */

TEST(__negvsi2, testMax) {
  EXPECT_EQ(-INT_MAX, -VEIL("r", INT_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__negvsi2, testMin0) {
  EXPROPRIATE(-VEIL("r", INT_MIN));
  EXPECT_TRUE(overflowed_);
}

/* 64-BIT SIGNED NEGATION */

TEST(__negvdi2, testMax) {
  EXPECT_EQ(-LONG_MAX, -VEIL("r", LONG_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__negvdi2, testMin0) {
  EXPROPRIATE(-VEIL("r", LONG_MIN));
  EXPECT_TRUE(overflowed_);
}

/* 32-BIT SIGNED MULTIPLICATION */

TEST(__mulvsi3, testMin0) {
  EXPECT_EQ(0, 0 * VEIL("r", INT_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvsi3, testMin1) {
  EXPECT_EQ(INT_MIN, 1 * VEIL("r", INT_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvsi3, testMin2) {
  EXPROPRIATE(2 * VEIL("r", INT_MIN));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvsi3, testMax0) {
  EXPECT_EQ(0, 0 * VEIL("r", INT_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvsi3, testMax1) {
  EXPECT_EQ(INT_MAX, 1 * VEIL("r", INT_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvsi3, testMax2) {
  EXPROPRIATE(2 * VEIL("r", INT_MAX));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvsi3, test7) {
  EXPECT_EQ(0x70000000, 7 * VEIL("r", 0x10000000));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvsi3, test8) {
  EXPROPRIATE(8 * VEIL("r", 0x10000000));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvsi3, test31337) {
  EXPROPRIATE(0x31337 * VEIL("r", 0x31337));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvsi3, standAndDeliver_aNegativeTimesANegativeEqualsAPositive) {
  EXPECT_EQ(25, -5 * VEIL("r", -5));
  EXPECT_FALSE(overflowed_);
}

/* 64-BIT SIGNED MULTIPLICATION */

TEST(__mulvdi3, testMin0) {
  EXPECT_EQ(0, 0 * VEIL("r", LONG_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvdi3, testMin1) {
  EXPECT_EQ(LONG_MIN, 1 * VEIL("r", LONG_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvdi3, testMin2) {
  EXPROPRIATE(2 * VEIL("r", LONG_MIN));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvdi3, testMax0) {
  EXPECT_EQ(0, 0 * VEIL("r", LONG_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvdi3, testMax1) {
  EXPECT_EQ(LONG_MAX, 1 * VEIL("r", LONG_MAX));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvdi3, testMax2) {
  EXPROPRIATE(2 * VEIL("r", LONG_MAX));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvdi3, test7) {
  EXPECT_EQ(0x7000000000000000l, 7 * VEIL("r", 0x1000000000000000l));
  EXPECT_FALSE(overflowed_);
}

TEST(__mulvdi3, test8) {
  EXPROPRIATE(8 * VEIL("r", 0x1000000000000000l));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvdi3, test31337) {
  EXPROPRIATE(0x3133700000000l * VEIL("r", 0x3133700000000l));
  EXPECT_TRUE(overflowed_);
}

TEST(__mulvdi3, standAndDeliver_aNegativeTimesANegativeEqualsAPositive) {
  EXPECT_EQ(25l, -5l * VEIL("r", -5l));
  EXPECT_FALSE(overflowed_);
}

/* 32-BIT SIGNED ADDITION */

TEST(__addvsi3, testMin1) {
  EXPECT_EQ(INT_MIN + 1, 1 + VEIL("r", INT_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__addvsi3, testMax1) {
  EXPROPRIATE(1 + VEIL("r", INT_MAX));
  EXPECT_TRUE(overflowed_);
}

TEST(__addvsi3, testNegPos) {
  EXPECT_EQ(2, -2 + VEIL("r", 4));
  EXPECT_FALSE(overflowed_);
}

TEST(__addvsi3, testPosNeg) {
  EXPECT_EQ(-2, 2 + VEIL("r", -4));
  EXPECT_FALSE(overflowed_);
}

/* 64-BIT SIGNED ADDITION */

TEST(__addvdi3, testMin1) {
  EXPECT_EQ(LONG_MIN + 1, 1 + VEIL("r", LONG_MIN));
  EXPECT_FALSE(overflowed_);
}

TEST(__addvdi3, testMax1) {
  EXPROPRIATE(1 + VEIL("r", LONG_MAX));
  EXPECT_TRUE(overflowed_);
}

TEST(__addvdi3, testNegPos) {
  EXPECT_EQ(2l, -2l + VEIL("r", 4l));
  EXPECT_FALSE(overflowed_);
}

TEST(__addvdi3, testPosNeg) {
  EXPECT_EQ(-2l, 2l + VEIL("r", -4l));
  EXPECT_FALSE(overflowed_);
}

/* 32-BIT SIGNED SUBTRACTION */

TEST(__subvsi3, testMin1) {
  EXPROPRIATE(VEIL("r", INT_MIN) - 1);
  EXPECT_TRUE(overflowed_);
}

TEST(__subvsi3, testMax1) {
  EXPECT_EQ(INT_MAX - 1, VEIL("r", INT_MAX) - 1);
  EXPECT_FALSE(overflowed_);
}

TEST(__subvsi3, testPosNeg) {
  EXPECT_EQ(-2, 2 - VEIL("r", 4));
  EXPECT_FALSE(overflowed_);
}

/* 64-BIT SIGNED SUBTRACTION */

TEST(__subvdi3, testMin1) {
  EXPROPRIATE(VEIL("r", LONG_MIN) - 1);
  EXPECT_TRUE(overflowed_);
}

TEST(__subvdi3, testMax1) {
  EXPECT_EQ(LONG_MAX - 1, VEIL("r", LONG_MAX) - 1);
  EXPECT_FALSE(overflowed_);
}
