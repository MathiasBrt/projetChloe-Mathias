;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test de manipulation de listes"
;———

(car (a))
(cdr (a))
(cdr (a b))
(car ((a b) c))
(cdr (a (b c)))
(cdr (a b c))
(car (cdr (a b)))
(cdr (car ((a b) c)))
