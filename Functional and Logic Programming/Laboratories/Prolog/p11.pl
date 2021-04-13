%a. substitute one elem with another
%p11a(L:list,P1:pos1,P2:pos2,R:list).

%index start with 0!!!
p11_elem([H|_],0,H).
p11_elem([_|T],P,R):-
    P1 is P-1,
    p11_elem(T,P1,R).

%p11_aux(L:list,E:elem,P:pos,R:list)
p11_aux([],_,_,[]).
p11_aux([_|T],E,P,R):-
    P=0,
    P1 is P-1,
    p11_aux(T,E,P1,R1),
    R=[E|R1].
p11_aux([H|T],E,P,R):-
    P\=0,
    P1 is P-1,
    p11_aux(T,E,P1,R1),
    R=[H|R1].

p11a([],_,_,[]).
p11a(L,P1,P2,R):-
    p11_elem(L,P1,E1),
    p11_elem(L,P2,E2),
    p11_aux(L,E2,P1,R1),
    p11_aux(R1,E1,P2,R2),
    R=R2.
