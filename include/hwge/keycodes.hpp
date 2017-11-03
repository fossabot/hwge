#pragma once

/*
 *
 * Sources: http://www.glfw.org/docs/latest/group__keys.html and https://wiki.libsdl.org/SDLKeycodeLookup
 * 
*/

#define HWGE_KEY_UNKNOWN -1
#define HWGE_KEY_SPACE 32
#define HWGE_KEY_EXCLAIM 33 // !
#define HWGE_KEY_QUOTEDBL 34 // Maybe "
#define HWGE_KEY_HASH 35 // #
#define HWGE_KEY_DOLLAR 36 // $
#define HWGE_KEY_PERCENT 37 // %
#define HWGE_KEY_AMPERSAND 38 // &
#define HWGE_KEY_QUOTE 39 // '
#define HWGE_KEY_LEFT_PAREN 40 // (
#define HWGE_KEY_RIGHT_PAREN 41 // )
#define HWGE_KEY_RIGHT_ASTERISK 42 // )
#define HWGE_KEY_PLUS 43 // )
#define HWGE_KEY_COMMA 44 // ,
#define HWGE_KEY_MINUS 45 // -
#define HWGE_KEY_PERIOD 46 // .
#define HWGE_KEY_SLASH 47 // /
#define HWGE_KEY_0 48
#define HWGE_KEY_1 49
#define HWGE_KEY_2 50
#define HWGE_KEY_3 51
#define HWGE_KEY_4 52
#define HWGE_KEY_5 53
#define HWGE_KEY_6 54
#define HWGE_KEY_7 55
#define HWGE_KEY_8 56
#define HWGE_KEY_9 57
#define HWGE_KEY_COLON 58 // :
#define HWGE_KEY_SEMICOLON 59 // ;
#define HWGE_KEY_LESS 60 // <
#define HWGE_KEY_EQUAL 61 // =
#define HWGE_KEY_GREATER 62 // >
#define HWGE_KEY_QUESTION 63 // ?
#define HWGE_KEY_AT 64 // @
#define HWGE_KEY_A 65
#define HWGE_KEY_B 66
#define HWGE_KEY_C 67
#define HWGE_KEY_D 68
#define HWGE_KEY_E 69
#define HWGE_KEY_F 70
#define HWGE_KEY_G 71
#define HWGE_KEY_H 72
#define HWGE_KEY_I 73
#define HWGE_KEY_J 74
#define HWGE_KEY_K 75
#define HWGE_KEY_L 76
#define HWGE_KEY_M 77
#define HWGE_KEY_N 78
#define HWGE_KEY_O 79
#define HWGE_KEY_P 80
#define HWGE_KEY_Q 81
#define HWGE_KEY_R 82
#define HWGE_KEY_S 83
#define HWGE_KEY_T 84
#define HWGE_KEY_U 85
#define HWGE_KEY_V 86
#define HWGE_KEY_W 87
#define HWGE_KEY_X 88
#define HWGE_KEY_Y 89
#define HWGE_KEY_Z 90
#define HWGE_KEY_LEFT_BRACKET 91 // [
#define HWGE_KEY_BACKSLASH 92 // \ 
#define HWGE_KEY_RIGHT_BRACKET 93 // ]
#define HWGE_KEY_CARET 94 // ^
#define HWGE_KEY_UNDERSCORE 95 // _
#define HWGE_KEY_GRAVE_ACCENT 96 // `
#define HWGE_KEY_WORLD_1 161 /* non-US #1 */
#define HWGE_KEY_WORLD_2 162 /* non-US #2 */
#define HWGE_KEY_ESCAPE 256
#define HWGE_KEY_ENTER 257
#define HWGE_KEY_TAB 258
#define HWGE_KEY_BACKSPACE 259
#define HWGE_KEY_INSERT 260
#define HWGE_KEY_DELETE 261
#define HWGE_KEY_RIGHT 262
#define HWGE_KEY_LEFT 263
#define HWGE_KEY_DOWN 264
#define HWGE_KEY_UP 265
#define HWGE_KEY_PAGE_UP 266
#define HWGE_KEY_PAGE_DOWN 267
#define HWGE_KEY_HOME 268
#define HWGE_KEY_END 269
#define HWGE_KEY_CAPS_LOCK 280
#define HWGE_KEY_SCROLL_LOCK 281
#define HWGE_KEY_NUM_LOCK 282
#define HWGE_KEY_PRINT_SCREEN 283
#define HWGE_KEY_PAUSE 284
#define HWGE_KEY_F1 290
#define HWGE_KEY_F2 291
#define HWGE_KEY_F3 292
#define HWGE_KEY_F4 293
#define HWGE_KEY_F5 294
#define HWGE_KEY_F6 295
#define HWGE_KEY_F7 296
#define HWGE_KEY_F8 297
#define HWGE_KEY_F9 298
#define HWGE_KEY_F10 299
#define HWGE_KEY_F11 300
#define HWGE_KEY_F12 301
#define HWGE_KEY_F13 302
#define HWGE_KEY_F14 303
#define HWGE_KEY_F15 304
#define HWGE_KEY_F16 305
#define HWGE_KEY_F17 306
#define HWGE_KEY_F18 307
#define HWGE_KEY_F19 308
#define HWGE_KEY_F20 309
#define HWGE_KEY_F21 310
#define HWGE_KEY_F22 311
#define HWGE_KEY_F23 312
#define HWGE_KEY_F24 313
#define HWGE_KEY_F25 314
#define HWGE_KEY_KP_0 320
#define HWGE_KEY_KP_1 321
#define HWGE_KEY_KP_2 322
#define HWGE_KEY_KP_3 323
#define HWGE_KEY_KP_4 324
#define HWGE_KEY_KP_5 325
#define HWGE_KEY_KP_6 326
#define HWGE_KEY_KP_7 327
#define HWGE_KEY_KP_8 328
#define HWGE_KEY_KP_9 329
#define HWGE_KEY_KP_DECIMAL 330
#define HWGE_KEY_KP_DIVIDE 331
#define HWGE_KEY_KP_MULTIPLY 332
#define HWGE_KEY_KP_SUBTRACT 333
#define HWGE_KEY_KP_ADD 334
#define HWGE_KEY_KP_ENTER 335
#define HWGE_KEY_KP_EQUAL 336
#define HWGE_KEY_LEFT_SHIFT 340
#define HWGE_KEY_LEFT_CONTROL 341
#define HWGE_KEY_LEFT_ALT 342
#define HWGE_KEY_LEFT_SUPER 343
#define HWGE_KEY_RIGHT_SHIFT 344
#define HWGE_KEY_RIGHT_CONTROL 345
#define HWGE_KEY_RIGHT_ALT 346
#define HWGE_KEY_RIGHT_SUPER 347
#define HWGE_KEY_MENU 348
#define HWGE_KEY_LAST HWGE_KEY_MENU