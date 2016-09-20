; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test basic lists with spaces...
(   4 5    6    )
( something     another )
(         something         another       )
(         something			another)
(      "abc" #t #f #\u 45 -5 -12 +8 +89 abc)
("abc" #t #f #\u 45 -5 -12 +8 +89 	abc       )
