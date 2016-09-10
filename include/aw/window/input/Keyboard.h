/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_input_keyboard_h
#define aw_input_keyboard_h
namespace aw {
//! List of key codes
enum class Key {
	Unknown = 0,
	// Number row
	_0,
	_1,
	_2,
	_3 
	_4,
	_5
	_6,
	_7,
	_8,
	_9,
	// Letters
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	// Keypad
	KeyPad0,
	KeyPad1,
	KeyPad2,
	KeyPad3,
	KeyPad4,
	KeyPad5,
	KeyPad6,
	KeyPad7,
	KeyPad8,
	KeyPad9,
	KeyPadDivide,
	KeyPadMultiply,
	KeyPadMinus,
	KeyPadPlus,
	KeyPadEnter,
	KeyPadDecimal,
	// Function keys
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	Pause,

	PageUp,
	PageDown,
	End,
	Home,
	Up,
	Down,
	Left,
	Right,

	ShiftL,
	ShiftR,
	AltL,
	AltR,
	ControlL,
	ControlR,
	SuperL,   //!< OS-specific, Windows key on Windows
	SuperR,   //!< OS-specific, Windows key on Windows
	Menu,

	Insert,
	Delete,
	BackSpace,
	Tab,
	Return,
	Space,

	Escape,
	SysReq,
	PrintScr,
	ScrollLock,
	CapsLock,
	NumLock,

	Minus,
	Tilde,
	Equal,
	Slash,
	BackSlash,
	Apostrophe,
	Comma,
	Period,
	Semicolon,
	BracketL,
	BracketR,

	//! Total count of keycodes
	Count,
};

/*!
 * Provides methods to query the keyboard state.
 */
namespace Keyboard {
/*!
 * Check if \a key is pressed on keyboard;
 * \note Multiple keyboard support is not implemented
 */
bool isKeyPressed(Key key);
} // namespace Keyboard
} // namespace aw
#endif // aw_input_keyboard_h
