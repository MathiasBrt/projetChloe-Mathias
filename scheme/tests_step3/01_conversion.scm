;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des conversions de type"
;———

(chartointeger #\a)
(chartointeger #\space)
(chartointeger #\newline)
(integer? (chartointeger #\a))
(integertochar 97)
(character? (integertochar 97))
(integertochar (chartointeger #\a))
(chartointeger (integertochar 97))
(numbertostring 97)
(numbertostring (+ 1 1 1))
(string? (numbertostring 97))

