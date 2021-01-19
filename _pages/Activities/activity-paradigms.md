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
        
tags:
  - paradigms
  
---

