
An ESP32 port of PH7, WORK IN PROGRESS! ESTIMATED RELEASE DATE: OCTOBER 2026

Breaking changes: code compiles in Cygwin environment only, as cygwin is the main development environment.

posix_vfs.c layer was extracted from amalgamated sources


===

NOTE: Small changes were made to make this compile and run in ESP-IDF environment, however
      scripts execution from files requires mmap() support, which does not exists in ESP-IDF.

      As a solution there is a [filesystem specifically made for ESP32 and PH7 - tarfs](https://github.com/vvb333007/tarfs)

NOTE: Upcoming changes: Complete WIN32 support removal, "Unix" code is refactored to use FreeRTOS,
VFS mmap() support added, pthreads were replaced with FreeRTOS primitives.  Memory backend: uses SPIRAM when available

[This is a fork of PH7 PHP engine](http://ph7.symisc.net/) :

 * Symisc PH7: An embeddable bytecode compiler and a virtual machine for the PHP(5) programming language.
 * Copyright (C) 2011-2012, Symisc Systems http://ph7.symisc.net/

