;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des manipulation de listes"
;———

(list! a)
(list! a b)
(list! "Bonjour" Bonjour #\a #\b #\t 1234)
(define a 1)
(define b 2)
(set-car! (a b) 3)
(set-cdr! ((set-car! (a b) 4) b) 4)