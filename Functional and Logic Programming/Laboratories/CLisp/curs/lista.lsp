;sa se defineasca o functie care sa determine lista perechilor dintre
;un element dat si elementele unei liste
;(lista 'A'(B C D)) = ((A B)(A C)(A D))
(defun lista(e l)
	(cond
		((null l) nil)
		(t(cons(list e(car l))(lista e(cdr l))))
	)
)