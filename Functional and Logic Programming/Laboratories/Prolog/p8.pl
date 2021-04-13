%even number of elems? not counting

p8([]).
p8([_|[_|T]]):-
    p8(T).

p8_min([E],E).
p8_min([H|T],E):-
    p8_min(T,E1),
    H<E1,
    E is H.
p8_min([H|T],E):-
    p8_min(T,E1),
    not(H<E1),
    E is E1.

p8b_aux([],_,_,[]).
p8b_aux([H|T],L,C,R):-
    p8_min(L,H),
    C=:=1,
    C1 is 0,
    p8b_aux(T,L,C1,R1),
    R=R1.
p8b_aux([H|T],L,C,R):-
    p8_min(L,H),
    C=:=0,
    p8b_aux(T,L,C,R1),
    R=[H|R1].
p8b_aux([H|T],L,C,R):-
    not(p8_min(L,H)),
    p8b_aux(T,L,C,R1),
    R=[H|R1].
