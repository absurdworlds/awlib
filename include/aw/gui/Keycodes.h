/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Keycodes_
#define _aw_Keycodes_

namespace aw {
//! Key code definitions (for future use)
enum class KeyCode : u8 {
	Unknown = 0x00,
	Escape    = 0x01,
	ScrollLock = 0x02,
	CapsLock  = 0x03,
	NumLock   = 0x04,
	Pause     = 0x07,
	BackSpace = 0x08,
	Tab       = 0x09,
	Clear     = 0x0B,
	Return    = 0x0D,
	Enter     = 0x0D,
	Kana      = 0x10,
	Kanji     = 0x12,
	SysReq    = 0x15,
	PrintScr  = 0x16,
	Space = 0x20,
	BracketL = 0x21,
	BracketR = 0x22,
	Semicolon = 0x26,
	Apostrophe = 0x27,
	BackSlash = 0x2B,
	Comma = 0x2C,
	Slash = 0x2D,
	Zero  = 0x30,  /*< Digit Zero  */
	One   = 0x31,  /*< Digit One   */
	Two   = 0x32,  /*< Digit Two   */
	Three = 0x33,  /*< Digit Three */
	Four  = 0x34,  /*< Digit Four  */
	Five  = 0x35,  /*< Digit Five  */
	Six   = 0x36,  /*< Digit Six   */
	Seven = 0x37,  /*< Digit Seven */
	Eight = 0x38,  /*< Digit Eight */
	Nine  = 0x39,  /*< Digit Nine  */
	Minus  = 0x3A,
	Equals  = 0x3B,
	A = 0x41, /*< Latin letter A */
	B = 0x42, /*< Latin letter B */
	C = 0x43, /*< Latin letter C */
	D = 0x44, /*< Latin letter D */
	E = 0x45, /*< Latin letter E */
	F = 0x46, /*< Latin letter F */
	G = 0x47, /*< Latin letter G */
	H = 0x48, /*< Latin letter H */
	I = 0x49, /*< Latin letter I */
	J = 0x4A, /*< Latin letter J */
	K = 0x4B, /*< Latin letter K */
	L = 0x4C, /*< Latin letter L */
	M = 0x4D, /*< Latin letter M */
	N = 0x4E, /*< Latin letter N */
	O = 0x4F, /*< Latin letter O */
	P = 0x50, /*< Latin letter P */
	Q = 0x51, /*< Latin letter Q */
	R = 0x52, /*< Latin letter R */
	S = 0x53, /*< Latin letter S */
	T = 0x54, /*< Latin letter T */
	U = 0x55, /*< Latin letter U */
	V = 0x56, /*< Latin letter V */
	W = 0x57, /*< Latin letter W */
	X = 0x58, /*< Latin letter X */
	Y = 0x59, /*< Latin letter Y */
	Z = 0x5A, /*< Latin letter Z */
	KeyPad0 = 0xB0, /*< Numeric keypad 0 */
	KeyPad1 = 0xB1, /*< Numeric keypad 1 */
	KeyPad2 = 0xB2, /*< Numeric keypad 2 */
	KeyPad3 = 0xB3, /*< Numeric keypad 3 */
	KeyPad4 = 0xB4, /*< Numeric keypad 4 */
	KeyPad5 = 0xB5, /*< Numeric keypad 5 */
	KeyPad6 = 0xB6, /*< Numeric keypad 6 */
	KeyPad7 = 0xB7, /*< Numeric keypad 7 */
	KeyPad8 = 0xB8, /*< Numeric keypad 8 */
	KeyPad9 = 0xB9, /*< Numeric keypad 9 */
	KeyPadDivide    = 0xBA,
	KeyPadMultiply  = 0xBB,
	KeyPadMinus     = 0xBC,
	KeyPadPlus      = 0xBD,
	KeyPadEnter     = 0xBE,
	KeyPadDecimal   = 0xBF,
	F1  = 0xC0,
	F2  = 0xC1,
	F3  = 0xC2,
	F4  = 0xC3,
	F5  = 0xC4,
	F6  = 0xC5,
	F7  = 0xC6,
	F8  = 0xC7,
	F9  = 0xC8,
	F10 = 0xC9,
	F11 = 0xCA,
	F12 = 0xCB,
	F13 = 0xCC,
	F14 = 0xCD,
	F15 = 0xCE,
	F16 = 0xCF,
	ShiftL = 0xE1,
	ShiftR = 0xE2,
	ControlL = 0xE3,
	ControlR = 0xE4,
	AltL = 0xE5,
	AltR = 0xE6,
	MenuL = 0xE7,
	MenuR = 0xE8,
	Up = 0xEA,
	Down = 0xEB,
	Left = 0xEC,
	Right = 0xED,
	PgUp = 0xEE,
	PgDn = 0xEF,
	End = 0xF0,
	Home = 0xF1,
	Insert = 0xF2,
	Delete = 0xF3,
};


} // namespace aw
#endif //_aw_Keycodes_
