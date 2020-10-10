% Prolog syntax
% 
% Term
% 	variable
% 	contents
% 		number
% 		atom
% 	compound terms

 
% % FACTS 
% with contents->atoms, atoms do not start with a capital letter or a number, only underscores or common letters
% males
male(john).
male(craig).
male(sammy).
male(jack).
male(johnny_bravo).


% females
female(sarah).
female(rachel).
female(rose).
female(sakura).
female(sam). % sam is both male and female


% children
child(craig, john). % craig is the child of john
child(craig, sarah). % craig is the child of sarah
child(sam, craig).
child(sam, rose).
child(sakura, craig).
child(sakura, rose).
%child(johnny_bravo, )




% RULES (used for queries)
% a rule with varibles,variables always start with capital letters
% checks if X is the father of Y
father(X, Y):-
    male(X),
    child(Y, X).

% checks if X is a parent of Y
parent(X, Y):-
    child(Y, X).

% X is not a parent of Y
not_parent(X, Y):-
    not(parent(X, Y)).

% checks if X is a grandparent of Z
% Y is an on the fly unifying variable
grandparents(X, Z):-
    parent(X, Y),
    parent(Y, Z).

% at least one parent is the same
half_or_full_sibling(X, Y):-
    parent(Z, X),
    parent(Z, Y).

% half sibling
half_sibling(X, Y):-
    child(X, P1),
    child(Y, P1),
    child(X, P2),
    not(X = Y),
    not(P1 = P2),
    not_parent(P2, Y).    

% full sibling
% find all possible parents of X and Y
% parents must not be the same and X and Y must not be the same
full_sibling(X, Y):-
    parent(P1, X),
    parent(P2, X),
    parent(P1, Y),
    parent(P2, Y),
    not(P1 = P2),
    not(X = Y).

% predicates
% findall predicate
all_children_of(Parent, Children):-
    finaall(Child, child(Child, Parent), children).
   	
    
    