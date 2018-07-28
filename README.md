# bitv - A viewer for hexadecimal data

Convert hex input to a binary output in command line

Options:
* {-v}           : print vertical[default horizontal]
* {-h}           : this help
* {-r}           : inverted order [default is incremental]
* {-s [8|16|32|64]} : input and display is 8, 16, 32 or 64 bits wide[default is 32bits]
* {-B}           : short hand for input/output as 8 bits
* {-S}           : short hand for input/output as 16 bits
* {-W}           : short hand for input/output as 32 bits
* {-L}           : short hand for input/output as 64 bits
* {-i [val]}     : input value - if provided, will exit, else will repeat for multiple entries

# Some examples:

* bitv -i 0xa5
```
---------------------------------------------------------------------------------------------------------------------------------
| 31| 30| 29| 28| 27| 26| 25| 24| 23| 22| 21| 20| 19| 18| 17| 16| 15| 14| 13| 12| 11| 10| 09| 08| 07| 06| 05| 04| 03| 02| 01| 00|
---------------------------------------------------------------------------------------------------------------------------------
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 1 | 0 | 1 |
---------------------------------------------------------------------------------------------------------------------------------
|            0x0|            0x0|            0x0|            0x0|            0x0|            0x0|            0xa|            0x5|
---------------------------------------------------------------------------------------------------------------------------------

```

* bitv -B -r -i 0xa5
```
---------------------------------
| 00| 01| 02| 03| 04| 05| 06| 07|
---------------------------------
| 1 | 0 | 1 | 0 | 0 | 1 | 0 | 1 |
---------------------------------
|            0x5|            0xa|
---------------------------------
```

* bitv -B  -v -i 0xa5
```
[07] - 1
[06] - 0
[05] - 1
[04] - 0
-- 0xa --
[03] - 0
[02] - 1
[01] - 0
[00] - 1
-- 0x5 --
```

* bitv -B -r -v -i 0xa5
```
[00] - 1
[01] - 0
[02] - 1
[03] - 0
-- 0x5 --
[04] - 0
[05] - 1
[06] - 0
[07] - 1
-- 0xa --
```

# Building
This is a simple file.. anyways.. _make_ and _make clean_ are supported.. you just need a compiler like gcc or something.
```
make
```
# Cross Comiling

Just override CC with your compiler of choice.

```
make CC=aarch64-linux-gnu-gcc
