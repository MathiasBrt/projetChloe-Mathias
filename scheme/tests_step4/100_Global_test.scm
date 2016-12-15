;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Global Test"
;———


10
(+ 137 349)
(- 1000 334)
(+ (* 3 5) (- 10 6))
(+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))
(+ (* 3
      (+ (* 2 4)
         (+ 3 5)))
   (+ (- 10 7)
      6))

(list 1 2 3)
(car (list 1 2 3))
(cdr (list 1 2 3))
(and (= 4 3) (< 4 9))
(define size 2)
size
(* 5 size)
(define power2 (lambda (x) (* x x))) 
(define sum-of-square (lambda (y z) (+ (power2 y) (power2 z))))
(sum-of-square 2 3)
(power2 21)

((lambda (x y z) (+ x y (power2 z))) 1 2 3)

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))
(a-plus-abs-b 3 -2)

(define count ((lambda (total)
(lambda (increment)
(set! total (+ total increment)) total))
0))
(count 3)

(if (= n 0)
1
(* n (factorial (- n 1))))))

(factorial 4)