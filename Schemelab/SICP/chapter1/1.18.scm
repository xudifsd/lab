(define (double x)
  (+ x x))

(define (fast-* a b)
  (define (fast-*-iter a b acc)
    (cond ((= b 0) acc)
          ((even? b) (fast-*-iter (double a ) (/ b 2) acc))
          (else (fast-*-iter a (- b 1) (+ a acc)))))
  (fast-*-iter a b 0))
