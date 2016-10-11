;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test de la forme quote : evolved_00"
;———

(quote (quote Bonjour))			
(quote ((quote Bonjour) Bonjour))
(quote					(bonjour))
(quote                  (Bonjour))
(quote 






Bonjour)
(quote Bonjour) (quote '12345) (quote #t)
'Bonjour 'Bonjour '12345 '#t