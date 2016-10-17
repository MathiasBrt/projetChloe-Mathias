;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : evolved_01"
;———

(if (#t) (quote Bonjour))
(if (#t) (quote Bonjour))
(if (#t) (quote (Bonjour)))
(if (#t) (and #t #t))
(if (#t) (and #t #f))
(if (#t) (and #f #f))
(if (#t) (and Bonjour Bonjour))
(if (#t) (or #t #t))
(if (#t) (or #t #f))
(if (#t) (or #f #f))
(if (#t) (or Bonjour Bonjour))