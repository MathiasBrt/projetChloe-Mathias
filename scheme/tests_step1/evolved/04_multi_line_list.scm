; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test multi line lists

( something ( another )
( aSymbol  ( 
	#\a a 56 
	) 
)
)


( aSymbol  ( 
	( nested )
	#\a 56 
	) 
)


( aSymbol  
	( 
	( 
nested )
		#\a 56  ( ploouf )
	) 
)

( lambda ( X ) ( * X 2
;; Some comment here
)

)

( define ( fun arg1 arg2 )
  ( + arg1 ( 7 arg2 ) ) )
