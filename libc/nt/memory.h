#ifndef COSMOPOLITAN_LIBC_NT_MEMORY_H_
#define COSMOPOLITAN_LIBC_NT_MEMORY_H_
#include "libc/nt/enum/filemapflags.h"
#include "libc/nt/enum/memflags.h"
#include "libc/nt/enum/offerpriority.h"
#include "libc/nt/enum/pageflags.h"
#if 0
/*                            ░░░░
                       ▒▒▒░░░▒▒▒▒▒▒▒▓▓▓░
                      ▒▒▒▒░░░▒▒▒▒▒▒▓▓▓▓▓▓░
                     ▒▒▒▒░░░▒▒▒▒▒▒▒▓▓▓▓▓▓  ▒▓░
                     ▒▒▒░░░░▒▒▒▒▒▒▓▓▓▓▓▓   ▓▓▓▓▓▓▒        ▒▒▒▓▓█
                    ▒▒▒▒░░░▒▒▒▒▒▒▒▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓
                   ░▒▒▒░░░░▒▒▒▒▒▒▓▓▓▓▓▓   █▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓█
                   ▒▒▒▒░░░▒▒▒▒▒▒▒▓▓▓▓▓░  ▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓
                  ▒▒▒▒░░░▒▒▒▒▒▒▒▓▓▓▓▓▓  ▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒
                  ▒▒▒▒▓▓      ▓▒▒▓▓▓▓   ▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓█
                                   ▒▓  ▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓
                  ░░░░░░░░░░░▒▒▒▒      ▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓█
                ▒▒░░░░░░░░░░▒▒▒▒▒▓▓▓     ▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓
               ░▒░░░░░░░░░░░▒▒▒▒▒▓▓   ▓░      ░▓███▓
               ▒▒░░░░░░░░░░▒▒▒▒▒▓▓░  ▒▓▓▓▒▒▒         ░▒▒▒▓   ████████████
              ▒▒░░░░░░░░░░░▒▒▒▒▒▓▓  ▒▓▓▓▓▒▒▒▒▒▒▒▒░░░▒▒▒▒▒░           ░███
              ▒░░░░░░░░░░░▒▒▒▒▒▓▓   ▓▓▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒▓            ███
             ▒▒░░░░░░░░░░▒▒▒▒▒▒▓▓  ▒▓▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒            ▓██
             ▒░░░░░░░░░░░▒▒▒▒▒▓▓   ▓▓▓▓▒▒▒▒▒▒▒▒░░░▒▒▒▒▒▓           ▓██
            ▒▒░░░▒▒▒░░░▒▒░▒▒▒▓▓▒  ▒▓▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒           ███
                            ░▒▓  ░▓▓▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒▓          ▓██
╔────────────────────────────────────────────────────────────────▀▀▀─────────│─╗
│ cosmopolitan § new technology » memory                                   ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/
#endif

#define kNtNumaNoPreferredNode 0xffffffff

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct NtMemoryBasicInformation;
struct NtMemoryRangeEntry;
struct NtSecurityAttributes;

int64_t CreateFileMappingNuma(
    int64_t opt_hFile /* -1ul is MAP_ANONYMOUS */,
    const struct NtSecurityAttributes *opt_lpFileMappingAttributes,
    uint32_t flProtect, uint32_t dwMaximumSizeHigh, uint32_t dwMaximumSizeLow,
    const char16_t *opt_lpName, uint32_t nndDesiredNumaNode);
void *MapViewOfFileExNuma(
    int64_t hFileMappingObject, /* @see CreateFileMapping() */
    uint32_t dwDesiredAccess, uint32_t dwFileOffsetHigh, /* high order bits */
    uint32_t dwFileOffsetLow,                            /* low order bits */
    size_t dwNumberOfBytesToMap, void *opt_lpDesiredBaseAddress,
    uint32_t nndDesiredNumaNode);
bool32 UnmapViewOfFile(const void *lpBaseAddress);
bool32 FlushViewOfFile(const void *lpBaseAddress,
                       size_t dwNumberOfBytesToFlush);

void *VirtualAlloc(void *opt_lpAddress, uint64_t dwSize,
                   uint32_t flAllocationType, uint32_t flProtect);
bool32 VirtualFree(void *lpAddress, uint64_t dwSize, uint32_t dwFreeType);
bool32 VirtualProtect(void *lpAddress, uint64_t dwSize, uint32_t flNewProtect,
                      uint32_t *lpflOldProtect) paramsnonnull();
uint64_t VirtualQuery(const void *lpAddress,
                      struct NtMemoryBasicInformation *lpBuffer,
                      uint64_t dwLength);
void *VirtualAllocEx(int64_t hProcess, void *lpAddress, uint64_t dwSize,
                     uint32_t flAllocationType, uint32_t flProtect);

bool32 PrefetchVirtualMemory(int64_t hProcess, const uint32_t *NumberOfEntries,
                             struct NtMemoryRangeEntry *VirtualAddresses,
                             uint32_t reserved_Flags);
bool32 OfferVirtualMemory(void *inout_VirtualAddress, size_t Size,
                          enum NtOfferPriority Priority);

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_MEMORY_H_ */
