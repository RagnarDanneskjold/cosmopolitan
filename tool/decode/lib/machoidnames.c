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
#include "libc/macho.h"
#include "tool/decode/lib/machoidnames.h"

const struct IdName kMachoFileTypeNames[] = {
    {MAC_OBJECT, "MAC_OBJECT"},
    {MAC_EXECUTE, "MAC_EXECUTE"},
    {MAC_FVMLIB, "MAC_FVMLIB"},
    {MAC_CORE, "MAC_CORE"},
    {MAC_PRELOAD, "MAC_PRELOAD"},
    {MAC_DYLIB, "MAC_DYLIB"},
    {MAC_DYLINKER, "MAC_DYLINKER"},
    {MAC_BUNDLE, "MAC_BUNDLE"},
    {0, 0},
};

const struct IdName kMachoFlagNames[] = {
    {MAC_NOUNDEFS, "MAC_NOUNDEFS"},
    {MAC_INCRLINK, "MAC_INCRLINK"},
    {MAC_DYLDLINK, "MAC_DYLDLINK"},
    {MAC_BINDATLOAD, "MAC_BINDATLOAD"},
    {MAC_PREBOUND, "MAC_PREBOUND"},
    {MAC_SPLIT_SEGS, "MAC_SPLIT_SEGS"},
    {MAC_LAZY_INIT, "MAC_LAZY_INIT"},
    {MAC_TWOLEVEL, "MAC_TWOLEVEL"},
    {MAC_FORCE_FLAT, "MAC_FORCE_FLAT"},
    {MAC_NOMULTIDEFS, "MAC_NOMULTIDEFS"},
    {MAC_NOFIXPREBINDING, "MAC_NOFIXPREBINDING"},
    {MAC_PREBINDABLE, "MAC_PREBINDABLE"},
    {MAC_ALLMODSBOUND, "MAC_ALLMODSBOUND"},
    {MAC_SUBSECTIONS_VIA_SYMBOLS, "MAC_SUBSECTIONS_VIA_SYMBOLS"},
    {MAC_CANONICAL, "MAC_CANONICAL"},
    {0, 0},
};

const struct IdName kMachoSegmentFlagNames[] = {
    {MAC_SG_HIGHVM, "MAC_SG_HIGHVM"},
    {MAC_SG_FVMLIB, "MAC_SG_FVMLIB"},
    {MAC_SG_NORELOC, "MAC_SG_NORELOC"},
    {0, 0},
};

const struct IdName kMachoSectionTypeNames[] = {
    {MAC_S_REGULAR, "MAC_S_REGULAR"},
    {MAC_S_ZEROFILL, "MAC_S_ZEROFILL"},
    {MAC_S_CSTRING_LITERALS, "MAC_S_CSTRING_LITERALS"},
    {MAC_S_4BYTE_LITERALS, "MAC_S_4BYTE_LITERALS"},
    {MAC_S_8BYTE_LITERALS, "MAC_S_8BYTE_LITERALS"},
    {MAC_S_LITERAL_POINTERS, "MAC_S_LITERAL_POINTERS"},
    {MAC_S_NON_LAZY_SYMBOL_POINTERS, "MAC_S_NON_LAZY_SYMBOL_POINTERS"},
    {MAC_S_LAZY_SYMBOL_POINTERS, "MAC_S_LAZY_SYMBOL_POINTERS"},
    {MAC_S_SYMBOL_STUBS, "MAC_S_SYMBOL_STUBS"},
    {MAC_S_MOD_INIT_FUNC_POINTERS, "MAC_S_MOD_INIT_FUNC_POINTERS"},
    {MAC_S_MOD_TERM_FUNC_POINTERS, "MAC_S_MOD_TERM_FUNC_POINTERS"},
    {MAC_S_COALESCED, "MAC_S_COALESCED"},
    {MAC_S_GB_ZEROFILL, "MAC_S_GB_ZEROFILL"},
    {MAC_S_INTERPOSING, "MAC_S_INTERPOSING"},
    {MAC_S_16BYTE_LITERALS, "MAC_S_16BYTE_LITERALS"},
    {0, 0},
};

const struct IdName kMachoSectionAttributeNames[] = {
    {MAC_SECTION_ATTRIBUTES_USR, "MAC_SECTION_ATTRIBUTES_USR"},
    {MAC_S_ATTR_PURE_INSTRUCTIONS, "MAC_S_ATTR_PURE_INSTRUCTIONS"},
    {MAC_S_ATTR_NO_TOC, "MAC_S_ATTR_NO_TOC"},
    {MAC_S_ATTR_STRIP_STATIC_SYMS, "MAC_S_ATTR_STRIP_STATIC_SYMS"},
    {MAC_S_ATTR_NO_DEAD_STRIP, "MAC_S_ATTR_NO_DEAD_STRIP"},
    {MAC_S_ATTR_LIVE_SUPPORT, "MAC_S_ATTR_LIVE_SUPPORT"},
    {MAC_S_ATTR_SELF_MODIFYING_CODE, "MAC_S_ATTR_SELF_MODIFYING_CODE"},
    {MAC_S_ATTR_DEBUG, "MAC_S_ATTR_DEBUG"},
    {MAC_SECTION_ATTRIBUTES_SYS, "MAC_SECTION_ATTRIBUTES_SYS"},
    {MAC_S_ATTR_SOME_INSTRUCTIONS, "MAC_S_ATTR_SOME_INSTRUCTIONS"},
    {MAC_S_ATTR_EXT_RELOC, "MAC_S_ATTR_EXT_RELOC"},
    {MAC_S_ATTR_LOC_RELOC, "MAC_S_ATTR_LOC_RELOC"},
    {0, 0},
};

const struct IdName kMachoLoadCommandNames[] = {
    {MAC_LC_REQ_DYLD, "MAC_LC_REQ_DYLD"},
    {MAC_LC_SEGMENT, "MAC_LC_SEGMENT"},
    {MAC_LC_SYMTAB, "MAC_LC_SYMTAB"},
    {MAC_LC_SYMSEG, "MAC_LC_SYMSEG"},
    {MAC_LC_THREAD, "MAC_LC_THREAD"},
    {MAC_LC_UNIXTHREAD, "MAC_LC_UNIXTHREAD"},
    {MAC_LC_LOADFVMLIB, "MAC_LC_LOADFVMLIB"},
    {MAC_LC_IDFVMLIB, "MAC_LC_IDFVMLIB"},
    {MAC_LC_IDENT, "MAC_LC_IDENT"},
    {MAC_LC_FVMFILE, "MAC_LC_FVMFILE"},
    {MAC_LC_PREPAGE, "MAC_LC_PREPAGE"},
    {MAC_LC_DYSYMTAB, "MAC_LC_DYSYMTAB"},
    {MAC_LC_LOAD_DYLIB, "MAC_LC_LOAD_DYLIB"},
    {MAC_LC_ID_DYLIB, "MAC_LC_ID_DYLIB"},
    {MAC_LC_LOAD_DYLINKER, "MAC_LC_LOAD_DYLINKER"},
    {MAC_LC_ID_DYLINKER, "MAC_LC_ID_DYLINKER"},
    {MAC_LC_PREBOUND_DYLIB, "MAC_LC_PREBOUND_DYLIB"},
    {MAC_LC_ROUTINES, "MAC_LC_ROUTINES"},
    {MAC_LC_SUB_FRAMEWORK, "MAC_LC_SUB_FRAMEWORK"},
    {MAC_LC_SUB_UMBRELLA, "MAC_LC_SUB_UMBRELLA"},
    {MAC_LC_SUB_CLIENT, "MAC_LC_SUB_CLIENT"},
    {MAC_LC_SUB_LIBRARY, "MAC_LC_SUB_LIBRARY"},
    {MAC_LC_TWOLEVEL_HINTS, "MAC_LC_TWOLEVEL_HINTS"},
    {MAC_LC_PREBIND_CKSUM, "MAC_LC_PREBIND_CKSUM"},
    {MAC_LC_LOAD_WEAK_DYLIB, "MAC_LC_LOAD_WEAK_DYLIB"},
    {MAC_LC_SEGMENT_64, "MAC_LC_SEGMENT_64"},
    {MAC_LC_ROUTINES_64, "MAC_LC_ROUTINES_64"},
    {MAC_LC_UUID, "MAC_LC_UUID"},
    {MAC_LC_CODE_SIGNATURE, "MAC_LC_CODE_SIGNATURE"},
    {MAC_LC_SEGMENT_SPLIT_INFO, "MAC_LC_SEGMENT_SPLIT_INFO"},
    {MAC_LC_LAZY_LOAD_DYLIB, "MAC_LC_LAZY_LOAD_DYLIB"},
    {MAC_LC_ENCRYPTION_INFO, "MAC_LC_ENCRYPTION_INFO"},
    {MAC_LC_DYLD_INFO, "MAC_LC_DYLD_INFO"},
    {MAC_LC_VERSION_MIN_MACOSX, "MAC_LC_VERSION_MIN_MACOSX"},
    {MAC_LC_VERSION_MIN_IPHONEOS, "MAC_LC_VERSION_MIN_IPHONEOS"},
    {MAC_LC_FUNCTION_STARTS, "MAC_LC_FUNCTION_STARTS"},
    {MAC_LC_DYLD_ENVIRONMENT, "MAC_LC_DYLD_ENVIRONMENT"},
    {MAC_LC_DATA_IN_CODE, "MAC_LC_DATA_IN_CODE"},
    {MAC_LC_SOURCE_VERSION, "MAC_LC_SOURCE_VERSION"},
    {MAC_LC_RPATH, "MAC_LC_RPATH"},
    {MAC_LC_MAIN, "MAC_LC_MAIN"},
    {0, 0},
};

const struct IdName kMachoVmProtNames[] = {
    {VM_PROT_READ, "VM_PROT_READ"},
    {VM_PROT_WRITE, "VM_PROT_WRITE"},
    {VM_PROT_EXECUTE, "VM_PROT_EXECUTE"},
    {VM_PROT_NO_CHANGE, "VM_PROT_NO_CHANGE"},
    {VM_PROT_COPY, "VM_PROT_COPY"},
    {VM_PROT_TRUSTED, "VM_PROT_TRUSTED"},
    {VM_PROT_STRIP_READ, "VM_PROT_STRIP_READ"},
    {0, 0},
};
