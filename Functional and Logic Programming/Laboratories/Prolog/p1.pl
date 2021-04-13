%a. Write a predicate to determine the lowest common multiple of a
% list formed from integer numbers.

% p1_gcd(A:int,B:int,R:int) --> greates common divisor with Euclid
% Algorithm
% flow model: (i,i,i),(i,i,o)
p1_gcd(0,B,B):-!.
p1_gcd(A,B,R):-
    A1 is B mod A,
    B1 is A,
    p1_gcd(A1,B1,R).

%p1_lcm(A:int,B:int,R:int) --> least common multiple = A*B/gcd(A,B)
%flow model: (i,i,i), (i,i,o)
p1_lcm(A,B,R):-
    C is A*B,
    p1_gcd(A,B,D),
    R is C/D.

%p1(L:list,R:int)
%flow model:(i,o), (i,i)
p1([H],R):-
    R is H.
p1([H|T],R):-
    p1(T,R1),
    p1_lcm(H,R1,R).


% b. Write a predicate to add a value v after 1-st, 2-nd, 4
%th, 8-th, …
% element in a list.

%p1b_insert_aux(L:list,E:elem,P:int,C:int,R:list)
%flow model(i,i,i,i,o)
p1b_insert_aux([],_,_,_,[]).
p1b_insert_aux([H|T],E,P,C,[H,E|TR]):-
    P=:=C,
    C1 is C+1,
    P1 is P*2,
    p1b_insert_aux(T,E,P1,C1,TR).
p1b_insert_aux([H|T],E,P,C,[H,TR]):-
    P=\=C,
    C1 is C+1,
    p1b_insert_aux(T,E,P,C1,TR).

%p1b_insert(L:list,E:elem,R:list)
%flow model(i,i,o)
p1b_insert(L,E,R):-
    p1b_insert_aux(L,E,1,1,R).
