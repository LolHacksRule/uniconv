#include "uniconv.h"
#include "converter.h"
#include "multibytecodec.h"
#include "singlebytecodec.h"

#include <stdlib.h>
#include <string.h>

struct tabconverter {
    struct converter base;

    MultibyteCodecState mstate;
    SingleByteCodecState sstate;
    int singlebyte;
};

static void
tabconverter_close(struct converter *uc)
{
    free(uc);
}


static int
tabconverter_encode(struct converter *suc,
		    const uc_char_t **inbuf,
		    size_t inleft,
		    char **outbuf,
		    size_t outbytesleft)
{
    struct tabconverter *uc = (struct tabconverter*)suc;
    int ret;

    if (uc->singlebyte) {
	/* flush */
	if (!inbuf)
	    return UNICONV_SUCCESS;

	ret = sbcs_encode(&uc->sstate, inbuf, inleft, outbuf, outbytesleft);
    } else {
	/* flush */
	if (!inbuf)
	    ret = mbcs_encode_reset(&uc->mstate, outbuf, outbytesleft);
	else
	    ret = mbcs_encode(&uc->mstate, inbuf, inleft, outbuf, outbytesleft, 0);
	if (ret == MBERR_TOOFEW)
	    ret = UNICONV_EINVAL;
	else if (ret == MBERR_TOOSMALL)
	    ret = UNICONV_E2BIG;
	else if (ret < 0 || ret > 0)
	    ret = UNICONV_EILSEQ;
    }

    return ret;
}

static int
tabconverter_decode(struct converter *suc,
		    const char **inbuf,
		    size_t inbytesleft,
		    uc_char_t **outbuf,
		    size_t outleft)
{
    struct tabconverter *uc = (struct tabconverter*)suc;
    int ret;

    if (uc->singlebyte) {
	ret = sbcs_decode(&uc->sstate, inbuf, inbytesleft, outbuf, outleft);
    } else {
	ret = mbcs_decode(&uc->mstate, inbuf, inbytesleft, outbuf, outleft);
	if (ret == MBERR_TOOFEW)
	    ret = UNICONV_EINVAL;
	else if (ret == MBERR_TOOSMALL)
	    ret = UNICONV_E2BIG;
	else if (ret < 0 || ret > 0)
	    ret = UNICONV_EILSEQ;
    }

    return ret;
}

static void
tabconverter_reset(struct converter *suc)
{
    struct tabconverter *uc = (struct tabconverter *)suc;

    if (!uc->singlebyte) {
	mbcs_encode_init(&uc->mstate);
	mbcs_decode_init(&uc->mstate);
    }
}

struct converter*
tabconverter_open(const char *charset)
{
    struct tabconverter sconv, *conv;

    if (!sbcs_init(&sconv.sstate, charset)) {
	sconv.singlebyte = 1;
    } else {
	static const char* modules[] = {
	    "cn", "hk", "hz", "jp", "kr", "tw", NULL
	};
	size_t i;

	for (i = 0; modules[i]; i++)
	    if (!mbcs_init(&sconv.mstate, modules[i], charset))
		break;
	if (!modules[i])
	    return NULL;
	sconv.singlebyte = 0;
    }

    conv = malloc(sizeof(struct tabconverter));
    if (!conv)
	return NULL;
    *conv = sconv;
    conv->base.encode = tabconverter_encode;
    conv->base.decode = tabconverter_decode;
    conv->base.close = tabconverter_close;
    conv->base.reset = tabconverter_reset;
    return &conv->base;
}
