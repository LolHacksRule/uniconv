#include <singlebytecodec.h>

static const int cp1256_decoding_table[256] = {
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
	0x67e,
	0x201a,
	0x192,
	0x201e,
	0x2026,
	0x2020,
	0x2021,
	0x2c6,
	0x2030,
	0x679,
	0x2039,
	0x152,
	0x686,
	0x698,
	0x688,
	0x6af,
	0x2018,
	0x2019,
	0x201c,
	0x201d,
	0x2022,
	0x2013,
	0x2014,
	0x6a9,
	0x2122,
	0x691,
	0x203a,
	0x153,
	0x200c,
	0x200d,
	0x6ba,
	0xa0,
	0x60c,
	0xa2,
	0xa3,
	0xa4,
	0xa5,
	0xa6,
	0xa7,
	0xa8,
	0xa9,
	0x6be,
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
	0x61b,
	0xbb,
	0xbc,
	0xbd,
	0xbe,
	0x61f,
	0x6c1,
	0x621,
	0x622,
	0x623,
	0x624,
	0x625,
	0x626,
	0x627,
	0x628,
	0x629,
	0x62a,
	0x62b,
	0x62c,
	0x62d,
	0x62e,
	0x62f,
	0x630,
	0x631,
	0x632,
	0x633,
	0x634,
	0x635,
	0x636,
	0xd7,
	0x637,
	0x638,
	0x639,
	0x63a,
	0x640,
	0x641,
	0x642,
	0x643,
	0xe0,
	0x644,
	0xe2,
	0x645,
	0x646,
	0x647,
	0x648,
	0xe7,
	0xe8,
	0xe9,
	0xea,
	0xeb,
	0x649,
	0x64a,
	0xee,
	0xef,
	0x64b,
	0x64c,
	0x64d,
	0x64e,
	0xf4,
	0x64f,
	0x650,
	0xf7,
	0x651,
	0xf9,
	0x652,
	0xfb,
	0xfc,
	0x200e,
	0x200f,
	0x6d2
};

static const struct encoding_map cp1256_encoding_map[] = {
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
	{ 0xa2, 0xa2 },
	{ 0xa3, 0xa3 },
	{ 0xa4, 0xa4 },
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
	{ 0xd7, 0xd7 },
	{ 0xe0, 0xe0 },
	{ 0xe2, 0xe2 },
	{ 0xe7, 0xe7 },
	{ 0xe8, 0xe8 },
	{ 0xe9, 0xe9 },
	{ 0xea, 0xea },
	{ 0xeb, 0xeb },
	{ 0xee, 0xee },
	{ 0xef, 0xef },
	{ 0xf4, 0xf4 },
	{ 0xf7, 0xf7 },
	{ 0xf9, 0xf9 },
	{ 0xfb, 0xfb },
	{ 0xfc, 0xfc },
	{ 0x152, 0x8c },
	{ 0x153, 0x9c },
	{ 0x192, 0x83 },
	{ 0x2c6, 0x88 },
	{ 0x60c, 0xa1 },
	{ 0x61b, 0xba },
	{ 0x61f, 0xbf },
	{ 0x621, 0xc1 },
	{ 0x622, 0xc2 },
	{ 0x623, 0xc3 },
	{ 0x624, 0xc4 },
	{ 0x625, 0xc5 },
	{ 0x626, 0xc6 },
	{ 0x627, 0xc7 },
	{ 0x628, 0xc8 },
	{ 0x629, 0xc9 },
	{ 0x62a, 0xca },
	{ 0x62b, 0xcb },
	{ 0x62c, 0xcc },
	{ 0x62d, 0xcd },
	{ 0x62e, 0xce },
	{ 0x62f, 0xcf },
	{ 0x630, 0xd0 },
	{ 0x631, 0xd1 },
	{ 0x632, 0xd2 },
	{ 0x633, 0xd3 },
	{ 0x634, 0xd4 },
	{ 0x635, 0xd5 },
	{ 0x636, 0xd6 },
	{ 0x637, 0xd8 },
	{ 0x638, 0xd9 },
	{ 0x639, 0xda },
	{ 0x63a, 0xdb },
	{ 0x640, 0xdc },
	{ 0x641, 0xdd },
	{ 0x642, 0xde },
	{ 0x643, 0xdf },
	{ 0x644, 0xe1 },
	{ 0x645, 0xe3 },
	{ 0x646, 0xe4 },
	{ 0x647, 0xe5 },
	{ 0x648, 0xe6 },
	{ 0x649, 0xec },
	{ 0x64a, 0xed },
	{ 0x64b, 0xf0 },
	{ 0x64c, 0xf1 },
	{ 0x64d, 0xf2 },
	{ 0x64e, 0xf3 },
	{ 0x64f, 0xf5 },
	{ 0x650, 0xf6 },
	{ 0x651, 0xf8 },
	{ 0x652, 0xfa },
	{ 0x679, 0x8a },
	{ 0x67e, 0x81 },
	{ 0x686, 0x8d },
	{ 0x688, 0x8f },
	{ 0x691, 0x9a },
	{ 0x698, 0x8e },
	{ 0x6a9, 0x98 },
	{ 0x6af, 0x90 },
	{ 0x6ba, 0x9f },
	{ 0x6be, 0xaa },
	{ 0x6c1, 0xc0 },
	{ 0x6d2, 0xff },
	{ 0x200c, 0x9d },
	{ 0x200d, 0x9e },
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
	{ 0x20ac, 0x80 },
	{ 0x2122, 0x99 }
};

SingleByteCodecState __uniconv_cp1256_state = {
	"cp1256", cp1256_decoding_table, 256, cp1256_encoding_map, 256
};

