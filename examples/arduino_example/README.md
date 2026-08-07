#### Arduino example, 3 files:

```
arduino_example.ino
example_scripts.tar
partitions.csv
```

These libraries must be installed before attemprting to compile:

```
  TARFS 0.1.5 or higher
  PH7-ESP32 0.0.1 or higher
```

[TARFS latest](https://github.com/vvb333007/tarfs)
[PH7-ESP32 latest](https://github.com/vvb333007/PH7-ESP32)


  1. Upload example_scripts.tar to your ESP32 at offset 0x310000:
    `esptool.exe --chip esp32s3 --port COM4 --baud 921600 write_flash 0x310000 example_scripts.tar`
    Replace `esp32s3` with your chip model, replace `COM4` to your port number

  2. Compile and upload .ino file




