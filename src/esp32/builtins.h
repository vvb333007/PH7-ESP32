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

#pragma once

#include "ph7int.h"

#define Have(Name_) \
int esp32_builtin_ ## Name_ (ph7_context *pCtx, int nArg, ph7_value **apArg);

#ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC

/* What do we have?
 * The list of supported Arduino Core functions (declarations only. Implemented in builtins.c)
 */
Have( shiftIn )
Have( shiftOut )
Have( makeWord )
Have( random )
Have( randomSeed )
Have( map )
Have( micros )
Have( millis )
Have( delay )
Have( delayMicroseconds )
Have( pulseIn )
Have( pulseInLong )

Have( pinMode )
Have( digitalWrite )
Have( digitalRead )

Have( digitalPinIsValid )
Have( digitalPinCanOutput )
Have( digitalPinToRtcPin )
Have( digitalPinToDacChannel )
Have( digitalPinToTouchChannel )
Have( digitalPinToAnalogChannel )
Have( analogChannelToDigitalPin )

//Have( analogRead )
//Have( analogReadResolution )
//Have( analogReadMilliVolts )
//Have( analogWrite )
//Have( analogWriteResolution )
//Have( analogWriteFrequency )
//Have( analogSetAttenuation )
//Have( analogSetPinAttenuation )
//Have( analogSetWidth )

//Have( attachInterrupt )
//Have( attachInterruptArg )
//Have( detachInterrupt )
//Have( enableInterrupt )
//Have( disableInterrupt )

//Have( ledcAttach )
//Have( ledcAttachChannel )
//Have( ledcChangeFrequency )
//Have( ledcDetach )
//Have( ledcFade )
//Have( ledcGetClockSource )
//Have( ledcOutputInvert )
//Have( ledcRead )
//Have( ledcReadFreq )
//Have( ledcSetClockSource )
//Have( ledcWrite )
//Have( ledcWriteChannel )
//Have( ledcWriteNote )
//Have( ledcWriteTone )

//Have( analogContinuous )
//Have( analogContinuousDeinit )
//Have( analogContinuousRead )
//Have( analogContinuousSetAtten )
//Have( analogContinuousSetWidth )
//Have( analogContinuousStart )
//Have( analogContinuousStop )

//Have( i2cDeinit )
//Have( i2cGetClock )
//Have( i2cInit )
//Have( i2cIsInit )
//Have( i2cRead )
//Have( i2cSetClock )
//Have( i2cWrite )
//Have( i2cWriteReadNonStop )

//Have( getApbFrequency )
//Have( getCpuFrequencyMhz )
//Have( getXtalFrequencyMhz )
//Have( setCpuFrequencyMhz )

//Have( isAlpha )
//Have( isAlphaNumeric )
//Have( isAscii )
//Have( isControl )
//Have( isDigit )
//Have( isGraph )
//Have( isHexadecimalDigit )
//Have( isLowerCase )
//Have( isPrintable )
//Have( isPunct )
//Have( isSpace )
//Have( isUpperCase )
//Have( isWhitespace )

//Have( toAscii )
//Have( toLowerCase )
//Have( toUpperCase )



//Have( rmtDeinit )
//Have( rmtInit )
//Have( rmtRead )
//Have( rmtReadAsync )
//Have( rmtReceiveCompleted )
//Have( rmtSetCarrier )
//Have( rmtSetEOT )
//Have( rmtSetRxMaxThreshold )
//Have( rmtSetRxMinThreshold )
//Have( rmtTransmitCompleted )
//Have( rmtWrite )
//Have( rmtWriteAsync )
//Have( rmtWriteLooping )
//Have( rmtWriteRepeated )





//Have( sigmaDeltaAttach )
//Have( sigmaDeltaDetach )
//Have( sigmaDeltaWrite )

//Have( temperatureRead )


//Have( touchAttachInterrupt )
//Have( touchAttachInterruptArg )
//Have( touchDetachInterrupt )
//Have( touchInterruptGetLastStatus )
//Have( touchInterruptSetThresholdDirection )

//Have( touchRead )
//Have( touchSetConfig )
//Have( touchSetDefaultThreshold )
//Have( touchSetTiming )
//Have( touchSleepWakeUpEnable )

  


//Have( uartAvailable )
//Have( uartAvailableForWrite )
//Have( uartBegin )
//Have( uartDetectBaudrate )
//Have( uartEnableRxInternalPull )
//Have( uartEnd )
//Have( uartFlush )
//Have( uartFlushTxOnly )
//Have( uartGetBaudRate )
//Have( uartGetDebug )
//Have( uartIsDriverInstalled )
//Have( uartPeek )
//Have( uartPinSignalInversion )
//Have( uartRead )
//Have( uartReadBytes )
//Have( uartSetBaudRate )
//Have( uartSetClockSource )
//Have( uartSetCtsInvert )
//Have( uartSetDebug )
//Have( uartSetFastReading )
//Have( uartSetHwFlowCtrlMode )
//Have( uartSetIrdaDirection )
//Have( uartSetMode )
//Have( uartSetPins )
//Have( uartSetRtsInvert )
//Have( uartSetRxFIFOFull )
//Have( uartSetRxInvert )
//Have( uartSetRxTimeout )
//Have( uartSetTxInvert )
//Have( uartStartDetectBaudrate )
//Have( uartWrite )
//Have( uartWriteBuf )
#endif // #ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC

#ifndef PH7_DISABLE_ESP32_FREERTOS_FUNC
/* What do we have?
 * FreeRTOS bindings. Useful stuff like queues, events etc
 */
//Have( vTaskDelay )
#endif // #ifndef PH7_DISABLE_ESP32_FREERTOS_FUNC

#ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC
/* What do we have?
 * Selected subset of ESP-IDF functions. There are too many :(
 */
//Have( gpio_config )
//Have( gpio_get_drive_capability )
//Have( gpio_get_io_config )
//Have( gpio_get_level )
//Have( gpio_hold_dis )
//Have( gpio_hold_en )
//Have( gpio_install_isr_service )
//Have( gpio_uninstall_isr_service )
//Have( gpio_intr_disable )
//Have( gpio_intr_enable )
//Have( gpio_isr_handler_add )
//Have( gpio_isr_handler_remove )
//Have( gpio_isr_register )
//Have( gpio_iomux_input )
//Have( gpio_iomux_output )
//Have( gpio_func_sel )
//Have( gpio_pulldown_dis )
//Have( gpio_pulldown_en )
//Have( gpio_pullup_dis )
//Have( gpio_pullup_en )
//Have( gpio_od_enable )
//Have( gpio_od_disable )
//Have( gpio_input_enable )
//Have( gpio_input_disable )
//Have( gpio_output_enable )
//Have( gpio_output_disable )
//Have( gpio_reset_pin )
//Have( gpio_set_direction )
//Have( gpio_set_drive_capability )
//Have( gpio_set_intr_type )
//Have( gpio_set_level )
//Have( gpio_set_pull_mode )
//Have( gpio_sleep_sel_dis )
//Have( gpio_sleep_sel_en )
//Have( gpio_sleep_set_direction )
//Have( gpio_sleep_set_pull_mode )
//Have( gpio_deep_sleep_hold_dis )
//Have( gpio_deep_sleep_hold_en )
//Have( gpio_deep_sleep_wakeup_disable )
//Have( gpio_deep_sleep_wakeup_enable )
//Have( gpio_force_hold_all )
//Have( gpio_force_unhold_all )
//Have( gpio_wakeup_disable )
//Have( gpio_wakeup_enable )
#endif // #ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC

#undef Have
