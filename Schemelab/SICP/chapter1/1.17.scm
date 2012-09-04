(define (double x)
  (+ x x))


(define (fast-* a b)
  (cond ((= b 0) 0)
        ((even? b ) (double (fast-* a (/ b 2))))
        (else (+ a (fast-* a (- b 1))))))
