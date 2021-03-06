#ifndef COSMOPOLITAN_LIBC_NT_INFO_H_
#define COSMOPOLITAN_LIBC_NT_INFO_H_
#include "libc/nt/struct/systeminfo.h"
#include "libc/nt/thunk/msabi.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct NtSystemInfo;

void GetSystemInfo(struct NtSystemInfo *lpSystemInfo);
uint32_t GetSystemDirectory(char16_t *lpBuffer, uint32_t uSize);
uint32_t GetSystemDirectoryA(char *lpBuffer, uint32_t uSize);
uint32_t GetWindowsDirectory(char16_t *lpBuffer, uint32_t uSize);
uint32_t GetTempPath(uint32_t uSize, char16_t *lpBuffer);

#if ShouldUseMsabiAttribute()
#include "libc/nt/thunk/systeminfo.inc"
#endif /* ShouldUseMsabiAttribute() */
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_INFO_H_ */
