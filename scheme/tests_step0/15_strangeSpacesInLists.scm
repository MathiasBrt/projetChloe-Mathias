;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test spaces between / after ( )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(4(5 6))
(4 (5 6))
( 4 (5 6))
( 4 ( 5 6))
( 4 ( 5 6 ))
( 4 ( 5 6 ) )
( 4
(5 6)
)


