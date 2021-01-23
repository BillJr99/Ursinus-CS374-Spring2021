---
layout: activity
permalink: /Activities/ParserInterpreter
title: "CS374: Programming Language Principles - Parsers and Interpreters"
excerpt: "CS374: Programming Language Principles - Parsers and Interpreters"

info: 
  goals: 
    - To remove left recursion and to left factor a grammar for LL(1) parsing, where possible
    - To describe the components of an LL(k) and an LR(k) parser
    - To implement a simple parser given a grammar, from code or using tools such as lex and yacc
    - To generate a parse table for a given grammar
  models:
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        // LL(1) means Left-To-Right scanning, Left-To-Right Parsing, and one character lookahead for parsing
        // https://gist.github.com/mlabbe/81d667bac36aa60787fee60e3647a0a8
        // https://github.com/meyerd/flex-bison-example
        /*
          expr: term addsub term 
              | term addsub term addsub expr
              | term
          term: factor muldiv factor
              | factor muldiv factor muldiv term
              | factor
          factor: num
                | "(" expr ")"
          addsub: "+" | "-"
          muldiv: "*" | "/"
          num: [0-9]+
         */

        #include <stdio.h>
        #include <ctype.h>
        #include <stdlib.h>
        #include <string.h>

        int expr(void);
        char token;

        // remove the next character from the stream
        char pop() {
            char ch = getchar();
            printf("Popped %c\n", ch);
            return ch;
        }

        // check the next character, but don't remove it from the stream
        char peek() {
            char ch = pop();
            ungetc(ch, stdin);
            printf("Pushed %c\n", ch);
            return ch;
        }

        int readint() {
            int numchars = 0;
            char* val = (char*) malloc(1); // for the trailing \0
            
            token = peek();
            while(isdigit(token)) {
                pop(); 
                
                numchars = numchars + 1;
                val = (char*) realloc(val, numchars + 1); // for the trailing \0
                
                val[numchars-1] = token;
                
                token = peek();
            }
            
            val[numchars] = '\0'; // null terminate
            
            int result = atoi(val);
            
            printf("Read int from string %s (length %d): %d\n", val, strlen(val), result);
            
            free(val);
            
            return result;
        }

        int factor(void) {
            printf("In factor\n");
            
            int value;
            token = peek();

            if (token == '(') { // resolve parens as a whole new expression, resolving to a value, regardless of where they occur in the input (since they are highest precedence)
                pop(); // (
                value = expr();
                token = pop(); // )

                if(token != ')') {
                    printf("Error parsing factor, imbalanced parenthesis\n");
                    exit(-1);
                }
            } else if (isdigit(token)) {
                value = readint();
            } else {
                printf("Error parsing factor\n");
            }
            
            printf("Factor value: %d\n", value);

            return value;
        }

        int term(void) {
            printf("In term\n");
            
            // get the mandatory first factor
            int value = factor();
            token = peek();

            // now handle the optional second factor
            if(token == '*') {
                pop(); // *
                value *= factor();       
            } else if(token == '/') {
                pop(); // /
                value /= factor();
            } // these are optional in the grammar, so no error if this is not found

            token = peek();
            
            // now handle the optional third term
            // since we're multiplying now, we only want to consider other multiplications and divisions, so that we don't accidentally add or subtract out of order.  the term grammar rule only has * and / in it, so that's safe.  We've built order of operations into our grammar!  It seems backwards, since we're worried about only multiplying and dividing in groups, but the expr's are "at the top" and will parse the + and - expressions once they resolve at the bottom.  That means these bottom "terms" resolve in their entirety first to a number that we *then* add together or subtract.
            // because there is no left recursion, we always know what to do next
            // but there is a common left prefix that we can try to simplify
            if(token == '*') {
                pop(); // *
                value *= term();       
            } else if(token == '/') {
                pop(); // /
                value /= term();
            } // these are optional in the grammar, so no error if this is not found    

            printf("Term value: %d\n", value);
            
            return value;
        }

        int expr() {
            printf("In expr\n");
            
            // get the mandatory first term
            int value = term();
            token = peek();

            // now handle the optional second term
            if(token == '+') {
                pop(); // +
                value += term();        
            } else if(token == '-') {
                pop(); // -
                value -= term();
            } // these are optional in the grammar, so no error if this is not found

            token = peek();
            
            // now handle the optional third expr
            // expr's have + and - in them, so it's safe to keep doing those since we're only adding and subtracting here (no risk of doing a multiplication)
            if(token == '+') {
                pop(); // +
                value += expr();        
            } else if(token == '-') {
                pop(); // -
                value -= expr();
            } // these are optional in the grammar, so no error if this is not found
            
            printf("Expression value: %d\n", value);
            
            return value;
        }

        int main(void) {
            token = peek();
            int result = expr();
            printf("Result: %d\n", result);

            return 0;
        }
        ]]></script> 
      title: "An LL(1) Parser Implemented with Recursive Descent"
      questions:
        - "Try this example with some sample calculations."
        - "An LL(1) parser requires a grammar with no left recursion, and with unique nonterminals starting each production.  Are these requirements met?  If not, on what inputs will this parser fail?  How can we fix it?"
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
         /*
          expr: term expr2
          expr2: addsub expr | null
          term: factor term2
          term2: muldiv term | null
          factor: num
                | "(" expr ")"
          addsub: "+" | "-"
          muldiv: "*" | "/"
          num: [0-9]+
         */
        ]]></script> 
      title: "An Alternative Grammar"
      questions:
        - "What is different about this grammar from the original one?"
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        %{

        #include <stdio.h>
        #include <stdlib.h>

        extern int yylex();
        extern int yyparse();
        extern FILE* yyin;

        void yyerror(const char* s);
        %}

        %union {
            int ival;
        }

        %token<ival> T_INT
        %token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_NEWLINE

        %type<ival> expr term factor
        %start calc

        %%

        calc:                               { printf("EOF\n"); exit(0); }
            | expr T_NEWLINE                { printf("%d\n", $1); exit(0); } // no return value needed, no type

        expr: term T_PLUS expr              { $$ = $1 + $3; }
            | term T_MINUS expr             { $$ = $1 - $3; }
            | term                          { $$ = $1; }
            
        term: factor T_MULTIPLY term        { $$ = $1 * $3; }
            | factor T_DIVIDE term          { $$ = $1 / $3; }
            | factor                        { $$ = $1; }
            
        factor: T_INT                       { $$ = $1; }            // just resolve the value!
              | T_LEFT expr T_RIGHT         { $$ = $2; }            // expr will resolve to a value!
              
        %%

        int main() {
            yyin = stdin;
            
            do {
                yyparse();
            } while(!feof(yyin));
        }

        void yyerror(const char* s) {
            fprintf(stderr, "Parse error: %s\n", s);
            exit(1);
        }

        // https://github.com/meyerd/flex-bison-example
        // the token types are as defined in the %union above
        ]]></script> 
      title: "Parsing with yacc"
      questions:
        - "How would you revise this to support the corrected LL(1) grammar?"
    - model: |
      <div align="left">
        xxx
      </div>
      title: "Generating an LR(0) Parse Table"
      questions: 
        - "Draw the state machine (the states and transitions) implemented by this LR(0) parse table."
        - "Augment the grammar and generate an LR(0) parse table for the grammar <code>S -> XX; X -> xXy; X -> x; X -> y</code>"        
    - model: |
        <a href="https://en.wikipedia.org/wiki/LR_parser#Bottom-up_parse_steps_for_example_A*2_+_1"><img alt="Wikipedia" src="https://upload.wikimedia.org/wikipedia/en/thumb/5/5f/Shift-Reduce_Parse_Steps_for_A%2A2%2B1.svg/512px-Shift-Reduce_Parse_Steps_for_A%2A2%2B1.svg.png"></a>
        <br>
        <!-- From https://en.wikipedia.org/wiki/LR_parser -->
        <style type="text/css">
        .tg  {border-collapse:collapse;border-spacing:0;}
        .tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg .tg-c2ay{background-color:#EAECF0;border-color:inherit;color:#202122;font-style:italic;font-weight:bold;text-align:center;
          vertical-align:top}
        .tg .tg-x6qv{background-color:#EAECF0;border-color:inherit;color:#202122;font-weight:bold;text-align:center;vertical-align:top}
        .tg .tg-89jx{background-color:#F8F9FA;border-color:inherit;color:#202122;font-weight:bold;text-align:left;vertical-align:top}
        .tg .tg-ft3i{background-color:#F8F9FA;border-color:inherit;color:#202122;text-align:left;vertical-align:top}
        .tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
        </style>
        <table class="tg">
        <thead>
          <tr>
            <th class="tg-x6qv"><span style="background-color:#EAECF0">Curr</span></th>
            <th class="tg-x6qv"></th>
            <th class="tg-x6qv" colspan="5"><span style="background-color:#EAECF0">Lookahead</span></th>
            <th class="tg-x6qv"></th>
            <th class="tg-x6qv" colspan="3"><span style="background-color:#EAECF0">LHS Goto</span></th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">State</span></td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">Current Rules</span></td>
            <td class="tg-c2ay">int</td>
            <td class="tg-c2ay">id</td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">*  </span></td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">+  </span></td>
            <td class="tg-c2ay">eof</td>
            <td class="tg-x6qv"></td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">Sums</span></td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">Products</span></td>
            <td class="tg-x6qv"><span style="background-color:#EAECF0">Value</span></td>
          </tr>
          <tr>
            <td class="tg-89jx">0</td>
            <td class="tg-ft3i">Goal → <span style="color:#F7F">•</span> Sums eof</td>
            <td class="tg-ft3i">8</td>
            <td class="tg-ft3i">9</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">1</td>
            <td class="tg-ft3i">4</td>
            <td class="tg-ft3i">7</td>
          </tr>
          <tr>
            <td class="tg-89jx">1</td>
            <td class="tg-ft3i">Goal → Sums <span style="color:#F7F">•</span> eof<br>Sums → Sums <span style="color:#F7F">•</span> + Products</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">2</td>
            <td class="tg-ft3i">done<br> </td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">2</td>
            <td class="tg-ft3i">Sums → Sums + <span style="color:#F7F">•</span> Products</td>
            <td class="tg-ft3i">8</td>
            <td class="tg-ft3i">9</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">3</td>
            <td class="tg-ft3i">7</td>
          </tr>
          <tr>
            <td class="tg-ft3i">3</td>
            <td class="tg-ft3i">Sums → Sums + Products <span style="color:#F7F">•</span><br>Products → Products <span style="color:#F7F">•</span> * Value</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">5</td>
            <td class="tg-ft3i">r1<br> </td>
            <td class="tg-ft3i">r1<br> </td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">4</td>
            <td class="tg-ft3i">Sums → Products <span style="color:#F7F">•</span><br>Products → Products <span style="color:#F7F">•</span> * Value</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">5</td>
            <td class="tg-ft3i">r2<br> </td>
            <td class="tg-ft3i">r2<br> </td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">5</td>
            <td class="tg-ft3i">Products → Products * <span style="color:#F7F">•</span> Value</td>
            <td class="tg-ft3i">8</td>
            <td class="tg-ft3i">9</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">6</td>
          </tr>
          <tr>
            <td class="tg-ft3i">6</td>
            <td class="tg-ft3i">Products → Products * Value <span style="color:#F7F">•</span></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">r3</td>
            <td class="tg-ft3i">r3</td>
            <td class="tg-ft3i">r3</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">7</td>
            <td class="tg-ft3i">Products → Value <span style="color:#F7F">•</span></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">r4</td>
            <td class="tg-ft3i">r4</td>
            <td class="tg-ft3i">r4</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">8</td>
            <td class="tg-ft3i">Value → int <span style="color:#F7F">•</span></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">r5</td>
            <td class="tg-ft3i">r5</td>
            <td class="tg-ft3i">r5</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
          </tr>
          <tr>
            <td class="tg-ft3i">9</td>
            <td class="tg-ft3i">Value → id <span style="color:#F7F">•</span></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i">r6</td>
            <td class="tg-ft3i">r6</td>
            <td class="tg-ft3i">r6</td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-ft3i"></td>
            <td class="tg-0pky"></td>
          </tr>
        </tbody>
        </table>
      title: "LR(0) Parse Tables"
      questions:
        - "Click on the image to see the steps involved with parsing <code>A*2 + 1</code>."
        - "Describe these steps in terms of the LR(0) parse table."
        - "What does the L, R, and 0 refer to in LR(0)?"
        
tags:
  - parser
  - interpreter
  
---

