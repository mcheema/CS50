# CS50
## Introduction
This repository is to share my submissions, alternate implementations, and notes for 2023 and 2024 iterations of Harvard's CS50 project. This work is done as part of the Q1, 2024, C study group organised by the R Core contributors team.
## Other Repositories from the R-core Bookclub: c study group 2024

1. https://github.com/EllaKaye/cs50/
2. https://github.com/jimgar/c-study-group/tree/main

## Lecture 1 Takeaways
Main problem featured [Luhn's Algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm)

C language semantics will truncate any double or float assigned/cast to an integer. This built in feature was highlighted in the learning materials and expected be exploited in the problem set. provides a *trunc* function out of the box. Which avoids some gotchas that relying on language semantics has. Also, *trunc* and *floor*, another function provided by "math.h", are almost identical except in the case of negative numbers which can lead to another type of gotcha when the full domain of reals is possible (edited) 

## Lecture 2 Takeaways
In the Section tutorial the instructor misspoke and asserted that if the initialiser of an array is incomplete then the uninitialised part of the array would be filled with garbage values. In the [C99 standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) though they would be set to 0:

> If there are fewer initializers in a brace-enclosed list than there are elements or members of an aggregate, or fewer characters in a string literal used to initialize an array of known size than there are elements in the array, the remainder of the aggregate shall be initialized implicitly the same as objects that have static storage duration.
## Glossary
### Operators
1. `=`: Is either a) an Initialiser when part of a _declaration_ or b) assignment operator when part of an expression.
### Preprocessor Directive (AKA macro)
1. #include _filename_ - inserts the contents of _filename_ into this file
2. #define _macroname_ _definition_ - creates a symbolic constant _macroname_ and replaces each instance of it with _definition_

