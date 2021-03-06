#ifndef COSMOPOLITAN_LIBC_STR_STR_H_
#define COSMOPOLITAN_LIBC_STR_STR_H_
#include "libc/bits/bits.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_
/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § characters » asa x3.4-1967                                ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│─╝
  fourth age telecommunications */

extern const uint8_t gperf_downcase[256];
extern const uint8_t kCtype[256];
extern const uint8_t kToLower[256];
extern const uint8_t kToUpper[256];
extern const uint16_t kToLower16[256];
extern const uint8_t kBase36[256];
extern const char16_t kCp437[256]; /** IBM Code Page 437 */

int isascii(int);
int isspace(int);
int isalpha(int);
int isdigit(int);
int isalnum(int);
int isxdigit(int);
int isprint(int);
int islower(int);
int isupper(int);
int isblank(int);
int iscntrl(int);
int isgraph(int);
int tolower(int);
int ispunct(int);
int toupper(int);
int hextoint(int);

void *isnotplaintext(const void *, size_t) nothrow nocallback nosideeffect;

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § characters » thompson-pike encoding                       ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│─╝
  fifth age telecommunications

      0123456789abcdef
    ┌0─ ☺☻♥♦♣♠•◘○◙♂♀♪♫☼┬───Control
    └1─►◄↕‼¶§▬↨↑↓→←∟↔▲▼┘
    ┌2─ !"#$%&'()*+,-./┐
    │3 0123456789:;<=>?│
    │4 @ABCDEFGHIJKLMNO├───ASA x3.4-1967
    │5 PQRSTUVWXYZ[\]^_│
    │6 `abcdefghijklmno│
    └7─pqrstuvwxyz{|}~⌂┘
    ┌8─ÇüéâäàåçêëèïîìÄÅ┐
    │9 ÉæÆôöòûùÿÖÜ¢£¥€ƒ├───Thompson-Pike Continuation
    │a á¡óúñÑªº¿⌐¬½¼¡«»│    (not really characters)
    └b─░▒▓│┤╡╢╖╕╣║╗╝╜╛┐┘
    ┌c─└┴┬├─┼╞╟╚╔╩╦╠═╬╧┬───1 Continuation will follow
    └d─╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀┘
    ─e─αßΓπΣσμτΦΘΩδ∞φε∩────2 Continuations will follow
     f─≡±≥≤⌠⌡÷≈°∙·√ⁿ²■λ
       │      ││  │││└┤
       │      ││  │└┤ └───5 Continuations follow (and is negative)
       │      │└─┬┘ └─────5 Continuations follow (note: -1=λ┐┐┐┐┐)
       └───┬──┘  └────────4 Continuations follow
           └──────────────3 Continuations follow */

#define INVALID_CODEPOINT 0xfffd
#define UTF16_MASK        0b1111110000000000
#define UTF16_MOAR        0b1101100000000000 /* 0xD800..0xDBFF */
#define UTF16_CONT        0b1101110000000000 /* 0xDC00..0xDBFF */

unsigned getutf16(const char16_t *p, wint_t *wc);
int pututf16(char16_t *s, size_t size, wint_t wc, bool awesome);
int iswalnum(wint_t);
int iswalpha(wint_t);
int iswblank(wint_t);
int iswcntrl(wint_t);
int iswdigit(wint_t);
int iswgraph(wint_t);
int iswlower(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);
int iswpunct(wint_t);
int iswprint(wint_t);
unsigned towlower(unsigned);
unsigned towupper(unsigned);

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings                                                   ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

void *memset(void *, int, size_t) memcpyesque;
void *memcpy(void *restrict, const void *restrict, size_t) memcpyesque;
void *mempcpy(void *restrict, const void *restrict, size_t) memcpyesque;
void *memccpy(void *restrict, const void *restrict, int, size_t) memcpyesque;
void *memmove(void *, const void *, size_t) memcpyesque;
void *memeqmask(void *, const void *, const void *, size_t) memcpyesque;

size_t strlen(const char *) strlenesque;
size_t strnlen(const char *, size_t) strlenesque;
size_t strnlen_s(const char *, size_t);
char *strchr(const char *, int) strlenesque;
char *index(const char *, int) strlenesque;
void *memchr(const void *, int, size_t) strlenesque;
char *strchrnul(const char *, int) strlenesque returnsnonnull;
void *rawmemchr(const void *, int) strlenesque returnsnonnull;
void bzero(void *, size_t) paramsnonnull() libcesque;
size_t strlen16(const char16_t *) strlenesque;
size_t strnlen16(const char16_t *, size_t) strlenesque;
size_t strnlen16_s(const char16_t *, size_t);
char16_t *strchr16(const char16_t *, int) strlenesque;
void *memchr16(const void *, int, size_t) strlenesque;
char16_t *strchrnul16(const char16_t *, int) strlenesque returnsnonnull;
void *rawmemchr16(const void *, int) strlenesque returnsnonnull;
size_t wcslen(const wchar_t *) strlenesque;
size_t wcsnlen(const wchar_t *, size_t) strlenesque;
size_t wcsnlen_s(const wchar_t *, size_t);
wchar_t *wcschr(const wchar_t *, wchar_t) strlenesque;
wchar_t *wmemchr(const wchar_t *, wchar_t, size_t) strlenesque;
wchar_t *wcschrnul(const wchar_t *, wchar_t) strlenesque returnsnonnull;
char *strstr(const char *, const char *) strlenesque;
char16_t *strstr16(const char16_t *, const char16_t *) strlenesque;
wchar_t *wcsstr(const wchar_t *, const wchar_t *) strlenesque;
void *rawwmemchr(const void *, wchar_t) strlenesque returnsnonnull;
int memcmp(const void *, const void *, size_t) strlenesque;
int strcmp(const char *, const char *) strlenesque;
int strncmp(const char *, const char *, size_t) strlenesque;
int strcmp16(const char16_t *, const char16_t *) strlenesque;
int strncmp16(const char16_t *, const char16_t *, size_t) strlenesque;
int wcscmp(const wchar_t *, const wchar_t *) strlenesque;
int wcsncmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
int wmemcmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
int strcasecmp(const char *, const char *) strlenesque;
int strcasecmp16(const char16_t *, const char16_t *) strlenesque;
int wcscasecmp(const wchar_t *, const wchar_t *) strlenesque;
int strncasecmp(const char *, const char *, size_t) strlenesque;
int strncasecmp16(const char16_t *, const char16_t *, size_t) strlenesque;
int wcsncasecmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
char *strrchr(const char *, int) strlenesque;
void *memrchr(const void *, int, size_t) strlenesque;
char16_t *strrchr16(const char16_t *, int) strlenesque;
void *memrchr16(const void *, int, size_t) strlenesque;
wchar_t *wcsrchr(const wchar_t *, int) strlenesque;
void *wmemrchr(const void *, wchar_t, size_t) strlenesque;
char *strpbrk(const char *, const char *) strlenesque;
char16_t *strpbrk16(const char16_t *, const char16_t *) strlenesque;
wchar_t *wcspbrk(const wchar_t *, const wchar_t *) strlenesque;
size_t strspn(const char *, const char *) strlenesque;
size_t strspn16(const char16_t *, const char16_t *) strlenesque;
size_t wcsspn(const wchar_t *, const wchar_t *) strlenesque;
size_t strcspn(const char *, const char *) strlenesque;
size_t strcspn16(const char16_t *, const char16_t *) strlenesque;
size_t wcscspn(const wchar_t *, const wchar_t *) strlenesque;
void *memfrob(void *, size_t) memcpyesque;
int strcoll(const char *, const char *) strlenesque;
char *strsep(char **, const char *) paramsnonnull();
int strcmpzbw(const uint16_t *, const char *) strlenesque;
int strcasecmpzbw(const uint16_t *, const char *) strlenesque;
char *stpcpy(char *, const char *) memcpyesque;
char *stpncpy(char *, const char *, size_t) memcpyesque;
char *strcat(char *, const char *) memcpyesque;
size_t strlcpy(char *, const char *, size_t);
size_t strlcat(char *, const char *, size_t);
char *strcpy(char *, const char *) memcpyesque;
char16_t *strcpy16(char16_t *, const char16_t *) memcpyesque;
char *strncat(char *, const char *, size_t) memcpyesque;
char *strncpy(char *, const char *, size_t) memcpyesque;
char *_strncpy(char *, const char *, size_t) asm("strncpy") memcpyesque;
char *strtok(char *, const char *) paramsnonnull((2)) libcesque;
char *strtok_r(char *, const char *, char **) paramsnonnull((2, 3));
uint16_t *strcpyzbw(uint16_t *, const char *) memcpyesque;
char *wstrtrunc(uint16_t *) memcpyesque;
char *wstrntrunc(uint16_t *, size_t) memcpyesque;
bool startswith(const char *, const char *) strlenesque;
bool startswith16(const char16_t *, const char16_t *) strlenesque;
bool wcsstartswith(const wchar_t *, const wchar_t *) strlenesque;
bool endswith(const char *, const char *) strlenesque;
bool endswith16(const char16_t *, const char16_t *) strlenesque;
bool wcsendswith(const wchar_t *, const wchar_t *) strlenesque;
const char *indexdoublenulstring(const char *, unsigned) strlenesque;
int getkvlin(const char *, const char *const[]);
void crc32init(uint32_t[hasatleast 256], uint32_t);
wchar_t *wmemset(wchar_t *, wchar_t, size_t) memcpyesque;
char16_t *memset16(char16_t *, char16_t, size_t) memcpyesque;
compatfn wchar_t *wmemcpy(wchar_t *, const wchar_t *, size_t) memcpyesque;
compatfn wchar_t *wmempcpy(wchar_t *, const wchar_t *, size_t) memcpyesque;
compatfn wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t) memcpyesque;

char *tinystrstr(const char *, const char *) strlenesque;
char16_t *tinystrstr16(const char16_t *, const char16_t *) strlenesque;
void *tinymemmem(const void *, size_t, const void *, size_t) strlenesque;

void *memtolower(void *p, size_t n);
char *strntolower(char *s, size_t n);
char *strtolower(char *s) paramsnonnull();
char *strntoupper(char *s, size_t n);
char *strtoupper(char *s) paramsnonnull();
char *chomp(char *line);
char16_t *chomp16(char16_t *line);
wchar_t *wchomp(wchar_t *line);

/* gcc -Werror=stringop-truncation misunderstands strncpy() api */
#define strncpy(DEST, SRC, N) _strncpy(DEST, SRC, N)

#define explicit_bzero(STR, BYTES)                                          \
  do {                                                                      \
    void *Str;                                                              \
    size_t Bytes;                                                           \
    asm volatile("call\texplicit_bzero"                                     \
                 : "=D"(Str), "=S"(Bytes)                                   \
                 : "0"(STR), "1"(BYTES)                                     \
                 : "rax", "rcx", "rdx", "r8", "r9", "r10", "r11", "memory", \
                   "cc", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5");   \
  } while (0)

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » multibyte                                       ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

typedef unsigned mbstate_t;

size_t tprecode8to16(char16_t *, size_t, const char *);
size_t tprecode16to8(char *, size_t, const char16_t *);
int strcmp8to16(const char *, const char16_t *) strlenesque;
int strncmp8to16(const char *, const char16_t *, size_t) strlenesque;
int strcasecmp8to16(const char *, const char16_t *) strlenesque;
int strncasecmp8to16(const char *, const char16_t *, size_t) strlenesque;
int strcmp16to8(const char16_t *, const char *) strlenesque;
int strncmp16to8(const char16_t *, const char *, size_t) strlenesque;
int strcasecmp16to8(const char16_t *, const char *) strlenesque;
int strncasecmp16to8(const char16_t *, const char *, size_t) strlenesque;
wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);
int mbtowc(wchar_t *, const char *, size_t);
size_t mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
size_t mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
size_t mbstowcs(wchar_t *, const char *, size_t);
size_t wcstombs(char *, const wchar_t *, size_t);
size_t wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
size_t wcrtomb(char *, wchar_t, mbstate_t *);
int wctomb(char *, wchar_t);
int wctob(wint_t);

size_t strclen(const char *) nosideeffect;
size_t strnclen(const char *, size_t) nosideeffect;
size_t strclen16(const char16_t *) nosideeffect;
size_t strnclen16(const char16_t *, size_t) nosideeffect;

typedef unsigned wctype_t;
wctype_t wctype(const char *name) strlenesque;
int iswctype(wint_t c, wctype_t type) pureconst;

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » hashing                                         ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

#define SHA256_BLOCK_SIZE 32

struct Sha256Ctx {
  uint8_t data[64];
  uint32_t datalen;
  uint64_t bitlen;
  uint32_t state[8];
};

uint32_t crc32_z(uint32_t, const void *, size_t);
extern uint32_t (*const crc32c)(uint32_t, const void *, size_t) paramsnonnull();

void sha256_init(struct Sha256Ctx *);
void sha256_update(struct Sha256Ctx *, const uint8_t *, size_t);
void sha256_final(struct Sha256Ctx *, uint8_t *);

bool luhn(const char *);

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » system                                          ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

char *strsignal(int) returnsnonnull libcesque;

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » hooks                                           ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
extern int (*const hook$strcmp16)(const char16_t *, const char16_t *);
extern int (*const hook$strncmp16)(const char16_t *, const char16_t *, size_t);
extern int (*const hook$wcscmp)(const wchar_t *, const wchar_t *);
extern int (*const hook$wcsncmp)(const wchar_t *, const wchar_t *, size_t);
#define __STR_HOOK(SYMBOL) hook$##SYMBOL
#else
#define __STR_HOOK(SYMBOL) SYMBOL
#endif /* GNUC && !ANSI */

/* TODO(jart): Use @gotpcrel. */
#undef __STR_HOOK
#define __STR_HOOK(SYMBOL) SYMBOL

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » generic typing                                  ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

#if __STDC_VERSION__ + 0 >= 201112

#define strstr(haystack, needle) \
  _Generic(*(haystack), wchar_t  \
           : wcsstr, char16_t    \
           : strstr16, default   \
           : strstr)(haystack, needle)

#define strchr(s, c)                                                           \
  _Generic(*(s), wchar_t                                                       \
           : wcschr, char16_t                                                  \
           : strchr16, default                                                 \
           : (isconstant(s) && isconstant(c) ? __builtin_strchr : _strchr))(s, \
                                                                            c)

#define strrchr(s, c)           \
  _Generic(*(s), wchar_t        \
           : wcsrchr, char16_t  \
           : strrchr16, default \
           : strrchr)(s, c)

#define strchrnul(s, c)           \
  _Generic(*(s), wchar_t          \
           : wcschrnul, char16_t  \
           : strchrnul16, default \
           : strchrnul)(s, c)

#define strnlen(s, n)           \
  _Generic(*(s), wchar_t        \
           : wcsnlen, char16_t  \
           : strnlen16, default \
           : strnlen)(s, n)

#define strnlen_s(s, n)           \
  _Generic(*(s), wchar_t          \
           : wcsnlen_s, char16_t  \
           : strnlen16_s, default \
           : strnlen_s)(s, n)

#define strpbrk(s, c)           \
  _Generic(*(s), wchar_t        \
           : wcspbrk, char16_t  \
           : strpbrk16, default \
           : strpbrk)(s, c)

#define strspn(s, c) \
  _Generic(*(s), wchar_t : wcsspn, char16_t : strspn16, default : strspn)(s, c)

#define strcspn(s, c)           \
  _Generic(*(s), wchar_t        \
           : wcscspn, char16_t  \
           : strcspn16, default \
           : strcspn)(s, c)

/* clang-format off */
#define strcmp(s1, s2)                \
  _Generic((s1)[0],                   \
    wchar_t: __STR_HOOK(wcscmp),      \
    char16_t: _Generic(*(s2),         \
      char: strcmp16to8,              \
      default: __STR_HOOK(strcmp16)), \
    default: _Generic(*(s2),          \
      char16_t: strcmp8to16,          \
      default: strcmp))(s1, s2)
/* clang-format on */

#define strncmp(s1, s2, n)                      \
  _Generic(*(s1), wchar_t                       \
           : __STR_HOOK(wcsncmp), char16_t      \
           : _Generic(*(s2), char               \
                      : strncmp16to8, default   \
                      : __STR_HOOK(strncmp16)), \
             default                            \
           : _Generic(*(s2), char16_t           \
                      : strncmp8to16, default   \
                      : strncmp))(s1, s2, n)

#define strcasecmp(s1, s2)         \
  _Generic(*(s1), wchar_t          \
           : wcscasecmp, char16_t  \
           : strcasecmp16, default \
           : strcasecmp)(s1, s2)

#define strncasecmp(s1, s2, n)      \
  _Generic(*(s1), wchar_t           \
           : wcsncasecmp, char16_t  \
           : strncasecmp16, default \
           : strncasecmp)(s1, s2, n)

#define startswith(s, c)             \
  _Generic(*(s), wchar_t             \
           : wcsstartswith, char16_t \
           : startswith16, default   \
           : startswith)(s, c)

#define endswith(s, c)             \
  _Generic(*(s), wchar_t           \
           : wcsendswith, char16_t \
           : endswith16, default   \
           : endswith)(s, c)

#define strclen(s) \
  _Generic(*(s), wchar_t : wcslen, char16_t : strclen16, default : strclen)(s)

#define strnclen(s, n)           \
  _Generic(*(s), wchar_t         \
           : wcslen, char16_t    \
           : strnclen16, default \
           : strnclen)(s, n)

#define chomp(s) \
  _Generic(*(s), wchar_t : wchomp, char16_t : chomp16, default : chomp)(s)

#endif /* C11 */

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » optimizations                                   ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)

#ifdef UNBLOAT_STDARG
#define __STR_XMM_CLOBBER
#else
#define __STR_XMM_CLOBBER "xmm3",
#endif

#define __memcpy_isgoodsize(SIZE)                              \
  (isconstant(SIZE) && ((SIZE) <= __BIGGEST_ALIGNMENT__ * 2 && \
                        __builtin_popcount((unsigned)(SIZE)) == 1))

#define __memset_isgoodsize(SIZE)                                      \
  (isconstant(SIZE) && (((SIZE) <= __BIGGEST_ALIGNMENT__ &&            \
                         __builtin_popcount((unsigned)(SIZE)) == 1) || \
                        ((SIZE) % __BIGGEST_ALIGNMENT__ == 0 &&        \
                         (SIZE) / __BIGGEST_ALIGNMENT__ <= 3)))

#define memcpy(DEST, SRC, SIZE)                                  \
  (__memcpy_isgoodsize(SIZE) ? __builtin_memcpy(DEST, SRC, SIZE) \
                             : __memcpy("_memcpy", DEST, SRC, SIZE))

#define memset(DEST, BYTE, SIZE)                                  \
  (__memset_isgoodsize(SIZE) ? __builtin_memset(DEST, BYTE, SIZE) \
                             : __memset(DEST, BYTE, SIZE))

#if defined(__STDC_HOSTED__) && (defined(__SSE2__) || defined(UNBLOAT_STDARG))

#define memmove(DEST, SRC, SIZE) __memcpy("_memmove", (DEST), (SRC), (SIZE))
#define __memcpy(FN, DEST, SRC, SIZE)                                      \
  ({                                                                       \
    void *DeSt = (DEST);                                                   \
    const void *SrC = (SRC);                                               \
    size_t SiZe = (SIZE);                                                  \
    asm("call\t" FN                                                        \
        : "=m"(*(char(*)[SiZe])(DeSt))                                     \
        : "D"(DeSt), "S"(SrC), "d"(SiZe), "m"(*(const char(*)[SiZe])(SrC)) \
        : __STR_XMM_CLOBBER "cc");                                         \
    DeSt;                                                                  \
  })
#define mempcpy(DEST, SRC, SIZE)                          \
  ({                                                      \
    size_t SIze = (SIZE);                                 \
    (void *)((char *)memcpy((DEST), (SRC), SIze) + SIze); \
  })
#define __memset(DEST, BYTE, SIZE)        \
  ({                                      \
    void *DeSt = (DEST);                  \
    size_t SiZe = (SIZE);                 \
    asm("call\t_memset"                   \
        : "=m"(*(char(*)[SiZe])(DeSt))    \
        : "D"(DeSt), "S"(BYTE), "d"(SiZe) \
        : __STR_XMM_CLOBBER "cc");        \
    DeSt;                                 \
  })

#else /* hosted/sse2/unbloat */

#define memmove(DEST, SRC, SIZE) __memcpy((DEST), (SRC), (SIZE))
#define mempcpy(DEST, SRC, SIZE)                                           \
  ({                                                                       \
    void *Rdi, *Dest = (DEST);                                             \
    const void *Rsi, *Src = (SRC);                                         \
    size_t SiZe = (SIZE);                                                  \
    size_t Rcx;                                                            \
    asm("rep movsb"                                                        \
        : "=D"(Rdi), "=S"(Rsi), "=D"(Rcx), "=m"(*(char(*)[SiZe])(Dest))    \
        : "0"(Dest), "1"(Src), "2"(SiZe), "m"(*(const char(*)[SiZe])(Src)) \
        : "cc");                                                           \
    Rdi;                                                                   \
  })
#define __memcpy(FN, DEST, SRC, SIZE)                                      \
  ({                                                                       \
    void *Rdi, *Dest = (DEST);                                             \
    const void *Rsi, *Src = (SRC);                                         \
    size_t SiZe = (SIZE);                                                  \
    size_t Rcx;                                                            \
    asm("rep movsb"                                                        \
        : "=D"(Rdi), "=S"(Rsi), "=c"(Rcx), "=m"(*(char(*)[SiZe])(Dest))    \
        : "0"(Dest), "1"(Src), "2"(SiZe), "m"(*(const char(*)[SiZe])(Src)) \
        : "cc");                                                           \
    Dest;                                                                  \
  })
#define __memset(DEST, BYTE, SIZE)                           \
  ({                                                         \
    void *Rdi, *Dest = (DEST);                               \
    size_t SiZe = (SIZE);                                    \
    size_t Rcx;                                              \
    asm("rep stosb"                                          \
        : "=D"(Rdi), "=c"(Rcx), "=m"(*(char(*)[SiZe])(Dest)) \
        : "0"(Dest), "1"(SiZe), "S"(BYTE)                    \
        : "cc");                                             \
    Dest;                                                    \
  })

#endif /* hosted/sse2/unbloat */

#if __STDC_VERSION__ + 0 >= 201112
#define strlen(s)                                         \
  chooseexpr((typescompatible(typeof(s), const char[]) && \
              isconstant(((const char *)(s))[0])),        \
             sizeof(s) - 1,                               \
             _Generic(*(s), wchar_t                       \
                      : wcslen, char16_t                  \
                      : strlen16, default                 \
                      : _strlen)(s))
#else
#define strlen(s)                                                       \
  chooseexpr(isconstant(s) && typescompatible(typeof(s), const char[]), \
             __builtin_strlen(s), _strlen(s))
#endif /* C11+ */

#define pututf16(BUF, SIZE, CH, AWESOME) __pututf16(BUF, SIZE, CH, AWESOME)
#define getutf16(BUF, CHPTR)             __getutf16(BUF, CHPTR)
size_t _strlen(const char *s) asm("strlen") strlenesque;
char *_strchr(const char *, int) asm("strchr") strlenesque;
void *_memchr(const void *, int, size_t) asm("memchr") strlenesque;
forceinline int __pututf16(char16_t *s, size_t size, wint_t wc,
                           bool32 awesome) {
  if (size >= 1 && (0x00 <= wc && wc <= 0xD7FF)) {
    if (wc >= 32 || !awesome) {
      s[0] = (char16_t)wc;
      return 1;
    } else if (size >= 2) {
      s[0] = 0xd800;
      s[1] = 0xdc00 | (char16_t)wc;
      return 2;
    }
  }
  int ax;
  asm("call\tpututf16"
      : "=a"(ax), "=m"(*(char16_t(*)[size])s)
      : "D"(s), "S"(size), "d"(wc)
      : "cc");
  return ax;
}
forceinline unsigned __getutf16(const char16_t *s, wint_t *wc) {
  if ((0x00 <= s[0] && s[0] <= 0xD7FF)) {
    *wc = s[0];
    return 1;
  }
  unsigned ax;
  asm("call\tgetutf16" : "=a"(ax), "=m"(*wc) : "D"(s), "S"(wc), "m"(*s) : "cc");
  return ax;
}

/*
 * GCC has builtins for these, that only do things for literals. They
 * also cause the compiler to whine in a kafkaesque way when flags like
 * -Werror=shadow and -Werror=implicit-function-declaration are passed.
 */
#define isascii(c)  isascii_(c)
#define isspace(c)  isspace_(c)
#define isalpha(c)  isalpha_(c)
#define isdigit(c)  isdigit_(c)
#define isalnum(c)  isalnum_(c)
#define isxdigit(c) isxdigit_(c)
#define isprint(c)  isprint_(c)
#define islower(c)  islower_(c)
#define isupper(c)  isupper_(c)
#define isblank(c)  isblank_(c)
#define iscntrl(c)  iscntrl_(c)
#define isgraph(c)  isgraph_(c)
#define tolower(c)  tolower_(c)
#define ispunct(c)  ispunct_(c)
#define toupper(c)  toupper_(c)
#define hextoint(c) hextoint_(c)
#define DECLARE_CTYPE(NAME, EXPR)                     \
  pureconst forceinline nodebuginfo int NAME(int i) { \
    unsigned char c = (unsigned char)i;               \
    return (EXPR);                                    \
  }
DECLARE_CTYPE(isascii_, 0 <= c && c <= 0x7f)
DECLARE_CTYPE(isspace_, kCtype[c] & 0x01)
DECLARE_CTYPE(isalpha_, kCtype[c] & 0x02)
DECLARE_CTYPE(isdigit_, '0' <= c && c <= '9')
DECLARE_CTYPE(isalnum_, kCtype[c] & 0x06)
DECLARE_CTYPE(isxdigit_, kCtype[c] & 0x08)
DECLARE_CTYPE(isprint_, kCtype[c] & 0x10)
DECLARE_CTYPE(islower_, 'a' <= c && c <= 'z')
DECLARE_CTYPE(isupper_, 'A' <= c && c <= 'Z')
DECLARE_CTYPE(isblank_, kCtype[c] & 0x80)
DECLARE_CTYPE(iscntrl_, !isprint_(c))
DECLARE_CTYPE(isgraph_, isprint_(c) && (c) != ' ')
DECLARE_CTYPE(tolower_, kToLower[c])
DECLARE_CTYPE(ispunct_, isprint(c) && !(kCtype[c] & 0x07))
DECLARE_CTYPE(toupper_, kToUpper[c])
DECLARE_CTYPE(hextoint_, (c + 9 * (1 & (SAR(c, 6)))) & 0xf)
#undef DECLARE_CTYPE
#define iswalnum(c)  iswalnum_(c)
#define iswalpha(c)  iswalpha_(c)
#define iswblank(c)  iswblank_(c)
#define iswcntrl(c)  iswcntrl_(c)
#define iswdigit(c)  iswdigit_(c)
#define iswgraph(c)  iswgraph_(c)
#define iswlower(c)  iswlower_(c)
#define iswspace(c)  iswspace_(c)
#define iswupper(c)  iswupper_(c)
#define iswxdigit(c) iswxdigit_(c)
#define iswpunct(c)  iswpunct_(c)
#define iswprint(c)  iswprint_(c)
#define towlower(c)  towlower_(c)
#define towupper(c)  towupper_(c)
#define DECLARE_WCTYPE(R, NAME, T, EXPR) \
  forceinline nodebuginfo R NAME(T c) {  \
    return EXPR;                         \
  }
DECLARE_WCTYPE(int, iswalnum_, wint_t, isascii(c) ? isalnum(c) : c)
DECLARE_WCTYPE(int, iswalpha_, wint_t, isascii(c) ? isalpha(c) : c)
DECLARE_WCTYPE(int, iswblank_, wint_t, isascii(c) ? isblank(c) : c)
DECLARE_WCTYPE(int, iswcntrl_, wint_t, isascii(c) ? iscntrl(c) : c)
DECLARE_WCTYPE(int, iswdigit_, wint_t, isascii(c) ? isdigit(c) : c)
DECLARE_WCTYPE(int, iswgraph_, wint_t, isascii(c) ? isgraph(c) : c)
DECLARE_WCTYPE(int, iswlower_, wint_t, isascii(c) ? islower(c) : c)
DECLARE_WCTYPE(int, iswspace_, wint_t, isascii(c) ? isspace(c) : c)
DECLARE_WCTYPE(int, iswupper_, wint_t, isascii(c) ? isupper(c) : c)
DECLARE_WCTYPE(int, iswxdigit_, wint_t, isascii(c) ? isxdigit(c) : c)
DECLARE_WCTYPE(int, iswpunct_, wint_t, !isascii(c) || ispunct(c))
DECLARE_WCTYPE(int, iswprint_, wint_t, !isascii(c) || isprint(c))
DECLARE_WCTYPE(unsigned, towlower_, unsigned, isascii(c) ? tolower(c) : c)
DECLARE_WCTYPE(unsigned, towupper_, unsigned, isascii(c) ? toupper(c) : c)
#undef DECLARE_WCTYPE

#endif /* __GNUC__ && !__STRICT_ANSI__ */
COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_STR_STR_H_ */
