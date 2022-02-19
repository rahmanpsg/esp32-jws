/*
 *
 * ElektronMart6x16
 *
 *
 * File Name           : ElektronMart6x16.h
 * Date                : 6 Sept 2019
 * Font width          : 6
 * Font height         : 16
 * Font first char     : 32
 * Font last char      : 127
 * Font used chars     : 94
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#ifndef ELEKTRONMART6x16_H
#define ELEKTRONMART6x16_H

#define ELEKTRONMART6x16_WIDTH 6
#define ELEKTRONMART6x16_HEIGHT 16

const static uint8_t ElektronMart6x16[] PROGMEM = {
    0x03, 0xD0, // size // size of zero indicates fixed width font, actual length is width * height
    0x06,       // width
    0x10,       // height
    0x30,       // first char
    0x0A,       // char count

    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06,

    // font data			   |
    0xfe, 0xfe, 0x06, 0x06, 0xfe, 0xfc, 0x3f, 0x7f, 0x60, 0x60, 0x7f, 0x7f, // 0
    0x00, 0x00, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x00, 0x00, // 1
    0x86, 0x86, 0x86, 0x86, 0xfe, 0xfc, 0x3f, 0x7f, 0x61, 0x61, 0x61, 0x61, // 2
    0x06, 0x86, 0x86, 0x86, 0xfe, 0xfc, 0x20, 0x61, 0x61, 0x61, 0x7f, 0x7f, // 3
    0xfe, 0xfe, 0x80, 0x80, 0xfe, 0xfc, 0x00, 0x01, 0x01, 0x01, 0x3f, 0x7f, // 4
    0xfe, 0xfe, 0x86, 0x86, 0x86, 0x84, 0x60, 0x61, 0x61, 0x61, 0x7f, 0x7f, // 5
    0xfe, 0xfe, 0x86, 0x86, 0x86, 0x84, 0x3f, 0x7f, 0x61, 0x61, 0x7f, 0x7f, // 6
    0x06, 0x06, 0x06, 0x06, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, // 7
    0xfe, 0xfe, 0x86, 0x86, 0xfe, 0xfc, 0x3f, 0x7f, 0x61, 0x61, 0x7f, 0x7f, // 8
    0xfe, 0xfe, 0x86, 0x86, 0xfe, 0xfc, 0x20, 0x61, 0x61, 0x61, 0x7f, 0x7f  // 9

};

#endif