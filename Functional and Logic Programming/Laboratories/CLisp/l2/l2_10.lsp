
;10. Return the level of a node X in a tree of type (2). The level of the root element is 0.
;example: (level '(a (b) (c (d) (e))) 'c) = 1

;math model: level_aux(l1...ln, x, r) = -1, if n = 0
;										r, if l1 = x
;										max(level_aux(l2, x, r), level_aux(l3, x, r))

(defun level_aux(l x r)
	(cond
		((null l) -1)
		((equal (car l) x) r)
		(t (max (level_aux (caddr l) x (+ 1 r)) (level_aux (cadr l) x (+ 1 r))))
	)
)


;math model: level(l1...ln, x) = level_aux(l1...ln, x, 0)
(defun level(l x)
	(level_aux l x 0)
)