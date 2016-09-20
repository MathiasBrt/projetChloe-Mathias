; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Strange strings

"this is a string"
" "

"another string with some scheme char inside #\t "

;; parenthesis should be OK
"a string with some parenthesis inside ( plop"
"a string with some parenthesis inside )"
"a string with some parenthesis inside # )"
"a string with some parenthesis inside # ("
"a string with some parenthesis inside ) ( plop"
"a string with some parenthesis inside ( ) (()))"

;; should we keep the anti slash char \ or not ???
"another string with escaped double quote \" "

;; ; inside a string is not a comment...
"semi colon inside a string is not a comment ; ; ;  "


;;; Make sure you put a return at
;;; the end of the input file
