#include <singlebytecodec.h>

static const int cp1026_decoding_table[256] = {
	0x0,
	0x1,
	0x2,
	0x3,
	0x9c,
	0x9,
	0x86,
	0x7f,
	0x97,
	0x8d,
	0x8e,
	0xb,
	0xc,
	0xd,
	0xe,
	0xf,
	0x10,
	0x11,
	0x12,
	0x13,
	0x9d,
	0x85,
	0x8,
	0x87,
	0x18,
	0x19,
	0x92,
	0x8f,
	0x1c,
	0x1d,
	0x1e,
	0x1f,
	0x80,
	0x81,
	0x82,
	0x83,
	0x84,
	0xa,
	0x17,
	0x1b,
	0x88,
	0x89,
	0x8a,
	0x8b,
	0x8c,
	0x5,
	0x6,
	0x7,
	0x90,
	0x91,
	0x16,
	0x93,
	0x94,
	0x95,
	0x96,
	0x4,
	0x98,
	0x99,
	0x9a,
	0x9b,
	0x14,
	0x15,
	0x9e,
	0x1a,
	0x20,
	0xa0,
	0xe2,
	0xe4,
	0xe0,
	0xe1,
	0xe3,
	0xe5,
	0x7b,
	0xf1,
	0xc7,
	0x2e,
	0x3c,
	0x28,
	0x2b,
	0x21,
	0x26,
	0xe9,
	0xea,
	0xeb,
	0xe8,
	0xed,
	0xee,
	0xef,
	0xec,
	0xdf,
	0x11e,
	0x130,
	0x2a,
	0x29,
	0x3b,
	0x5e,
	0x2d,
	0x2f,
	0xc2,
	0xc4,
	0xc0,
	0xc1,
	0xc3,
	0xc5,
	0x5b,
	0xd1,
	0x15f,
	0x2c,
	0x25,
	0x5f,
	0x3e,
	0x3f,
	0xf8,
	0xc9,
	0xca,
	0xcb,
	0xc8,
	0xcd,
	0xce,
	0xcf,
	0xcc,
	0x131,
	0x3a,
	0xd6,
	0x15e,
	0x27,
	0x3d,
	0xdc,
	0xd8,
	0x61,
	0x62,
	0x63,
	0x64,
	0x65,
	0x66,
	0x67,
	0x68,
	0x69,
	0xab,
	0xbb,
	0x7d,
	0x60,
	0xa6,
	0xb1,
	0xb0,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x6e,
	0x6f,
	0x70,
	0x71,
	0x72,
	0xaa,
	0xba,
	0xe6,
	0xb8,
	0xc6,
	0xa4,
	0xb5,
	0xf6,
	0x73,
	0x74,
	0x75,
	0x76,
	0x77,
	0x78,
	0x79,
	0x7a,
	0xa1,
	0xbf,
	0x5d,
	0x24,
	0x40,
	0xae,
	0xa2,
	0xa3,
	0xa5,
	0xb7,
	0xa9,
	0xa7,
	0xb6,
	0xbc,
	0xbd,
	0xbe,
	0xac,
	0x7c,
	0xaf,
	0xa8,
	0xb4,
	0xd7,
	0xe7,
	0x41,
	0x42,
	0x43,
	0x44,
	0x45,
	0x46,
	0x47,
	0x48,
	0x49,
	0xad,
	0xf4,
	0x7e,
	0xf2,
	0xf3,
	0xf5,
	0x11f,
	0x4a,
	0x4b,
	0x4c,
	0x4d,
	0x4e,
	0x4f,
	0x50,
	0x51,
	0x52,
	0xb9,
	0xfb,
	0x5c,
	0xf9,
	0xfa,
	0xff,
	0xfc,
	0xf7,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x5a,
	0xb2,
	0xd4,
	0x23,
	0xd2,
	0xd3,
	0xd5,
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
	0xb3,
	0xdb,
	0x22,
	0xd9,
	0xda,
	0x9f
};

static const struct encoding_map cp1026_encoding_map[] = {
	{ 0x0, 0x0 },
	{ 0x1, 0x1 },
	{ 0x2, 0x2 },
	{ 0x3, 0x3 },
	{ 0x4, 0x37 },
	{ 0x5, 0x2d },
	{ 0x6, 0x2e },
	{ 0x7, 0x2f },
	{ 0x8, 0x16 },
	{ 0x9, 0x5 },
	{ 0xa, 0x25 },
	{ 0xb, 0xb },
	{ 0xc, 0xc },
	{ 0xd, 0xd },
	{ 0xe, 0xe },
	{ 0xf, 0xf },
	{ 0x10, 0x10 },
	{ 0x11, 0x11 },
	{ 0x12, 0x12 },
	{ 0x13, 0x13 },
	{ 0x14, 0x3c },
	{ 0x15, 0x3d },
	{ 0x16, 0x32 },
	{ 0x17, 0x26 },
	{ 0x18, 0x18 },
	{ 0x19, 0x19 },
	{ 0x1a, 0x3f },
	{ 0x1b, 0x27 },
	{ 0x1c, 0x1c },
	{ 0x1d, 0x1d },
	{ 0x1e, 0x1e },
	{ 0x1f, 0x1f },
	{ 0x20, 0x40 },
	{ 0x21, 0x4f },
	{ 0x22, 0xfc },
	{ 0x23, 0xec },
	{ 0x24, 0xad },
	{ 0x25, 0x6c },
	{ 0x26, 0x50 },
	{ 0x27, 0x7d },
	{ 0x28, 0x4d },
	{ 0x29, 0x5d },
	{ 0x2a, 0x5c },
	{ 0x2b, 0x4e },
	{ 0x2c, 0x6b },
	{ 0x2d, 0x60 },
	{ 0x2e, 0x4b },
	{ 0x2f, 0x61 },
	{ 0x30, 0xf0 },
	{ 0x31, 0xf1 },
	{ 0x32, 0xf2 },
	{ 0x33, 0xf3 },
	{ 0x34, 0xf4 },
	{ 0x35, 0xf5 },
	{ 0x36, 0xf6 },
	{ 0x37, 0xf7 },
	{ 0x38, 0xf8 },
	{ 0x39, 0xf9 },
	{ 0x3a, 0x7a },
	{ 0x3b, 0x5e },
	{ 0x3c, 0x4c },
	{ 0x3d, 0x7e },
	{ 0x3e, 0x6e },
	{ 0x3f, 0x6f },
	{ 0x40, 0xae },
	{ 0x41, 0xc1 },
	{ 0x42, 0xc2 },
	{ 0x43, 0xc3 },
	{ 0x44, 0xc4 },
	{ 0x45, 0xc5 },
	{ 0x46, 0xc6 },
	{ 0x47, 0xc7 },
	{ 0x48, 0xc8 },
	{ 0x49, 0xc9 },
	{ 0x4a, 0xd1 },
	{ 0x4b, 0xd2 },
	{ 0x4c, 0xd3 },
	{ 0x4d, 0xd4 },
	{ 0x4e, 0xd5 },
	{ 0x4f, 0xd6 },
	{ 0x50, 0xd7 },
	{ 0x51, 0xd8 },
	{ 0x52, 0xd9 },
	{ 0x53, 0xe2 },
	{ 0x54, 0xe3 },
	{ 0x55, 0xe4 },
	{ 0x56, 0xe5 },
	{ 0x57, 0xe6 },
	{ 0x58, 0xe7 },
	{ 0x59, 0xe8 },
	{ 0x5a, 0xe9 },
	{ 0x5b, 0x68 },
	{ 0x5c, 0xdc },
	{ 0x5d, 0xac },
	{ 0x5e, 0x5f },
	{ 0x5f, 0x6d },
	{ 0x60, 0x8d },
	{ 0x61, 0x81 },
	{ 0x62, 0x82 },
	{ 0x63, 0x83 },
	{ 0x64, 0x84 },
	{ 0x65, 0x85 },
	{ 0x66, 0x86 },
	{ 0x67, 0x87 },
	{ 0x68, 0x88 },
	{ 0x69, 0x89 },
	{ 0x6a, 0x91 },
	{ 0x6b, 0x92 },
	{ 0x6c, 0x93 },
	{ 0x6d, 0x94 },
	{ 0x6e, 0x95 },
	{ 0x6f, 0x96 },
	{ 0x70, 0x97 },
	{ 0x71, 0x98 },
	{ 0x72, 0x99 },
	{ 0x73, 0xa2 },
	{ 0x74, 0xa3 },
	{ 0x75, 0xa4 },
	{ 0x76, 0xa5 },
	{ 0x77, 0xa6 },
	{ 0x78, 0xa7 },
	{ 0x79, 0xa8 },
	{ 0x7a, 0xa9 },
	{ 0x7b, 0x48 },
	{ 0x7c, 0xbb },
	{ 0x7d, 0x8c },
	{ 0x7e, 0xcc },
	{ 0x7f, 0x7 },
	{ 0x80, 0x20 },
	{ 0x81, 0x21 },
	{ 0x82, 0x22 },
	{ 0x83, 0x23 },
	{ 0x84, 0x24 },
	{ 0x85, 0x15 },
	{ 0x86, 0x6 },
	{ 0x87, 0x17 },
	{ 0x88, 0x28 },
	{ 0x89, 0x29 },
	{ 0x8a, 0x2a },
	{ 0x8b, 0x2b },
	{ 0x8c, 0x2c },
	{ 0x8d, 0x9 },
	{ 0x8e, 0xa },
	{ 0x8f, 0x1b },
	{ 0x90, 0x30 },
	{ 0x91, 0x31 },
	{ 0x92, 0x1a },
	{ 0x93, 0x33 },
	{ 0x94, 0x34 },
	{ 0x95, 0x35 },
	{ 0x96, 0x36 },
	{ 0x97, 0x8 },
	{ 0x98, 0x38 },
	{ 0x99, 0x39 },
	{ 0x9a, 0x3a },
	{ 0x9b, 0x3b },
	{ 0x9c, 0x4 },
	{ 0x9d, 0x14 },
	{ 0x9e, 0x3e },
	{ 0x9f, 0xff },
	{ 0xa0, 0x41 },
	{ 0xa1, 0xaa },
	{ 0xa2, 0xb0 },
	{ 0xa3, 0xb1 },
	{ 0xa4, 0x9f },
	{ 0xa5, 0xb2 },
	{ 0xa6, 0x8e },
	{ 0xa7, 0xb5 },
	{ 0xa8, 0xbd },
	{ 0xa9, 0xb4 },
	{ 0xaa, 0x9a },
	{ 0xab, 0x8a },
	{ 0xac, 0xba },
	{ 0xad, 0xca },
	{ 0xae, 0xaf },
	{ 0xaf, 0xbc },
	{ 0xb0, 0x90 },
	{ 0xb1, 0x8f },
	{ 0xb2, 0xea },
	{ 0xb3, 0xfa },
	{ 0xb4, 0xbe },
	{ 0xb5, 0xa0 },
	{ 0xb6, 0xb6 },
	{ 0xb7, 0xb3 },
	{ 0xb8, 0x9d },
	{ 0xb9, 0xda },
	{ 0xba, 0x9b },
	{ 0xbb, 0x8b },
	{ 0xbc, 0xb7 },
	{ 0xbd, 0xb8 },
	{ 0xbe, 0xb9 },
	{ 0xbf, 0xab },
	{ 0xc0, 0x64 },
	{ 0xc1, 0x65 },
	{ 0xc2, 0x62 },
	{ 0xc3, 0x66 },
	{ 0xc4, 0x63 },
	{ 0xc5, 0x67 },
	{ 0xc6, 0x9e },
	{ 0xc7, 0x4a },
	{ 0xc8, 0x74 },
	{ 0xc9, 0x71 },
	{ 0xca, 0x72 },
	{ 0xcb, 0x73 },
	{ 0xcc, 0x78 },
	{ 0xcd, 0x75 },
	{ 0xce, 0x76 },
	{ 0xcf, 0x77 },
	{ 0xd1, 0x69 },
	{ 0xd2, 0xed },
	{ 0xd3, 0xee },
	{ 0xd4, 0xeb },
	{ 0xd5, 0xef },
	{ 0xd6, 0x7b },
	{ 0xd7, 0xbf },
	{ 0xd8, 0x80 },
	{ 0xd9, 0xfd },
	{ 0xda, 0xfe },
	{ 0xdb, 0xfb },
	{ 0xdc, 0x7f },
	{ 0xdf, 0x59 },
	{ 0xe0, 0x44 },
	{ 0xe1, 0x45 },
	{ 0xe2, 0x42 },
	{ 0xe3, 0x46 },
	{ 0xe4, 0x43 },
	{ 0xe5, 0x47 },
	{ 0xe6, 0x9c },
	{ 0xe7, 0xc0 },
	{ 0xe8, 0x54 },
	{ 0xe9, 0x51 },
	{ 0xea, 0x52 },
	{ 0xeb, 0x53 },
	{ 0xec, 0x58 },
	{ 0xed, 0x55 },
	{ 0xee, 0x56 },
	{ 0xef, 0x57 },
	{ 0xf1, 0x49 },
	{ 0xf2, 0xcd },
	{ 0xf3, 0xce },
	{ 0xf4, 0xcb },
	{ 0xf5, 0xcf },
	{ 0xf6, 0xa1 },
	{ 0xf7, 0xe1 },
	{ 0xf8, 0x70 },
	{ 0xf9, 0xdd },
	{ 0xfa, 0xde },
	{ 0xfb, 0xdb },
	{ 0xfc, 0xe0 },
	{ 0xff, 0xdf },
	{ 0x11e, 0x5a },
	{ 0x11f, 0xd0 },
	{ 0x130, 0x5b },
	{ 0x131, 0x79 },
	{ 0x15e, 0x7c },
	{ 0x15f, 0x6a }
};

SingleByteCodecState __uniconv_cp1026_state = {
	"cp1026", cp1026_decoding_table, 256, cp1026_encoding_map, 256
};

