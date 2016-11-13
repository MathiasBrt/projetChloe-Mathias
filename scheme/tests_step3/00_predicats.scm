;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des predicats"
;———

(null? ())
(null? "null?")
(null? (()))
(boolean? #t)
(boolean? #f)
(boolean? "boolean?")
(boolean? (and #t #t))
(boolean? (or #f #f))
(symbol? symbol)


