#ifndef UNICONV_ICONV_H
#define UNICONV_ICONV_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* iconv_t;

extern iconv_t uc_iconv_open(const char *to, const char *from);
#define iconv_open(to, from) uc_iconv_open((to), (from))

extern size_t uc_iconv (iconv_t cd, char **inbuf,
			size_t *inbytesleft,
			char **outbuf,
			size_t *outbytesleft);
#define iconv(cd, ib, ibl, ob, obl) uc_iconv((cd), (ib), (ibl), (ob), (obl))

extern int uc_iconv_close (iconv_t cd);
#define iconv_close(cd) uc_iconv_close((cd))

#ifdef __cplusplus
}
#endif

#endif
