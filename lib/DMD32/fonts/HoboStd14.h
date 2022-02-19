/*
 * Fareed Read
 * http://www.facebook.com/fareed.reads
 *
 * HoboStd14
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : HoboStd14.h
 * Date                : 27.06.2018
 * Font size in bytes  : 11316
 * Font width          : 10
 * Font height         : 18
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
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
#include <pgmspace.h>

#ifndef HOBOSTD14_H
#define HOBOSTD14_H

#define HOBOSTD14_WIDTH 10
#define HOBOSTD14_HEIGHT 18

const static uint8_t HoboStd14[] PROGMEM = {
    0x2C, 0x34, // size
    0x0A,       // width
    0x12,       // height
    0x20,       // first char
    0x60,       // char count

    // char widths
    0x00, 0x03, 0x03, 0x08, 0x08, 0x09, 0x0B, 0x01, 0x05, 0x05,
    0x06, 0x07, 0x03, 0x04, 0x03, 0x06, 0x08, 0x03, 0x07, 0x07,
    0x08, 0x06, 0x08, 0x06, 0x08, 0x08, 0x03, 0x03, 0x07, 0x07,
    0x06, 0x05, 0x0B, 0x08, 0x08, 0x09, 0x08, 0x08, 0x07, 0x09,
    0x08, 0x03, 0x05, 0x08, 0x07, 0x0A, 0x08, 0x09, 0x08, 0x08,
    0x08, 0x07, 0x09, 0x08, 0x09, 0x0C, 0x09, 0x09, 0x09, 0x04,
    0x05, 0x04, 0x07, 0x08, 0x03, 0x07, 0x06, 0x06, 0x07, 0x07,
    0x05, 0x08, 0x06, 0x03, 0x04, 0x06, 0x03, 0x0A, 0x06, 0x07,
    0x06, 0x07, 0x05, 0x06, 0x05, 0x06, 0x07, 0x0A, 0x07, 0x07,
    0x05, 0x05, 0x02, 0x05, 0x07, 0x07,

    // font data
    0x7E, 0xFE, 0x06, 0x1C, 0x1D, 0x1C, 0x00, 0x00, 0x00,                                                                                                                                                                   // 33
    0x1E, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                                   // 34
    0x60, 0x60, 0xF8, 0x7C, 0x60, 0xF8, 0x7C, 0x60, 0x03, 0x1F, 0x0F, 0x03, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 35
    0x70, 0xFC, 0xCC, 0xFE, 0x8C, 0x9C, 0x0C, 0x00, 0x08, 0x1C, 0x18, 0x3F, 0x19, 0x19, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 36
    0x3C, 0x62, 0x62, 0x3C, 0xE0, 0x3C, 0x8E, 0x82, 0x00, 0x00, 0x00, 0x18, 0x0F, 0x01, 0x0F, 0x18, 0x18, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 37
    0x00, 0x9C, 0xFC, 0xE6, 0xE6, 0x3E, 0x1C, 0x80, 0xC0, 0xC0, 0xC0, 0x0E, 0x1F, 0x19, 0x19, 0x0F, 0x0F, 0x1F, 0x1B, 0x19, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                   // 38
    0x1E, 0x00, 0x00,                                                                                                                                                                                                       // 39
    0xF0, 0xFC, 0x0E, 0x06, 0x04, 0x03, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 40
    0x00, 0x00, 0x06, 0xFE, 0xF0, 0x08, 0x18, 0x1C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 41
    0x0C, 0x38, 0x3E, 0x1E, 0x3C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 42
    0x80, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 43
    0x00, 0x00, 0x00, 0x08, 0x3C, 0x1C, 0x00, 0x00, 0x00,                                                                                                                                                                   // 44
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                 // 45
    0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00,                                                                                                                                                                   // 46
    0x00, 0x00, 0xC0, 0x78, 0x1E, 0x06, 0x18, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 47
    0xF0, 0xFC, 0x0E, 0x06, 0x06, 0x0E, 0xFC, 0xF0, 0x03, 0x0F, 0x1C, 0x18, 0x18, 0x1C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 48
    0x04, 0xFE, 0xFE, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00,                                                                                                                                                                   // 49
    0x08, 0x1C, 0x86, 0xC6, 0xFE, 0x3C, 0x00, 0x1C, 0x1F, 0x1B, 0x19, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 50
    0x10, 0x0C, 0x8C, 0xCC, 0xEC, 0xBC, 0x0C, 0x08, 0x1C, 0x18, 0x18, 0x18, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 51
    0x80, 0xE0, 0x70, 0x1C, 0x8C, 0xE4, 0x10, 0x00, 0x03, 0x03, 0x03, 0x03, 0x1F, 0x1F, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 52
    0xF8, 0xFC, 0xCC, 0xCC, 0x8C, 0x04, 0x1D, 0x18, 0x18, 0x18, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 53
    0xE0, 0xF8, 0xCC, 0x6E, 0x66, 0xE6, 0xC6, 0x80, 0x03, 0x0F, 0x1C, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 54
    0x1C, 0x0C, 0xCC, 0xEC, 0x3C, 0x1C, 0x00, 0x0F, 0x1F, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 55
    0x00, 0x38, 0xFC, 0xC6, 0xC6, 0xFE, 0xBC, 0x00, 0x0E, 0x1F, 0x19, 0x18, 0x18, 0x19, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 56
    0x70, 0xFC, 0xCE, 0x86, 0x86, 0xCE, 0xFC, 0xF0, 0x00, 0x18, 0x19, 0x19, 0x1D, 0x0C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 57
    0x70, 0x70, 0x70, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00,                                                                                                                                                                   // 58
    0x70, 0x70, 0x70, 0x08, 0x3C, 0x1C, 0x00, 0x00, 0x00,                                                                                                                                                                   // 59
    0x80, 0x80, 0xC0, 0x40, 0x60, 0x30, 0x00, 0x01, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 60
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 61
    0x30, 0x60, 0x40, 0xC0, 0x80, 0x80, 0x18, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 62
    0x0C, 0xC6, 0xE6, 0xFE, 0x38, 0x1C, 0x1D, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 63
    0x80, 0x60, 0x10, 0xD8, 0xE8, 0x68, 0xE8, 0x48, 0x10, 0x30, 0xC0, 0x0F, 0x38, 0x27, 0x4F, 0x4C, 0x46, 0x67, 0x0C, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                   // 64
    0x80, 0xF0, 0xD8, 0xCC, 0xC6, 0xDC, 0xF8, 0x80, 0x1F, 0x1F, 0x13, 0x01, 0x01, 0x11, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 65
    0xFC, 0xFE, 0xCE, 0x46, 0x66, 0xFE, 0x9C, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 66
    0xE0, 0xF8, 0x1C, 0x0C, 0x06, 0x06, 0x06, 0x0E, 0x0C, 0x03, 0x0F, 0x0E, 0x1C, 0x18, 0x18, 0x18, 0x0C, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 67
    0xFE, 0xFE, 0x0E, 0x06, 0x0E, 0x1C, 0xF8, 0xC0, 0x1F, 0x1F, 0x1C, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 68
    0xF0, 0xFE, 0xEE, 0x66, 0xE6, 0x6E, 0x06, 0x00, 0x1F, 0x1F, 0x1C, 0x18, 0x18, 0x1C, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 69
    0xFE, 0xFE, 0xCE, 0xC6, 0xE6, 0x6E, 0x06, 0x1F, 0x1F, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 70
    0xE0, 0xF8, 0x1C, 0x0C, 0x06, 0x06, 0x86, 0x8E, 0x8C, 0x03, 0x0F, 0x0C, 0x18, 0x18, 0x18, 0x1D, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 71
    0xFC, 0xFE, 0xE2, 0x60, 0x60, 0x66, 0xFE, 0xF8, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 72
    0xFE, 0xFE, 0x02, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00,                                                                                                                                                                   // 73
    0x00, 0x00, 0x02, 0xFE, 0xFE, 0x08, 0x1C, 0x18, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 74
    0xFE, 0xFE, 0xC2, 0xE0, 0xF8, 0x9E, 0x0E, 0x02, 0x1F, 0x1F, 0x00, 0x00, 0x01, 0x1F, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 75
    0xF0, 0xFE, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1C, 0x18, 0x18, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 76
    0xFC, 0xFE, 0x0E, 0x3C, 0xF8, 0xF0, 0x3C, 0x0E, 0xFE, 0xFE, 0x1F, 0x1F, 0x18, 0x00, 0x03, 0x03, 0x00, 0x10, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                     // 77
    0xFC, 0xFE, 0x1E, 0x78, 0xE0, 0x82, 0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x00, 0x03, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 78
    0xC0, 0xF8, 0x3C, 0x0E, 0x06, 0x0E, 0x3C, 0xF8, 0xC0, 0x07, 0x0F, 0x1C, 0x18, 0x18, 0x18, 0x1C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 79
    0xFE, 0xFE, 0x8E, 0x86, 0xC6, 0x66, 0x3E, 0x1C, 0x1F, 0x1F, 0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 80
    0xF0, 0xFC, 0x0C, 0x86, 0x06, 0x0E, 0xFC, 0xF0, 0x03, 0x0F, 0x1C, 0x19, 0x1F, 0x1E, 0x0F, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 81
    0xFE, 0xFE, 0xC6, 0xC6, 0xE6, 0xA6, 0x3E, 0x1C, 0x1F, 0x1F, 0x11, 0x00, 0x03, 0x1F, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 82
    0x38, 0x7C, 0xE6, 0xC6, 0xC6, 0x8C, 0x00, 0x0F, 0x1C, 0x18, 0x18, 0x19, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 83
    0x18, 0x0E, 0x06, 0xF6, 0xFE, 0x0E, 0x06, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 84
    0xFE, 0xFE, 0x02, 0x00, 0x00, 0x02, 0xFE, 0xFE, 0x03, 0x0F, 0x1C, 0x18, 0x18, 0x1C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 85
    0x7E, 0xFE, 0x82, 0x00, 0x00, 0x00, 0x02, 0xFE, 0x7E, 0x00, 0x03, 0x0F, 0x0E, 0x1C, 0x0E, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 86
    0xFE, 0xFE, 0x00, 0x00, 0x80, 0xFE, 0xFE, 0x00, 0x00, 0x82, 0xFE, 0x3E, 0x00, 0x07, 0x1F, 0x0E, 0x07, 0x01, 0x03, 0x0F, 0x1E, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x00, 0x0E, 0x3E, 0xFE, 0xE0, 0xE0, 0x3E, 0x1E, 0x00, 0x18, 0x1E, 0x1F, 0x01, 0x01, 0x03, 0x1F, 0x1E, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 88
    0x0E, 0x3E, 0x7E, 0xE0, 0xC0, 0xC0, 0xF0, 0x3E, 0x0E, 0x00, 0x00, 0x1C, 0x1F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 89
    0x00, 0x0E, 0x86, 0xC6, 0xF6, 0x7E, 0x1E, 0x0E, 0x06, 0x18, 0x1E, 0x1F, 0x19, 0x18, 0x18, 0x18, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                       // 90
    0xFC, 0xFE, 0x06, 0x02, 0x0F, 0x1F, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                 // 91
    0x06, 0x3E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3E, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 92
    0x02, 0x06, 0xFE, 0xFC, 0x10, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                 // 93
    0x80, 0xE0, 0x38, 0x04, 0x38, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 95
    0x01, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                                   // 96
    0x60, 0x70, 0x30, 0x30, 0xB0, 0xE0, 0xC0, 0x0E, 0x0F, 0x19, 0x19, 0x19, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 97
    0xFC, 0xFE, 0x30, 0x30, 0xE0, 0xC0, 0x1F, 0x1F, 0x18, 0x18, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 98
    0x80, 0xE0, 0x60, 0x30, 0x30, 0x70, 0x07, 0x0F, 0x1C, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 99
    0x80, 0xE0, 0x70, 0x30, 0x32, 0xFE, 0xFC, 0x07, 0x0F, 0x1C, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 100
    0x80, 0xE0, 0x70, 0x30, 0xB0, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x19, 0x19, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 101
    0x30, 0xF8, 0xFE, 0x36, 0x36, 0x00, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 102
    0x00, 0xC0, 0xE0, 0x30, 0x30, 0xF8, 0xEC, 0x08, 0x0C, 0x1C, 0x1B, 0x1B, 0x0F, 0x0D, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 103
    0xFC, 0xFE, 0x32, 0x30, 0xF0, 0xE0, 0x1F, 0x1F, 0x00, 0x10, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 104
    0xF6, 0xF6, 0x00, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00,                                                                                                                                                                   // 105
    0x00, 0x06, 0xF6, 0xF0, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00,                                                                                                                                                 // 106
    0xFE, 0xFE, 0xC0, 0xF0, 0x30, 0x00, 0x1F, 0x1F, 0x01, 0x03, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 107
    0xFE, 0xFE, 0x02, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00,                                                                                                                                                                   // 108
    0xF0, 0xF0, 0x20, 0x30, 0xF0, 0xE0, 0x30, 0x30, 0xF0, 0xC0, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                     // 109
    0xF0, 0xF0, 0x30, 0x30, 0xF0, 0xE0, 0x1F, 0x1F, 0x00, 0x10, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 110
    0x80, 0xE0, 0x70, 0x30, 0x70, 0xE0, 0x80, 0x07, 0x0F, 0x1C, 0x18, 0x1C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 111
    0xF0, 0xF0, 0x30, 0x30, 0xE0, 0xE0, 0x1F, 0x1F, 0x02, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 112
    0xC0, 0xE0, 0x30, 0x30, 0x30, 0xF0, 0xF0, 0x00, 0x03, 0x07, 0x06, 0x02, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 113
    0xF0, 0xF0, 0x60, 0x30, 0x70, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 114
    0xE0, 0xF0, 0xB0, 0x30, 0x70, 0x20, 0x0E, 0x19, 0x19, 0x1B, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 115
    0x30, 0xF8, 0xFC, 0x34, 0x30, 0x00, 0x1F, 0x1F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 116
    0xF0, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0x07, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 117
    0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x07, 0x0E, 0x1C, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 118
    0xF0, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0xF0, 0xF0, 0x01, 0x07, 0x1E, 0x0E, 0x03, 0x0F, 0x1E, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                     // 119
    0x00, 0xF0, 0xF0, 0xC0, 0xC0, 0xF0, 0x10, 0x18, 0x1E, 0x03, 0x03, 0x07, 0x1E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 120
    0x70, 0xF0, 0x80, 0x00, 0x00, 0xF0, 0x70, 0x18, 0x19, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 121
    0x10, 0x30, 0xB0, 0xF0, 0x70, 0x1C, 0x1F, 0x1B, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 122
    0xC0, 0xFC, 0xFE, 0x02, 0x02, 0x00, 0x0F, 0x1F, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 123
    0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0,                                                                                                                                                                                     // 124
    0x02, 0x02, 0xFE, 0xFC, 0xC0, 0x10, 0x10, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                                               // 125
    0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                           // 126
    0xF8, 0x38, 0x48, 0x88, 0x68, 0x18, 0xF8, 0x1F, 0x1C, 0x12, 0x11, 0x16, 0x18, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                                                                                            // 127

};

#endif