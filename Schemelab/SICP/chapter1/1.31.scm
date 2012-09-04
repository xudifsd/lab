(define (term x)
  (let ((numerator (* (ceiling (/ (+ x 1) 2)) 2))
        (denominator (+ (* (ceiling (/ x 2)) 2) 1)))
    (/ numerator denominator)))

(define (product term a next b)
  (define (iter term a next b result)
    (if (> a b)
      result
      (iter term (next a) next b (* result (term a)))))
  (iter term a next b 1))

(define (inc x)
  (+ x 1))

(define (get-pi accuracy)
  (* 4 (product term 1 inc accuracy)))
