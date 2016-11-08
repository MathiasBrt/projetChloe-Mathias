;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du prédicat boolean"
;———

(boolean? #t)
(boolean? #f)
(boolean? "boolean?")
(boolean? (and #t #t))
(boolean? (or #f #f))

