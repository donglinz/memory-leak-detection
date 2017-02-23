# DESCRIPTION

This is an simple memory leak detector to detect memory leak without modify your code

this can detect the memory allocated by operator 'new' of 'new[]' and not be freed by corresponding operator of not be freed appropriate.

you just need to include "LeakDetector.hpp" in your code

Example:

```
#include "LeakDetector.hpp"

//
//  your code
//  your code
//  your code

```

if there exist memory leak, the detector will show the infromation in stdout

Example:

```
leak   0x224fc20 size 4 locate in /home/ubuntu/Desktop/main.cpp line 24
Total 1 leaks, size 4byte.

```
