#ifndef COSMOPOLITAN_LIBC_ALG_ARRAYLIST2_H_
#define COSMOPOLITAN_LIBC_ALG_ARRAYLIST2_H_
#include "libc/mem/mem.h"
#include "libc/str/str.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

/* TODO(jart): Fully develop these better macros. */

#define APPEND(LIST_P, LIST_I, LIST_N, ITEM) \
  CONCAT(LIST_P, LIST_I, LIST_N, ITEM, 1)

#define CONCAT(LIST_P, LIST_I, LIST_N, ITEM, COUNT)                   \
  ({                                                                  \
    autotype(LIST_P) ListP = (LIST_P);                                \
    autotype(LIST_I) ListI = (LIST_I);                                \
    autotype(LIST_N) ListN = (LIST_N);                                \
    typeof(&(*ListP)[0]) Item = (ITEM);                               \
    size_t SizE = sizeof(*Item);                                      \
    size_t Count = (COUNT);                                           \
    ssize_t Entry = -1;                                               \
    if (*ListI + Count < *ListN || grow(ListP, ListN, SizE, Count)) { \
      memcpy(&(*ListP)[*ListI], Item, (SizE) * (Count));              \
      Entry = *ListI;                                                 \
      *ListI += Count; /* happens after copy in case signal */        \
    }                                                                 \
    Entry;                                                            \
  })

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_ALG_ARRAYLIST2_H_ */
