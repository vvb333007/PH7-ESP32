/*
 * PlatformPHP - An ESP32 port and further development of the PH7 PHP Engine
 *
 * Copyright (c) 2026 Viacheslav Logunov
 * SPDX-License-Identifier: GPL
 *
 * Author:
 *   Viacheslav Logunov <vvb333007@gmail.com>
 *
 * Project:
 *   https://github.com/vvb333007/PH7-ESP32
 */

#include "ph7int.h"
/*
 * Implementation of xExpand callback for every constant >= 0; For constants which are < 0 use MinusConst
 *
 * Const(0) -- creates a function which returns 0
 * Const(0xff) -- returns 255
 * MinusConst(27) -- returns -27
 * MinusConst(0xff) -- returns -255
 *
 *
 * WARNING!!!: a Value_ argument MUST BE a simple number: 1,5, 0xffff, 0777; 
 * Not 89.3, -78, -0xff
 * 
 */

#define Const( Value_ ) \
void esp32_const_int ## Value_ ( ph7_value *pVal, void *pUserData ) { \
\
  SXUNUSED( pUserData ); \
  ph7_value_int( pVal, Value_ ); \
}

#define MinusConst( Value_ ) \
void esp32_const_mint ## Value_ ( ph7_value *pVal, void *pUserData ) { \
\
  SXUNUSED( pUserData ); \
  ph7_value_int( pVal, -Value_ ); \
}

Const(0)
Const(1)
Const(2)
Const(3)
Const(4)
Const(5)
Const(6)
Const(7)
Const(8)
Const(9)
Const(12)
Const(13)
Const(16)
Const(19)
Const(32)
Const(64)
Const(128)
Const(192)

MinusConst(1)

#undef Const
#undef MinusConst
