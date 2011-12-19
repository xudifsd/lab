(define (double f)
 (lambda (x)
  (f (f x))))

(define (inc x)
 (+ x 1))

(define (answer)
 (((double (double double)) inc) 5))
