#include <singlebytecodec.h>

static const int cp1255_decoding_table[256] = {
	0x0,
	0x1,
	0x2,
	0x3,
	0x4,
	0x5,
	0x6,
	0x7,
	0x8,
	0x9,
	0xa,
	0xb,
	0xc,
	0xd,
	0xe,
	0xf,
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1a,
	0x1b,
	0x1c,
	0x1d,
	0x1e,
	0x1f,
	0x20,
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2a,
	0x2b,
	0x2c,
	0x2d,
	0x2e,
	0x2f,
	0x30,
	0x31,
	0x32,
	0x33,
	0x34,
	0x35,
	0x36,
	0x37,
	0x38,
	0x39,
	0x3a,
	0x3b,
	0x3c,
	0x3d,
	0x3e,
	0x3f,
	0x40,
	0x41,
	0x42,
	0x43,
	0x44,
	0x45,
	0x46,
	0x47,
	0x48,
	0x49,
	0x4a,
	0x4b,
	0x4c,
	0x4d,
	0x4e,
	0x4f,
	0x50,
	0x51,
	0x52,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x5a,
	0x5b,
	0x5c,
	0x5d,
	0x5e,
	0x5f,
	0x60,
	0x61,
	0x62,
	0x63,
	0x64,
	0x65,
	0x66,
	0x67,
	0x68,
	0x69,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x6e,
	0x6f,
	0x70,
	0x71,
	0x72,
	0x73,
	0x74,
	0x75,
	0x76,
	0x77,
	0x78,
	0x79,
	0x7a,
	0x7b,
	0x7c,
	0x7d,
	0x7e,
	0x7f,
	0x20ac,
	0xfffe,
	0x201a,
	0x192,
	0x201e,
	0x2026,
	0x2020,
	0x2021,
	0x2c6,
	0x2030,
	0xfffe,
	0x2039,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0x2018,
	0x2019,
	0x201c,
	0x201d,
	0x2022,
	0x2013,
	0x2014,
	0x2dc,
	0x2122,
	0xfffe,
	0x203a,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0xa0,
	0xa1,
	0xa2,
	0xa3,
	0x20aa,
	0xa5,
	0xa6,
	0xa7,
	0xa8,
	0xa9,
	0xd7,
	0xab,
	0xac,
	0xad,
	0xae,
	0xaf,
	0xb0,
	0xb1,
	0xb2,
	0xb3,
	0xb4,
	0xb5,
	0xb6,
	0xb7,
	0xb8,
	0xb9,
	0xf7,
	0xbb,
	0xbc,
	0xbd,
	0xbe,
	0xbf,
	0x5b0,
	0x5b1,
	0x5b2,
	0x5b3,
	0x5b4,
	0x5b5,
	0x5b6,
	0x5b7,
	0x5b8,
	0x5b9,
	0xfffe,
	0x5bb,
	0x5bc,
	0x5bd,
	0x5be,
	0x5bf,
	0x5c0,
	0x5c1,
	0x5c2,
	0x5c3,
	0x5f0,
	0x5f1,
	0x5f2,
	0x5f3,
	0x5f4,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0xfffe,
	0x5d0,
	0x5d1,
	0x5d2,
	0x5d3,
	0x5d4,
	0x5d5,
	0x5d6,
	0x5d7,
	0x5d8,
	0x5d9,
	0x5da,
	0x5db,
	0x5dc,
	0x5dd,
	0x5de,
	0x5df,
	0x5e0,
	0x5e1,
	0x5e2,
	0x5e3,
	0x5e4,
	0x5e5,
	0x5e6,
	0x5e7,
	0x5e8,
	0x5e9,
	0x5ea,
	0xfffe,
	0xfffe,
	0x200e,
	0x200f,
	0xfffe
};

static const struct encoding_map cp1255_encoding_map[] = {
	{ 0x0, 0x0 },
	{ 0x1, 0x1 },
	{ 0x2, 0x2 },
	{ 0x3, 0x3 },
	{ 0x4, 0x4 },
	{ 0x5, 0x5 },
	{ 0x6, 0x6 },
	{ 0x7, 0x7 },
	{ 0x8, 0x8 },
	{ 0x9, 0x9 },
	{ 0xa, 0xa },
	{ 0xb, 0xb },
	{ 0xc, 0xc },
	{ 0xd, 0xd },
	{ 0xe, 0xe },
	{ 0xf, 0xf },
	{ 0x10, 0x10 },
	{ 0x11, 0x11 },
	{ 0x12, 0x12 },
	{ 0x13, 0x13 },
	{ 0x14, 0x14 },
	{ 0x15, 0x15 },
	{ 0x16, 0x16 },
	{ 0x17, 0x17 },
	{ 0x18, 0x18 },
	{ 0x19, 0x19 },
	{ 0x1a, 0x1a },
	{ 0x1b, 0x1b },
	{ 0x1c, 0x1c },
	{ 0x1d, 0x1d },
	{ 0x1e, 0x1e },
	{ 0x1f, 0x1f },
	{ 0x20, 0x20 },
	{ 0x21, 0x21 },
	{ 0x22, 0x22 },
	{ 0x23, 0x23 },
	{ 0x24, 0x24 },
	{ 0x25, 0x25 },
	{ 0x26, 0x26 },
	{ 0x27, 0x27 },
	{ 0x28, 0x28 },
	{ 0x29, 0x29 },
	{ 0x2a, 0x2a },
	{ 0x2b, 0x2b },
	{ 0x2c, 0x2c },
	{ 0x2d, 0x2d },
	{ 0x2e, 0x2e },
	{ 0x2f, 0x2f },
	{ 0x30, 0x30 },
	{ 0x31, 0x31 },
	{ 0x32, 0x32 },
	{ 0x33, 0x33 },
	{ 0x34, 0x34 },
	{ 0x35, 0x35 },
	{ 0x36, 0x36 },
	{ 0x37, 0x37 },
	{ 0x38, 0x38 },
	{ 0x39, 0x39 },
	{ 0x3a, 0x3a },
	{ 0x3b, 0x3b },
	{ 0x3c, 0x3c },
	{ 0x3d, 0x3d },
	{ 0x3e, 0x3e },
	{ 0x3f, 0x3f },
	{ 0x40, 0x40 },
	{ 0x41, 0x41 },
	{ 0x42, 0x42 },
	{ 0x43, 0x43 },
	{ 0x44, 0x44 },
	{ 0x45, 0x45 },
	{ 0x46, 0x46 },
	{ 0x47, 0x47 },
	{ 0x48, 0x48 },
	{ 0x49, 0x49 },
	{ 0x4a, 0x4a },
	{ 0x4b, 0x4b },
	{ 0x4c, 0x4c },
	{ 0x4d, 0x4d },
	{ 0x4e, 0x4e },
	{ 0x4f, 0x4f },
	{ 0x50, 0x50 },
	{ 0x51, 0x51 },
	{ 0x52, 0x52 },
	{ 0x53, 0x53 },
	{ 0x54, 0x54 },
	{ 0x55, 0x55 },
	{ 0x56, 0x56 },
	{ 0x57, 0x57 },
	{ 0x58, 0x58 },
	{ 0x59, 0x59 },
	{ 0x5a, 0x5a },
	{ 0x5b, 0x5b },
	{ 0x5c, 0x5c },
	{ 0x5d, 0x5d },
	{ 0x5e, 0x5e },
	{ 0x5f, 0x5f },
	{ 0x60, 0x60 },
	{ 0x61, 0x61 },
	{ 0x62, 0x62 },
	{ 0x63, 0x63 },
	{ 0x64, 0x64 },
	{ 0x65, 0x65 },
	{ 0x66, 0x66 },
	{ 0x67, 0x67 },
	{ 0x68, 0x68 },
	{ 0x69, 0x69 },
	{ 0x6a, 0x6a },
	{ 0x6b, 0x6b },
	{ 0x6c, 0x6c },
	{ 0x6d, 0x6d },
	{ 0x6e, 0x6e },
	{ 0x6f, 0x6f },
	{ 0x70, 0x70 },
	{ 0x71, 0x71 },
	{ 0x72, 0x72 },
	{ 0x73, 0x73 },
	{ 0x74, 0x74 },
	{ 0x75, 0x75 },
	{ 0x76, 0x76 },
	{ 0x77, 0x77 },
	{ 0x78, 0x78 },
	{ 0x79, 0x79 },
	{ 0x7a, 0x7a },
	{ 0x7b, 0x7b },
	{ 0x7c, 0x7c },
	{ 0x7d, 0x7d },
	{ 0x7e, 0x7e },
	{ 0x7f, 0x7f },
	{ 0xa0, 0xa0 },
	{ 0xa1, 0xa1 },
	{ 0xa2, 0xa2 },
	{ 0xa3, 0xa3 },
	{ 0xa5, 0xa5 },
	{ 0xa6, 0xa6 },
	{ 0xa7, 0xa7 },
	{ 0xa8, 0xa8 },
	{ 0xa9, 0xa9 },
	{ 0xab, 0xab },
	{ 0xac, 0xac },
	{ 0xad, 0xad },
	{ 0xae, 0xae },
	{ 0xaf, 0xaf },
	{ 0xb0, 0xb0 },
	{ 0xb1, 0xb1 },
	{ 0xb2, 0xb2 },
	{ 0xb3, 0xb3 },
	{ 0xb4, 0xb4 },
	{ 0xb5, 0xb5 },
	{ 0xb6, 0xb6 },
	{ 0xb7, 0xb7 },
	{ 0xb8, 0xb8 },
	{ 0xb9, 0xb9 },
	{ 0xbb, 0xbb },
	{ 0xbc, 0xbc },
	{ 0xbd, 0xbd },
	{ 0xbe, 0xbe },
	{ 0xbf, 0xbf },
	{ 0xd7, 0xaa },
	{ 0xf7, 0xba },
	{ 0x192, 0x83 },
	{ 0x2c6, 0x88 },
	{ 0x2dc, 0x98 },
	{ 0x5b0, 0xc0 },
	{ 0x5b1, 0xc1 },
	{ 0x5b2, 0xc2 },
	{ 0x5b3, 0xc3 },
	{ 0x5b4, 0xc4 },
	{ 0x5b5, 0xc5 },
	{ 0x5b6, 0xc6 },
	{ 0x5b7, 0xc7 },
	{ 0x5b8, 0xc8 },
	{ 0x5b9, 0xc9 },
	{ 0x5bb, 0xcb },
	{ 0x5bc, 0xcc },
	{ 0x5bd, 0xcd },
	{ 0x5be, 0xce },
	{ 0x5bf, 0xcf },
	{ 0x5c0, 0xd0 },
	{ 0x5c1, 0xd1 },
	{ 0x5c2, 0xd2 },
	{ 0x5c3, 0xd3 },
	{ 0x5d0, 0xe0 },
	{ 0x5d1, 0xe1 },
	{ 0x5d2, 0xe2 },
	{ 0x5d3, 0xe3 },
	{ 0x5d4, 0xe4 },
	{ 0x5d5, 0xe5 },
	{ 0x5d6, 0xe6 },
	{ 0x5d7, 0xe7 },
	{ 0x5d8, 0xe8 },
	{ 0x5d9, 0xe9 },
	{ 0x5da, 0xea },
	{ 0x5db, 0xeb },
	{ 0x5dc, 0xec },
	{ 0x5dd, 0xed },
	{ 0x5de, 0xee },
	{ 0x5df, 0xef },
	{ 0x5e0, 0xf0 },
	{ 0x5e1, 0xf1 },
	{ 0x5e2, 0xf2 },
	{ 0x5e3, 0xf3 },
	{ 0x5e4, 0xf4 },
	{ 0x5e5, 0xf5 },
	{ 0x5e6, 0xf6 },
	{ 0x5e7, 0xf7 },
	{ 0x5e8, 0xf8 },
	{ 0x5e9, 0xf9 },
	{ 0x5ea, 0xfa },
	{ 0x5f0, 0xd4 },
	{ 0x5f1, 0xd5 },
	{ 0x5f2, 0xd6 },
	{ 0x5f3, 0xd7 },
	{ 0x5f4, 0xd8 },
	{ 0x200e, 0xfd },
	{ 0x200f, 0xfe },
	{ 0x2013, 0x96 },
	{ 0x2014, 0x97 },
	{ 0x2018, 0x91 },
	{ 0x2019, 0x92 },
	{ 0x201a, 0x82 },
	{ 0x201c, 0x93 },
	{ 0x201d, 0x94 },
	{ 0x201e, 0x84 },
	{ 0x2020, 0x86 },
	{ 0x2021, 0x87 },
	{ 0x2022, 0x95 },
	{ 0x2026, 0x85 },
	{ 0x2030, 0x89 },
	{ 0x2039, 0x8b },
	{ 0x203a, 0x9b },
	{ 0x20aa, 0xa4 },
	{ 0x20ac, 0x80 },
	{ 0x2122, 0x99 },
	{ 0xfffe, 0xff }
};

SingleByteCodecState __uniconv_cp1255_state = {
	"cp1255", cp1255_decoding_table, 256, cp1255_encoding_map, 234
};
