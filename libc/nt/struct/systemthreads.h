#ifndef COSMOPOLITAN_LIBC_NT_STRUCT_SYSTEMTHREADS_H_
#define COSMOPOLITAN_LIBC_NT_STRUCT_SYSTEMTHREADS_H_
#include "libc/nt/enum/kwaitreason.h"
#include "libc/nt/enum/threadstate.h"
#include "libc/nt/struct/clientid.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)

struct NtSystemThreads {
  int64_t KernelTime;
  int64_t UserTime;
  int64_t CreateTime;
  uint32_t WaitTime;
  void *StartAddress;
  struct NtClientId ClientId;
  int32_t Priority;
  int32_t BasePriority;
  uint32_t ContextSwitchCount;
  enum NtThreadState State;
  uint32_t WaitReason;
};

#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_STRUCT_SYSTEMTHREADS_H_ */
