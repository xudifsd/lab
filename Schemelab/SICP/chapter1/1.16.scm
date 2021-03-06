(define (fast-expt b n)
  (define (fast-expt-iter b n coe)
    (cond ((= n 0) coe)
          ((even? n) (fast-expt-iter (* b b) (/ n 2) coe))
          (else (fast-expt-iter b (- n 1) (* b coe)))))
  (fast-expt-iter b n 1))
