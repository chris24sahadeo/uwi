# 17-18-S3-COMP-2611-Assignment-2  
## Teams


COMP2611/COMP2000 – Data Structures  
Semester 3, 2017-2018  
Assignment 2  
Teams Due: 11.55 p.m., June 23rd, 2018  


Write a program to read data about persons who belong to certain teams and determine
the members of each team.

Data for the program consists of lines of input. Each line contains one or more distinct
one-word names, all of whom belong to the same team. You may assume that names
consist of letters only, upper or lowercase, and are separated by one or more blanks. For
our purposes, the names john, JOHN, jOHn and JohN all refer to the same person and
should be output as John (first letter uppercase, the rest lowercase). Assume that no
name contains more than 20 letters.

The data structure must be organized such that, given any name, all his/her team
members can be quickly found. A name can appear on more than one line. If a name
appears on more than one line then all names on those lines belong to the same team.
After all the data has been read, print a listing of the teams as in the sample below. Team
members must be listed in alphabetical order. The teams are listed in order by the first
names of each team. For example, a team with Janet as the first name (in alphabetical
order) will be listed before a team with Lovette as the first name.


### Sample input
ConRad peter BETTY connie  
Richard leonard Davindra  
Kelvin kade  
Rebecca  
Kerron Kade Kamal  
Lincia Indra angela JennifeR  


### Sample output
Team 1  
Angela Indra Jennifer Lincia  
Team 2  
Betty Connie Conrad Peter  
Team 3  
Davindra Leonard Richard  
Team 4  
Kade Kamal Kelvin Kerron  
Team 5  
Rebecca  
