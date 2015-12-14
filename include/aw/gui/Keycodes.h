/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Keycodes_qwerty_us__
#define aw_Keycodes_qwerty_us__
#include <aw/common/types.h>
namespace aw {
/*!
 * Keycodes, lossely based on key position on the keyboard.
 * Contains keycodes for US keyboard.
 */
enum class Keycode : u8 {
	Unknown    = 0x00,

	Escape     = 0x01,

	F1  = 0xA0,
	F2  = 0xA1,
	F3  = 0xA2,
	F4  = 0xA3,
	F5  = 0xA4,
	F6  = 0xA5,
	F7  = 0xA6,
	F8  = 0xA7,
	F9  = 0xA8,
	F10 = 0xA9,
	F11 = 0xAA,
	F12 = 0xAB,
	F13 = 0xAC,
	F14 = 0xAD,
	F15 = 0xAE,
	F16 = 0xAF,

	Print      = 0x02,
	ScrollLock = 0x03,
	Pause      = 0x04,

	Grave = 0x10,  /*< Key ` */
	One   = 0x11,  /*< Key 1 */
	Two   = 0x12,  /*< Key 2 */
	Three = 0x13,  /*< Key 3 */
	Four  = 0x14,  /*< Key 4 */
	Five  = 0x15,  /*< Key 5 */
	Six   = 0x16,  /*< Key 6 */
	Seven = 0x17,  /*< Key 7 */
	Eight = 0x18,  /*< Key 8 */
	Nine  = 0x19,  /*< Key 9 */
	Zero  = 0x1A,  /*< Key 0 */
	Minus = 0x1B,  /*< Key - */
	Equal = 0x1C,  /*< Key = */

	BackSpace  = 0x1D  /*< Backspace key */,

	Tab = 0x20,
	Q = 0x21, /*< Latin letter Q */
	W = 0x22, /*< Latin letter W */
	E = 0x23, /*< Latin letter E */
	R = 0x24, /*< Latin letter R */
	T = 0x25, /*< Latin letter T */
	Y = 0x26, /*< Latin letter Y */
	U = 0x27, /*< Latin letter U */
	I = 0x28, /*< Latin letter I */
	O = 0x29, /*< Latin letter O */
	P = 0x2A, /*< Latin letter P */
	BracketLeft  = 0x2B /*< Key [  */,
	BracketRight = 0x2C /*< Key ]  */,
	BackSlash    = 0x2D /*< Key \| */,
	Return       = 0x2E /*< Enter key */,
	CapsLock     = 0x2F /*< Caps lock key */,

	A = 0x30, /*< Latin letter A */
	S = 0x31, /*< Latin letter S */
	D = 0x32, /*< Latin letter D */
	F = 0x33, /*< Latin letter F */
	G = 0x34, /*< Latin letter G */
	H = 0x35, /*< Latin letter H */
	J = 0x36, /*< Latin letter J */
	K = 0x37, /*< Latin letter K */
	L = 0x38, /*< Latin letter L */
	Semicolon  = 0x39 /*< Key ;: */,
	Apostrophe = 0x3A /*< Key '" */,

	ShiftL = 0x3B /*< Left Shift key */,
	Z = 0x3C, /*< Latin letter Z */
	X = 0x3D, /*< Latin letter X */
	C = 0x3E, /*< Latin letter C */
	V = 0x3F, /*< Latin letter V */
	B = 0x41, /*< Latin letter B */
	N = 0x42, /*< Latin letter N */
	M = 0x43, /*< Latin letter M */
	Period = 0x44 /*< Key .< */,
	Comma  = 0x45 /*< Key ,> */,
	Slash  = 0x46 /*< Key /? */,
	ShiftR = 0x47 /*< Right Shift key */,

	ControlL = 0x50,
	SuperL   = 0x51,
	AltL     = 0x52,
	Space    = 0x53,
	AltR     = 0x54,
	SuperR   = 0x55,
	ControlR = 0x57,

	End    = 0xC0,
	Home   = 0xC1,
	Insert = 0xC2,
	Delete = 0xC3,
	Prior  = 0xC4, /*< Page Up   */
	Next   = 0xC5, /*< Page Down */

	Up    = 0xCA,
	Down  = 0xCB,
	Left  = 0xCC,
	Right = 0xCD,

	NumLock = 0x7F,
	KP_0 = 0x80, /*< Keypad 0 */
	KP_1 = 0x81, /*< Keypad 1 */
	KP_2 = 0x82, /*< Keypad 2 */
	KP_3 = 0x83, /*< Keypad 3 */
	KP_4 = 0x84, /*< Keypad 4 */
	KP_5 = 0x85, /*< Keypad 5 */
	KP_6 = 0x86, /*< Keypad 6 */
	KP_7 = 0x87, /*< Keypad 7 */
	KP_8 = 0x88, /*< Keypad 8 */
	KP_9 = 0x89, /*< Keypad 9 */
	KP_Divide    = 0x8A, /*< Keypad / */
	KP_Multiply  = 0x8B, /*< Keypad * */
	KP_Minus     = 0x8C, /*< Keypad - */
	KP_Plus      = 0x8D, /*< Keypad + */
	KP_Enter     = 0x8E, /*< Keypad Enter */
	KP_Decimal   = 0x8F, /*< Keypad . */
};
} // namespace aw
#endif //aw_Keycodes_qwerty_us__
