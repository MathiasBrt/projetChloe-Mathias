;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test de l'égalité polymorphique"
;———

(eq? 1 1)
(eq? a a)
(eq? #\r #\r)
(eq? #t #t)
(eq? () ())
(eq? "chaine" "chaine")
(define x 2)
(eq? x 2)
(eq? x (+ 1 1) (- 3 1))
