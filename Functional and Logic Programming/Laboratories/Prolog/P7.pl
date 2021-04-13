%member(E:elem, L:list) -checks if e is in list L
%flow model: (i,i), (o,i).
p7_member(E,[_|L]):-
    p7_member(E,L).
p7_member(E,[E|_]).

%p7_a(A:set, B:set, R:set)
%flow model: (i,i,o), (i,i,i)

%math model: p7a(a1..an,b1..bm):-
%                   [] if n=0
%                   [] if m = 0
%                   a1 U p7a(a2..an,b1..bm) if a1 in b1.bm
%                   p7a(a2..an,b1..bm) otherwise

p7_a([],_,[]).
p7_a(_,[],[]).
p7_a([H|T],B,R):-
    p7_member(H,B),
    p7_a(T,B,R1),
    !,
    R=[H|R1].
p7_a([H|T],B,R):-
    %not(p7_member(H,B)),
    p7_a(T,B,R).

%interval(a:int, b:int, R:list)
%flow model(i,i,o),(i,i,i)

%math model: interval(a,b)-
%                   [] if b<a
%                   a U interval(a+1,b) if a < b
p7_interval(A,B,R):-
    B<A,
    R=[].
p7_interval(A,A,[A]).
p7_interval(A,B,R):-
    A<B,
    A1 is A+1,
    p7_interval(A1,B,R1),
    R=[A|R1].
