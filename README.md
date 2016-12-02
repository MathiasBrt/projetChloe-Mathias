# projetChloe-Mathias

"Fait"


"A faire"

- Gestion des erreurs
	-Let
		- Syntaxe
	-Quote
		- "'"
	-Opération
		
(define (sum-of-squares x y)
  (+ (square x) (square y)))
(sum-of-squares 3 4)
; expect 25


(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))
(f 5)


(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))
(a-plus-abs-b 3 -2)



((lambda (x y z) (+ x y (square z))) 1 2 3)


(define (f x y)
  (let ((a (+ 1 (* x y)))
        (b (- 1 y)))
    (+ (* x (square a))
       (* y b)
       (* a b))))
(f 3 4)


(define one-through-four (list 1 2 3 4))
one-through-four

On récupère (list 1 2 3 4) au lieu de (1 2 3 4)




(equal? '(1 2 three) '(1 2 (three)))




