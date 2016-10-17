;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : evolved_03"
;———

(if (#t) (if (#t) Vrai Faux) "1ere condition fausse")
(if (#f) (if (#t) Vrai Faux) "1ere condition fausse")
(if (or (and (or (and #t #t) #f) #f)#f) (if (and (and #t #t) #t) Vrai Faux) "1ere condition fausse")
(if (or (and (or (and #t #t) #f) #f) #t) (if (and (and #t #t) #t) Vrai Faux) "1ere condition fausse")
(if (or (and (or (and #t #t) #f) #f) #f) (if (and (and #t #t) #t) Vrai_Vrai Vrai_Faux) (if (and (and #t #t) #f) Faux_Vrai Faux_Faux))