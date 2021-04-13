%15. For a given n, positive, determine all decompositions
% of n as sum of consecutive natural numbers

%math model
%p3_15_aux(N,F,L)=(F,L), if 2*N=(L-F)*(L+F+1) and L<N and F>=L
%                =p3_15_aux(N,F+1,L), if L<N and F>=L
%                =p3_15_aux(N,0,L+1), if L<N and F>L

%p3_15_aux(N:number,F:number,L:number,R1:number,R2:number)
%flow model: (i,i,i,o,o)
p3_15_aux(N,F,L,R1,R2):-
    L < N,
    F =< L,
    2*N =:= (L+F)*(L-F+1),
    R1 is F,
    R2 = L.
p3_15_aux(N,F,L,R1,R2):-
    L < N,
    F =< L,
    F1 is F + 1,
    p3_15_aux(N,F1,L,R1,R2).
p3_15_aux(N,F,L,R1,R2):-
    L < N,
    F > L,
    F1 is 0,
    L1 is L + 1,
    p3_15_aux(N,F1,L1,R1,R2).


%math model
%p3_15_make_list(F,L)= F U p3_15_make_list(F+1,L), if F >= L
%                    =[], if F > L

%p3_15_make_list(F:number, L:number, R:list)
%flow model: (i,i,0)
p3_15_make_list(F,L,R):-
    F =< L,
    F1 is F + 1,
    p3_15_make_list(F1,L,R1),
    R = [F|R1].
p3_15_make_list(F,L,[]):-
    F>L.


%math model
%p3_15(N)=list, (F,L)=p3_15_aux(N,1,0),
%               list=p3_15_make_list(F,L)

%p3_15(N:number, R:list)
%flow model: (i,o)
p3_15(N,R):-
    p3_15_aux(N,1,0,F,L),
    p3_15_make_list(F,L,R1),
    R = R1.


%math model
%p3_15_findall(N) = U p3_15(N)

%p3_15_findall(N:number, L:list)
%flow model: (i,o)
p3_15_findall(N,R):-
    findall(X,p3_15(N,X),R).



