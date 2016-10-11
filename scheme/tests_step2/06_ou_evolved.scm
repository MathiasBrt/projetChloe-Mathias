;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du Ou logique : evolved"
;———

(or (or #f #f)	#f)
(or( or (or #f #t) #t) #f)	
12345 (or #f x) 
12345 (or #t #f) #\B #\newline  				12345	    	   (or #t #f) 	 	 	 	#\newline		
(quote (or #t #f))
('(or #t #f))