;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : evolved_02"
;———

(if (and #t #t) Bonjour Faux)
(if (or #t #t) Bonjour Faux)
(if (and #t #t) Bonjour Faux)
(if (or #t #t) Bonjour Faux)