(define (zero f)
  (lambda (x) x))

(define (add-1 n)
  (lambda (f)
    (lambda (x)
      (f ((n f) x)))))

(define (one f)
  (lambda (x)
    (f x)))

(define (two f)
  (lambda (x)
    (f (f x))))

(define (+ n1 n2)
  (lambda (f)
    (lambda (x)
      ((n2 f) ((n1 f) x)))))
