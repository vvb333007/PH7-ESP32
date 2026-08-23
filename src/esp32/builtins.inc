#ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC
  { "pinMode", esp32_builtin_pinMode }, 
  { "digitalRead", esp32_builtin_digitalRead }, 
  { "digitalWrite", esp32_builtin_digitalWrite }, 
#endif

#if 0
  { "analogRead", esp32_builtin_analogRead }, 
  { "analogReadResolution", esp32_builtin_analogReadResolution }, 
  { "analogReadMilliVolts", esp32_builtin_analogReadMilliVolts }, 

  { "analogWrite", esp32_builtin_analogWrite }, 
  { "analogWriteResolution", esp32_builtin_analogWriteResolution }, 
  { "analogWriteFrequency", esp32_builtin_analogWriteFrequency }, 

  { "analogSetAttenuation", esp32_builtin_analogSetAttenuation }, 
  { "analogSetPinAttenuation", esp32_builtin_analogSetPinAttenuation }, 
  { "analogSetWidth", esp32_builtin_analogSetWidth }, 




  { "analogChannelToDigitalPin", esp32_builtin_analogChannelToDigitalPin }, 

  { "analogContinuous", esp32_builtin_analogContinuous }, 
  { "analogContinuousDeinit", esp32_builtin_analogContinuousDeinit }, 
  { "analogContinuousRead", esp32_builtin_analogContinuousRead }, 
  { "analogContinuousSetAtten", esp32_builtin_analogContinuousSetAtten }, 
  { "analogContinuousSetWidth", esp32_builtin_analogContinuousWidth }, 
  { "analogContinuousStart", esp32_builtin_analogContinuousStart }, 
  { "analogContinuousStop", esp32_builtin_analogContinuousStop }, 


  { "attachInterrupt", esp32_builtin_attachInterrupt }, 
  { "attachInterruptArg", esp32_builtin_attachInterruptArg }, 
  { "detachInterrupt", esp32_builtin_detachInterrupt }, 
  { "disableInterrupt", esp32_builtin_disableInterrupt }, 
  { "enableInterrupt", esp32_builtin_enableInterrupt }, 


  { "delay", esp32_builtin_delay }, 
  { "delay_us", esp32_builtin_delay_us },
  

  { "digitalPinCanOutput", esp32_builtin_digitalPinCanOutput }, 
  { "digitalPinIsValid", esp32_builtin_digitalPinIsValid }, 
  { "digitalPinToAnalogChannel", esp32_builtin_digitalPinToAnalogChannel }, 
  { "digitalPinToDacChannel", esp32_builtin_ digitalPinToDacChannel}, 
  { "digitalPinToRtcPin", esp32_builtin_digitalPinToRtcPin }, 
  { "digitalPinToTouchChannel", esp32_builtin_digitalPinToTouchChannel }, 



  { "getApbFrequency", esp32_builtin_getApbFrequency }, 
  { "getCpuFrequencyMhz", esp32_builtin_getCpuFrequencyMhz }, 
  { "getXtalFrequencyMhz", esp32_builtin_getXtalFrequencyMhz }, 

  { "i2cDeinit", esp32_builtin_i2cDeinit }, 
  { "i2cGetClock", esp32_builtin_i2cGetClock }, 
  { "i2cInit", esp32_builtin_i2cInit }, 
  { "i2cIsInit", esp32_builtin_i2cIsInit }, 
  { "i2cRead", esp32_builtin_i2cRead }, 
  { "i2cSetClock", esp32_builtin_i2cSetClock }, 
  { "i2cWrite", esp32_builtin_i2cWrite }, 
  { "i2cWriteReadNonStop", esp32_builtin_i2cWriteReadNonStop }, 

  { "isAlpha", esp32_builtin_isAlpha }, 
  { "isAlphaNumeric", esp32_builtin_isAlphaNumeric }, 
  { "isAscii", esp32_builtin_isAscii }, 
  { "isControl", esp32_builtin_isControl }, 
  { "isDigit", esp32_builtin_isDigit }, 
  { "isGraph", esp32_builtin_isGraph }, 
  { "isHexadecimalDigit", esp32_builtin_isHexadecimalDigit }, 
  { "isLowerCase", esp32_builtin_isLowerCase }, 
  { "isPrintable", esp32_builtin_isPrintable }, 
  { "isPunct", esp32_builtin_isPunct }, 
  { "isSpace", esp32_builtin_isSpace }, 
  { "isUpperCase", esp32_builtin_isUpperCase }, 
  { "isWhitespace", esp32_builtin_isWhiteSpace }, 

  { "ledcAttach", esp32_builtin_ledcAttach }, 
  { "ledcAttachChannel", esp32_builtin_ledcAttachChannel }, 
  { "ledcChangeFrequency", esp32_builtin_ledcChangeFrequency }, 
  { "ledcDetach", esp32_builtin_ledcDetach }, 
  { "ledcFade", esp32_builtin_ledcFade }, 
  { "ledcGetClockSource", esp32_builtin_ledcGetClockSource }, 
  { "ledcOutputInvert", esp32_builtin_ledcOutputInvert }, 
  { "ledcRead", esp32_builtin_ledcRead }, 
  { "ledcReadFreq", esp32_builtin_ledcReadFreq }, 
  { "ledcSetClockSource", esp32_builtin_ledcSetClockSource }, 
  { "ledcWrite", esp32_builtin_ledcWrite }, 
  { "ledcWriteChannel", esp32_builtin_ledcWriteChannel }, 
  { "ledcWriteNote", esp32_builtin_ledcWriteNote }, 
  { "ledcWriteTone", esp32_builtin_ledcWriteTone }, 

  { "makeWord", esp32_builtin_makeWord }, 

  { "map", esp32_builtin_map }, 

  { "micros", esp32_builtin_micros }, 
  { "millis", esp32_builtin_millis }, 

  

  { "pulseIn", esp32_builtin_pulseIn }, 
  { "pulseInLong", esp32_builtin_pulseInLong }, 

  { "random", esp32_builtin_random }, 
  { "randomSeed", esp32_builtin_randomSeed }, 

  { "rmtDeinit", esp32_builtin_rmtDeinit }, 
  { "rmtInit", esp32_builtin_rmtInit }, 
  { "rmtRead", esp32_builtin_rmtRead }, 
  { "rmtReadAsync", esp32_builtin_rmtReadAsync }, 
  { "rmtReceiveCompleted", esp32_builtin_rmtReceiveCompleted }, 
  { "rmtSetCarrier", esp32_builtin_rmtSetCarrier }, 
  { "rmtSetEOT", esp32_builtin_rmtSetEOT }, 
  { "rmtSetRxMaxThreshold", esp32_builtin_rmtSetRxMaxThreshold }, 
  { "rmtSetRxMinThreshold", esp32_builtin_rmtSetRxMinThreshold }, 
  { "rmtTransmitCompleted", esp32_builtin_rmtTransmitCompleted }, 
  { "rmtWrite", esp32_builtin_rmtWrite }, 
  { "rmtWriteAsync", esp32_builtin_rmtWriteAsync }, 
  { "rmtWriteLooping", esp32_builtin_rmtWriteLooping }, 
  { "rmtWriteRepeated", esp32_builtin_rmtWriteRepeated }, 

  { "setCpuFrequencyMhz", esp32_builtin_setCpuFrequencyMhz }, 

  { "shiftIn", esp32_builtin_shiftIn }, 
  { "shiftOut", esp32_builtin_shiftOut }, 

  { "sigmaDeltaAttach", esp32_builtin_sigmaDeltaAttach }, 
  { "sigmaDeltaDetach", esp32_builtin_sigmaDeltaDetach }, 
  { "sigmaDeltaWrite", esp32_builtin_sigmaDeltaWrite }, 

  { "temperatureRead", esp32_builtin_temperatureRead }, 

  { "toAscii", esp32_builtin_ toAscii}, 
  { "toLowerCase", esp32_builtin_toLowerCase }, 
  { "toUpperCase", esp32_builtin_toUpperCase }, 

  { "touchAttachInterrupt", esp32_builtin_touchAttachInterrupt }, 
  { "touchAttachInterruptArg", esp32_builtin_touchAttachInterruptArg }, 
  { "touchDetachInterrupt", esp32_builtin_touchDetachInterrupt }, 
  { "touchInterruptGetLastStatus", esp32_builtin_touchInterruptGetLastStatus }, 
  { "touchInterruptSetThresholdDirection", esp32_builtin_touchInterruptSetThresholdDirection }, 

  { "touchRead", esp32_builtin_touchRead }, 
  { "touchSetConfig", esp32_builtin_touchSetConfig }, 
  { "touchSetDefaultThreshold", esp32_builtin_touchSetDefaultThreshold }, 
  { "touchSetTiming", esp32_builtin_touchSetTiming }, 
  { "touchSleepWakeUpEnable", esp32_builtin_touchSleepWakeUpEnable }, 

  

  { "uart_get_CtsPin", esp32_builtin_ }, 
  { "uart_get_max_rx_timeout", esp32_builtin_ }, 
  { "uart_get_RtsPin", esp32_builtin_ }, 
  { "uart_get_RxPin", esp32_builtin_ }, 
  { "uart_get_TxPin", esp32_builtin_ }, 
  { "uart_internal_hw_flow_ctrl_loopback", esp32_builtin_ }, 
  { "uart_internal_loopback", esp32_builtin_ }, 
  { "uart_send_break", esp32_builtin_ }, 
  { "uart_send_msg_with_break", esp32_builtin_ }, 

  { "uartAvailable", esp32_builtin_ }, 
  { "uartAvailableForWrite", esp32_builtin_ }, 
  { "uartBegin", esp32_builtin_ }, 
  { "uartDetectBaudrate", esp32_builtin_ }, 
  { "uartEnableRxInternalPull", esp32_builtin_ }, 
  { "uartEnd", esp32_builtin_ }, 
  { "uartFlush", esp32_builtin_ }, 
  { "uartFlushTxOnly", esp32_builtin_ }, 
  { "uartGetBaudRate", esp32_builtin_ }, 
  { "uartGetDebug", esp32_builtin_ }, 
  { "uartIsDriverInstalled", esp32_builtin_ }, 
  { "uartPeek", esp32_builtin_ }, 
  { "uartPinSignalInversion", esp32_builtin_ }, 
  { "uartRead", esp32_builtin_ }, 
  { "uartReadBytes", esp32_builtin_ }, 
  { "uartSetBaudRate", esp32_builtin_ }, 
  { "uartSetClockSource", esp32_builtin_ }, 
  { "uartSetCtsInvert", esp32_builtin_ }, 
  { "uartSetDebug", esp32_builtin_ }, 
  { "uartSetFastReading", esp32_builtin_ }, 
  { "uartSetHwFlowCtrlMode", esp32_builtin_ }, 
  { "uartSetIrdaDirection", esp32_builtin_ }, 
  { "uartSetMode", esp32_builtin_ }, 
  { "uartSetPins", esp32_builtin_ }, 
  { "uartSetRtsInvert", esp32_builtin_ }, 
  { "uartSetRxFIFOFull", esp32_builtin_ }, 
  { "uartSetRxInvert", esp32_builtin_ }, 
  { "uartSetRxTimeout", esp32_builtin_ }, 
  { "uartSetTxInvert", esp32_builtin_ }, 
  { "uartStartDetectBaudrate", esp32_builtin_ }, 
  { "uartWrite", esp32_builtin_ }, 
  { "uartWriteBuf", esp32_builtin_ }, 

  { "useRealRandomGenerator", esp32_builtin_ }, 


#ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC
  { "gpio_config", esp32_builtin_gpio_config },

  { "gpio_get_drive_capability", esp32_builtin_gpio_get_drive_capability },
  { "gpio_get_io_config", esp32_builtin_gpio_get_io_config },
  { "gpio_get_level", esp32_builtin_gpio_get_level },

  { "gpio_hold_dis", esp32_builtin_gpio_hold_dis },
  { "gpio_hold_en", esp32_builtin_gpio_hold_en },


  { "gpio_install_isr_service", esp32_builtin_gpio_install_isr_service },
  { "gpio_uninstall_isr_service", esp32_builtin_gpio_uninstall_isr_service },
  { "gpio_intr_disable", esp32_builtin_gpio_intr_disable },
  { "gpio_intr_enable", esp32_builtin_gpio_intr_enable },
  { "gpio_isr_handler_add", esp32_builtin_gpio_isr_handler_add },
  { "gpio_isr_handler_remove", esp32_builtin_gpio_isr_handler_remove },
  { "gpio_isr_register", esp32_builtin_gpio_isr_register },

  { "gpio_iomux_input", esp32_builtin_gpio_iomux_input },
  { "gpio_iomux_output", esp32_builtin_gpio_iomux_output },
  { "gpio_func_sel", esp32_builtin_gpio_func_sel },

  { "gpio_pulldown_dis", esp32_builtin_gpio_pulldown_dis },
  { "gpio_pulldown_en", esp32_builtin_gpio_pulldown_en },
  { "gpio_pullup_dis", esp32_builtin_gpio_pullup_dis },
  { "gpio_pullup_en", esp32_builtin_gpio_pullup_en },
  { "gpio_od_enable", esp32_builtin_gpio_od_enable },
  { "gpio_od_disable", esp32_builtin_gpio_od_disable },
  { "gpio_input_enable", esp32_builtin_gpio_input_enable },
  { "gpio_input_disable", esp32_builtin_gpio_input_disable },
  { "gpio_output_enable", esp32_builtin_gpio_output_enable },
  { "gpio_output_disable", esp32_builtin_gpio_output_disable },

  { "gpio_reset_pin", esp32_builtin_gpio_reset_pin },

  { "gpio_set_direction", esp32_builtin_gpio_set_direction },
  { "gpio_set_drive_capability", esp32_builtin_gpio_set_drive_capability },
  { "gpio_set_intr_type", esp32_builtin_gpio_set_intr_type },
  { "gpio_set_level", esp32_builtin_gpio_set_level },
  { "gpio_set_pull_mode", esp32_builtin_gpio_set_pull_mode },

  { "gpio_sleep_sel_dis", esp32_builtin_gpio_sleep_sel_dis },
  { "gpio_sleep_sel_en", esp32_builtin_gpio_sleep_sel_en },
  { "gpio_sleep_set_direction", esp32_builtin_gpio_sleep_set_direction },
  { "gpio_sleep_set_pull_mode", esp32_builtin_gpio_sleep_set_pull_mode },

  { "gpio_deep_sleep_hold_dis", esp32_builtin_gpio_deep_sleep_hold_dis },
  { "gpio_deep_sleep_hold_en", esp32_builtin_gpio_deep_sleep_hold_en },
  { "gpio_deep_sleep_wakeup_disable", esp32_builtin_gpio_deep_sleep_wakeup_disable },
  { "gpio_deep_sleep_wakeup_enable", esp32_builtin_gpio_deep_sleep_wakeup_enable },

  { "gpio_force_hold_all", esp32_builtin_gpio_force_hold_all },
  { "gpio_force_unhold_all", esp32_builtin_gpio_force_unhold_all },

  { "gpio_wakeup_disable", esp32_builtin_gpio_wakeup_disable },
  { "gpio_wakeup_enable", esp32_builtin_gpio_wakeup_enable },
#endif

#endif
