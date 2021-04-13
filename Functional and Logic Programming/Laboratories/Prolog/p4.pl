%a. Write a predicate to determine the difference of two sets.
% b. Write a predicate to add value 1 after every even elemen
%from a list.

p4_member([H|_],H).
p4_member([_|T],H):-
    p4_member(T,H).


p4a([],_,[]).
p4a([H|T],B,R):-
    p4_member(B,H),
    p4a(T,B,R).
p4a([H|T],B,R):-
    not(p4_member(B,H)),
    p4a(T,B,R1),
    R=[H|R1].

p4b([],[]).
p4b([H|T],R):-
    0=:=mod(H,2),
    p4b(T,R1),
    R=[H|R1].
p4b([H|T],R):-
    1=:=mod(H,2),
    p4b(T,R1),
    R=[H,1|R1].
