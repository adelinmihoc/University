;se da o lista neliniara
;se cere sa se dubleze valorile numerice
;de la orice nivel al listei, pastrand structura ierarhica 
;a acesteia

;(dublare '(1 b 2 (c (3 h 4))(d 6))) = (2 b 8 (c (6 h 8))(d 12))

(defun dublare(l)
	(cond
		((numberp l)(* 2 l))
		((atom l)l)
		(t (cons (dublare (car l)) (dublare (cdr l))))
	)
)