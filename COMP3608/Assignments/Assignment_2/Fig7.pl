% Christopher Sahadeo
% 816000772
% christophersahadeo@gmail.com
% COMP 3608

:- dynamic f1/1.

f1(_A).
f1(_B).
f1(_C).
f1(_D).
f1(_E).

r1(_Z) :- 
    r2(_Y), f1(_D), 
    writeln("R1: Asserted Z"),
    assertz(f1(_Z)).

r2(_Y) :- 
    r3(_X), f1(_B), f1(_E), 
    writeln("R2: Asserted Y"),
    assertz(f1(_Y)).

r3(_X) :- 
    f1(_A), 
    writeln("R3: Asserted X"),
    assertz(f1(_X)).
   	
r4(_L) :-
    f1(_C),
    writeln("R4: Asserted L"),
    assertz(f1(_L)).

r5(_N) :-
    r4(_L), f1(_M),
    writeln("R5: Asserted N"),
    assertz(f1(_N)).