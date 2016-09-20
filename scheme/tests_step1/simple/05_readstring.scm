; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test read basic strings

"this is a string"
" "

"another string with some scheme char inside #\t "
"another string with some scheme char inside #\space "
"another string with some scheme parenthesis () "
  "another string with some scheme parenthesis ()  ( )"  

;;; Make sure you put a return at
;;; the end of the input file
