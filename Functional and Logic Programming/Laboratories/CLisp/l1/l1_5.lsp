
;a) Write twice the n-th element of a linear list.
; Example: for (10 20 30 40 50) and n=3 will produce
; (10 20 30 30 40 50).

;math model: a_aux(m, c, l1...ln) = [], if n = 0
;								    l1 U a_aux(m, c + 1, l2...ln), if c = m
;								    a_aux(m, c + 1, l2...ln), otherwise
(defun a_aux(m c l)
	(cond
		((null l)nil)
		((= c m) (cons (car l) (cons (car l) (a_aux m (+ c 1) (cdr l)))))
		((cons (car l) (a_aux m (+ c 1) (cdr l))))
	)
)

;math model: a(m, l1...ln) = a_aux(m, 1, l1...ln)
(defun a(m l)
	(a_aux m 1 l)
)

;b) Write a function to return an association list with 
;the two lists given as parameters. 
;Example: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).

;math model: b(a1...an, b1...bm) = [], if n = 0 or m = 0
;								   [a1 U b1] U b(a2...an, b2...bn), otherwise
(defun b(l1 l2)
	(cond
		((or (null l1) (null l2)) nil)
		((cons (cons (car l1) (car l2)) (b (cdr l1) (cdr l2))))
	)
)

;c) Write a function to determine the number of all sublists 
;of a given list, on any level. 
; A sublist is either the list itself, or any element that 
;is a list, at any level. Example: 
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 lists:
;(list itself, (3 ...), (4 5), (6 7), (9 10)).

;math model: c_aux(l1...ln) = 0, if n = 0
;							  c_aux(l1) + (1 + c_aux(l2...ln)), if l1 is list
;							  c_aux(l2...ln), otherwise
(defun c_aux(l)
	(cond 
		((null l) 0)
		((listp (car l)) (+ (c_aux (car l)) (+ 1 (c_aux (cdr l)))))
		(t(c_aux (cdr l)))
	)
)

;math model: c(l1...ln) = 1 + c_aux(l1...ln)
(defun c(l)
	(+ 1 (c_aux l))
)

;d) Write a function to return the number of all numerical
; atoms in a list at superficial level.

;math model: d(l1...ln) = 0, if n = 0
;						  1 + d(l2...ln), if l1 is number
;						  d(l2...ln), otherwise
(defun d(l)
	(cond 
		((null l) 0)
		((numberp (car l)) (+ 1 (d (cdr l))))
		(t (d (cdr l)))
	)
)






