; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Global basic test

0
1
2
3
4

-5
+4

-6786

12
-78

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
 "   another string with some scheme char inside #\space "
"another string ( ) () a"

	aSymbol 

anotherSymbol

  (   4 5    6    )
( something     another )
(         something         another       )
(         something			another)
(      "abc" #t #f #\u 45 -5 -12 +8 +89 abc)
	(	"abc" #t #f #\u 45 -5 -12 +8 +89 	abc       )

;; a comment 
;; another comment

( something another ( 4 5 ) )
(    4 5 ( #\a 56 ( plouf  ( test ( +6 -7 ) test ) ( another ) ) ) )
( define ( fun arg1 arg2 ) ( + arg1 ( 5 #t ) )      )
  ( lambda ( X ) 		( * X 2 )   	  )	

;;; Make sure you put a return at
;;; the end of the input file
