;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : syntax"
;———

(if (#t) #t)
(if (#t) 					    #\a)
(if 		 	 	(#t) Bonjour)
(if (#f) Bonjour Faux)
(if
 (
 	#t
 	)
 	 45 )