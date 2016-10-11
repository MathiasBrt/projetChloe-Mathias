;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du And logique : evolved"
;———


(and (and #f #f)	#f)
(and( and (and #f #t) #t) #f)
(quote (and #t #f))
'(and #t #f)