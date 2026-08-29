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

/* This file contains native bindings to the Arduino Core functions + some of ESP-IDF functions
 * 
 *
 */
#include "ph7int.h"
#include "builtins.h"

#define Impl( Name_ , pCtx_ , nArg_, apArg_) \
esp32_builtin_ ## Name_ (ph7_context *pCtx_, int nArg_, ph7_value **apArg_)


#ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC
# ifdef ESP32
#  include <Arduino.h>
# endif

// pinMode(int $pin, int $mode)
//
int Impl(pinMode, pCtx, nArg, apArg) {

  if (nArg >= 2 && ph7_value_is_numeric(apArg[0])) {

    unsigned int pin = (unsigned int)ph7_value_to_int(apArg[0]);
    int mode = ph7_value_to_int(apArg[1]);
#ifdef __CYGWIN__
    printf("pinMode(%u, %u) called\r\n", pin, mode);
#else
    pinMode(pin, mode);
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_null(pCtx);
  return PH7_OK;
}

// digitalWrite($pin, $value)
//
int Impl(digitalWrite, pCtx, nArg, apArg) {

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

// int $value = digitalRead(int $pin)
//
int Impl(digitalRead, pCtx, nArg, apArg) {

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


// bool $ret = digitalPinIsInvalid($pin)
//
int Impl(digitalPinIsValid, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinIsValid(%d) called\r\n", pin);
#else
    value = digitalPinIsValid( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;
}

// bool digitalPinCanOutput($pin)
//
int Impl(digitalPinCanOutput, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinCanOutput(%d) called\r\n", pin);
#else
    value = digitalPinCanOutput( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;

}

// $rtc_pin = digitalPinToRtcPin($pin)
//
int Impl(digitalPinToRtcPin, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinToRtcPin(%d) called\r\n", pin);
#else
    value = digitalPinToRtcPin( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;

}

// $chan = digitalPinToDacChannel($pin)
//
int Impl(digitalPinToDacChannel, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinToDacChannel(%d) called\r\n", pin);
#else
    value = digitalPinToDacChannel( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;

}

// $chan = digitalPinToTouchChannel($pin)
//
int Impl(digitalPinToTouchChannel, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinToTouchChannel(%d) called\r\n", pin);
#else
    value = digitalPinToTouchChannel( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;

}

// $chan = digitalPinToAnalogChannel($pin)
//
int Impl(digitalPinToAnalogChannel, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int pin = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("digitalPinToAnalogChannel(%d) called\r\n", pin);
#else
    value = digitalPinToAnalogChannel( pin );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing GPIO number");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;

}

// $digi_pin = analogChannelToDigitalPin($ana_pin);
//
int Impl(analogChannelToDigitalPin, pCtx, nArg, apArg) {
  int value = 0;

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    int channel = ph7_value_to_int(apArg[0]);
#ifdef __CYGWIN__
    printf("analogChannelToDigitalPin(%d) called\r\n", channel);
#else
    value = analogChannelToDigitalPin( channel );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_int(pCtx, value);

  return PH7_OK;
}

//
//
int Impl(shiftIn, pCtx, nArg, apArg) {
  return PH7_OK;
}

//
//
int Impl(shiftOut, pCtx, nArg, apArg) {
  return PH7_OK;
}

// $res = makeWord($a)
// $res = makeWord($a, $b)
//
int Impl(makeWord, pCtx, nArg, apArg) {
  return PH7_OK;
}

// random($upper_limit)
// random($lower_limit, $upper_limit)
//
int Impl(random, pCtx, nArg, apArg) {

  long min = 0, max;

  if (nArg == 1 && ph7_value_is_numeric(apArg[0])) {

    max = (long)ph7_value_to_int(apArg[0]);

  } else if (nArg == 2 && ph7_value_is_numeric(apArg[0]) && ph7_value_is_numeric(apArg[1])) {

    min = (long)ph7_value_to_int(apArg[0]);
    max = (long)ph7_value_to_int(apArg[1]);

  } else {

    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
    return PH7_OK;
  }

#ifdef __CYGWIN__
  printf("random(%d, %d) called\r\n", min, max);
#else
  if (min < max)
    min = (esp_random() % (howbig - howsmall) + howsmall);
#endif

  ph7_result_int(pCtx, min);
  return PH7_OK;
}
// randomSeed();
// No-op: we use HWRNG which requires no seeding
//
int Impl(randomSeed, pCtx, nArg, apArg) {

  SXUNUSED(pCtx);
  SXUNUSED(nArg);
  SXUNUSED(apArg);

  return PH7_OK;
}

// useRealRandomGenerator();
// No-op: we use HWRNG always, no software PRNG fallback
//
int Impl(useRealRandomGenerator, pCtx, nArg, apArg) {

  SXUNUSED(pCtx);
  SXUNUSED(nArg);
  SXUNUSED(apArg);

  return PH7_OK;
}


//$scaled_x = map( long $x, long $in_min, long $in_max, long $out_min, long $out_max) {
//
int Impl(map, pCtx, nArg, apArg) {

  long ret;

  if (nArg == 5) {

    long x = (long)ph7_value_to_int(apArg[0]);
    long in_min = (long)ph7_value_to_int(apArg[1]);
    long in_max = (long)ph7_value_to_int(apArg[2]);
    long out_min = (long)ph7_value_to_int(apArg[3]);
    long out_max = (long)ph7_value_to_int(apArg[4]);

    const long run = in_max - in_min;

    if (run == 0)
      ret = -1;
    else {
      const long rise = out_max - out_min;
      const long delta = x - in_min;
      ret = (delta * rise) / run + out_min;
    }

    ph7_result_int(pCtx, ret);
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
    return PH7_OK;
  }

  return PH7_OK;
}

// $tim = micros();
//
int Impl(micros, pCtx, nArg, apArg) {

  SXUNUSED(nArg);
  SXUNUSED(apArg);
#ifdef __CYGWIN__
  SXUNUSED(pCtx);
  printf("micros() called\r\n");
#else
  ph7_result_int64(pCtx, micros());
#endif
  return PH7_OK;
}

// $tim = millis();
//
int Impl(millis, pCtx, nArg, apArg) {

  SXUNUSED(nArg);
  SXUNUSED(apArg);
#ifdef __CYGWIN__
  SXUNUSED(pCtx);
  printf("millis() called\r\n");
#else
  ph7_result_int64(pCtx, millis());
#endif
  return PH7_OK;
}

// delay($millis);
//
int Impl(delay, pCtx, nArg, apArg) {

  if (nArg >= 1 && ph7_value_is_numeric(apArg[0])) {

    unsigned int interval = (unsigned int)ph7_value_to_int(apArg[0]); // TODO: int64 ?
#ifdef __CYGWIN__
    printf("delay(%u) called\r\n", interval);
#else
    delay( interval );
#endif
  } else {
    ph7_context_throw_error(pCtx, PH7_CTX_WARNING, "Missing numeric argument");
  }

  ph7_result_null(pCtx);
  return PH7_OK;
}


// $v = pulseIn($pin, $state, $timeout);
//
int Impl(pulseIn, pCtx, nArg, apArg) {
//unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  return PH7_OK;
}

// $v = pulseInLong($pin, $state, $timeout);
//
int Impl(pulseInLong, pCtx, nArg, apArg) {
//unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout) {
  return PH7_OK;
}

#endif // ARDUINO

#ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC
#if 0
/**
 * @brief Structure that contains the configuration of an IO
 */

$config = array(
  'fun_sel' => 0,                   /*!< Value of IOMUX function selection */
  'sig_out' => 0,                   /*!< Index of the outputting peripheral signal */
  'drv' => 1,                       /*!< Value of drive strength */
  'pu' => 0,                        /*!< Status of pull-up enabled or not */
  'pd' => 0,                        /*!< Status of pull-down enabled or not */
  'ie' => 0,                        /*!< Status of input enabled or not */
  'oe' => 1,                        /*!< Status of output enabled or not */
  'oe_ctrl_by_periph' = 0,          /*!< True if use output enable signal from peripheral, otherwise False */
  'oe_inv' = 0,                     /*!< Whether the output enable signal is inversed or not */
  'od' = 0,                         /*!< Status of open-drain enabled or not */
  'slp_sel' = 0                     /*!< Status of pin sleep mode enabled or not */
);

int Impl(gpio_reset_pin(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_config(ph7_context *ctx, int argc, ph7_value **argv) {  return PH7_OK; }
int Impl(gpio_get_io_config(ph7_context *ctx, int argc, ph7_value **argv)  { return PH7_OK; }

int Impl(gpio_get_drive_capability(ph7_context *ctx, int argc, ph7_value **argv) { return PH7_OK; }
int Impl(gpio_set_drive_capability(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_get_level(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_set_level(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_set_direction(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_iomux_input(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_iomux_output(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_func_sel(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_pulldown_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_pulldown_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_pullup_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_pullup_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_set_pull_mode(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_od_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_od_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_input_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_input_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_output_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_output_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_sleep_sel_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_sleep_sel_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_sleep_set_direction(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_sleep_set_pull_mode(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_hold_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_hold_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_deep_sleep_hold_dis(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_deep_sleep_hold_en(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_deep_sleep_wakeup_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_deep_sleep_wakeup_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_force_hold_all(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_force_unhold_all(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_wakeup_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_wakeup_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

int Impl(gpio_install_isr_service(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_uninstall_isr_service(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_intr_disable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_intr_enable(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_isr_handler_add(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_isr_handler_remove(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_isr_register(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }
int Impl(gpio_set_intr_type(ph7_context *ctx, int argc, ph7_value **argv) {   return PH7_OK; }

#endif
#endif // ESP-IDF


#ifndef PH7_DISABLE_ESP32_FREERTOS_FUNC
#if 0
int Impl(vTaskDelay(ph7_context *ctx, int argc, ph7_value **argv) {
  return PH7_OK;
}
#endif
#endif


#undef Impl

