%a) add e after 1-st, 3-rd, 7-th, 15-th in a list

%a math model
%p2_9a_aux(l1..ln,e,c,n) = [], if n = 0
%           l1 U p2_9a_aux(l2..ln,e,c+1,n), if c != n
%           l1 U e U p2_9a_aux(l2..ln,e,c+1,n+n+1), otherwise
%
% p2_9a(l1..ln,e) = [], if length = 0
%           p2_9a_aux(l1..ln,1,1)

%p2_9a_aux(L:list, E:elem, c:currentPos, n:neededPos, R:list)
%flow model: (i,i,i,i,o), (i,i,i,i,i)

p2_9a_aux([],_,_,_,[]).
p2_9a_aux([H|T],E,C,N,R):-
    C=:=N,
    N1 is N + N + 1,
    C1 is C + 1,
    p2_9a_aux(T,E,C1,N1,R1),
    R=[H,E|R1].
p2_9a_aux([H|T],E,C,N,R):-
    C=\=N,
    C1 is C+1,
    p2_9a_aux(T,E,C1,N,R1),
    R=[H|R1].

% p2_9a(L:list, E:elem, R:list)
% flow model: (i, i, o), (i,i,i)
p2_9a([],_,[]).
p2_9a(L,E,R):-
    p2_9a_aux(L,E,1,1,R).



%b) heterogeneous list. add in every sublist after 1-st, 3-3d
% 7-th, 15-th.. element the number before in the list

%math model: p2_9b_aux(l1..ln,e) = [], if n = 0
%        p2_9a(l1,e) U p2_9b_aux(l2..ln,e), if l1 is list
%        l1 U p2_9b_aux(l2..ln,l1), if l1 is number

%p2_9b_aux(L:list,E:number to insert, R:list)
%flow model(i,i,o), (i,i,i)

p2_9b_aux([],_,[]).
p2_9b_aux([H|T],E,R):-
    is_list(H),
    p2_9a(H,E,R1),
    p2_9b_aux(T,E,R2),
    R=[R1|R2].
p2_9b_aux([H|T],_,R):-
    number(H),
    p2_9b_aux(T,H,R1),
    R=[H|R1].


%math model: p2_9b(l1..ln) = [], if length = 0
%        l1 U p2_9b_aux(l2..ln,l1).

%p2_9b(L:list,R:list)
%flow model: (i,o), (i,i)

p2_9b([],[]).
p2_9b([H|T],R):-
    p2_9b_aux(T,H,R1),
    R=[H|R1].
