### A further development of PH7 PHP Engine. 

#### Compiles and runs on ESP32-family, Linux and Windows (Cygwin).


### Memory footprint: requires about 100KiB of memory for the Engine plus ~180 KiB per virtual machine; Running PH7 without external RAM is barely possible. Modern ESP32 chips are all equipped with plenty of PSRAM (4..8MiB)


### Work in progress. [A roadmap](https://github.com/vvb333007/PH7-ESP32/blob/master/TODO.md)
### Lanuage/Engine changes:


 * function return types (function test():int { ... }) and type checks,
 * enums (typed, non-typed, mixed type etc) + enum extensions. Enum values can be complex expressions ("case A = ' '.rand_str(3)"), with commas: (case A = 1, B = 2;)
 * new keyword 'never' as function return type
 * HEREDOC is now parsed correctly when HEREDOC statement is empty; No compilation failure anymore
 * Empty strings '' are not null anymore, they are still strings with zero bytes inside; === operator correctly works with empty strings and null
 * OOB memory accesses (incorrect use of sizeof() in array declaration, incorrect use of sizeof() in string comparisions)
 * Compilation is getting stricter: abort compilation on serious errors




[![Build Status](https://travis-ci.org/symisc/PH7.svg?branch=master)](https://travis-ci.org/symisc/PH7)

PH7 is a in-process software C library which implements a highly-efficient embeddable bytecode compiler and a virtual machine for the PHP programming language. In other words, PH7 is a PHP engine which allow the host application to compile and execute PHP scripts in-process. PH7 is to PHP what SQLite is to SQL.

PH7 implements most of the constructs introduced by the PHP 5.3 release such as heredoc, nowdoc, gotos, classes, anonymous functions, closures and so on and introduces very [powerful extensions](http://ph7.symisc.net/features.html) to the PHP programming language such as:


 * Function & Method Overloading.
 * Full Type Hinting.
 * Introducing comma expressions.
 * Introducing the eq and ne operators for strict string comparison.
 * Improved operators precedences.
 * Powerful OO subsystem.
 * Function arguments can take any complex expressions as their default values.
 * 64-bit integer arithmetic for all platforms.
 * Native UTF-8 support.
 * Written in ANSI C, thread-safe, full-reentrant; compile and run unmodified in any platform including restricted embedded devices with a C compiler.
 * Amalgamation: All C source code for PH7 are combined into a single source file.
 * Built with more 470 function including an XML parser (with namespace support), INI processor, CSV reader/writer, UTF-8 encoder/decoder, zip archive extractor, JSON encoder/decoder, random number/strings generator, native and efficient File IO for Windows and UNIX systems and many more without the need of any external library to link with.
 * PH7 is an Open-Source product.
 

As an embedded interpreter, it allows multiple interpreter states to coexist in the same program, without any interference between them. Programmatically, foreign functions in C/C++ can be added and values can be defined in the PHP environment. Being a quite small program, it is easy to comprehend, get to grips with, and use. 

Documentation describing the APIs used to program PH7. Note that PH7 is very easy to learn, even for new programmer. Here is some useful links to start with:


[PH7 In 5 Minutes Or Less](http://ph7.symisc.net/intro.html):  Gives a high-level overview on the how to embed the PH7 engine in a host application.

[An Introduction To The PH7 C/C++ Interface](http://ph7.symisc.net/api_intro.html): Gives an overview and roadmap to the C/C++ interface to PH7.

[C/C++ API Reference Guide](http://ph7.symisc.net/c_api.html):  This document describes each API function in details.

[Foreign Function Implementation](http://ph7.symisc.net/func_intro.html): Is a how-to guide on how to install C functions and invoke them from your PHP script.

[Constant Expansion Mechanism](http://ph7.symisc.net/const_intro.html):   Is a how-to guide on how to install foreign constants and expand their values from your PHP script.

