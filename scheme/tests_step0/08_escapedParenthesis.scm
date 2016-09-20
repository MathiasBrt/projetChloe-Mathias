;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="Test parenthesis in strings and char parenthesis"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( something ( "a string with parenthesis ) !!!" ) other)

( something ( "Now, a char parenthesis " #\) ) )

	( something ( "Now, a char parenthesis " #\( ) )
