;5. Write a function that computes the sum of even numbers and the decrease the sum of odd numbers,
;at any level of a list.
;(sumevendecrodd '(1 2 a 3 (4 5) () (6 (b (c)) d) 7 8)) = 4

;math model: sumevendecrodd(n) = -n, if n is a number and n is odd
;								  n, if n is a number and n is even
;								  0, if n is an atom but not a number
;								  Σ i = 1,n sumevendecrodd(n_i), otherwise 

(defun sumevendecrodd(n)
	(cond 
		((and (numberp n) (oddp n)) (* -1 n))
		((and (numberp n) (evenp n)) n)
		((atom n) 0)
		(t (apply #'+(mapcar #' sumevendecrodd n)))
	)

)