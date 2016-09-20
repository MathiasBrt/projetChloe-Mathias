; TEST_RETURN_CODE=FAIL
; TEST_COMMENT=Trailing expr at end of line : error

( 4 5 -9 abc (def))

( 3 7 -9 abc (def)) (uneautreexpr 9 0)

( 9 12 -9 abc (def))
