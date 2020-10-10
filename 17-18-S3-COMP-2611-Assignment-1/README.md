# 17-18-S3-COMP-2611-Assignment-1
## Text Prediction Algorithm  
  
COMP2611/COMP2000 – Data Structures  
Semester 3, 2017-2018  
Assignment 1  
Predictive Text Due: 11.55 p.m., June 10th, 2018  

On a non-touch screen mobile phone, a text message word can be created by pressing the
digits 2 to 9.   
For example, to spell the word rake, you press 7 three times, 2 once, 5 twice and 3 twice.  
  
  
In so-called ‘predictive text’ mode, you will press 7 2 5 3 – each digit once and the phone
will try and figure out which word you want.   
If there are several possibilities, it will allow you to choose the one you want.   
In this example, possible words are pale, rake, sake and sale.   
The phone uses a dictionary to decide which combinations of letters are valid.  

<p align="center"> 
<img src="https://github.com/chris24s/17-18-S3-COMP-2611-Assignment-1/blob/master/keypad.PNG?raw=true">
</p>

Data are stored in the file input.txt.  

The first part of the data consists of the words in the dictionary in arbitrary order, one
word per line.   
Assume each word is no longer than 10 letters and there are no more than 100 words in the dictionary.   
This part of the data is terminated by the word $$$$.  
Following the dictionary is a set of ‘digit’ strings, one per line.   
For each string, print all possible ‘dictionary’ words which can be formed from that string.   
This part of the data is terminated by 0.  
  
All output must be sent to the file output.txt.  
You must use a binary search to look-up the dictionary.  
You may assume that all data are valid.  
