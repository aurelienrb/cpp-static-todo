# C++ TODO / FIXME macros that expire (fail to compile) at a given date
![C++14](https://img.shields.io/badge/c%2B%2B-14-blue.svg) [![pipeline status](https://gitlab.com/aurelienrb/cpp-static-todo/badges/master/pipeline.svg)](https://gitlab.com/aurelienrb/cpp-static-todo/commits/master)

`TODO_BEFORE()` and `FIXME_BEFORE()` macros insert a compilation "time bomb" that will trigger a *TODO* or *FIXME* build error a soon as the given date is reached.

This is useful to force attention on a specific piece of code that should not been forgotten among a growing list of many other *TODO* or *FIXME* comments...

## Example

```cpp
#include "static_todo.h"

TODO_BEFORE(01, 2018, "refactor to use std::optional<> once we compile in C++17 mode");
bool readConfigInt(const std::string & key, int & value);
```

```
 In file included from example.cpp:1:0:
static_todo.hpp:48:5: error: static assertion failed: TODO: refactor to use std::optional<> once we compile in C++17 mode
     static_assert((year >= 2018 && month > 0 && month <= 12) &&                                    \
     ^
example.cpp:6:1: note: in expansion of macro 'TODO_BEFORE'
 TODO_BEFORE(01, 2018, "refactor to use std::optional<> once we compile in C++17 mode");
 ^~~~~~~~~~~
```

## Supported compilers

The code requires a **C++14** compiler (it *won't* work in C++11 mode).

It has been successfully tested with a high level of warnings on:
- g++ >= 5.1 (`-std=c++14`)
- clang++ >= 3.9 (`-std=c++14`)
- VC++ 2017 (`/std:c++14`)

## License

MIT License: feel free to copy and modify this code however you like.

Original idea and implementation by Aurélien Regat-Barrel.
