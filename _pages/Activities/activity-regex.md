---
layout: activity
permalink: /Activities/Regex
title: "CS374: Programming Language Principles - Regular Expressions"
excerpt: "CS374: Programming Language Principles - Regular Expressions"

info: 
  goals: 
    - To define regular expressions
    - To relate regular expressions to lexemes
  models:
    - model: |
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        I think you are right!!!
        What do you think of this?
        WHY DOES IT WORK THIS WAY
        What else do you think?
        (610)555-1212
        ]]></script> 
        <br>
        <script type="syntaxhighlighter" class="brush: cpp"><![CDATA[
        .*!{3}.*
        What.*do
        What.*do*
        [A-Z ]+
        \(?\d{3}\)?\d{3}-\d{4}
        ]]></script> 
      title: Regular Expressions
      questions:
        - "What lines do you think are matched by each of the regular expressions?"
        - "How would you modify the phone number matching regular expression to allow an optional space in-between the area code and phone number?"
    - model: |
        <img src="https://slideplayer.com/slide/12841769/78/images/34/TREASURE+HUNT%3A+Treasure+Island.jpg" alt="CS Unplugged Finite State Machine Activity">
      title: Languages for a Finite State Machine
      questions:
        - "What pattern of A and B would take one from Shipwreck Bay to Treasure Island?"
        - "What regular expression automatically checks that a series of navigational guesses would lead from Shipwreck Bay to Treasure Island?  Note that [AB] means to match either character A or B once."
  additional_reading:
    - title: "Regex Parser Online"
      link: "https://regex101.com/"    
tags:
  - regex
  
---

