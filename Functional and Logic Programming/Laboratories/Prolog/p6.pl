%test if list is set

p6_count([],_,0).
p6_count([H|T],E,R):-
    p6_count(T,E,R1),
    H=:=E,
    R is R1+1.
p6_count([H|T],E,R):-
    p6_count(T,E,R1),
    H=\=E,
    R is R1.

p6([]).
p6([H|T]):-
    p6_count([H|T],H,1),
    p6(T).

p6b([],_,_,[]).
p6b(L,_,0,L).
p6b([H|T],E,C,R):-
    H=:=E,
    C1 is C-1,
    p6b(T,E,C1,R).
p6b([H|T],E,C,R):-
    H=\=E,
    p6b(T,E,C,R1),
    R=[H|R1].

