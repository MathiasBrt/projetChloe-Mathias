;———
; TEST_RETURN_CODE=PASS		
; TEST_COMMENT="Test set! : evolved_01"
;———

(define Thomas 4)
(if (if #t #t #f) (set! Thomas 5) (define Francois 6))
(if (if #f #t #f) (set! Arthur 5) (define Benjamin 6))
(if (if Arthur=5 #t #f) (set! Thomas 2) (define Arnaud 6))
(if (if Arthur=12 #t #f) (set! Thomas 4) (define Arnaud 6))
(if (if Arthur=Benjamin #t #f) (set! Thomas 3) (define Arnaud 6))
