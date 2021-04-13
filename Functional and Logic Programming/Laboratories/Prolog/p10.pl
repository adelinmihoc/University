%valley

p10_valley([A1,A2],D):-
    D=:=0,
    A1<A2.
p10_valley([H1,H2|T],D):-
    D=:=1,
    H1>H2,
    p10_valley([H2|T],D).
p10_valley([H1,H2|T],D):-
    D=:=1,
    H1<H2,
    D1 is 0,
    p10_valley([H2|T],D1).
p10_valley([H1,H2|T],D):-
    D=:=0,
    H1<H2,
    p10_valley([H2|T],D).


p10_down([A1,A2]):-
    A1>A2.
p10_down([H1,H2|T]):-
    H1>H2,
    p10_down([H2|T]).

%p10b(L:list,R:int)
p10b([],0).
p10b([E],E).
p10b([H1,H2|T],R):-
    p10b(T,R1),
    R is R1+H1-H2.
