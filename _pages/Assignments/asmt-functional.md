---
layout: assignment
permalink: /Assignments/Functional
title: "CS374: Principles of Programming Languages - Functional Programming"
excerpt: "CS374: Principles of Programming Languages - Functional Programming"

info:
  coursenum: CS374
  points: 100
  goals:
    - To explore the functional programming paradigm using the Scheme language
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
  readings:
    - rtitle: "Programming Paradigms Activity"
      rlink: "../Activities/Paradigms"  
      
tags:
  - functional
  
---

The purpose of this assignment is to explore the functional programming paradigm in Scheme.

## Preparation

If you have not already, install scheme on your computer.  If you can type `scheme` and hit Enter, and see Scheme load, you are ready to proceed.  If you need to install Scheme on Ubuntu, you can execute this command:

`sudo apt update && sudo apt install mit-scheme`

or install [Homebrew](https://brew.sh) on the mac, and run this command from the Mac terminal:

`brew install mit-scheme`

Alternatively, you can use a web-based IDE such as [repl.it](https://repl.it).

When you run `scheme`, you'll be presented with an interpreter where you can write or paste code directly, or use the following command to load a file (here, called `myfile.scm`, from your current directory (from which you started scheme):

`(load "myfile.scm")`

## Part 1: Warmup with Lambda Procedures

Using `lambda`, define a procedure that computes a value on a line according to the classic formula:

<span>\\(y = mx + b\\)</span><br>

## Part 2: Warmup with Anonymous Lambda Procedures

Define an anonymous or secondary lambda procedure to compute the discriminant of a quadratic function:

<span>\\(x1, x2 = \frac{-b \pm \sqrt{b^{2} - 4ac}}{2a}\\)</span><br>

Specificaly, your anonymous lambda should compute:

<span>\\(\sqrt{b^{2} - 4ac}\\)</span><br>

And you can compose and return a list from your main lambda procedure that adds to, and subtracts from, the discriminant to obtain your two roots.

## Part 3: Mapping

Using an anonymous `lambda` procedure, create a `map` that applies your anonymous `lambda` to two lists.  `map` works like this:

```
(map <your lambda procedure> '(1 2 3) '(4 5 6))
```

This map will apply your lambda procedure to each pair of items in the list (1 and 4, 2 and 5, and 4 and 6).  Your `lambda` should accept, then, two parameters.  Modify this map to multiply each pair of items together.

Next, you can use `apply` to reduce this list.  Prepend the following (and balnace the parentheses on the right) to compute the dot product of the two lists by adding together all the items in the resulting list:

```
(apply + <your map here>)
```

## Part 4: Working with Lists

Write a `lambda` procedure called `czr` which returns the last item in the list.  If the `cdr` of the list is `null`, then you have found the last item: otherwise, you can recurse into `czr` on the `cdr` of the list until the last item is found.

Write a second `lambda` function called `cxr` that returns everything **except** the last item in the list.  You may write or find (and cite) a procedure to reverse a list, and note that `cxr` is the `cdr` of the reverse of a list, reversed again.