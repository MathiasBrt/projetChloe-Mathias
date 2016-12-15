;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test de défintions de fonctions"
;———

(begin (define f (lambda (n) (+ n 1))) (f 3))
(begin (define (g x y) (* x y)) (g 4 5))
(f (g 6 5))
(g (f 4) 5)
(f (f (f 3)))
(begin (define (fcarre proc args) (proc args)) (fcarre f 1))
(define (h x y) (* x x))
(h 3 4)

