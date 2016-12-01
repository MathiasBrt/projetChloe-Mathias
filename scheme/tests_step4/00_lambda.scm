;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du lambda"
;———

((lambda (n) (+ n 1)) 4)
((lambda (x y) (* x y)) 4 5)
((lambda (x y) (if (> x y) "ok" "ko")) 9 5)
