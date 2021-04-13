;sa se defineasca o functie care sa determine lista 
;perechilor cu elemente in ordine stric crescatoare care
;se pot forma cu elementele unei liste numerice (se va
; pastra ordinea elementelor din lista)
;
;(perechi '(3 1 5 0 4))=((3 5)(3 4)(1 5)(1 4))

;(per '2'(3 1 5 0 4)) = ((2 3)(2 5)(2 4))
(defun per (e l)
	(cond
		((null l) nil)
		(T (cond((< e (car l)) (cons (list e (car l))(per e (cdr l)))) 
		(T (per e (cdr l))))) 
	)
)

(defun perechi (l)
	(cond
		((null l) nil)
		(t (append (per (car l)(cdr l)) (perechi(cdr l))))
	)
)