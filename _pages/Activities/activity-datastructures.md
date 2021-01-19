---
layout: activity
permalink: /Activities/DataStructures
title: "CS374: Programming Language Principles - Data Structures"
excerpt: "CS374: Programming Language Principles - Data Structures"

info: 
  goals: 
    - To explain data types from a record perspective
    - To explain data types from a tuple perspective
    - To relate the Lambda calculus to the Turing Machine abstraction
  models:
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        // C++
        template <typename T>
        T min(T a, T b) {
            if(a < b) {
                return a;
            } else {
                return b;
            }
        }
        ]]></script> 
      title: Generics
      questions:
        - "If the language supports coercion or casting, this might not seem useful at first glance.  In what circumstances might this be a useful construct?"
        - "Consider the C library function <code>void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))</code>.  How might you sort an array of <code>int</code>, or an array of <code>char*</code>, using this same function?"
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        (define x (list 0))
        (define y (list 1 x))
        (define z (list 2 y))

        z ; (2 (1 (0)))
        
        (define a (cons 1 2))
        (define b (list x (cons 8 9)))
        b ; (1 . 2) (8 . 9)
        
        (define c (cons "Bill" 38))
        c ; ("Bill" . 38)
        ]]></script> 
      title: Tuple Linked Lists and Data Structures
      questions:
        - "What, in an abstract sense, is a linked list (regardless of its implementation in a particular programming language)?"
        - "What is a data structure in Scheme?"
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        01  sale-date.
           05  the-year       PIC 9(4).
           05  the-month      PIC 99.
           05  the-day        PIC 99.
        ]]></script> 
      title: COBOL Records
      questions:
        - "What, in your own words, is a data structure in COBOL?"
    - model: |
        <code>&lambda;x.x</code>
      title: Lambda Calculus
      questions:
        - "The first statement defines a parmeter called <code>x</code> and returns <code>x</code>. What does <code>(&lambda;x.x)y</code> do?"
  additional_reading:
    - title: "Lambda Calculus"
      link: "https://plato.stanford.edu/entries/lambda-calculus/"
    - title: "Lambda Calculus Notes"
      link: "http://www.cs.unc.edu/~stotts/723/Lambda/"
        
tags:
  - datastructures
  
---

