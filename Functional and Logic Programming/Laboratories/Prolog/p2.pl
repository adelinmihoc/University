%a.Write a predicate to remove all occurrences of a certain
% atom from a list.
% b.Define a predicate to produce a list of pairs (atom n)
%from an initial list of atoms.
%In this initial list atom has n occurrences.
% Eg.: numberatom([1,2,1,2,1,3,1],X) => X=[[1,4],[2,2],[3,1]].

%p2_count(L:list,E:elem,R:int)
%flow model: (i,i,o),(i,i,i)
p2_count([],_,0).
p2_count([H|T],E,R):-
    H=:=E,
    p2_count(T,E,R1),
    R is R1+1.
p2_count([H|T],E,R):-
    H=\=E,
    p2_count(T,E,R).

%p2_member(L:list,E:elem)
%flow model(i,i)
p2_member([E|_],E).
p2_member([_|T],E):-
    p2_member(T,E).


%p2_number_atom_aux(L:list,A:list,R:list)
%flow model: (i,i,o)
p2_number_atom_aux([],_,[]):-!.
p2_number_atom_aux([H|T],A,R):-
    not(p2_member(A,H)),
    p2_count([H|T],H,C),
    D=[H,C],
    A1=[H|A],
    p2_number_atom_aux(T,A1,R1),
    R=[D|R1].
p2_number_atom_aux([H|T],A,R):-
    p2_member(A,H),
    p2_number_atom_aux(T,A,R).

%p2_number_atom(L:list,R:list)
%flow model: (i,i),(i,o)
p2_number_atom(L,R):-
    p2_number_atom_aux(L,[],R).
