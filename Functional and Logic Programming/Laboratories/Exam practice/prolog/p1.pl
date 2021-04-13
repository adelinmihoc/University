%a. Write a predicate to determine the lowest common multiple of a list formed from integer numbers.

p1_gcd(0, B, B).
p1_gcd(A, B, R):-
    A1 is B mod A,
    B1 is A,
    p1_gcd(A1, B1, R).

p1_lcm(A, B, R):-
    C is A * B,
    p1_gcd(A, B, D),
    R is C / D.

p1_a([H], H).
p1_a([H|T], R):-
    p1_a(T, R1),
    p1_lcm(H, R1, R).
