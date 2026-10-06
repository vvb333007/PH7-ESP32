### PH8 : A further development of PH7 PHP Engine. 

#### Compiles and runs on ESP32-family, Linux and Windows (Cygwin).


### Memory footprint: requires about 100KiB of memory for the Engine plus ~180 KiB per virtual machine; Running PH8 without external RAM is barely possible. Modern ESP32 chips are all equipped with plenty of PSRAM (4..8MiB)


### Work in progress. [A roadmap](https://github.com/vvb333007/PH8-ESP32/blob/master/TODO.md)
### Lanuage/Engine changes:


 * function return types (function test():int { ... }) and type checks,
 * arrow function
 * typed class attributes
 * enums (typed, non-typed, mixed type etc) + enum extensions. Enum values can be complex expressions ("case A = ' '.rand_str(3)"), with commas: (case A = 1, B = 2;)
 * new keyword 'never' as function return type
 * HEREDOC is now parsed correctly when HEREDOC statement is empty; No compilation failure anymore
 * Empty strings '' are not null anymore, they are still strings with zero bytes inside; === operator correctly works with empty strings and null
 * OOB memory accesses (incorrect use of sizeof() in array declaration, incorrect use of sizeof() in string comparisions)
 * Compilation is getting stricter: abort compilation on serious errors
 * And many more

