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