(define (repeated f n)
  (define (iter f n result)
    (if (< n 1)
      result
      (iter f (- n 1) (lambda (x) (f (result x))))))
  (iter f n identity))

(define (square x)
  (* x x))

(define (answer)
  ((repeated square 2) 5))
