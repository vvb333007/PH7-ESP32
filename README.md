[This is a fork of PH7 PHP engine](http://ph7.symisc.net/) :

 * Symisc PH7: An embeddable bytecode compiler and a virtual machine for the PHP(5) programming language.
 * Copyright (C) 2011-2012, Symisc Systems http://ph7.symisc.net/


An ESP32 port of PH7, WORK IN PROGRESS! ESTIMATED RELEASE DATE: OCTOBER 2026

Status: code compiles in Cygwin environment only, as cygwin is the main development environment.
        `make` to create inter.exe - a standalone php machine which can execute scripts (see scripts/ directory with example scripts)
        ESP32-related changes are merged but not compilable yet

posix_vfs.c layer was extracted from amalgamated sources

Some critical bugs were fixed (incorrect sizeof() use)


===

NOTE: Small changes were made to make this compile and run in ESP-IDF environment, however
      scripts execution from files requires mmap() support, which does not exists in ESP-IDF.

      As a solution there is a [filesystem specifically made for ESP32 and PH7 - tarfs](https://github.com/vvb333007/tarfs)


VFS mmap() support added, pthreads were replaced with FreeRTOS primitives.  Memory backend: uses SPIRAM when available


