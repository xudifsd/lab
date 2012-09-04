(define (close-enough? a b)
  (< (abs (- a b)) 0.0001))

(define (report x)
  (display x)
  (newline))

(define (fixed-point f guess)
  (let ((guess-value (f guess)))
    (report guess)
    (if (close-enough? guess guess-value)
      guess
      (fixed-point f guess-value))))

(define (answer-without-average-damping)
  (fixed-point (lambda (x) (/ (log 1000) (log x))) 2))

(define (answer-with-average-damping)
  (fixed-point (lambda (x) (* 0.5 (+ x (/ (log 1000) (log x))))) 2))
