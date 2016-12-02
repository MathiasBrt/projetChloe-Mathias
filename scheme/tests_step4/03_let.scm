;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test du let"
;———

(let ((x 1)) x)
(begin
  (define x 3)
  (let ((y x))
    (if (= x y) (quote "gnagnagna"))))
(let ((x 7))
  (if (= x 7)
      (quote "let utilise son propre environnement")
      (quote "x ne doit pas valoir 3 !")))
(let ((x 2) (y 3))
  (set! x (+ y x))
  (set! y (- x y))
  y) 
