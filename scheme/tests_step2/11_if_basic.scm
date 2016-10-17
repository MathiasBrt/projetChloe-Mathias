;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : basic"
;———

(if #t Bonjour)
(if #f Bonjour)
(if #t #\a)
(if #t #\space)
(if #t "Bonjour")
(if #t 12345)
(if #t ())