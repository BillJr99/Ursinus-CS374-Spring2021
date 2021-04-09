---
layout: assignment
permalink: /Assignments/Libraries
title: "CS374: Principles of Programming Languages - Libraries"
excerpt: "CS374: Principles of Programming Languages - Libraries"

info:
  coursenum: CS374
  points: 100
  goals:
    - To create a static library that can be shared with others
    - To use dynamic loading to augment existing functionality such as malloc()
  rubric:
    - weight: 60
      description: Algorithm Implementation
      preemerging: The algorithm fails on the test inputs due to major issues, or the program fails to compile and/or run
      beginning: The algorithm fails on the test inputs due to one or more minor issues
      progressing: The algorithm is implemented to solve the problem correctly according to given test inputs, but would fail if executed in a general case due to a minor issue or omission in the algorithm design or implementation
      proficient: A reasonable algorithm is implemented to solve the problem which correctly solves the problem according to the given test inputs, and would be reasonably expected to solve the problem in the general case
    - weight: 30
      description: Code Quality and Documentation
      preemerging: Code commenting and structure are absent, or code structure departs significantly from best practice, and/or the code departs significantly from the style guide
      beginning: Code commenting and structure is limited in ways that reduce the readability of the program, and/or there are minor departures from the style guide
      progressing: Code documentation is present that re-states the explicit code definitions, and/or code is written that mostly adheres to the style guide
      proficient: Code is documented at non-trivial points in a manner that enhances the readability of the program, and code is written according to the style guide
    - weight: 10
      description: Writeup and Submission
      preemerging: An incomplete submission is provided
      beginning: The program is submitted, but not according to the directions in one or more ways (for example, because it is lacking a readme writeup)
      progressing: The program is submitted according to the directions with a minor omission or correction needed, and with at least superficial responses to the bolded questions throughout
      proficient: The program is submitted according to the directions, including a readme writeup describing the solution, and thoughtful answers to the bolded questions throughout    
  
tags:
  - libraries
  
---

The purpose of this assignment is to implement, load, and use, a static library (at compile time) in C++, and also to dynamically load functionality from a library (at runtime).

## Part 1: Static Libraries \[[^1]\]
Follow [this tutorial](https://ncona.com/2019/03/building-and-using-a-library-in-cpp/) on creating a library in C++.  In summary, you will create a `.cpp` file with functionality inside, and a `.h` file with your header definition.  

You may choose any library functionality you would like, and references are OK as long as they are cited in your source.  Be creative - what are some functions that you might find useful to have someday (or might find useful to share with someone else)?

## Part 2: Dynamic Library Loading \[[^2]\]
Create a function called `malloc` that accepts an `int size` and returns a `void *`, just like `malloc` does.  In that function, create a pointer `static void*(*mymalloc)(int n)` that you will assign to a call to `dlsym(RTLD_NEXT, "malloc")`.  Call `mymalloc(size)` within this function, and store the result in a `void *` variable that your function will return.  Also increment a global variable that you'll store statically within your module.  This call will look like this:

```java
#include <dlfcn.h>

void* malloc(int size) {
    void*(*mymalloc)(int) = (void* (*)(int)) dlsym(RTLD_NEXT, "malloc");
}
```

Next, do the same for `free`, which is a `void` function that accepts a `void *` parameter.  This time, decrement your counter, and print out that variable on each call to your custom `malloc` and `free`.  Test it out with a main() function that calls `malloc` and `free` a few times so you can verify the result.  You should have a count of 0 if you call `free` the same number of times as you call `malloc`!

To compile your library, you can save your file as `mallocfree.c` and run:

`gcc -ldl -o mallocfree.so -shared mallocfree.c`

And, to call your test program `main.c`, you can compile it as usual and run:

`LD_PRELOAD="/usr/lib/libdl.so" ./a.out`

## References:

[^1]: https://ncona.com/2019/03/building-and-using-a-library-in-cpp/
[^2]: https://www.cs.cmu.edu/afs/cs.cmu.edu/academic/class/15213-f03/www/interposition/mymalloc.c