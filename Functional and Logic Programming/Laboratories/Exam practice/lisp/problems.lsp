;suma numere nivel superficial lista neliniara

(defun suma (l)
	(cond 
		((null l) 0)
		((numberp (car l)) ( + (suma (cdr l)) 1))
		(t(suma (cdr l)))
	)
)

;suma numere orice nivel lista neliniara

(defun suma (l)
	(cond
		((null l) 0)
		((numberp (car l)) (+ (car l) (suma(cdr l))))
		((atom (car l)) (suma(cdr l)))
		(t(+(suma(car l)) (suma(cdr l))))
	)
)

;ultimul element al unei liste nivel superficial

(defun ultim (x)
	(cond
		((atom x)x)
		((null (cdr x))(car x))
		(t (ultim(cdr x)))
	)
)

;suma numerelor orice nivel list neliniara

(defun suma(l)
	(cond 
		((null l) 0)
		((numberp (car l)) (+ (suma(cdr l)) (car l)))
		((atom (car l)) (suma (cdr l)))
		(t(+ (suma (car l)) (suma(cdr l))))
	)
)


;sa se construiasca o list prin adaugarea unui element la sfarsitul unei liste

(defun adaug(e l)
	(cond
		((null l) (list e))
		(t(cons (car l)(adaug e (cdr l))))
	)
)

; functie inverseaza o list liniara

(defun invers(l)
	(cond
		((atom l) l)
		(t(append (invers (cdr l)) (list (car l))))
	)
)



;perechi dintre un element si elementele unei liste
;a si (1 2 3 4) -> ((a 1) (a 2) (a 3) (a 4))

(defun lista(e l)
	(cond
		((null l) nil)
		(t(cons (list e (car l)) (lista e (cdr l)) ))
	)
)


;a nonlinear list is given 
;write a function to remove all numeric atoms divisible with 3 from all levels
;use map functions
; eg. (1(2 a (3 a)) (6)) -> (1(2 a (a)) nil)

(defun sterg(l)
	(cond
		((and (numberp l) (= (mod l 3) 0)) nil)
		((atom l) list(l))
		(t(list (apply #'append 
					(mapcar #'sterg l)
				)
			)
		
		)
	)
)


; functie modif care modifica o lista: atomii nenumerici raman nemodificati iar cei numerici isi dubleaza valoarea

;math model: modif(l) = 2l if l numberp
;						l if l atom
;						U, i=1,m modif(l_i), otherwis, l=(l1..lm)

(defun modif(l)
	(cond
		((numberp l)(* 2 l))
		((atom l)l)
		(t(mapcar #'modif l))
	)
)

; lista neliniara, se returneaza lista din care au fost stersi atomii numerici negativi
; se va folosi functie map

; math model: sterg(l) = () if l numeric negativi
;							l if l atom
;							sterg(li), otherwise, l=(l1,l2,ln)

(defun sterg(l)
	(cond
		((and (numberp l) (minusp l)) nil)
		((atom l) (list l))
		(t(list (apply #'append
						(mapcar #'sterg l)
				)
			)
		)
	)
)

(defun stergere(l)
	(car(sterg l))
)


; se da un arbore n-ar v2 sa se determine adancimea arborelui, nivelul radacinii este 0
;(adancime '(a(b(c)(d(e)))(f(g)))) -> 3

;math model: adancime(l1...ln) = 0 if n = 1
;									max(adancime(l2), adancime(l3), ... ,adancime(ln)), otherwise

(defun adancime(l)
	(cond
		((null (cdr l)) 0)
		(t(+ 1 (apply #'max
					(mapcar #'adancime(cdr l))
				)
		   )
		)
	)
)

; sa se defineasca o functie care avand ca parametru o lista neliniara sa returneze numerul de subliste 
;(inclusiv lista) avand lungime numar par (la nivel superficial)


(defun par(l)
	(cond
		((= 0 (mod (length l )2)) t)
		(t nil)
	)
)

(defun nr(l)
	(cond
		((atom l) 0)
		((par l) (+ 1 (apply #' + (mapcar #' nr l))))
		(t(apply #' + (mapcar #' nr l)))
	)
)


;sa se defineasca o functie care avand ca parametru o lista neliniara sa returneze lista atomilor (de la orice nivel) din lista

;math model: (l) if l is atom
;				U i,m atomi(l_i) if l is (l1...lm)

(defun atomi(l)
	(cond
		((atom l) (list l))
		(t(mapcan #'atomi l))
	)
)

(defun atomi(l)
	(cond
		((atom l)(list l))
		(t(apply #' append (mapcar #'atomi l)))
	)
)


; sa se defineasca o functie care determina numarul de aparitii, de la orice nivel, ale unui element intr-o lista neliniara

;math model: nrap(e, l) = 1 if l = eg
;						  0 if l is atom
;						  sigma i=1,m nrap(e,l_i), otherwise, l = (l1,l2,..lm) it's the list

(defun nrap(e l)
	(cond
		((equal l e) l)
		((atom l) 0)
		(t(apply #' + (mapcar #' (lambda(l)
									(nrap e l)
								 )
								 l
					  )
		  )
		)
	)
)



; an n-ary tree is represented in lisp (root subtree1 sunbtree 2 ... ...).
;write a function to replace all nodes from the odd levels in the tree with a given value e.
;the level of root is considered 0/
;use a map function.
;eg tree(a(b (g)) (c (d (e)) (f))) si e = h => (a(h(g)) (h (d (h)) (f)))


(defun tree(e l)
	(cond
		((atom l) (list l))
		(t (list (apply#'append (mapcar #' (lamda(l) 
												(tree e l)									
											)
								)
				  )
			)
		)
	)
) ; this doesn't change the initial list it is awesome. 

(defun tree(e l c)
	(cond
	    ((and (atom l) (=  1 (mod c 2)) ) (list e))
		((atom l) (list l))
		(t (list (apply #'append (mapcar #' (lambda(l) 
												(tree e l (+ c 1))									
											)
										l
								)
				  )
			)
		)
	)
) ; this is the correct solution



; a nonlinear list is given. Write a function to return as result the initial list in which the
; atoms from the level k from the initial list have been replaced with 0.
; the superficial level is considerated 1. use map functions
; eg. (a (1 (2 b)) (c (d))) and k = 2 => (a (0 (2 b)) (0 (d)))

(defun schimb(k l c) ; initially c = 0 because superficial level = 1 , if super. lev. = 0 => c = -1
	(cond
		((and (atom l) (= c k)) (list 0))
		((atom l) (list l))
		(t(list (apply #'append (mapcar #'(lambda (l) 
												(schimb k l (+ 1 c))
										  )
								l
								)
				)
		   )
		 )
	)
)


=======================================================================================================
==   									EVITAREA APELURILOR REPETATE                                 ==
=======================================================================================================

; fie urmatoarea functie 

(defun g(l)
	(cond
		((null l) nil)
		(t(cons (car(f1)) cadr(f1)))
	)
)

--varianta 1

(defun g(l)
	(cond
		((null l) nil)
		(t((lambda (v)
				(cons(car v) (cadr v))
		    )
			(f1)
		   )
		)
	)
)

-- varianta 2

(defun g(l)
	(cond
		((lambda (v)
			(cond
				((null l) nil)
				(t (cons (car v) (cadr v)))
			)
		  )
		  (f1)
		)
	)
)


; fie urmatoarea functie

(defun subm(l)
	(cond
		((null l) (list nil))
		(t(append (subm (cdr l))(insPrimaPoz(car l)(subm (cdr l))) ))
	)
)

	
(defun subm(l)
	(cond
		((null l) (list nil))
		(t (
			lambda(s)
				(append s (insPrimaPoz (car l) s))
		   )
		   (subm (cdr l))
		)
	)
)

; give a solution to avoid double recursive call 

(defun f(l1 l2)
	(append (f(car l1) l2)
		(cond
			((null l1) (cdr l2))
			(t (list (f(car l1) l2)(car l2)))
		)
	)
)

(defun f(l1 l2)
	(
		(lambda (v)
			(append v 
				(cond
					((null l1) (cdr l2))
					(t (list v (car l2)))
				)
			)
		)
		(f(car l1) l2)
	)
)







