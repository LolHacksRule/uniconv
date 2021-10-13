#include "iconv.h"
#include "uniconv.h"
#include "uniconvint.h"

#include <errno.h>

iconv_t
uc_iconv_open(const char *to, const char *from)
{
    uniconv_t *uc = uniconv_open(to, from);
    if (!uc)
	return (iconv_t)-1;
    return uc;
}

size_t
uc_iconv (iconv_t cd, char **inbuf,
	  size_t *inbytesleft,
	  char **outbuf,
	  size_t *outbytesleft)
{
    int ret;

    if (cd == (iconv_t)-1 || !cd) {
	errno = EBADF;
	return (size_t)-1;
    }

    ret = uniconv_conv(cd, (const char **)inbuf, inbytesleft,
		       outbuf, outbytesleft);
    if (ret == UNICONV_EBADF) {
	errno = EBADF;
	return (size_t)-1;
    } else if (ret == UNICONV_EINVAL) {
	errno = EINVAL;
	return (size_t)-1;
    } else if (ret == UNICONV_E2BIG) {
	errno = E2BIG;
	return (size_t)-1;
    } else if (ret == UNICONV_EILSEQ) {
	errno = EILSEQ;
	return (size_t)-1;
    }

    return ret;
}

int
uc_iconv_close (iconv_t cd)
{
    if (cd == (iconv_t)-1 || !cd) {
	errno = EBADF;
	return -1;
    }

    uniconv_close(cd);
    return 0;
}

#if defined(__GNUC__) && !defined(UNICONV_REPLACE_ICONV)
#define weak_alias(name, aliasname) _weak_alias(name, aliasname)
#define _weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));
#undef iconv_open
#undef iconv
#undef iconv_close
weak_alias (uc_iconv_open, iconv_open)
weak_alias (uc_iconv, iconv)
weak_alias (uc_iconv_close, iconv_close)
#endif

#ifdef UNICONV_REPLACE_ICONV
#undef iconv_open
#undef iconv
#undef iconv_close

iconv_t iconv_open(const char *to, const char *from)
{
    return uc_iconv_open(to, from);
}

size_t iconv (iconv_t cd, char **inbuf,
	      size_t *inbytesleft,
	      char **outbuf,
	      size_t *outbytesleft)
{
    return uc_iconv (cd, inbuf, inbytesleft, outbuf, outbytesleft);
}

int
iconv_close (iconv_t cd)
{
    return uc_iconv_close (cd);
}

#endif
