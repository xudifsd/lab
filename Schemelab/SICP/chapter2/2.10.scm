(define (div-interval x y)
  (cond ((= 0 (lower-bound y))
         (error "lower bound of second argument is 0"))
        ((= 0 (upper-bound y))
         (error "upper bound of second argument is 0"))
        (else
          (mul-interval x
                        (make-interval (/ 1 (upper-bound y)) (/ 1 (lower-bound y)))))))
