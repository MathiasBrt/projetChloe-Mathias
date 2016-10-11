;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du Ou logique"
;———

(or #f #f)	
(or #f #t)	
(or #f x)
(or #t #f)
(or x #f)		
(or #t #t)
(or x #t)	
(or x x)			