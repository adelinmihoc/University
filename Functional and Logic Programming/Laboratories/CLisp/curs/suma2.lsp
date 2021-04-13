;Sa se calculeze suma atomilor numerici de la orice nivel dintr-o lista
;neliniara

(defun suma(l)
    (cond
      ((null l) 0)
      ((numberp (car l)) (+ (car l)(suma (cdr l))))
      ((atom (car l)) (suma (cdr l)))
      (t(+ (suma (car l))(suma (cdr l))))
    )

)
