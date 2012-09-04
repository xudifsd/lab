(define (average x y)
  (/ (+ x y) 2))

(define (square x)
  (* x x))

(define (my-sqrt y)
  (define (improve x)
    (average x (/ y x)))
  (define (good-enought? guess)
    (> 0.000001 (abs (- guess (improve guess)))))
  (define (sqrt-iter guess)
    (if (good-enought? guess)
      guess
      (sqrt-iter (improve guess))))
  (sqrt-iter 1))
