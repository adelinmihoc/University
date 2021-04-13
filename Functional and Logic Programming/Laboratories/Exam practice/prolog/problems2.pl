%a list of integer numbers is given. generate the list of all permutations having the property
%that absolute value of difference between two consecutive values from each permutation is <= 3
%eg: [2,5,7] -> [[2,5,7],[7,5,2]]

H = head
T = tail
LE = last added element

conditie(H,LE):-
	D is LE - H,
	D1 is abs(D),
	D1 =< 3.

%returneaza pe rand fiecare elem al listei L
elem([E|T],E,T).
elem([_|T],E,R):-
	elem(T,E,R).
	
%sterge elementul E din lista (o singura aparitie)
stergeE([E|R],E,R):-!.
stergeE([H|T],E,[H|R]):-
	stergeE(T,E,R).
	
%genereaza toate permutarile ce satisfac conditia
permCond([],_,[]).
permCond(L,LE,[E|R]):-
	elem(L,E,_),
	stergeE(L,E,T),
	conditie(E,LE),
	permCond(T,E,R).

generator(L,[E|R]):-
	elem(L,E,_),
	stergeE(L,E,T),
	permCond(T,E,R).
	
gen2(L,R):-findall(O, generator(L,O),R).


%.Pentru o valoare N data sa se genereze lista permutarilor cu elementele N, N+1,..., 2*N-1 
avand proprietatea ca valoarea absoluta a diferentei dintre 2 valori consecutive din permutare este <=2. Explicati algoritmul.

generateList(1,[1]).
generateList(N,R):-
	N1 is N - 1,
	N > 1,
	generateList(N1,R1),
    R = [N|R1].
    
elem([E|_], E).
elem([_|T], E):-
	elem(T, E).
	

sterge([E|R], E, R):-!.
sterge([H|T], E, [H|R]):-
	sterge(T, E, R).
	
%conditie([]).
conditie(H1,H2):-
    D is H1 - H2,
    D1 is abs(D),
    D1 =< 2.

perm([],_,[]).
perm(L,LE,[E|RR]):-
    elem(L,E),
    sterge(L,E,R),
    conditie(E,LE),
    perm(R,E,RR).


wrapper(N,R):-
    generateList(N, [H|T]),
    findall(O, perm([H|T],H,O),R).



; let L be a numerical list and consider the following prolog predicate

f([], 0).
f([H|T],S):-f(T,S1),S1<H,!,S is H.
f([_|T], S):-f(T,S1), S is S1.

f([], 0).
f([H|T],S):-
	f(T,S1),
	f_aux(H,S1,S).
	
f_aux(H,S1,S):-
	S1 < H, !, S is H.
f_aux(_,S,S). 


%write a program to generate arrangements of k elements from a list of integer numbers with the product P given
eg. [2,5,2,4,10], k=2 and P=20
[[2,10],[10,2],[5,4],[4,5]]










