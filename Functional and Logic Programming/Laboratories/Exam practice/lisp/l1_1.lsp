;1.
;a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.

(defun l1_1a(l n c)
	(cond
	((null l) nil)
	((= c n) (car l))
	(t(l1_1a (cdr l) n (+ c 1)))
	)
)


;b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.

(defun l1_1b(l e)
	(cond
	((null l) nil)
	((and(atom (car l)) (equal (car l) e)) t)
	((listp (car l)) (or(l1_1b (car l) e) (l1_1b (cdr l) e)))
	(t(l1_1b (cdr l) e))
	)
)

;c) Write a function to determine the list of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
; ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )

(defun l1_1c (l r)
	(cond
		((null l) nil)
		((listp (car l)) (append (car l) l) (l1_1c (car l) r))
		(t(l1_1c (cdr l) r))
	)
)

;member of a list

(defun membera (l e)
	(cond
		((null l) nil)
		((equal e (car l)) t)
		((listp (car l)) (and(membera (car l) e) (membera (cdr l) e)))
		(t(membera (cdr l) e))
	)
)



(defun apare(e l)
	(cond 
		((null l) nil)
		((eq (car l) e) t)
		(t(apare e (cdr l)))
	)
)

;d) Write a function to transform a linear list into a set.


(defun to_set(l c)
	(cond
		((null l) c)
		((not (apare (car l) c)) (to_set (cdr l) (cons (car l) c)) )
		(t(to_set (cdr l) c))
	)
)













