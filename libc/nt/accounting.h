#ifndef COSMOPOLITAN_LIBC_NT_ACCOUNTING_H_
#define COSMOPOLITAN_LIBC_NT_ACCOUNTING_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_
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
│ cosmopolitan § new technology » accounting                               ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/
#endif

struct NtFileTime;
struct NtIoCounters;
struct NtMemoryStatusEx;

int GetUserName(char16_t (*buf)[257], uint32_t *in_out_size);
bool32 GlobalMemoryStatusEx(struct NtMemoryStatusEx *lpBuffer);
int32_t GetExitCodeProcess(int64_t hProcess, uint32_t *lpExitCode);
int32_t GetProcessHandleCount(int64_t hProcess, uint32_t *pdwHandleCount);
bool32 GetProcessTimes(int64_t hProcess,
                       struct NtFileTime *out_lpCreationFileTime,
                       struct NtFileTime *out_lpExitFileTime,
                       struct NtFileTime *out_lpKernelFileTime,
                       struct NtFileTime *out_lpUserFileTime);
bool32 GetThreadTimes(int64_t hThread,
                      struct NtFileTime *out_lpCreationFileTime,
                      struct NtFileTime *out_lpExitFileTime,
                      struct NtFileTime *out_lpKernelFileTime,
                      struct NtFileTime *out_lpUserFileTime);
int32_t GetProcessIoCounters(int64_t hProcess,
                             struct NtIoCounters *lpIoCounters);
int32_t GetProcessWorkingSetSize(int64_t hProcess,
                                 uint64_t *lpMinimumWorkingSetSize,
                                 uint64_t *lpMaximumWorkingSetSize);
int32_t GetProcessWorkingSetSizeEx(int64_t hProcess,
                                   uint64_t *lpMinimumWorkingSetSize,
                                   uint64_t *lpMaximumWorkingSetSize,
                                   uint32_t *Flags);
int32_t SetProcessWorkingSetSize(int64_t hProcess,
                                 uint64_t dwMinimumWorkingSetSize,
                                 uint64_t dwMaximumWorkingSetSize);
int32_t SetProcessWorkingSetSizeEx(int64_t hProcess,
                                   uint64_t dwMinimumWorkingSetSize,
                                   uint64_t dwMaximumWorkingSetSize,
                                   uint32_t Flags);

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_ACCOUNTING_H_ */
