;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des conversions de type"
;———

(chartointeger #\a)
(chartointeger #\space)
(chartointeger #\newline)
(integertochar 97)
(integertochar (chartointeger #\a))
(chartointeger (integertochar 97))
(numbertostring 3)
(numbertostring (+ 1 1 1))

