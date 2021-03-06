#ifndef COSMOPOLITAN_TOOL_VIZ_LIB_FORMATSTRINGTABLE_H_
#define COSMOPOLITAN_TOOL_VIZ_LIB_FORMATSTRINGTABLE_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

typedef void *StringTableFormatter(long yn, long xn, const char *const[yn][xn],
                                   int emit(), void *, const char *,
                                   const char *, const char *);

StringTableFormatter FormatStringTable;
StringTableFormatter FormatStringTableBasic;
StringTableFormatter FormatStringTableAsCode;
StringTableFormatter FormatStringTableAsAssembly;
StringTableFormatter FormatStringTableForAssertion;

void *FreeStringTableCells(long yn, long xn, char *[yn][xn]);

void FormatMatrixDouble(long yn, long xn, const double[yn][xn], int emit(),
                        void *, StringTableFormatter, const char *,
                        const char *, const char *, double,
                        double rounder(double));
void FormatMatrixFloat(long yn, long xn, const float[yn][xn], int emit(),
                       void *, StringTableFormatter, const char *, const char *,
                       const char *, double, double rounder(double));
void FormatMatrixByte(long yn, long xn, const unsigned char[yn][xn], int emit(),
                      void *, StringTableFormatter, const char *, const char *,
                      const char *);
void FormatMatrixShort(long yn, long xn, const short[yn][xn], int emit(),
                       void *, StringTableFormatter, const char *, const char *,
                       const char *);

char *StringifyMatrixDouble(long yn, long xn, const double[yn][xn],
                            StringTableFormatter, const char *, const char *,
                            const char *, double,
                            double rounder(double)) mallocesque;
char *StringifyMatrixFloat(long yn, long xn, const float[yn][xn],
                           StringTableFormatter, const char *, const char *,
                           const char *, double,
                           double rounder(double)) mallocesque;
char *StringifyMatrixByte(long yn, long xn, const unsigned char[yn][xn],
                          StringTableFormatter, const char *, const char *,
                          const char *) mallocesque;
char *StringifyMatrixShort(long yn, long xn, const short[yn][xn],
                           StringTableFormatter, const char *, const char *,
                           const char *) mallocesque;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_TOOL_VIZ_LIB_FORMATSTRINGTABLE_H_ */
