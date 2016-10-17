;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test de la forme quote : evolved_02"
;———

(quote "Bonjour					")
(quote ())
(quote 					(123 							 	))
(quote (quote (quote(quote quote))))
(quote (quote						12345 quote (Bonjour quote(()))))
'(quote Bonjour #t #f #\f )
'(())
'((			)	) 
'()