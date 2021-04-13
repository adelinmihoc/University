;a) Write a function to return the n-th element of a list, 
;or NIL if such an element does not exist.

(defun f1(p c l)
	(cond 
		((null l) nil)
		((= c p) (car l))
		(t(f1 p(+ c 1)(cdr l)))
	)
)
;b) Write a function to check whether an atom E is 
;a member of a list which is not necessarily linear.
(defun f2(e l)
	(cond
		((null l) nil)
		( (and(numberp (car l))(= e (car l))) 1)
		((listp (car l)) (f2 e (car l)))
		((f2 e (cdr l)))
	)
)

