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

/* This file contains native bindings to the Arduino Core functions (a selection, not all of the Arduino Core)
 * Bindings to functions like pinMode() or digitalWrite() are implemented here
 *
 */
#include "ph7int.h"
#ifdef ESP32
#include <Arduino.h>
#endif

#ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC

int esp32_builtin_pinMode(ph7_context *pCtx, int nArg, ph7_value **apArg) {

  if (nArg >= 2 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
    int mode = ph7_value_to_int(apArg[1]);
#ifdef __CYGWIN__
    printf("pinMode(%d, %d) called\r\n", pin, mode);
#else
    pinMode(pin, mode);
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_null(pCtx);
  return PH7_OK;
}

int esp32_builtin_digitalWrite(ph7_context *pCtx, int nArg, ph7_value **apArg) {

  if (nArg >= 2 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
    int value = ph7_value_to_int(apArg[1]);
#ifdef __CYGWIN__
    printf("digitalWrite(%d, %d) called\r\n", pin, value);
#else
    digitalWrite(pin, value);
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_null(pCtx);
  return PH7_OK;
}

int esp32_builtin_digitalRead(ph7_context *pCtx, int nArg, ph7_value **apArg) {

  int value = -1;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalRead(%d) called\r\n", pin);
#else
    value = digitalRead( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_int(pCtx, value);
  return PH7_OK;
}
#endif

#if 0
#ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC
int esp32_builtin_gpio_config(ph7_context *ctx, int argc, ph7_value **argv) {  return PH7_OK; }

int esp32_builtin_gpio_get_drive_capability(ph7_context *ctx, int argc, ph7_value **argv) { return PH7_OK; }
int esp32_builtin_gpio_get_io_config(ph7_context *ctx, int argc, ph7_value **argv)  { return PH7_OK; }
int esp32_builtin_gpio_get_level(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_hold_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_hold_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_install_isr_service(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_uninstall_isr_service(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_intr_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_intr_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_isr_handler_add(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_isr_handler_remove(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_isr_register(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_iomux_input(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_iomux_output(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_func_sel(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_pulldown_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_pulldown_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_pullup_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_pullup_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_od_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_od_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_input_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_input_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_output_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_output_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_reset_pin(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_set_direction(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_set_drive_capability(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_set_intr_type(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_set_level(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_set_pull_mode(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_sleep_sel_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_sleep_sel_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_sleep_set_direction(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_sleep_set_pull_mode(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_deep_sleep_hold_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_deep_sleep_hold_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_deep_sleep_wakeup_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_deep_sleep_wakeup_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_force_hold_all(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_force_unhold_all(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int esp32_builtin_gpio_wakeup_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int esp32_builtin_gpio_wakeup_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
#endif
#endif
