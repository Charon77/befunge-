Befunge++
=========

A Befunge interpreter written in C++
------------------------------------

Usage
-----

```bash
befunge.exe <filename>
```

Compiling
---------

```bash
g++ befunge.cpp state.cpp debug.cpp stack.cpp util.cpp file.cpp io.cpp vars.cpp main.cpp -o befunge.exe -Wno-write-strings
```