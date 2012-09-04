(define (iterative-improve good-enough? improve)
  (define (report x)
    (display x)
    (newline))
  (define (iter guess)
    (let ((improved (improve guess)))
      (report guess)
      (if (good-enough? improved guess)
        guess
        (iter improved))))
  iter)

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

(define (fixed-point f guess)
  (define (close-enough? improved guess)
    (< (abs (- improved guess)) 0.00001))
  ((iterative-improve close-enough? f) guess))

(define (log2 x)
  (/ (log x) (log 2)))

(define (nth-root x n)
  (fixed-point ((repeated average-damp (floor (log2 n)))
                (lambda (y) (/ x (expt y (- n 1)))))
               1))
