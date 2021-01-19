---
layout: activity
permalink: /Activities/Grammars
title: "CS374: Programming Language Principles - Grammars"
excerpt: "CS374: Programming Language Principles - Grammars"

info: 
  goals: 
    - To describe a grammar in terms of tokens in BNF form
    - To disambiguate a grammar
  models:
    - model: |
        <a title="J. Finkelstein, CC BY-SA 3.0 &lt;https://creativecommons.org/licenses/by-sa/3.0&gt;, via Wikimedia Commons" href="https://en.wikipedia.org/wiki/Chomsky_hierarchy#The_hierarchy"><img width="512" alt="Chomsky-hierarchy" src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9a/Chomsky-hierarchy.svg/512px-Chomsky-hierarchy.svg.png"></a>
        <br>
        <!-- From Wikipedia https://en.wikipedia.org/wiki/Chomsky_hierarchy 
             and https://www.cs.ru.nl/~herman/onderwijs/2016TnA/lecture7.pdf -->
        <style type="text/css">
        .tg  {border-collapse:collapse;border-spacing:0;}
        .tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
          font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
        .tg .tg-7btt{border-color:inherit;font-weight:bold;text-align:center;vertical-align:top}
        .tg .tg-fymr{border-color:inherit;font-weight:bold;text-align:left;vertical-align:top}
        .tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
        </style>
        <table class="tg">
        <thead>
          <tr>
            <th class="tg-7btt"><span style="background-color:#EAECF0">Grammar</span></th>
            <th class="tg-7btt"><span style="background-color:#EAECF0">Languages</span></th>
            <th class="tg-7btt"><span style="background-color:#EAECF0">Automaton</span></th>
            <th class="tg-7btt"><span style="background-color:#EAECF0">Production rules (constraints)*</span></th>
            <th class="tg-7btt"><span style="background-color:#EAECF0"><a href="https://www.cs.ru.nl/~herman/onderwijs/2016TnA/lecture7.pdf">Examples</a></span></th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td class="tg-fymr">Type-0</td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Recursively_enumerable_language"><span style="text-decoration:none;color:#0B0080;background-color:initial">Recursively enumerable</span></a></td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Turing_machine"><span style="text-decoration:none;color:#0B0080;background-color:initial">Turing machine</span></a></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/902fc01e3f2cc85935e36efe834b543eb6b19d5b" alt="{\displaystyle \gamma \rightarrow \alpha }" width="46" height="17"><br>(no constraints)</td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/46f75a36ee91fb70c39b78145c087df4abdb1035" alt="{\displaystyle L=\{w|w}" width="71" height="21"># describes a terminating Turing machine<img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/2cf208e5d370391e66767f13641bd5ee6ad93825" alt="\}" width="8" height="21"></td>
          </tr>
          <tr>
            <td class="tg-fymr">Type-1</td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Context-sensitive_grammar"><span style="text-decoration:none;color:#0B0080;background-color:initial">Context-sensitive</span></a></td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Linear_bounded_automaton"><span style="text-decoration:none;color:#0B0080;background-color:initial">Linear-bounded non-deterministic Turing machine</span></a></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/1173552bcbf68bb06baf9b0a2f543dbc845caefd" alt="\alpha A \beta \rightarrow \alpha \gamma \beta" width="89" height="19"></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/2bb63b71ffcba840f36e802aafe4c9951cf9ec38" alt="{\displaystyle L=\{a^{n}b^{n}c^{n}|n>0\}}" width="147" height="21"></td>
          </tr>
          <tr>
            <td class="tg-fymr">Type-2</td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Context-free_grammar"><span style="text-decoration:none;color:#0B0080;background-color:initial">Context-free</span></a></td>
            <td class="tg-0pky">Non-deterministic <a href="https://en.wikipedia.org/wiki/Pushdown_automaton"><span style="text-decoration:none;color:#0B0080;background-color:initial">pushdown automaton</span></a></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/13dc432701b1477bc9ba32b0d71c58ecf2d44d9e" alt="{\displaystyle A\rightarrow \alpha }" width="50" height="16"></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/dfafe0fa14e5249f492f5cbde42062ba4904d56f" alt="{\displaystyle L=\{a^{n}b^{n}|n>0\}}" width="130" height="21"></td>
          </tr>
          <tr>
            <td class="tg-fymr">Type-3</td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Regular_grammar"><span style="text-decoration:none;color:#0B0080;background-color:initial">Regular</span></a></td>
            <td class="tg-0pky"><a href="https://en.wikipedia.org/wiki/Finite_state_automaton"><span style="text-decoration:none;color:#0B0080;background-color:initial">Finite state automaton</span></a></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/c5a21ff7c854fa27daf7ab3882590f938e5720e9" alt="{\displaystyle A\rightarrow {\text{a}}}" width="47" height="16"><br>and<br><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/8a487d4dba9e9959ea3a34e06b5e5677c8eff4d4" alt="{\displaystyle A\rightarrow {\text{a}}B}" width="60" height="16"></td>
            <td class="tg-0pky"><img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/2d8085f37ec7d2aa499b0d27008c940279088d09" alt="{\displaystyle L=\{a^{n}|n\geq 0\}}" width="114" height="21"></td>
          </tr>
        </tbody>
        </table>
      title: Chomsky Hierarchy of Languages
      questions:
        - xxx
  additional_reading:
    title: "Formal Languages Notes"
    link: "https://www.cs.ru.nl/~herman/onderwijs/2016TnA/lecture7.pdf"
      
tags:
  - grammar
  
---

