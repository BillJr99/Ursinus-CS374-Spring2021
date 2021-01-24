---
layout: activity
permalink: /Activities/Lambda Calculus
title: "CS374: Programming Language Principles - The Lambda Calculus"
excerpt: "CS374: Programming Language Principles - The Lambda Calculus"

info: 
  goals: 
    - To relate the Lambda calculus to the Turing Machine abstraction, and to describe their equivalence
    - To derive boolean, numeric, and recursive structures using the Lambda Calculus, beta-reductions, and the Y Combinator
  models:
    - model: |
        <code>&lambda;x.x</code>
      title: Lambda Calculus
      questions:
        - "The first statement defines a parmeter called <code>x</code> and returns <code>x</code>. What does <code>(&lambda;x.x)y</code> do?"
    - model: |
        <code>true = &lambda;xy.x</code><br>
        <code>true = &lambda;xy.y</code><br>
        Here, <code>x</code> and <code>y</code> are <strong>bound variables</strong>.  Variables that appear in the lambda expression that are not defined are referred to as <strong>free</strong> variables.
      title: Fundamental Constructs with the Lambda Calculus
      questions:
        - "In your own words, what does it mean for something to be true in the lambda calculus, when choosing between two alternative parameters?"
    - model: |
        <div align="left">
        <div>
        <code>not x = &lambda;x.x false true</code><br>
        <code>not x = (&lambda;x.x false true) true</code><br>
        These expansions are called <strong>currying</strong>.  Now, substitute <code>true</code> for <code>x</code>:<br>
        <code>not x = (true false true)</code><br>
        Substitute <code>&lambda;xy.x</code> for <code>true</code>:<br>
        <code>not x = (&lambda;xy.x false true)</code><br>
        Given two parameters, select the first one, where the parameters are <code>x = true</code>, <code>y = false</code>:
        <code>not true = false</code>
        </div>
        <br>
        <div>
        <code>equals(x, y) = &lambda;xy.???</code><br>
        Apply one of the parameters to see if it expands to <code>true</code> or <code>false</code>:<br>
        <code>equals(x, y) = &lambda;xy.x ???</code><br>
        If <code>x</code> is <code>true</code>, then they are equal if <code>y</code> is <code>true</code>, and <code>false</code> otherwise.  In other words, the value of <code>y</code> is the result.<br>
        <code>equals(x, y) = &lambda;xy.xy ???</code><br>
        Otherwise, <code>x</code> is <code>false</code>, and so the result is <code>true</code> if <code>y</code> is also <code>false</code>; in other words, the result is <code>not y</code>.<br>
        <code>equals(x, y) = &lambda;xy.xy not y</code><br>
        Which we can expand from our prior definition:
        <code>equals(x, y) = &lambda;xy.xy x false true</code><br>
        Which we expand again to substitute our definitions for <code>true</code> and <code>false</code>:
        <code>equals(x, y) = &lambda;xy.xy x &lambda;xy.y &lambda;xy.x</code><br>
        These substitutions are called <strong>beta-reductions</strong>.
        </div>
        <br>
        <div>
        <code>and(x, y) = y</code> when <code>x = true</code>, and <code>false</code> if <code>x = false</code>.<br>
        <code>&lambda;xy.xy false</code><br>
        <code>&lambda;xy.xy &lambda;ab.b</code>
        </div>
        </div>
      title: Boolean Constructions with the Lambda Calculus
      questions:
        - "Verify the behavior of <code>not false</code> using the lambda expression above."     
        - "All boolean expressions can be constructed using the NAND operator.  What is the lambda expression for NAND, which is (NOT AND x y)?" 
    - model: |
        <div align="left">
        <code>let 0 = &lambda;n(&lambda;z.z)</code><br>
        <code>let 1 = &lambda;nz.n(z)</code><br>
        <code>let 2 = &lambda;nz.n(n(z))</code><br>
        <code>...</code><br>
        <code>successor(n) = &lambda;wyx.y(wyx) (n)</code><br>
        <code>successor(0) = &lambda;wyx.y(wyx) (0) = &lambda;wyx.y(wyx) (&lambda;nz.z) = &lambda;nz.n(z) = 1</code><br>
        <code>mul(x, y) = &lambda;xyz.x(yz)</code><br>
        <code>mul(3, 2) = &lambda;xyz.x(yz) 3 2 = &lambda;z.3(2z) = 6</code>
        </div>
      title: "Arithmetic with the Lambda Calculus"
      questions:
        - "How might you define addition using the successor function?"  
    - model: |
        <div align="left">
        <code>Y = &lambda;f.(&lambda;x.f(x x)) (&lambda;x.f(x x))</code><br>
        <code>Y g = &lambda;f.(&lambda;x.f(x x)) (&lambda;x.f(x x)) g</code><br>
        <code>Y g = (&lambda;x.g(x x)) (&lambda;x.g(x x))</code><br>
        <code>Y g = g ((&lambda;x.g(x x)) (&lambda;x.g(x x)))</code><br>
        <code>Y g = g (Y g)</code>
        </div>
      title: "Recursion and the Y Combinator"
      questions:
        - "How can this model be extended to support recursive procedures?"          
  additional_reading:
    - title: "Lambda Calculus"
      link: "https://plato.stanford.edu/entries/lambda-calculus/"
    - title: "Lambda Calculus Notes"
      link: "http://www.cs.unc.edu/~stotts/723/Lambda/"
    - title: "A Tutorial Introduction to the Lambda Calculus"
      link: "https://personal.utdallas.edu/~gupta/courses/apl/lambda.pdf"
        
tags:
  - lambdacalculus
  
---

