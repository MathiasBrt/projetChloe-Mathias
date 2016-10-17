;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du And et Ou logique : evolved"
;———


(and (and



	 #f #f)  	#f)
(and(
 and (and #f 
 	#t) #t)
 																           #f)
(quote           	 (and
			 #t #f)				)
'(and 		
	#t 				        #f 
	)
(or    (or #f  	
	


				 #f)	#f)
(or( or 	
	



					 (or  #f #t)           #t)      



					      #f)		
(quote     








										(or  #t #f))
'(or      #t #f)