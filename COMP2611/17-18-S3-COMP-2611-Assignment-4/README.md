# 17-18-S3-COMP-2611-Assignment-4
## User Identifiers  
  
Write a program to produce a cross-reference listing of the user identifiers in a C/C++ program.  

## Output   
Consists of the given program with the lines numbered.   
This is followed by an alphabetical listing of the identifiers; each identifier is followed by the line number(s) in which the identifier
appears.   
Identifiers within string constants (delimited by double quotes) or comments (delimitedby /* and */) are not to be included. Identifiers within // comments are not to be included.  
Identifiers within single quotes (character constants) are not to be included.   
Reserved words are not to be included.  
Identifiers must be kept in a binary search tree and the line number(s) for a given identifier held on a linked list.   

## Input
List of reserved words (in no particular order and any number per line) terminated by the word ENDOFLIST on a line by itself.   
This is followed by the program to be cross-referenced.
