# XS Easy

This library is a toolbox that assists with creation & maintenance
of Perl XS code.

# Usage

1. Make this repository a
[git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
of your own XS module.

2. Pick which pieces of XS Easy you’d like to include in your code.

# Rationale

Perl’s C API makes lots of things _possible_ without making them
_easy_ (or _safe_).

This library attempts to provide shims around that API that make it easy
and safe (or, at least, safe-_er_!) to write XS code … maybe even *fun!* :-)

# Library Components

## `init.h`

Includes the standard boilerplate code you normally stick at the top
of a `*.xs` file. Now instead of those 3-4 includes you can just:
```
#include "xseasy/init.h"
```

# License & Copyright

Copyright 2022 by Gasper Software Consulting. All rights reserved.

This library is released under the terms of the
[MIT License](https://mitlicense.org/).