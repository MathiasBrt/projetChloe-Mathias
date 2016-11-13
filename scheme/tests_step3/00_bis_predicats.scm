;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test des predicats"
;———

(pair? (1 2 3))
(pair? (a b c))
(pair? ((a b)c))
(pair? ("bonjour") ("bonjour") ("bonjour"))
(pair? ("Bonjour") "Bonjour")
(string? "Bonjour")
(string? "Bonjour" "Comment vas-tu?")
(string? "Bonjour" "Comment vas-tu?" Je                  vais bien)
(string? Je vais bien "Comment vas-tu?" "Bonjour")
(character? #\a)
(character? #\b #\c #\d            #\e)
(character? #\azerty #\a)
(character? #\azerty azerty)
(character? azerty #\azerty)
(character? azerty #\azerty azerty azerty)
(integer? 1)
(integer? 1 2 3 4 5)
(integer? 1234 1234 1234 )
(integer? 1234       1234                 1234)
(integer? 123 "1234" (123) 1234,4)
