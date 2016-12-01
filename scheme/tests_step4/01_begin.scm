;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du begin"
;———

(begin (quote "expr1") (quote "expr2") (quote "begin n'affiche que la dernière expr!"))
(begin (define i 0) i)
(if (= i 0) (begin (set! i 5) (* i i)) (quote "i a changé !"))
(if (= i 0) (begin (set! i 5) (* i i)) (quote "i a changé !"))
(begin (define w 0) (set! w 4) w)
((lambda (x y z)
  (begin
    (define hyp (* x x))
    (define sum (+ (* y y) (* z z)))
    (if (= hyp sum)
	(quote "le carré de l'hypothénuse...")
	)
    )
  )
5 3 4
)
