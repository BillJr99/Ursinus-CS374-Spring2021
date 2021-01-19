---
layout: activity
permalink: /Activities/TokensScanning
title: "CS374: Programming Language Principles - Tokens and Scanning Lexemes"
excerpt: "CS374: Programming Language Principles - Tokens and Scanning Lexemes"

info: 
  goals: 
    - To define a lexeme and to define tokens based on lexemes
    - To differentiate between types, reserved words, and identifiers in a scanner
    - To read a file and identify defined tokens
  models:
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        %option noyywrap       

        %{
        #include <stdio.h>

        #define YY_DECL int yylex()

        #include "calc.tab.h"

        %}

        %%

        [ \t]	                ; // ignore all whitespace
        [0-9]+		            {yylval.ival = atoi(yytext); return T_INT;}
        "+"		                {return T_PLUS;}
        "-"		                {return T_MINUS;}
        "*"		                {return T_MULTIPLY;}
        "/"		                {return T_DIVIDE;}
        "("		                {return T_LEFT;}
        ")"		                {return T_RIGHT;}
        \n                      {return T_NEWLINE;}

        %%

        // https://github.com/meyerd/flex-bison-example
        // noyywrap assumes that there are no additional files to be parsed
        ]]></script> 
      title: Scanning Lexemes for Tokens with flex
      questions:
        - "What is a lexeme?  What is a token?"
        - "Describe an algorithm to read a <code>String</code> from left to right, returning tokens as they are identified."
        - "How would you modify this scanner configuration to support an assignment operator and an identifier (variable) token?"
      
tags:
  - tokens
  - lexemes
  - scanner
  
---

