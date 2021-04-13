%Prolog elem sterg perm subm comb aranj

elem([E|_], E).
elem([_|T], E):-
	elem(T, E).
	
	
	
sterge([E|R], E, R):-!.
sterge([H|T], E, [H|R]):-
	sterge(T, E, R).
	
	
	
perm([],[]).
perm(L, [E | RR]):-
	elem(L, E),
	sterge(L, E, R),
	perm(R, RR).
	
	
	
subm([],[]).
subm([H|T], [H|R]):-
	subm(T, R).
subm([_|T], R):-
	subm(T, R).
	
	
	
comb([], 0, []).
comb([H|T], K, [H|R]):-
	K1 is K - 1,
	comb(T, K1, R).
comb([_|T], K, R):-
	comb(T, K, R).
	
	
	
aranj(L, K, RR):-
	comb(L, K, R),
	perm(R, RR).
	

%a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]

%sort a list
insert_sort(List,Sorted):-i_sort(List,[],Sorted).
i_sort([],Acc,Acc).
i_sort([H|T],Acc,Sorted):-insert(H,Acc,NAcc),i_sort(T,NAcc,Sorted).
   
insert(X,[Y|T],[Y|NT]):-X>Y,insert(X,T,NT).
insert(X,[Y|T],[X,Y|T]):-X=<Y.
insert(X,[],[X]).

remove([],[]).
remove([H|T],R):-
	remove(T,R1),
	elem(R1, H),
	R = R1.
remove([H|T],R):-
	remove(T,R1),
    !,
	R = [H|R1].
	
sortremove(L,R):-
	remove(L, R1),
    insert_sort(R1,R).
	

%a. Write a predicate to remove all occurrences of a certain atom from a list.

sterg([],_,[]).
sterg([H|T],X,R):-
	sterg(T,X,R1),
	X =\= H,
	R = [H|R1].
sterg([H|T],X,R):-
	sterg(T,X,R1),
	R = R1.
	

% lista eterogena. sa se determine suma numerelor din lista.

sumalist([],0).
sumalist([H|T],R):-
	sumalist(T, R1),
	R is H + R1.

suma([], 0).
suma([H|T],R):-
	number(H),
	suma(T, R1),
	R is H + R1.
suma([H|T],R):-
	list(H),
	sumalist(H,R1),
	suma(T,R2),
	R is R1 + R2.
suma([_|T],R):-
	suma(T,R).
	
; varianta 2 folosind obiecte compuse

%suma(L: heterogeneous list, S:number)
%(i,o)-determine
?????????????????
suma([],0).
sumalist([i(H)|T],S):-
	H mod 2 =:= 0, !,
	suma(T,S1),
	S is S1 + H.
suma([_|T],S):-suma(T,S).


%sa se scrie un predicat care concateneaza doua listen

? concatenare([1, 2],[3, 4], R).
R=[1, 2, 3, 4].


%math model concatenare(a1...an, b1...bm) = b1...bm if n = 0
											a1 U concatenare(a2..an, b1...bm), otherwise
											
%concatenare(L1:list, L2:list,L3:list)
%(i,i,o)

concatenare([],L,L).
concatenare([H|T1], L2, [H|L3]):-
	concatenare(T,L2,L3).
	
; sa se scrie un predicat care determina lista submultimilor unei liste reprezentate sub forma de multime

sumb(l1..ln) = [] if n = 0
				subm(l2...ln)
				l1 U sumb(l2...ln)
		
%subm(L:list, R:list)
%(i, o) - nedeterminist
subm([],[]).
subm([_|T],S):-sumb(T,S).
subm([H|T],[H|S]):- subm(T,S).

%submultimi(L:list, LRez:list of lists)
%(i,o) - determinist

submultimi(L,LRez):-findall(S,subm(L,S),LRez).


; sa se calculeze minimul unei liste de numere intregi

%minim(L:list,M:integer)
%(i,o)-determinist

minim([A],A).
minim([H|T],R):-
	minim(T,M),
	H =< M, !, R=H.
minim([_|T],M):- minim(T,M).


%solutia 1
minim([A],A).
minim([H|T],M):-
	minim(T,M),
	H>M, !.
minim([H|_],H).

%solutia 2 se foloseste un predicat auxiliar pentru a evita apelul recursiv repetat din 2 si 3

minim([A],A).
minim([H|T],Rez):-
	minim(T,M),
	aux(H,M,Rez).

%aux(H:int, M:int, Rez:int)
%(i,i,o) determinist

aux(H,M,Rez):-
	H=< M, !, Rez = H.
aux(_,M,M).

%se da o lista numerica. sa se dea o solutie pentru evitarea apelului recursiv repetat.

%f(L:list of numbers, E:number)
%(i,o) - determina

f([E],E).
f([H|T],Y):-
	f(T,X),
	H=<X,
	!,
	Y=H.
f([_|T],X):- f(T,X).

f([E],E).
f([H|T],Y):-
	f(T,X),
	aux(H, X, Y).
	
aux(H, X, Y):-
	H =< X, !, Y = H.
aux(_,X,X).

%sa se dea o solutie pentru evitarea apelului recursiv repetat
%f(K:number, X:number)
%(i,o)- determina

f(1, 1):-!.
f(2, 2):-!.
f(K, X):- 
	K1 is K-1,
	f(K1, Y),
	Y > 1,
	!,
	k2 IS k - 2,
	X = K2.
f(K,X):-
	K1 is K - 1,
	f(K1, X).
	
f(1,1):-!.
f(2,2):-!.
f(K,X):-K1 is K - 1,
		f(K1, Y),
		aux(K, Y, X).
		
%aux(K:int, Y:int, X:int)
%(i,i,o)- determinist

aux(k,Y,X):-
	Y>1,
	!,
	K2 is K - 2,
	X = K2.
aux(_,Y,Y).


%sa se scrie un predicat nedeterminist care genereaza combinari cu k elemente
dintr-o multime nevida reprezentata sub forma unei liste

%math model: comb(l1...ln k) = (l1) if k = 1
								comb(l2...ln, k)
								l1 U comb(l2...ln, k-1) if k > 1
								
comb([H|_],1,[H]).
comb([_|T],K,C):-
	comb(T,K,C).
comb([H|T], K, [H|C]):-
	K > 1,
	K1 is K-1,
	comb(T,K1,C).
	
%sa se scrie un predicat care insereaza un element pe toate pozitiile intr o lista

insereaza(e,l1..ln) = e U l1...ln
						l1 U insereaza(e, l2...ln)
						
insereaza(E,L, [E|L]).
insereaza(E,[H|T],[H|R]):- insereaza(E, T, R).


%sa se scrie un predicat care sterge un element pe rand de pe toate pozitiile pe care acesta apare intr o lista

elimin(e, l1..ln) = l2...ln if e = l1
					l1 U elimin(e, l2...ln)
					
elimin(E,L,[E|L]).
elimin(E,[H|T],[H|X]):-elimin(E,T,X).


%sa se scrie un predicat nedeterminist care genereaza permutarile unei liste

perm(l1..ln) = [] if n = 0
				insereaza(l1, perm(l2..ln)), otherwise
		

perm([],[]).
perm([E|T],P):-
	perm(T,L),
	insereaza(E,L,P).


===================================================================================
=									BACKTRACKING                                  =
===================================================================================


%sa se scrie un predicat nedeterminist care genereaza combinari cu k!= 1 elemente
dintr o multime nevida ale carei elemente sunt numere naturale nenule pozitive, astfel
incat suma elementelor din combinare sa fie o valoare S data


--Varianta 1 generam solutiile direct recursiv

combSuma(l1..ln, k, s) = (l1) if k = 1 si l1 = s
						comb(l2..ln, k, s)
						l1 U comb(l2..ln, k-1, s-l1) if k > 1 is S-l1 > 0
						
combSuma([H|_],1,H,[H]).
combSuma([_|T],K,S,C):-
	combSuma(T,K,S,C).
combSuma([H|T], K, S, [H|C]):-
	K > 1,
	S1 is S - H,
	S1 > 0,
	K1 is K - 1,
	combSuma(T,K1,S1,C).
	
toateCombSuma(L,K,S,LC):-
	findall(C, combSuma(L,K,S,C), LC)

--Varianta 2 se genereaza combinarile ci k elemente si apoi se verifica daca suma unei combinari este s. 
---> ineficient

combSuma(L,K,S,C):-
	comb(L,K,C0,
	suma(C,S).
	
---Varianta 3 folosind predicat nedeterminist candidat (E:element, L:List) (o,i)
care genereaza cate un element al unei liste

candidat(l1..ln)= l1 if n != 0
candidat(l2..ln)

condidat(E,[E|_]),
candidat(E,[_|T]):-
	candidat(E,T).

combSuma(L,K,S,C):-
	candidat(E,L),
	E =<S,
	combaux(L,K,S,C,1,E,[E]).
	
combaux(l,k,s,lg,sum,col) = col if sum = s si k = lg
							combaux(l,k,s,lg+1, sum+e, e U col) if sum != s sau k != lg
																	si lg < k
																	si e = candidat(l1..ln) si e < col1 si sum + e <= s-l
																	


													



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
