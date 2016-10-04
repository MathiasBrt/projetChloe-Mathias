;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du And logique"
;———

(and #f #f)	
(and #f #t)	
(and #f x)
(and #t #f)
(and x #f)		
(and #t #t)
(and x #t)	
(and x x)			