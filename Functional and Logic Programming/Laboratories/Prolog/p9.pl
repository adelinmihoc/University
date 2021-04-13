%insert an elem on pos n in list

%list start with pos 0;
%p9a(L:list,E:elem,N:pos,R:list)
p9a([],_,_,[]).
p9a([H|T],E,N,R):-
    N=\=0,
    N1 is N-1,
    p9a(T,E,N1,R1),
    R=[H|R1].
p9a([H|T],E,N,R):-
    N=:=0,
    N1 is N-1,
    p9a(T,R,N1,R1),
    R=[H,E|R1].

p9b_gcd(0,B,B).
p9b_gcd(A,B,R):-
    A1 is mod(B,A),
    B1 is A,
    p9b_gcd(A1,B1,R).

p9b([E],E).
p9b([H|T],R):-
    p9b(T,R1),
    p9b_gcd(H,R1,R).
