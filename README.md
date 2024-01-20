# CS50
## Introduction
This repository is to share my submissions, alternate implementations, and notes for 2023 and 2024 iterations of Harvard's CS50 project. This work is done as part of the Q1, 2024, C study group organised by the R Core contributors team.
## Other Repositories from the R-core Bookclub: c study group 2024

1. https://github.com/EllaKaye/cs50/
2. https://github.com/jimgar/c-study-group/tree/main

## Lecture 1 Takeaways
C language semantics will truncate any double or float assigned/cast to an integer. This built in feature was highlighted in the learning materials and expected be exploited in the problem set. provides a *trunc* function out of the box. Which avoids some gotchas that relying on language semantics has. Also, *trunc* and *floor*, another function provided by "math.h", are almost identical except in the case of negative numbers which can lead to another type of gotcha when the full domain of reals is possible (edited) 


## Glossary
### Operators
1. `=`: Is either a) an Initialiser when part of a _declaration_ or b) assignment operator when part of an expression.
### Preprocessor Directive (AKA macro)
1. #include _filename_ - inserts the contents of _filename_ into this file
2. #define _macroname_ _definition_ - creates a symbolic constant _macroname_ and replaces each instance of it with _definition_

