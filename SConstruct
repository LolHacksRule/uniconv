# -*- coding: utf-8 -*-
# -*- python -*-
# Author: Luo Jinghua
import os

env = Environment(tools = ['default', 'convlib'],
                  ENV = os.environ)
bareenv = env.Clone()
srcs = ['codecs_cn.c', 'codecs_hk.c',  'codecs_iso2022.c',
        'codecs_jp.c', 'codecs_kr.c',  'codecs_tw.c',
        'multibytecodec.c']
srcs += Glob('*-table.c')
srcs += ['singlebytetables.c', 'singlebytecodec.c', 'uniconv.c',
         'charsetalias.c', 'unicode.c', 'converter.c',
         'tableconverter.c', 'utfconverter.c']
env.AppendUnique(CCFLAGS = ['-Wall', '-g'],
                 LINKFLAGS = ['-g'],
		 CPPPATH = ['.'])

uniconv = env.ConvenienceLibrary ('uniconv', srcs)

iconv_env = env.Clone()
iconv_src = ['iconv.c']
if iconv_env['PLATFORM'] == 'win32':
    iconv_def = os.path.join('win32', 'iconv.def')
    if 'gcc' in iconv_env['CC']:
        iconv_src.append(iconv_def)
    else:
        iconv_env.AppendUnique(LINKFLAGS = ['/DEF:' + iconv_def])
    iconv_env.AppendUnique(CPPDEFINES = ['UNICONV_REPLACE_ICONV'])

iconv = iconv_env.SharedLibrary('iconv', iconv_src,
                                LIBS = ['uniconv'],
                                LIBPATH = ['.'],
                                CPPPATH = ['.'])

test = env.Program ('test', 'main.c',
                    LIBS = ['uniconv'],
                    LIBPATH = ['.'],
                    CPPPATH = ['.'])
conv = env.Program ('uconv', 'uconv.c',
                    LIBS = ['uniconv'],
                    LIBPATH = ['.'],
                    CPPPATH = ['.'])

conv2_env = bareenv.Clone()
if env['PLATFORM'] == 'win32':
    conv2_env.AppendUnique(CPPPATH = ['win32'],
                           LIBS = ['iconv'],
                           LIBPATH = ['.'])
conv2 = conv2_env.Program ('uconv2', 'uconv2.c')
