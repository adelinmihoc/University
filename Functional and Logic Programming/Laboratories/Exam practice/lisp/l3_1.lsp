;1. Write a function to check if an atom is member of a list (the list is non-liniar)

(defun member1(l x)
	(cond
		((and (atom l) (equal x l) ) 1)
		(t (mapcar #'(lambda(a b) (eval (member a b)) )))
	)
)
