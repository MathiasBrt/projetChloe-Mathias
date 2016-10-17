;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test set! : basic"
;———

(define Bob 3)
(set! Bob 4)
(set! Bob x)
(set! Bob #/e)
(set! Bob #t)
(set! Bob "Bonjour")
(set! Bob #\space)