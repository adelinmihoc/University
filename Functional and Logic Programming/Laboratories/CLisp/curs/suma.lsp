;sa se calculeze suma atomilor numerici de la nivelul superficial dintr o lista
;neliniara
;(suma '(1(2(3 4)5)1)) -> 2
(defun suma(l)
    (cond
        ((null l) 0)
        ((numberp (car l)) (+ (car l) (suma (cdr l))))
        (t(suma(cdr l)))
    )
)
