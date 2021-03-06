#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘

PKGS += TEST_LIBC_FMT

TEST_LIBC_FMT_SRCS := $(wildcard test/libc/fmt/*.c)
TEST_LIBC_FMT_SRCS_TEST = $(filter %_test.c,$(TEST_LIBC_FMT_SRCS))
TEST_LIBC_FMT_COMS = $(TEST_LIBC_FMT_OBJS:%.o=%.com)
TEST_LIBC_FMT_BINS = $(TEST_LIBC_FMT_COMS) $(TEST_LIBC_FMT_COMS:%=%.dbg)
TEST_LIBC_FMT_TESTS = $(TEST_LIBC_FMT_SRCS_TEST:%.c=o/$(MODE)/%.com.ok)

TEST_LIBC_FMT_OBJS =					\
	$(TEST_LIBC_FMT_SRCS:%=o/$(MODE)/%.zip.o)	\
	$(TEST_LIBC_FMT_SRCS:%.c=o/$(MODE)/%.o)

TEST_LIBC_FMT_CHECKS =					\
	$(TEST_LIBC_FMT_SRCS_TEST:%.c=o/$(MODE)/%.com.runs)

TEST_LIBC_FMT_DIRECTDEPS =				\
	LIBC_CALLS_HEFTY				\
	LIBC_FMT					\
	LIBC_MEM					\
	LIBC_NEXGEN32E					\
	LIBC_RUNTIME					\
	LIBC_STR					\
	LIBC_STUBS					\
	LIBC_SYSV					\
	LIBC_TESTLIB					\
	LIBC_UNICODE					\
	LIBC_X

TEST_LIBC_FMT_DEPS :=					\
	$(call uniq,$(foreach x,$(TEST_LIBC_FMT_DIRECTDEPS),$($(x))))

o/$(MODE)/test/libc/fmt/fmt.pkg:			\
		$(TEST_LIBC_FMT_OBJS)			\
		$(foreach x,$(TEST_LIBC_FMT_DIRECTDEPS),$($(x)_A).pkg)

o/$(MODE)/test/libc/fmt/%.com.dbg:			\
		$(TEST_LIBC_FMT_DEPS)			\
		o/$(MODE)/test/libc/fmt/%.o		\
		o/$(MODE)/test/libc/fmt/fmt.pkg		\
		$(LIBC_TESTMAIN)			\
		$(CRT)					\
		$(APE)
	@$(APELINK)

$(TEST_LIBC_FMT_OBJS):					\
		$(BUILD_FILES)				\
		test/libc/fmt/test.mk

.PHONY: o/$(MODE)/test/libc/fmt
o/$(MODE)/test/libc/fmt:				\
		$(TEST_LIBC_FMT_BINS)			\
		$(TEST_LIBC_FMT_CHECKS)
