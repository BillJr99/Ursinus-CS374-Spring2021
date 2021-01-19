---
layout: activity
permalink: /Activities/Paradigms
title: "CS374: Programming Language Principles - Programming Paradigms"
excerpt: "CS374: Programming Language Principles - Programming Paradigms"

info: 
  goals: 
    - To define the imperative, declarative (functional and logic), object-oriented, and scripting programming paradigms
    - To explore concurrency within programming paradigms
  models:
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        public class Main {
            public static void main(String[] args) {
                int a = 1, b = 2, c = 1;
                
                float discriminant = Math.sqrt(4.0*a*c) / 2*a;
                
                float root = -b + discriminant;
                
                System.out.println(root);
                
                root = -b - discriminant;
                
                System.out.println(root);
            }
        }
        ]]></script> 
      title: "Imperative Languages and the Object-Oriented Paradigm"
      questions:
        - "What defines a statement?"
        - "What, in general, does a statement realy do?"
        - "At what points do the value of root change?"
        - "What would happen if <code>a</code> is 0?"
        - "How can we represent this program using an Object-Oriented style?  What state might the object represent?"
        - "Sketch out an object-oriented design representing students and courses, in which students are enrolled in one or more sections of the course."
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        #include <math.h>
        #include <stdio.h>
        
        void calcroot(float* root, float discriminant, int b) {
            *root = -b + discriminant;
        }
        
        int main(void) {
            int a = 1, b = 2, c = 1;
            
            float discriminant = sqrt(4.0*a*c) / 2*a;
            float root = 0;
            
            calcroot(&root, discriminant, b);
            printf("%d\n", root);
            
            calcroot(&root, -discriminant, b);
            printf("%d\n", root);
        }
        ]]></script> 
      title: Imperative Languages
      questions:
        - "At what points do the value of <code>root</code> change?  Where are they changed, and where are they effective?"
        - "What would happen if <code>a</code> is 0?" 
        - "How many copies of <code>discriminant</code> exist on the call to <code>calcroot</code>?"
        - "How does the <code>calcroot</code> function know to use the <code>discriminant</code> variable in its local function?"
        - "What would happen if <code>discriminant</code> was modified inside <code>calcroot</code>?  Why is this different than for the <code>root</code> variable?"
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        (define L (list 'a 'b 'c))
        (car L)
        (cdr L)
        
        (define x (+ 3 2))
        (+ x 5)
        
        (define add +)
        (add 3 2)
        ]]></script>
        <br>
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        (define square
          (lambda(n)
            (* n n)
          )
        )

        (define pow
          (lambda(n k)
            (if (= k 0)
              1
              (* n (pow n (- k 1)))
            )
          )
        )
              
        (square (pow 5 3))
        ]]></script> 
      title: "Declarative Languages - Functional"
      questions:
        - "What is a statement in Scheme?"
        - "What shared variables exist in this program?"
        - "What are some potential advantages of Functional Programming as a paradigm?" 
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
           course(CS173).
           course(CS374).
           course(CS374).
           course(CS475).
           
           prereq(CS174, CS173).
           prereq(CS374, CS174).
           
           ?-prereq(CS475, CS374). % no
           
           /* Horn Clause: does there exist a Z such that Y is a prereq of Z AND that X must be taken before Z? */
           take_before(X, Y) :- prereq(Z, Y), take_before(X, Z). % Transitive closure through recursion
           
           ?-take_before(CS173, CS374). % yes
        ]]></script> 
      title: "Declarative Languages - Logic"
      questions:
        - "What query would result in a <code>yes</code> response according to the prerequisite rules above?" 
        - "In your own words, what does the <code>take_before</code> clause specify, and how does it do so?"  
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
         % From https://en.wikipedia.org/wiki/Prolog
         perfect(N) :-
            between(1, inf, N), U is N // 2,
            findall(D, (between(1,U,D), N mod D =:= 0), Ds),
            sumlist(Ds, N).
        ]]></script> 
      title: "Declarative Languages - Prolog"
      questions:
        - "Describe, in your own words, what this program does."  
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
         #!/bin/bash
         
         COURSE=CS374
         cd ${COURSE}
         
         FILES=$(ls)
         echo ${FILES}
        ]]></script> 
      title: "Declarative Languages - Scripting"
      questions:
        - "What is a statement in this language?"
        - "How are variables expanded?"
        - "What potential benefit can you see with the use of shell scripting?" 
        
tags:
  - paradigms
  
---

