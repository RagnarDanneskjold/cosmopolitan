#ifndef COSMOPOLITAN_LIBC_ZIPOS_ZIPOS_H_
#define COSMOPOLITAN_LIBC_ZIPOS_ZIPOS_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct stat;
struct iovec;

struct ZiposUri {
  const char *path;
  size_t len;
};

struct ZiposHandle {
  uint8_t *mem;   /* deflated file base */
  size_t size;    /* byte length of file */
  size_t pos;     /* read/write byte offset state */
  uint32_t cfile; /* central directory entry rva */
  uint8_t *map;
  size_t mapsize;
};

extern const char kZiposSchemePrefix[4];

ssize_t __zipos_parseuri(const char *, struct ZiposUri *);
ssize_t __zipos_find(const struct ZiposUri *);
int __zipos_close(struct ZiposHandle *);
int __zipos_open(const struct ZiposUri *, unsigned, int);
int __zipos_stat(const struct ZiposUri *, struct stat *);
int __zipos_fstat(const struct ZiposHandle *, struct stat *);
int __zipos_stat_impl(size_t, struct stat *);
ssize_t __zipos_read(struct ZiposHandle *, const struct iovec *, size_t,
                     ssize_t);
ssize_t __zipos_write(struct ZiposHandle *, const struct iovec *, size_t,
                      ssize_t);

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_ZIPOS_ZIPOS_H_ */
