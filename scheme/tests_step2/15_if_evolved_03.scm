;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : evolved_03"
;———

(if (and (and (or#t #f) #f) #f) "Je suis vrai" "Je suis faux")
(if (and (or #t #f) #t) (quote "Je suis vrai") "Je suis faux")
(if (#t) (define bob 1) "Je suis faux" ) 
(if (or #f #f) (define Pierre 1) "Je suis faux" ) 
(if (#t) "Je suis vrai" (define Sam 1)) 
(if (or #f #f) "Je suis vrai" (define Paul 1) ) 