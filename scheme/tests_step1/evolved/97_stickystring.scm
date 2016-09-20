; TEST_RETURN_CODE=PASS
; TEST_COMMENT=string sans espaces de separation

("ceci est une chaine" 5)
(5 "ceci est une chaine")
("ceci est une chaine" "ca aussi")

; la ca se corse !

("ceci est une chaine" 5)
(5"ceci est une chaine")
("ceci est une chaine""ca aussi")