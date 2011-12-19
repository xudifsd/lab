(define (fixed-point f guess)
 (define (close-enough? a b)
  (< (abs (- a b)) 0.0001))
 (define (report x)
  (display x)
  (newline))
 (let ((guess-value (f guess)))
  (report guess)
  (if (close-enough? guess guess-value)
   guess
   (fixed-point f guess-value))))

(define (repeated f n)
 (define (iter f n result)
  (if (< n 1)
   result
   (iter f (- n 1) (lambda (x) (f (result x))))))
 (iter f n identity))

(define (average-damp f)
 (lambda (x)
  (average x (f x))))

(define (average a b)
 (/ (+ a b) 2))

(define (square x)
 (* x x))

(define (log2 x)
 (/ (log x) (log 2)))

(define (nth-root x n)
 (fixed-point ((repeated average-damp (floor (log2 n)))
				(lambda (y) (/ x (expt y (- n 1)))))
              1))
