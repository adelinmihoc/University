;sa se defineasca o functie care inverseaza o lista liniara

(defun invers(l)
	(cond
		((atom l)l)
		(t(append(invers(cdr l))(list (car l))))
	)
)

(defun invers2_aux(l Col)
	(cond
		((null l)Col)
		(t(invers2_aux(cdr l)(cons (car l)Col)))
		)
)
(
	defun invers2(l)
	(invers2_aux l ())
	)
