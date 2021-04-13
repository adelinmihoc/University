;sa se construiasca lista obtinuta prin adaugarea unui element la
;sfarsitul unei liste

(defun adaug(e l)
    (cond
        ((null l)(list e))
        (t(cons (car l)(adaug e(cdr l))))
    )
)
