#include "headers/ascii_dithrer.h"
#include "headers/Image.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstring>

// Edge direction characters
static const char edge_chars[4] = {'|', '-', '/', '\\'};
// Luminance ramp for fill
static const char* luminance_chars = " .:-=+*#%@";

// Helper clamp function
static int clampi(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

// Font8x8 data - Basic Latin characters (U+0020 to U+007F)
const unsigned char AsciiDithrer::font8x8_basic[128][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0000 (nul)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0001
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0002
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0003
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0004
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0005
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0006
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0007
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0008
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0009
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0010
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0011
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0012
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0013
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0014
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0015
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0016
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0017
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0018
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0019
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0020 (space)
    { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   // U+0021 (!)
    { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0022 (")
    { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},   // U+0023 (#)
    { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},   // U+0024 ($)
    { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},   // U+0025 (%)
    { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},   // U+0026 (&)
    { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0027 (')
    { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},   // U+0028 (()
    { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},   // U+0029 ())
    { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   // U+002A (*)
    { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},   // U+002B (+)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+002C (,)
    { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},   // U+002D (-)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+002E (.)
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},   // U+002F (/)
    { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},   // U+0030 (0)
    { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},   // U+0031 (1)
    { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},   // U+0032 (2)
    { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},   // U+0033 (3)
    { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},   // U+0034 (4)
    { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},   // U+0035 (5)
    { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},   // U+0036 (6)
    { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},   // U+0037 (7)
    { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},   // U+0038 (8)
    { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},   // U+0039 (9)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+003A (:)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+003B (;)
    { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},   // U+003C (<)
    { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},   // U+003D (=)
    { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},   // U+003E (>)
    { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},   // U+003F (?)
    { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},   // U+0040 (@)
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0042 (B)
    { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},   // U+0043 (C)
    { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},   // U+0044 (D)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0045 (E)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},   // U+0046 (F)
    { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},   // U+0047 (G)
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0048 (H)
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0049 (I)
    { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},   // U+004A (J)
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+004B (K)
    { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},   // U+004C (L)
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+004D (M)
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+004E (N)
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+004F (O)
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+0050 (P)
    { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},   // U+0051 (Q)
    { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},   // U+0052 (R)
    { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},   // U+0053 (S)
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0054 (T)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},   // U+0055 (U)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0056 (V)
    { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},   // U+0057 (W)
    { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+0058 (X)
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+0059 (Y)
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+005A (Z)
    { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},   // U+005B ([)
    { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},   // U+005C (\)
    { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},   // U+005D (])
    { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},   // U+005E (^)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+005F (_)
    { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0060 (`)
    { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},   // U+0061 (a)
    { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},   // U+0062 (b)
    { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},   // U+0063 (c)
    { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},   // U+0064 (d)
    { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},   // U+0065 (e)
    { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},   // U+0066 (f)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0067 (g)
    { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},   // U+0068 (h)
    { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0069 (i)
    { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},   // U+006A (j)
    { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},   // U+006B (k)
    { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+006C (l)
    { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},   // U+006D (m)
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},   // U+006E (n)
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+006F (o)
    { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},   // U+0070 (p)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},   // U+0071 (q)
    { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},   // U+0072 (r)
    { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},   // U+0073 (s)
    { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0074 (t)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},   // U+0075 (u)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0076 (v)
    { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},   // U+0077 (w)
    { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},   // U+0078 (x)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0079 (y)
    { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},   // U+007A (z)
    { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},   // U+007B ({)
    { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   // U+007C (|)
    { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},   // U+007D (})
    { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}    // U+007F
};

// Font8x8 block characters (U+2580 to U+259F)
const unsigned char AsciiDithrer::font8x8_block[32][8] = {
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},   // U+2580 (top half)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+2581 (box 1/8)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},   // U+2582 (box 2/8)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF},   // U+2583 (box 3/8)
    { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2584 (bottom half)
    { 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2585 (box 5/8)
    { 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2586 (box 6/8)
    { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2587 (box 7/8)
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2588 (solid)
    { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F},   // U+2589 (box 7/8)
    { 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F},   // U+258A (box 6/8)
    { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},   // U+258B (box 5/8)
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},   // U+258C (left half)
    { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},   // U+258D (box 3/8)
    { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},   // U+258E (box 2/8)
    { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},   // U+258F (box 1/8)
    { 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0},   // U+2590 (right half)
    { 0x55, 0x00, 0xAA, 0x00, 0x55, 0x00, 0xAA, 0x00},   // U+2591 (25% solid)
    { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA},   // U+2592 (50% solid)
    { 0xFF, 0xAA, 0xFF, 0x55, 0xFF, 0xAA, 0xFF, 0x55},   // U+2593 (75% solid)
    { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+2594 (box 1/8)
    { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},   // U+2595 (box 1/8)
    { 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F},   // U+2596 (box bottom left)
    { 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0},   // U+2597 (box bottom right)
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00},   // U+2598 (box top left)
    { 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF},   // U+2599 (boxes left and bottom)
    { 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0},   // U+259A (boxes top-left and bottom right)
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F},   // U+259B (boxes top and left)
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0},   // U+259C (boxes top and right)
    { 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00},   // U+259D (box top right)
    { 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F},   // U+259E (boxes top right and bottom left)
    { 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF}    // U+259F (boxes right and bottom)
};

AsciiDithrer::AsciiDithrer(AsciiCharSet charSet, bool detectEdges)
    : charSet_(charSet), detectEdges_(detectEdges),
      edgeThreshold_(0.3f), contrast_(1.0f), brightness_(0.0f), gamma_(1.0f),
      dogSigma_(1.0f), dogSigmaScale_(1.6f), dogTau_(1.0f), dogThreshold_(0.02f), edgePixelThreshold_(8),
      colorTheme_(ColorTheme::MONOCHROME), depthMode_(DepthMode::NONE), depthThreshold_(0.5f), depthFade_(0.3f),
      bloomIntensity_(0.1f), colorBurn_(0.0f), toneMapping_(1.0f), lowContrast_(false), tileSize_(8), computeShaderMode_(false) {
    initializeCharMap();
}

void AsciiDithrer::initializeCharMap() {
    switch (charSet_) {
        case AsciiCharSet::BASIC:
            charMap_ = " .:-=+*#%@";
            break;
        case AsciiCharSet::EXTENDED:
            charMap_ = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            break;
        case AsciiCharSet::ARTISTIC:
            charMap_ = " ░▒▓█";
            break;
        case AsciiCharSet::SIMPLE:
            charMap_ = ".#";
            break;
        case AsciiCharSet::SHADER:
            charMap_ = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            break;
        case AsciiCharSet::RETRO:
            charMap_ = " █";
            break;
        case AsciiCharSet::ADVANCED:
            charMap_ = luminance_chars;
            break;
        case AsciiCharSet::FONT8X8:
            charMap_ = luminance_chars;
            break;
    }
}

float AsciiDithrer::getBrightness(const Color& color) {
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
}

float AsciiDithrer::applyImageProcessing(float value) {
    value += brightness_;
    value = (value - 0.5f) * contrast_ + 0.5f;
    if (gamma_ != 1.0f) value = std::pow(value, gamma_);
    return std::max(0.0f, std::min(1.0f, value));
}

// --- DoG and Sobel routines ---
float AsciiDithrer::gaussian(float sigma, float pos) {
    return (1.0f / std::sqrt(2.0f * M_PI * sigma * sigma)) * std::exp(-(pos * pos) / (2.0f * sigma * sigma));
}

void AsciiDithrer::calculateLuminanceBuffer(const Image& image) {
    int width = image.getWidth();
    int height = image.getHeight();
    luminanceBuffer_.resize(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            luminanceBuffer_[y * width + x] = getBrightness(image.getPixel(x, y));
        }
    }
}

void AsciiDithrer::horizontalBlur(std::vector<float>& input, std::vector<float>& output, int width, int height) {
    output.resize(width * height);
    int ksize = static_cast<int>(std::ceil(dogSigma_ * 3));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sum = 0.0f, wsum = 0.0f;
            for (int k = -ksize; k <= ksize; ++k) {
                int xx = clampi(x + k, 0, width - 1);
                float w = gaussian(dogSigma_, k);
                sum += input[y * width + xx] * w;
                wsum += w;
            }
            output[y * width + x] = sum / wsum;
        }
    }
}

void AsciiDithrer::verticalBlur(std::vector<float>& input, std::vector<float>& output, int width, int height) {
    output.resize(width * height);
    int ksize = static_cast<int>(std::ceil(dogSigma_ * 3));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sum = 0.0f, wsum = 0.0f;
            for (int k = -ksize; k <= ksize; ++k) {
                int yy = clampi(y + k, 0, height - 1);
                float w = gaussian(dogSigma_, k);
                sum += input[yy * width + x] * w;
                wsum += w;
            }
            output[y * width + x] = sum / wsum;
        }
    }
}

void AsciiDithrer::applyDifferenceOfGaussians() {
    // DoG: blur with sigma, blur with sigma*scale, subtract
    int width = static_cast<int>(std::sqrt(luminanceBuffer_.size()));
    int height = luminanceBuffer_.size() / width;
    std::vector<float> blur1, blur2, temp;
    // Horizontal + vertical blur for both sigmas
    horizontalBlur(luminanceBuffer_, temp, width, height);
    verticalBlur(temp, blur1, width, height);
    float sigma2 = dogSigma_ * dogSigmaScale_;
    int ksize2 = static_cast<int>(std::ceil(sigma2 * 3));
    // Blur2: use sigma2
    // Horizontal
    temp.resize(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sum = 0.0f, wsum = 0.0f;
            for (int k = -ksize2; k <= ksize2; ++k) {
                int xx = clampi(x + k, 0, width - 1);
                float w = gaussian(sigma2, k);
                sum += luminanceBuffer_[y * width + xx] * w;
                wsum += w;
            }
            temp[y * width + x] = sum / wsum;
        }
    }
    verticalBlur(temp, blur2, width, height);
    // DoG = blur1 - tau * blur2
    dogBuffer_.resize(width * height);
    for (int i = 0; i < width * height; ++i) {
        dogBuffer_[i] = blur1[i] - dogTau_ * blur2[i];
    }
}

void AsciiDithrer::applySobelFilter() {
    int width = static_cast<int>(std::sqrt(dogBuffer_.size()));
    int height = dogBuffer_.size() / width;
    edgeBuffer_.resize(width * height);
    edgeDirectionBuffer_.resize(width * height);
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float gx =
                -1 * dogBuffer_[(y - 1) * width + (x - 1)] + 1 * dogBuffer_[(y - 1) * width + (x + 1)] +
                -2 * dogBuffer_[y * width + (x - 1)] + 2 * dogBuffer_[y * width + (x + 1)] +
                -1 * dogBuffer_[(y + 1) * width + (x - 1)] + 1 * dogBuffer_[(y + 1) * width + (x + 1)];
            float gy =
                -1 * dogBuffer_[(y - 1) * width + (x - 1)] + -2 * dogBuffer_[(y - 1) * width + x] + -1 * dogBuffer_[(y - 1) * width + (x + 1)] +
                1 * dogBuffer_[(y + 1) * width + (x - 1)] + 2 * dogBuffer_[(y + 1) * width + x] + 1 * dogBuffer_[(y + 1) * width + (x + 1)];
            float mag = std::sqrt(gx * gx + gy * gy);
            float theta = std::atan2(gy, gx);
            edgeBuffer_[y * width + x] = mag;
            edgeDirectionBuffer_[y * width + x] = getEdgeDirection(theta);
        }
    }
}

EdgeDirection AsciiDithrer::getEdgeDirection(float theta) {
    float deg = theta * 180.0f / M_PI;
    deg = std::fmod(deg + 360.0f, 360.0f); // [0,360)
    if ((deg < 22.5f) || (deg >= 157.5f && deg < 202.5f) || (deg >= 337.5f)) return EdgeDirection::VERTICAL;
    if ((deg >= 67.5f && deg < 112.5f) || (deg >= 247.5f && deg < 292.5f)) return EdgeDirection::HORIZONTAL;
    if ((deg >= 22.5f && deg < 67.5f) || (deg >= 202.5f && deg < 247.5f)) return EdgeDirection::DIAGONAL_1;
    if ((deg >= 112.5f && deg < 157.5f) || (deg >= 292.5f && deg < 337.5f)) return EdgeDirection::DIAGONAL_2;
    return EdgeDirection::NONE;
}

// --- Main ASCII logic ---
char AsciiDithrer::getAdvancedChar(int x, int y, float brightness, EdgeDirection direction) {
    if (direction != EdgeDirection::NONE) {
        return edge_chars[static_cast<int>(direction)];
    } else {
        // Map brightness to luminance ramp
        brightness = applyImageProcessing(brightness);
        int idx = static_cast<int>(brightness * (std::strlen(luminance_chars) - 1));
        return luminance_chars[idx];
    }
}

void AsciiDithrer::applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) {
    // Not used for ASCII
    outputImage = inputImage;
}

// Map brightness [0,1] to a font8x8 character (basic set, ASCII 32-126)
char AsciiDithrer::selectFont8x8Char(float brightness) {
    // Map brightness to printable ASCII range (32-126)
    int numChars = 95; // 126-32+1
    int idx = static_cast<int>(brightness * (numChars - 1));
    idx = clampi(idx, 0, numChars - 1);
    return static_cast<char>(32 + idx);
}

// Render an 8x8 tile using the font8x8 bitmap for the given character
void AsciiDithrer::renderFont8x8Tile(std::ofstream& file, char asciiChar) {
    int fontIdx = static_cast<unsigned char>(asciiChar);
    if (fontIdx < 0 || fontIdx > 127) fontIdx = 32; // fallback to space
    const unsigned char* bitmap = font8x8_basic[fontIdx];
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            bool pixelOn = (bitmap[row] & (1 << (7 - col)));
            file << (pixelOn ? '#' : ' ');
        }
        file << '\n';
    }
}

// --- Update saveAsText for FONT8X8 mode ---
bool AsciiDithrer::saveAsText(const Image& inputImage, const std::string& filename) {
    int width = inputImage.getWidth();
    int height = inputImage.getHeight();
    int tileSize = 8; // 8x8 tiles
    int tilesX = width / tileSize;
    int tilesY = height / tileSize;
    if (tilesX < 1 || tilesY < 1) return false;

    calculateLuminanceBuffer(inputImage);
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    if (charSet_ == AsciiCharSet::FONT8X8) {
        // Render each tile as an 8x8 ASCII block
        for (int ty = 0; ty < tilesY; ++ty) {
            // For each row of the tile
            for (int row = 0; row < tileSize; ++row) {
                for (int tx = 0; tx < tilesX; ++tx) {
                    // Compute average brightness for this tile
                    float avgBrightness = 0.0f;
                    for (int dy = 0; dy < tileSize; ++dy) {
                        for (int dx = 0; dx < tileSize; ++dx) {
                            int x = tx * tileSize + dx;
                            int y = ty * tileSize + dy;
                            int idx = y * width + x;
                            avgBrightness += luminanceBuffer_[idx];
                        }
                    }
                    avgBrightness /= (tileSize * tileSize);
                    char asciiChar = selectFont8x8Char(applyImageProcessing(avgBrightness));
                    // Output the row of the font8x8 bitmap
                    renderFont8x8Tile(file, asciiChar);
                }
                file << '\n';
            }
        }
        file.close();
        return true;
    }
    // ... fallback to previous logic for other charsets ...
    // ... existing code ...
    return false;
}

bool AsciiDithrer::saveAsAsciiImage(const Image& inputImage, const std::string& filename, const Color& fg, const Color& bg, int scale) {
    int width = inputImage.getWidth();
    int height = inputImage.getHeight();
    int tilesX = width / tileSize_;
    int tilesY = height / tileSize_;
    if (tilesX < 1 || tilesY < 1) return false;
    int outW = tilesX * tileSize_ * scale;
    int outH = tilesY * tileSize_ * scale;
    Image outImg(outW, outH);
    
    // Fill background
    for (int y = 0; y < outH; ++y) {
        for (int x = 0; x < outW; ++x) {
            outImg.setPixel(x, y, bg);
        }
    }
    
    // Process tiles using advanced shader techniques
    if (computeShaderMode_) {
        processTiles(inputImage);
    }
    
    calculateLuminanceBuffer(inputImage);
    
    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            TileInfo tile;
            
            if (computeShaderMode_ && !tileBuffer_.empty()) {
                int tileIndex = ty * tilesX + tx;
                if (tileIndex < tileBuffer_.size()) {
                    tile = tileBuffer_[tileIndex];
                } else {
                    tile = analyzeTile(inputImage, tx, ty);
                }
            } else {
                // Compute average brightness for this tile
                float avgBrightness = 0.0f;
                for (int dy = 0; dy < tileSize_; ++dy) {
                    for (int dx = 0; dx < tileSize_; ++dx) {
                        int x = tx * tileSize_ + dx;
                        int y = ty * tileSize_ + dy;
                        if (x < width && y < height) {
                            int idx = y * width + x;
                            avgBrightness += luminanceBuffer_[idx];
                        }
                    }
                }
                avgBrightness /= (tileSize_ * tileSize_);
                tile.averageLuminance = avgBrightness;
                tile.depth = 1.0f - avgBrightness / 255.0f;
                tile.dominantEdge = EdgeDirection::NONE;
                tile.hasSignificantEdges = false;
            }
            
            // Apply depth thresholding
            if (depthMode_ != DepthMode::NONE && tile.depth > depthThreshold_) {
                continue; // Skip distant tiles
            }
            
            char asciiChar = selectTileCharacter(tile);
            if (asciiChar == 0) asciiChar = selectFont8x8Char(applyImageProcessing(tile.averageLuminance));
            
            int fontIdx = static_cast<unsigned char>(asciiChar);
            if (fontIdx < 0 || fontIdx > 127) fontIdx = 32;
            const unsigned char* bitmap = font8x8_basic[fontIdx];
            
            // Apply color theming
            Color tileFg = fg;
            if (colorTheme_ != ColorTheme::MONOCHROME) {
                tileFg = applyColorTheme(fg, tile.averageLuminance, tile.depth);
            }
            
            // Render the 8x8 bitmap into the output image
            for (int row = 0; row < tileSize_; ++row) {
                for (int col = 0; col < tileSize_; ++col) {
                    bool pixelOn = (bitmap[row] & (1 << (7 - col)));
                    Color color = pixelOn ? tileFg : bg;
                    // Scale the tile if needed
                    for (int sy = 0; sy < scale; ++sy) {
                        for (int sx = 0; sx < scale; ++sx) {
                            int outX = tx * tileSize_ * scale + col * scale + sx;
                            int outY = ty * tileSize_ * scale + row * scale + sy;
                            if (outX < outW && outY < outH) {
                                outImg.setPixel(outX, outY, color);
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Apply post-processing effects if enabled
    if (bloomIntensity_ > 0.0f || colorBurn_ > 0.0f || toneMapping_ > 0.0f || lowContrast_) {
        std::vector<Color> colors(outW * outH);
        
        // Extract colors from image
        for (int y = 0; y < outH; ++y) {
            for (int x = 0; x < outW; ++x) {
                colors[y * outW + x] = outImg.getPixel(x, y);
            }
        }
        
        // Apply effects
        if (bloomIntensity_ > 0.0f) {
            applyBloomEffect(colors, outW, outH);
        }
        if (colorBurn_ > 0.0f) {
            applyColorBurnEffect(colors);
        }
        if (toneMapping_ > 0.0f) {
            applyToneMapping(colors);
        }
        if (lowContrast_) {
            applyLowContrastEffect(colors);
        }
        
        // Write back to image
        for (int y = 0; y < outH; ++y) {
            for (int x = 0; x < outW; ++x) {
                outImg.setPixel(x, y, colors[y * outW + x]);
            }
        }
    }
    
    return outImg.save(filename, "png");
}

// New advanced methods implementation
void AsciiDithrer::processTiles(const Image& image) {
    int width = image.getWidth();
    int height = image.getHeight();
    int numTilesX = width / tileSize_;
    int numTilesY = height / tileSize_;
    
    tileBuffer_.resize(numTilesX * numTilesY);
    
    for (int tileY = 0; tileY < numTilesY; ++tileY) {
        for (int tileX = 0; tileX < numTilesX; ++tileX) {
            int tileIndex = tileY * numTilesX + tileX;
            tileBuffer_[tileIndex] = analyzeTile(image, tileX, tileY);
        }
    }
}

TileInfo AsciiDithrer::analyzeTile(const Image& image, int tileX, int tileY) {
    TileInfo tile;
    tile.averageLuminance = 0.0f;
    tile.edgeStrength = 0.0f;
    tile.edgePixelCount = 0;
    tile.depth = 0.0f;
    tile.hasSignificantEdges = false;
    
    std::vector<EdgeDirection> edgeDirections;
    std::vector<float> luminances;
    
    int startX = tileX * tileSize_;
    int startY = tileY * tileSize_;
    int endX = std::min(startX + tileSize_, image.getWidth());
    int endY = std::min(startY + tileSize_, image.getHeight());
    
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            Color pixel = image.getPixel(x, y);
            float luminance = getBrightness(pixel);
            luminances.push_back(luminance);
            tile.averageLuminance += luminance;
            
            // Calculate depth based on luminance (simplified depth estimation)
            tile.depth += (1.0f - luminance) * 0.5f;
            
            if (detectEdges_ && isEdgePixel(image, x, y)) {
                float edgeStrength = calculateEdgeStrength(image, x, y);
                tile.edgeStrength += edgeStrength;
                tile.edgePixelCount++;
                
                if (edgeStrength > edgeThreshold_) {
                    EdgeDirection direction = getEdgeDirection(atan2(
                        calculateEdgeStrength(image, x, y + 1) - calculateEdgeStrength(image, x, y - 1),
                        calculateEdgeStrength(image, x + 1, y) - calculateEdgeStrength(image, x - 1, y)
                    ));
                    edgeDirections.push_back(direction);
                }
            }
        }
    }
    
    int pixelCount = (endX - startX) * (endY - startY);
    if (pixelCount > 0) {
        tile.averageLuminance /= pixelCount;
        tile.depth /= pixelCount;
        
        if (tile.edgePixelCount > 0) {
            tile.edgeStrength /= tile.edgePixelCount;
            tile.hasSignificantEdges = tile.edgePixelCount >= edgePixelThreshold_;
            tile.dominantEdge = getDominantEdgeDirection(edgeDirections);
        } else {
            tile.dominantEdge = EdgeDirection::NONE;
        }
    }
    
    return tile;
}

EdgeDirection AsciiDithrer::getDominantEdgeDirection(const std::vector<EdgeDirection>& directions) {
    if (directions.empty()) return EdgeDirection::NONE;
    
    std::vector<int> counts(4, 0);
    for (EdgeDirection dir : directions) {
        if (dir != EdgeDirection::NONE) {
            counts[static_cast<int>(dir)]++;
        }
    }
    
    int maxCount = 0;
    EdgeDirection dominant = EdgeDirection::NONE;
    for (int i = 0; i < 4; ++i) {
        if (counts[i] > maxCount) {
            maxCount = counts[i];
            dominant = static_cast<EdgeDirection>(i);
        }
    }
    
    return dominant;
}

char AsciiDithrer::selectTileCharacter(const TileInfo& tile) {
    if (tile.hasSignificantEdges && tile.dominantEdge != EdgeDirection::NONE) {
        // Use edge-aware character selection
        return getDirectionalChar(tile.averageLuminance, tile.dominantEdge);
    } else {
        // Use luminance-based character selection
        return brightnessToChar(tile.averageLuminance, false);
    }
}

Color AsciiDithrer::applyColorTheme(const Color& original, float luminance, float depth) {
    Color themed = getThemeColor(luminance, depth);
    
    // Apply depth effect
    float depthEffect = calculateDepthEffect(depth);
    themed = Color(
        themed.r * depthEffect,
        themed.g * depthEffect,
        themed.b * depthEffect
    );
    
    return themed;
}

float AsciiDithrer::calculateDepthEffect(float depth) {
    switch (depthMode_) {
        case DepthMode::NONE:
            return 1.0f;
        case DepthMode::LINEAR:
            return 1.0f - depth * depthFade_;
        case DepthMode::EXPONENTIAL:
            return exp(-depth * depthFade_);
        case DepthMode::GAUSSIAN:
            return exp(-(depth * depth) / (2.0f * depthFade_ * depthFade_));
        default:
            return 1.0f;
    }
}

void AsciiDithrer::applyBloomEffect(std::vector<Color>& colors, int width, int height) {
    if (bloomIntensity_ <= 0.0f) return;
    
    std::vector<Color> bloomed = colors;
    
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int index = y * width + x;
            Color& current = colors[index];
            
            // Simple bloom: average with bright neighbors
            Color bloom(0, 0, 0);
            int brightNeighbors = 0;
            
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        Color neighbor = bloomed[ny * width + nx];
                        float neighborLuminance = getBrightness(neighbor);
                        
                        if (neighborLuminance > 0.7f) { // Bright threshold
                            bloom.r += neighbor.r;
                            bloom.g += neighbor.g;
                            bloom.b += neighbor.b;
                            brightNeighbors++;
                        }
                    }
                }
            }
            
            if (brightNeighbors > 0) {
                bloom.r /= brightNeighbors;
                bloom.g /= brightNeighbors;
                bloom.b /= brightNeighbors;
                
                current.r = std::min(255, int(current.r + bloom.r * bloomIntensity_));
                current.g = std::min(255, int(current.g + bloom.g * bloomIntensity_));
                current.b = std::min(255, int(current.b + bloom.b * bloomIntensity_));
            }
        }
    }
}

void AsciiDithrer::applyColorBurnEffect(std::vector<Color>& colors) {
    if (colorBurn_ <= 0.0f) return;
    
    for (Color& color : colors) {
        float luminance = getBrightness(color);
        float burnFactor = 1.0f - luminance * colorBurn_;
        
        color.r = std::max(0, int(color.r * burnFactor));
        color.g = std::max(0, int(color.g * burnFactor));
        color.b = std::max(0, int(color.b * burnFactor));
    }
}

void AsciiDithrer::applyToneMapping(std::vector<Color>& colors) {
    if (toneMapping_ <= 0.0f) return;
    
    for (Color& color : colors) {
        // Simple Reinhard tone mapping
        float luminance = getBrightness(color) / 255.0f;
        float mapped = luminance / (1.0f + luminance * toneMapping_);
        
        float scale = mapped / (luminance + 0.0001f);
        color.r = std::min(255, int(color.r * scale));
        color.g = std::min(255, int(color.g * scale));
        color.b = std::min(255, int(color.b * scale));
    }
}

void AsciiDithrer::applyLowContrastEffect(std::vector<Color>& colors) {
    if (!lowContrast_) return;
    
    for (Color& color : colors) {
        // Reduce contrast by moving values toward middle
        color.r = 128 + (color.r - 128) * 0.7f;
        color.g = 128 + (color.g - 128) * 0.7f;
        color.b = 128 + (color.b - 128) * 0.7f;
    }
}

Color AsciiDithrer::getThemeColor(float luminance, float depth) {
    switch (colorTheme_) {
        case ColorTheme::MONOCHROME:
            return Color(luminance, luminance, luminance);
            
        case ColorTheme::CYBERPUNK:
            return Color(
                luminance * 0.8f + 50,  // Reddish
                luminance * 0.3f,       // Low green
                luminance * 0.9f + 30   // Blueish
            );
            
        case ColorTheme::CRT:
            return Color(
                luminance * 0.2f,       // Low red
                luminance * 0.9f + 20,  // Green dominant
                luminance * 0.3f        // Low blue
            );
            
        case ColorTheme::COMMAND_PROMPT:
            return Color(
                luminance * 0.9f,       // High white
                luminance * 0.9f,
                luminance * 0.9f
            );
            
        case ColorTheme::RETRO_GAME:
            return Color(
                luminance * 0.7f + 30,  // Warm red
                luminance * 0.6f + 20,  // Warm green
                luminance * 0.5f + 10   // Warm blue
            );
            
        case ColorTheme::CUSTOM:
        default:
            return Color(luminance, luminance, luminance);
    }
}

// Simple edge pixel detection using Sobel magnitude threshold
bool AsciiDithrer::isEdgePixel(const Image& image, int x, int y) {
    // Use Sobel filter for edge detection
    int w = image.getWidth();
    int h = image.getHeight();
    if (x <= 0 || y <= 0 || x >= w - 1 || y >= h - 1) return false;
    float gx = 0, gy = 0;
    float kernelX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    float kernelY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    for (int ky = -1; ky <= 1; ++ky) {
        for (int kx = -1; kx <= 1; ++kx) {
            float lum = getBrightness(image.getPixel(x + kx, y + ky));
            gx += kernelX[ky+1][kx+1] * lum;
            gy += kernelY[ky+1][kx+1] * lum;
        }
    }
    float mag = sqrt(gx*gx + gy*gy) / 1020.0f; // Normalize
    return mag > edgeThreshold_;
}

// Simple brightness to ASCII char mapping
char AsciiDithrer::brightnessToChar(float brightness, bool isEdge) {
    const char* ramp = charMap_.empty() ? luminance_chars : charMap_.c_str();
    int levels = strlen(ramp);
    int idx = clampi(int((brightness / 255.0f) * (levels - 1)), 0, levels - 1);
    if (isEdge && levels > 2) idx = levels - 1;
    return ramp[idx];
}

// Directional edge character selection
char AsciiDithrer::getDirectionalChar(float brightness, EdgeDirection direction) {
    switch (direction) {
        case EdgeDirection::VERTICAL: return '|';
        case EdgeDirection::HORIZONTAL: return '-';
        case EdgeDirection::DIAGONAL_1: return '/';
        case EdgeDirection::DIAGONAL_2: return '\\';
        default: return brightnessToChar(brightness, false);
    }
}

// Simple Sobel magnitude as edge strength
float AsciiDithrer::calculateEdgeStrength(const Image& image, int x, int y) {
    int w = image.getWidth();
    int h = image.getHeight();
    if (x <= 0 || y <= 0 || x >= w - 1 || y >= h - 1) return 0.0f;
    float gx = 0, gy = 0;
    float kernelX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    float kernelY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    for (int ky = -1; ky <= 1; ++ky) {
        for (int kx = -1; kx <= 1; ++kx) {
            float lum = getBrightness(image.getPixel(x + kx, y + ky));
            gx += kernelX[ky+1][kx+1] * lum;
            gy += kernelY[ky+1][kx+1] * lum;
        }
    }
    return sqrt(gx*gx + gy*gy) / 1020.0f;
}

bool AsciiDithrer::saveAsTextAdvanced(const Image& inputImage, const std::string& filename) {
    int width = inputImage.getWidth();
    int height = inputImage.getHeight();
    int tilesX = width / tileSize_;
    int tilesY = height / tileSize_;
    if (tilesX < 1 || tilesY < 1) return false;
    
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    // Use advanced tile analysis
    processTiles(inputImage);
    
    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            int tileIndex = ty * tilesX + tx;
            TileInfo tile = tileBuffer_[tileIndex];
            char asciiChar = selectTileCharacter(tile);
            if (asciiChar == 0) asciiChar = selectFont8x8Char(applyImageProcessing(tile.averageLuminance));
            file << asciiChar;
        }
        file << '\n';
    }
    file.close();
    return true;
}

bool AsciiDithrer::saveAsTextSimplified(const Image& inputImage, const std::string& filename) {
    int width = inputImage.getWidth();
    int height = inputImage.getHeight();
    int tileSize = 8;
    int tilesX = width / tileSize;
    int tilesY = height / tileSize;
    if (tilesX < 1 || tilesY < 1) return false;
    
    // Create a copy of the image for Gaussian blur
    Image blurredImage = inputImage;
    
    // Apply Gaussian blur to simplify the image
    std::vector<float> tempBuffer(width * height);
    std::vector<float> blurredBuffer(width * height);
    
    // Convert to luminance buffer
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color pixel = inputImage.getPixel(x, y);
            tempBuffer[y * width + x] = getBrightness(pixel);
        }
    }
    
    // Apply Gaussian blur (sigma = 2.0)
    float sigma = 2.0f;
    int kernelSize = 5;
    std::vector<float> kernel(kernelSize);
    float sum = 0.0f;
    
    for (int i = 0; i < kernelSize; ++i) {
        float x = (i - kernelSize/2) / sigma;
        kernel[i] = exp(-x*x/2.0f);
        sum += kernel[i];
    }
    
    // Normalize kernel
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i] /= sum;
    }
    
    // Horizontal blur
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sum = 0.0f;
            for (int k = 0; k < kernelSize; ++k) {
                int nx = x + k - kernelSize/2;
                nx = std::max(0, std::min(nx, width - 1));
                sum += tempBuffer[y * width + nx] * kernel[k];
            }
            blurredBuffer[y * width + x] = sum;
        }
    }
    
    // Vertical blur
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float sum = 0.0f;
            for (int k = 0; k < kernelSize; ++k) {
                int ny = y + k - kernelSize/2;
                ny = std::max(0, std::min(ny, height - 1));
                sum += blurredBuffer[ny * width + x] * kernel[k];
            }
            tempBuffer[y * width + x] = sum;
        }
    }
    
    // Character sets
    const char* luminanceChars = ". : c o P 0 ? @";
    const char* boundaryChars = "\\ | / _ - =";
    
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            // Calculate average brightness for this tile
            float totalBrightness = 0.0f;
            int pixelCount = 0;
            
            for (int dy = 0; dy < tileSize; ++dy) {
                for (int dx = 0; dx < tileSize; ++dx) {
                    int x = tx * tileSize + dx;
                    int y = ty * tileSize + dy;
                    if (x < width && y < height) {
                        totalBrightness += tempBuffer[y * width + x];
                        pixelCount++;
                    }
                }
            }
            
            float avgBrightness = totalBrightness / pixelCount;
            
            // Check if this tile has significant edges (boundaries)
            bool hasBoundary = false;
            float maxGradient = 0.0f;
            
            for (int dy = 0; dy < tileSize; ++dy) {
                for (int dx = 0; dx < tileSize; ++dx) {
                    int x = tx * tileSize + dx;
                    int y = ty * tileSize + dy;
                    if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
                        float gx = tempBuffer[y * width + (x + 1)] - tempBuffer[y * width + (x - 1)];
                        float gy = tempBuffer[(y + 1) * width + x] - tempBuffer[(y - 1) * width + x];
                        float gradient = sqrt(gx*gx + gy*gy);
                        maxGradient = std::max(maxGradient, gradient);
                    }
                }
            }
            
            hasBoundary = maxGradient > 30.0f; // Threshold for boundary detection
            
            char asciiChar;
            if (hasBoundary) {
                // Use boundary characters based on gradient direction
                int boundaryIndex = (int)(maxGradient / 50.0f) % 6; // 6 boundary characters
                asciiChar = boundaryChars[boundaryIndex * 2]; // Skip spaces in string
            } else {
                // Use luminance characters
                int luminanceLevels = 8; // 8 luminance characters
                int index = (int)((avgBrightness / 255.0f) * (luminanceLevels - 1));
                index = std::max(0, std::min(index, luminanceLevels - 1));
                asciiChar = luminanceChars[index * 2]; // Skip spaces in string
            }
            
            file << asciiChar;
        }
        file << '\n';
    }
    
    file.close();
    return true;
} 