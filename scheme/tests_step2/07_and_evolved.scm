;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du And logique : evolved"
;———


(and (and #f #f)	#f)
(and( and (and #f #t) #t) #f)	
12345 (and #f x) 
12345 (and #t #t) #\B #\newline  				12345	    	   (and #t #f) 	 	 	 	#\newline		
(quote (and #t #f))
('(and #t #f))	