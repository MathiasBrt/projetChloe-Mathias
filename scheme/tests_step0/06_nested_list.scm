;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="Test nested lists"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( something another ( 4 5 ) )
( 4 5 ( #\a 56 ( plouf ( test ( 6 7 ) test ) ( another ) )))
( define ( fun arg1 arg2 ) ( + arg1 ( 5 arg2 ) ) )
( lambda ( X ) ( * X 2 ) )