(define (cont-frac n d k)
  (define (iter n d k result)
    (if (< k 1)
      result
      (iter n d (- k 1) (/ (n k) (+ (d k) result)))))
  (iter n d k 0))

(define (n i)
  1)

(define (d i)
  (let ((i (+ 1 i)))
    (if (not (= (remainder i 3) 0))
      1
      (* (/ i 3) 2))))

;;the bigger the accuracy is the accurate the answer got, and accuracy is
;;a positive integer, use (answer 19) to get answer
(define (answer accuracy)
  (+ (cont-frac n d accuracy) 2))
