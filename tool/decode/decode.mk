#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘

PKGS += TOOL_DECODE

TOOL_DECODE_FILES := $(wildcard tool/decode/*)
TOOL_DECODE_HDRS = $(filter %.h,$(TOOL_DECODE_FILES))
TOOL_DECODE_SRCS = $(filter %.c,$(TOOL_DECODE_FILES))
TOOL_DECODE_COMS = $(TOOL_DECODE_OBJS:%.o=%.com)

TOOL_DECODE_OBJS =					\
	$(TOOL_DECODE_SRCS:%=o/$(MODE)/%.zip.o)		\
	$(TOOL_DECODE_SRCS:%.c=o/$(MODE)/%.o)

TOOL_DECODE_BINS =					\
	$(TOOL_DECODE_COMS)				\
	$(TOOL_DECODE_COMS:%=%.dbg)

TOOL_DECODE_CHECKS =					\
	$(TOOL_DECODE_HDRS:%=o/$(MODE)/%.ok)

TOOL_DECODE_DIRECTDEPS =				\
	LIBC_CALLS					\
	LIBC_CONV					\
	LIBC_ELF					\
	LIBC_FMT					\
	LIBC_LOG					\
	LIBC_MEM					\
	LIBC_NEXGEN32E					\
	LIBC_RAND					\
	LIBC_RUNTIME					\
	LIBC_RUNTIME					\
	LIBC_STDIO					\
	LIBC_STR					\
	LIBC_STUBS					\
	LIBC_SYSV					\
	LIBC_UNICODE					\
	LIBC_X						\
	TOOL_DECODE_LIB					\
	THIRD_PARTY_GETOPT				\
	THIRD_PARTY_XED

TOOL_DECODE_DEPS :=					\
	$(call uniq,$(foreach x,$(TOOL_DECODE_DIRECTDEPS),$($(x))))

o/$(MODE)/tool/decode/decode.pkg:			\
		$(TOOL_DECODE_OBJS)			\
		$(foreach x,$(TOOL_DECODE_DIRECTDEPS),$($(x)_A).pkg)

o/$(MODE)/tool/decode/%.com.dbg:			\
		$(TOOL_DECODE_DEPS)			\
		o/$(MODE)/tool/decode/%.o		\
		o/$(MODE)/tool/decode/decode.pkg	\
		$(CRT)					\
		$(APE)
	@$(APELINK)

$(TOOL_DECODE_OBJS):					\
		$(BUILD_FILES)				\
		tool/decode/decode.mk

.PHONY: o/$(MODE)/tool/decode
o/$(MODE)/tool/decode:					\
		o/$(MODE)/tool/decode/lib		\
		$(TOOL_DECODE_BINS)			\
		$(TOOL_DECODE_CHECKS)
