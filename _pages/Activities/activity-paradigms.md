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
        <script type="syntaxhighlighter" class="brush: java"><![CDATA[
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
      title: "Imperative Languages"
      questions:
        - "What defines a statement?"
        - "What, in general, does a statement realy do?"
        - "At what points do the value of root change?"
        - "What would happen if <code>a</code> is 0?"
        - "How can we represent this program using an Object-Oriented style?  What state might the object represent?"
    - model: |
        <script type="syntaxhighlighter" class="brush: c"><![CDATA[
        #include <string.h>
        #include <stdlib.h>
        #include <stdio.h>

        struct Person {
            char* name;
            int age;
            float salary;
        };

        void tax(struct Person* p) {
            if(p->salary > 100000) {
                p->salary = p->salary * 0.85;
            } else {
                p->salary = p->salary * 0.95;
            }
        }

        int main(void) {
            struct Person* bill = (struct Person*) malloc(sizeof(struct Person));
            bill->name = (char*) malloc(strlen("Bill")+1);
            strncpy(bill->name, "Bill", strlen("Bill")+1);
            bill->age = 38;
            bill->salary = 20000;
            tax(bill);
            printf("%s (%d): %f\n", bill->name, bill->age, bill->salary);
            free(bill);
        }
        ]]></script> 
      title: "The C Programming Language and Memory Management"
      questions:
        - "What is the value of <code>bill->salary</code> after the call to <code>tax()</code>?"        
        - "The above program has a memory leak.  Which variable should also be freed?"
        - "Why is there a <code>+1</code> in the <code>malloc</code> call on <code>bill->name</code>?"
        - "Suppose we had set <code>p</code> equal to a newly <code>malloc</code>'ed person in <code>tax</code>.  How would this affect <code>bill</code>?"
    - model: |
        <script type="syntaxhighlighter" class="brush: java"><![CDATA[  
        import java.util.Random;
        
        public abstract class Vehicle {
            protected int gear;
            protected boolean parked;
            protected int speed;
            protected boolean locked;
         
            public Vehicle() {
               this.gear = 1;
               this.parked = true;
               this.speed = 0;
               this.locked = true;
            }
         
            public void drive(int speed) {
               if(this.parked == true) {
                 this.parked = false;
               }
               this.speed = speed;
            }
         
            // return a boolean if the vehicle is parked
            public abstract boolean stop();
         
            public int getSpeed() {
               return this.speed;
            }
         
            public void unlock() {
               this.locked = false;
            }
         
            public void lock() {
               this.locked = true;
            }
        }
        
        public interface Home {
            public int cook();
         
            public void makeBed();
        }

        public class Car extends Vehicle {
             public Car() {
               super();
             }
             
             public void drive(int speed) {
               super.drive(speed);
             
               this.gear = this.speed / 10;
             }
             
             // return a boolean if the vehicle is parked
             public boolean stop() {
               this.speed = 0;
               this.gear = 1;
               return this.parked;
            }
        }
        
        // Unlike interfaces, you can only extend a single class
        public class MotorHome extends Vehicle implements Home {
             private boolean bedmade;
             
             public MotorHome() {
               super();
               this.bedmade = true;
             }
             
             public void drive(int speed) {
               super.drive(speed);
             
               this.gear = this.speed / 5;
             }
             
             // return a boolean if the vehicle is parked
             public boolean stop() {
               this.speed = 0;
               this.gear = 1;
               return this.parked;
             }
             
             public int cook() {
               return 1; // yum?
             }
             
             public void makeBed() {
               this.bedmade = true;
             }
             
             public boolean isBedMade() {
               return this.bedmade;
             }
        }

        class Main {
             public static void main(String[] args) {
               Random r = new Random();
             
               Vehicle[] vehicles = new Vehicle[2];
             
               Car c = new Car();
               MotorHome m = new MotorHome();
             
               vehicles[0] = c;
               vehicles[1] = m;
             
               m.makeBed();
             
               for(Vehicle v: vehicles) {
                 v.drive(r.nextInt(50));
               }
             
               // Methods in the Interface can be called on variables whose type is just the interface, no matter what it really is!
               System.out.println("How fast is the car driving? " + vehicles[0].getSpeed());
             
               System.out.println("How about the Motor Home? " + vehicles[1].getSpeed());
             
               // Methods specific to a class can always be called from the object.
               System.out.println("Is the Motor Home bed made? " + m.isBedMade());
             }
        }
        ]]></script>    
      title: "The Object-Oriented Paradigm"
      questions:
        - How did each file change above by converting the <code>Vehicle</code> interface to a class?
        - By converting the <code>Vehicle</code> interface to a class, what can we now define in a <code>Vehicle</code> that we could not define in the <code>interface</code>?
        - You can implement an <code>interface</code>; what is the keyword to subclass a class?
        - From context, what do you think the abstract keyword means in the <code>Vehicle</code> class?
        - From context, what do you think the call to <code>super()</code> does?
        - Notice that some elements are scoped to be <code>public</code> and <code>private</code>, like before, but now some items are <code>protected</code>.  Which items are <code>protected</code>, and in which files do they reside?  What do you think this scope allows/disallows?
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
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
        (define L (list 'a 'b 'c))
        (car L)
        (cdr L)
        
        (define x (+ 3 2))
        (+ x 5)
        
        (define add +)
        (add 3 2)
        ]]></script>
        <br>
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
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
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
        (define y
          (lambda(m x b)
            (+ (* x m) b)))
            
        (y 5 6 7)
        ]]></script>
        <br>
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
        (define v0 3)
        (define t 5)
        (define a 9.80665)

        (define square
          (lambda(n)
            (* n n)))
            
        (+ (* v0 t) (* 0.5 (* a (* t t))))

        (+ (* v0 t) (* 0.5 (* a (square t))))
        ]]></script>     
        <br>
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
        (define czr
          (lambda(l)
            (if (null? (cdr l))
              (car l)
              (czr (cdr l))
            )
          )
        )
        ]]></script>  
        <br>
        <script type="syntaxhighlighter" class="brush: scheme"><![CDATA[
        (define plusminus 
          (lambda(a b)
            (
              (lambda (x y) (list (+ x y) (- x y)))
              a b
            )
          )
        )

        (plusminus 6 2)
        ]]></script>          
      title: "The Scheme Programming Language"
      questions: 
        - "How are function parameters handled in Scheme?  Are they passed by value or by reference?"        
        - "What is a function in Scheme?  How is it represented?"
        - "What does <code>czr</code> do in your own words?"
        - "Write a function to count the number of items in a list using a recursive call and a base case, using <code>czr</code> as a guide to traversing a list."
        - "Diagram the binding of the values in the call to <code>plusminus</code>."
    - model: |
        <script type="syntaxhighlighter" class="brush: prolog"><![CDATA[
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
        - "Write a <a href=\"https://en.wikipedia.org/wiki/Horn_clause#Definition\">Horn Clause</a> that specifies that one might go outside if it is warm and not raining outside."
    - model: |
        <script type="syntaxhighlighter" class="brush: prolog"><![CDATA[
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
        <script type="syntaxhighlighter" class="brush: python"><![CDATA[
        heights = [50, 62, 73, 58, 46, 49, 43]
        minheight = 48
        canride = []
        canride2 = []
        
        # version 1
        for height in heights:
            if height > minheight:
                canride.append(height)
          
        # version 2
        canride2 = [height for height in heights if height > minheight]  

        # version 3
        canridebool = list(map(lambda height: height > minheight, heights))
        canride3 = [x[0] for x in zip(heights, canridebool) if x[1]]
        ]]></script> 
      title: "Applications of the Declarative Paradigm - Pythonic List Comprehension"
      questions:
        - "What are the advantages and disadvantages of each approach?"         
        - "Which version do you find more convenient and why?"   
    - model: |
        <script type="syntaxhighlighter" class="brush: bash"><![CDATA[
         #!/bin/bash
         
         COURSE=CS374
         cd ${COURSE}
         
         FILES=$(ls *.txt)
         echo ${FILES}
        ]]></script> 
      title: "Scripting Languages - Bash"
      questions:
        - "What is a statement in this language?"
        - "How are variables expanded?"
        - "What potential benefit can you see with the use of shell scripting?" 
        - "Are scripting languages imperative or declarative?" 
    - model: |
        <script type="syntaxhighlighter" class="brush: bash"><![CDATA[
         #!/bin/bash
         
         let "x = $1 * 2" # equivalent to x=$(expr $1 \* 2) and x=$(($1 * 2))
         let x++
         
         NAME="Alexandra"
         echo ${NAME} has ${#NAME} characters in it
         echo ${NAME} goes by ${NAME:0:4} for short.
         echo ${NAME%a*} ${NAME%%a*} # the # sign instead of % in the variable expansion 
                                     # does this behavior from the left instead of the right    

         echo ${NAME/xandra/jandro}
                                     
         echo Here is a name that doesn't exist yet: ${NAME2}
         echo Here is the value of another variable: ${NAME2:=Unknown} 
         echo How about now: ${NAME2}
        ]]></script> 
        <br>
        <script type="syntaxhighlighter" class="brush: bash"><![CDATA[
         #!/bin/bash
         
         x=0
         while [[ ${x} -lt 10 ]] # (( ${x} < 10 )) is also acceptable
         do
                 echo ${x}
                 x=$((${x} + 1))
         done
         
         if [[ ${x} -eq 10 ]] # (( ${x} == 10 )) is also acceptable
         then
            echo "x is now 10"
         else
            echo "x is not 10 but rather ${x}"
         fi
         
         if [[ -e 'doit.sh' ]]
         then
            echo "doit.sh exists"
         else
            echo "doit.sh does not exist"
         fi

         if [[ -d 'doit.sh' ]]
         then
            echo "doit.sh is a directory"
         else
            echo "doit.sh is not a directory"
         fi         
        ]]></script>         
      title: "Programming Constructs in bash"
      questions:
        - "What do you think <code>$1</code> means?"
        - "If <code>$1</code> is 5, what is the final value of <code>x</code>?"
        - "Why was the <code>&#92;</code> character necessary in the <code>x=$(expr $1 &#92;* 2)</code> command?"
        - "What do each of the variable expansions do in the first example above?"
        - "What would happen if the <code>-lt</code> in the loop above was modified to <code>&lt;</code>?  Similarly, what is the difference between <code>-eq</code> and <code>=</code> in bash?"   
    - model: |
        <div align="left">
        <h3>Concurrency in the Go Language</h3>
        <iframe src="https://tour.golang.org/concurrency/2" title="Concurrency in the Go Language" width="90%" height="600"></iframe>
        <br>
        <h3>Non-Blocking Concurrency Channels in the Go Language</h3>
        <iframe src="https://gobyexample.com/non-blocking-channel-operations" title="Non-Blocking Concurrency with Channels in the Go Language" width="90%" height="600"></iframe>
        <br>
        <iframe src="https://www.thepolyglotdeveloper.com/2017/05/network-sockets-with-the-go-programming-language/" title="Socket Programming in the Go Language" width="90%" height="600"></iframe>
        </div>
      title: "Concurrent and Socket Programming in the Go Language"
      questions: 
        - "How might you add concurrency to a socket program to allow the program to send data without having to wait to receive a message?"        
  additional_reading:
    - title: "Concise Introduction to Prolog"
      link: "https://www.cis.upenn.edu/~matuszek/Concise%20Guides/Concise%20Prolog.html"
    - title: "The Scheme Programming Language"
      link: "https://www.scheme.com/tspl3/"
    - title: "Bash Syntax Reference"
      link: "https://tiswww.case.edu/php/chet/bash/bashref.html"
    - title: "Bash Scripting Tutorial"
      link: "https://linuxconfig.org/bash-scripting-tutorial-for-beginners" 
    - title: "MapReduce"
      link: "https://web.archive.org/web/20150226152956/http://jsmapreduce.com/"
    
tags:
  - paradigms
  
---

