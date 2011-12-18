(define (cont-frac n d k)
 (define (iter n d k result)
  (if (< k 1)
   result
   (iter n d (- k 1) (/ (n k) (+ (d k) result)))))
 (iter n d k 0))

;;often you can take 15 as k to calculate it
(define (tan-cf x k)
 (define (n i)
  (if (= i 1)
   x
   (- 0 (* x x))))
 (define (d i)
  (- (* 2 i) 1))
 (cont-frac n d k))
