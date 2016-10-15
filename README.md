# DESCRIPTION

This is an simple memory leak detector to detect memory leak without modify your code

this can detect the memory allocated by operator 'new' of 'new[]' and not be freed by corresponding operator of not be freed appropriate

you need include "LeakDetector.cpp" to your code

Example:

```
#include "LeakDetector.cpp"

//
//  your code
//  your code
//  your code

```

if there exist sume memory leak, the detector will show the infromation in stdout

Example:

```
leak   0x224fc20 size 4(Cannot find position)
Total 1 leaks, size 4byte.

```
