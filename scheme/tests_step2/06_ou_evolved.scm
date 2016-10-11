;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du Ou logique : evolved"
;———

(or (or #f #f)	#f)
(or( or (or #f #t) #t) #f)		
(quote (or #t #f))
'(or #t #f)