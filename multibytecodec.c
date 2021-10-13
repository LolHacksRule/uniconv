/*
 * multibytecodec.c: Common Multibyte Codec Implementation
 *
 * Written by Hye-Shik Chang <perky@FreeBSD.org>
 */

#include "multibytecodec.h"
#include "cjkcodecs.h"
#include "codecs_cn.h"
#include "codecs_hk.h"
#include "codecs_jp.h"
#include "codecs_kr.h"
#include "codecs_tw.h"
#include "codecs_iso2022.h"

#include <stddef.h>
#include <string.h>

#define MBCM_MAX 7
struct MultibyteCodecModule {
    const char *name;
    const struct dbcs_map *mappings;
    const MultibyteCodec *codecs;
};

static struct MultibyteCodecModule *
mbcms_init(struct MultibyteCodecModule mbcs[])
{
    size_t i = 0;

#define MBCM_SET(mod)				\
    do {					\
	mbcs[i].name = #mod;			\
	mbcs[i].mappings = mod##_mapping_list;	\
	mbcs[i].codecs = mod##_codec_list;	\
	i++;					\
    } while(0);
#define MBCM_END()				\
    do {					\
	mbcs[i].name = NULL;			\
	mbcs[i].mappings = NULL;		\
	mbcs[i].codecs = NULL;			\
	i++;					\
    } while(0);

    MBCM_SET(cn);
    MBCM_SET(hk);
    MBCM_SET(kr);
    MBCM_SET(jp);
    MBCM_SET(tw);
    MBCM_SET(iso2022);
    MBCM_END()

    return mbcs;
}

struct MultibyteCodecModule*
mbc_find(struct MultibyteCodecModule *mbcms,
	 const char *modname)
{
    int i;

    for (i = 0; mbcms[i].name; i++)
	if (!strcmp (mbcms[i].name, modname))
	    return &mbcms[i];

    return NULL;
}

static const MultibyteCodec*
mbc_module_find_codec(struct MultibyteCodecModule* module,
		      const char *encoding)
{
    int i;

    for (i = 0; module->codecs[i].encoding && module->codecs[i].encoding[0]; i++)
	if (!strcmp (module->codecs[i].encoding, encoding))
	    return &module->codecs[i];

    return NULL;
}

int
mbc_importmap(const char *modname, const char *symbol,
	      const void **encmap, const void **decmap)
{
    struct MultibyteCodecModule mbcms[MBCM_MAX];
    struct MultibyteCodecModule* module;
    const struct dbcs_map *map;

    module = mbc_find(mbcms_init(mbcms), modname);
    if (!module)
	return -1;

    map = module->mappings;
    for (; map->charset; map++)
	if (!strcmp (map->charset, symbol))
	    break;
    if (!map->charset)
	return -1;

    if (encmap != NULL)
	*encmap = map->encmap;
    if (decmap != NULL)
	*decmap = map->decmap;
    return 0;
}

int
mbcs_init(MultibyteCodecState *state,
	  const char *modname,
	  const char* encoding)
{
    struct MultibyteCodecModule mbcms[MBCM_MAX];
    struct MultibyteCodecModule* module;

    memset(state, 0, sizeof(MultibyteCodecState));

    module = mbc_find(mbcms_init(mbcms), modname);
    if (!module)
	return -1;

    state->codec = mbc_module_find_codec(module, encoding);
    if (!state->codec)
	return -1;

    if (state->codec->codecinit && state->codec->codecinit(state->codec->config))
	return -1;

    mbcs_decode_init(state);
    return 0;
}

int
mbcs_decode(MultibyteCodecState *state,
	    const char** inbuf, size_t inlen,
	    ucs4_t** outbuf, size_t outlen)
{
    return state->codec->decode(&state->state, state->codec->config,
				(const unsigned char**)inbuf, inlen,
				outbuf, outlen);
}

void
mbcs_decode_init(MultibyteCodecState *state)
{
    if (state->codec->decinit)
	state->codec->decinit(&state->state, state->codec->config);
}

int
mbcs_decode_reset(MultibyteCodecState *state)
{
    if (state->codec->decreset)
	return state->codec->decreset(&state->state,
				      state->codec->config);
    return 0;
}

int
mbcs_encode(MultibyteCodecState *state,
	    const ucs4_t** inbuf, size_t inlen,
	    char** outbuf, size_t outlen,
	    int flags)
{
    return state->codec->encode(&state->state,
				state->codec->config,
				inbuf, inlen,
				(unsigned char **)outbuf, outlen,
				flags);
}

void
mbcs_encode_init(MultibyteCodecState *state)
{
  if (state->codec->encinit)
      state->codec->encinit(&state->state, state->codec->config);
}

int
mbcs_encode_reset(MultibyteCodecState *state,
		  char **outbuf, int outleft)
{
    if (state->codec->encreset)
	return state->codec->encreset(&state->state, state->codec->config,
				      (unsigned char **)outbuf, outleft);
    return 0;
}
