%a. Define a predicate to remove from a list all repetitive
%elements.
%Eg.: l=[1,2,1,4,1,3,4] => l=[2,3])
% b. Remove all occurrence of a maximum value from a list
%on integer numbers

%p3_count(L:list,E:elem,R:int)
%flow model: (i,i), (i,o).
p3_count([],_,0).
p3_count([H|T],E,R):-
    H=:=E,
    p3_count(T,E,R1),
    R is R1+1.
p3_count([H|T],E,R):-
    H=\=E,
    p3_count(T,E,R).

%p3_remove_aux(L:list,L2:list,R:list)
%flow model: (i,i,i), (i,i,o)
p3_remove_aux([],_,[]).
p3_remove_aux([H|T],L,R):-
    p3_count(L,H,1),
    p3_remove_aux(T,L,R1),
    R=[H|R1].
p3_remove_aux([H|T],L,R):-
    not(p3_count(L,H,1)),
    p3_remove_aux(T,L,R).

%p3_remove(L:list,R:list).
%flow model: (i,i), (i,o)
p3_remove(L,R):-H
    p3_remove_aux(L,L,R).

%p3_max(L:list,R:int)
%flow model:(i,i),(i,o)
p3_max([E],E).
p3_max([H|T],R):-
    p3_max(T,R1),
    H>R1,
    R is H.
p3_max([H|T],R):-
    p3_max(T,R1),
    H=<R1,
    R is R1.

%p3_aux(L:list,L2:list,R:list)
%flow model: (i,i,i),(i,i,o)
p3_aux([],_,[]).
p3_aux([H|T],L,R):-
    p3_max([H|T],H),
    p3_aux(T,L,R).
p3_aux([H|T],L,R):-
    not(p3_max([H|T],H)),
    p3_aux(T,L,R1),
    R=[H|R1].

%p3b(L:list,R:list)
%flow model: (i,i),(i,o)
p3b(L,R):-
    p3_aux(L,L,R).
