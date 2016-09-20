;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="Test read basic atoms : strings, integers, chars, booleans, symbols, etc"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
0
1
2
3
4

#t
#f

a
b
c

#\a
#\t
#\n
#\0
#\^
#\'
#\"
#\(
#\)

#\space
#\newline

42
-55
+43

"this is a string"
" "
	"another string with an anti-slash \" "
 "another string with an anti-slash #\" "
"another string with some scheme char inside #\t "
"another string with some scheme char inside #\space "

aSymbol

anotherSymbol

;;; Make sure you put a return at
;;; the end of the input file
