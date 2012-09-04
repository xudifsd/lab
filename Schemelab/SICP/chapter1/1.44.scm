(define (repeated f n)
  (define (iter f n result)
    (if (< n 1)
      result
      (iter f (- n 1) (lambda (x) (f (result x))))))
  (iter f n identity))

(define (average a b c)
  (/ (+ a b c) 3))

(define (smooth f)
  (let ((dx 0.001))
    (lambda (x)
      (average (f (- x dx)) (f x) (f (+ x dx))))))

(define (square x)
  (* x x))

;;the function that needs to be smoothed
(define (f x)
  (if (> x 0)
    (- 0 x)
    x))

(define (answer)
  ((repeated smooth 3) f))
