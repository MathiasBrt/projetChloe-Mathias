;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du if : evolved_03"
;———

(define Bob 1)
(define Pierre 2)
(define (Paul) (+ Pierre Bob))
(define (Bertrand) (* (+ Pierre Bob) Paul))
(define (Bernard) (/ (* (+ Pierre Bob) Paul) Paul))
(define (Adrien) (- Bernard Paul))
