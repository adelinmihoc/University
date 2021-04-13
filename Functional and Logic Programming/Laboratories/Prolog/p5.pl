%a. Write a predicate to compute the union of two sets.
%b. Write a predicate to determine the set of all the pairs of
%elements in a list.
%Eg.: L = [a b c d] => [[a b] [a c] [a d] [b c] [b d] [c d]].

p5_member([L|_],L).
p5_member([_|L],E):-
    p5_member(L,E).

%p5a(A:set,B:set,R:rez)
p5a([],B,B).
p5a(A,_,A).
p5a([H1|T1],[H2|T2],R):-
    p5a(T1,T2,R1),
    p5_member(R1,H1),
    p5_member(R1,H2),
    R=R1.
p5a([H1|T1],[H2|T2],R):-
    p5a(T1,T2,R1),
    p5_member(R1,H1),
    not(p5_member(R1,H2)),
    R=[H2|R1].
p5a([H1|T1],[H2|T2],R):-
    p5a(T1,T2,R1),
    not(p5_member(R1,H1)),
    p5_member(R1,H2),
    R=[H1|R1].


%p5b(L:list,R:list)
%p5b_aux(E:elem,L:list,R:list)form a pair[E,_] every e in L
p5b_aux(_,[],[]).
p5b_aux(E,[H1|T1],R):-
    p5b_aux(E,T1,R1),
    R=[[E,H1]|R1].

p5b([],[]).
p5b([H|T],R):-
    p5b(T,R1),
    p5b_aux(H,T,R2),
    R=[R2|R1].

