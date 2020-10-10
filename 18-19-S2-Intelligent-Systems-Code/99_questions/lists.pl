% my attempts

% 1 - last element
last([], '').
last([H|T], X) :- T = [], X is H.
last([H|T], X) :- last(T, X).
% we must pass the SAME variable (in this case X) along the recursion trace as we go


% 2 - poor instructions


% 3 - kth  element
kth([], _, 'out of bounds').
kth([H|T], K, X) :- K = 1, X is H.
kth([H|T], K, X) :- L is K - 1, kth(T, L, X).
% only works with a list of integers, not atoms
% note we are not allowed to say X is X - 1, must use another variable: X1 =  X - 1