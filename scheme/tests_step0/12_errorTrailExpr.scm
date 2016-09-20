;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="Error trailing chars at end of S-Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( a (b ) ( c d ( e ) ) ) 
( a (b ) ( c d ( e ) ) ) (ab (cd)
( a (b ) ( c d ( e ) ) ) 
