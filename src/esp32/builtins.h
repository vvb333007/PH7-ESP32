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

int esp32_builtin_pinMode(ph7_context *pCtx, int nArg, ph7_value **apArg);
int esp32_builtin_digitalWrite(ph7_context *pCtx, int nArg, ph7_value **apArg);
int esp32_builtin_digitalRead(ph7_context *pCtx, int nArg, ph7_value **apArg);





#if 0
int esp32_builtin_gpio_config(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_get_drive_capability(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_get_io_config(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_get_level(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_hold_dis(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_hold_en(ph7_context *, int , ph7_value **);


int esp32_builtin_gpio_install_isr_service(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_uninstall_isr_service(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_intr_disable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_intr_enable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_isr_handler_add(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_isr_handler_remove(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_isr_register(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_iomux_input(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_iomux_output(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_func_sel(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_pulldown_dis(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_pulldown_en(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_pullup_dis(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_pullup_en(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_od_enable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_od_disable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_input_enable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_input_disable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_output_enable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_output_disable(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_reset_pin(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_set_direction(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_set_drive_capability(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_set_intr_type(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_set_level(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_set_pull_mode(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_sleep_sel_dis(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_sleep_sel_en(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_sleep_set_direction(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_sleep_set_pull_mode(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_deep_sleep_hold_dis(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_deep_sleep_hold_en(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_deep_sleep_wakeup_disable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_deep_sleep_wakeup_enable(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_force_hold_all(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_force_unhold_all(ph7_context *, int , ph7_value **);

int esp32_builtin_gpio_wakeup_disable(ph7_context *, int , ph7_value **);
int esp32_builtin_gpio_wakeup_enable(ph7_context *, int , ph7_value **);
#endif
