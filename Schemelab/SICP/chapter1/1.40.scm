(define (close-enough? a b)
 (< (abs (- a b)) 0.0000001))

(define (report x)
 (display x)
 (newline))

(define (deriv g)
 (let ((dx 0.0000001))
  (lambda (x)
   (/ (- (g (+ x dx)) (g x))
    dx))))

(define (fixed-point f guess)
 (let ((guess-value (f guess)))
  (report guess)
  (if (close-enough? guess guess-value)
   guess
   (fixed-point f guess-value))))

(define (newton-transform g)
 (lambda (x)
  (- x (/ (g x) ((deriv g) x)))))

(define (newtons-method g guess)
 (fixed-point (newton-transform g) guess))

(define (cubic a b c)
 (lambda (x)
  (+ (* x x x) (* x x a) (* b x) c)))

(define (answer a b c)
 (newtons-method (cubic a b c) 1))
