(define (close-enough? a b)
  (< (abs (- a b)) 0.000000000000001))

(define (fixed-point f guess)
  (let ((guess-value (f guess)))
    (if (close-enough? guess guess-value)
      guess
      (fixed-point f guess-value))))

(define (get-golden-ratio)
  (fixed-point (lambda (x) (+ 1 (/ 1 x))) 2))
