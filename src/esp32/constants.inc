#ifndef PH7_DISABLE_ESP32_ESPIDF_FUNC
  { "GPIO_PORT_0",    esp32_const_int0 },
  { "GPIO_PORT_MAX",  esp32_const_int1 },

  { "GPIO_INTR_DISABLE",    esp32_const_int0 },
  { "GPIO_INTR_POSEDGE",    esp32_const_int1 },
  { "GPIO_INTR_NEGEDGE",    esp32_const_int2 },
  { "GPIO_INTR_ANYEDGE",    esp32_const_int3 },
  { "GPIO_INTR_LOW_LEVEL",  esp32_const_int4 },
  { "GPIO_INTR_HIGH_LEVEL", esp32_const_int5 },
  { "GPIO_INTR_MAX",        esp32_const_int6 },

  { "GPIO_MODE_DEF_DISABLE",esp32_const_int0 },
  { "GPIO_MODE_DEF_INPUT",  esp32_const_int1 },
  { "GPIO_MODE_DEF_OUTPUT", esp32_const_int2 },
  { "GPIO_MODE_DEF_OD",     esp32_const_int4 },


  { "GPIO_MODE_DISABLE",          esp32_const_int0 },
  { "GPIO_MODE_INPUT",            esp32_const_int1 },
  { "GPIO_MODE_OUTPUT",           esp32_const_int2 },
  { "GPIO_MODE_OUTPUT_OD",        esp32_const_int6 },
  { "GPIO_MODE_INPUT_OUTPUT_OD",  esp32_const_int7 },
  { "GPIO_MODE_INPUT_OUTPUT",     esp32_const_int3 },


  { "GPIO_PULLUP_DISABLE",  esp32_const_int0 },
  { "GPIO_PULLUP_ENABLE",   esp32_const_int1 },

  { "GPIO_PULLDOWN_DISABLE",esp32_const_int0 },
  { "GPIO_PULLDOWN_ENABLE", esp32_const_int1 },

  { "GPIO_PULLUP_ONLY",     esp32_const_int0 },
  { "GPIO_PULLDOWN_ONLY",   esp32_const_int1 },
  { "GPIO_PULLUP_PULLDOWN", esp32_const_int2 },
  { "GPIO_FLOATING",        esp32_const_int3 },

  { "GPIO_DRIVE_CAP_0",       esp32_const_int0 },
  { "GPIO_DRIVE_CAP_1",       esp32_const_int1 },
  { "GPIO_DRIVE_CAP_2",       esp32_const_int2 },
  { "GPIO_DRIVE_CAP_DEFAULT", esp32_const_int2 },
  { "GPIO_DRIVE_CAP_3",       esp32_const_int3 },
  { "GPIO_DRIVE_CAP_MAX",     esp32_const_int4 },
#endif

#ifndef PH7_DISABLE_ESP32_ARDUINO_FUNC

  { "ADC_0db", esp32_const_int0 },
  { "ADC_2_5db", esp32_const_int1 },
  { "ADC_6db", esp32_const_int2 },
  { "ADC_11db", esp32_const_int3 },
  { "ADC_ATTENDB_MAX", esp32_const_int4 }, //
  { "LOW", esp32_const_int0 },               //  0x0
  { "HIGH", esp32_const_int1 },               // 0x1
  { "INPUT", esp32_const_int1 },             // 0x01
  { "OUTPUT", esp32_const_int3 }, //            0x03
  { "PULLUP", esp32_const_int4 }, //            0x04
  { "INPUT_PULLUP", esp32_const_int5 }, //      0x05
  { "PULLDOWN", esp32_const_int8 }, //          0x08
  { "INPUT_PULLDOWN", esp32_const_int9 }, //    0x09
  { "OPEN_DRAIN", esp32_const_int16 }, //        0x10
  { "OUTPUT_OPEN_DRAIN", esp32_const_int19 }, // 0x13
  { "ANALOG", esp32_const_int192 }, //            0xC0
  { "DISABLED", esp32_const_int0 },         //  0x00
  { "RISING", esp32_const_int1 },         //    0x01
  { "FALLING", esp32_const_int2 },         //   0x02
  { "CHANGE", esp32_const_int3 },         //    0x03
  { "ONLOW", esp32_const_int4 },         //     0x04
  { "ONHIGH", esp32_const_int5 },         //    0x05
  { "ONLOW_WE", esp32_const_int12 },         //  0x0C
  { "ONHIGH_WE", esp32_const_int13 },         // 0x0D
#endif
