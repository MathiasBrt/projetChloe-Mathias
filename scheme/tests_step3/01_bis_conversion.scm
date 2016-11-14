;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des conversions_bis"
;———

(stringtosymbol "Bonjour")
(symboltostring Bonjour)
(stringtonumber "Bonjour")
(stringtonumber "Bonjour, Comment vas-tu ?")
(stringtonumber "Bonjour                          comment vas-tu?")