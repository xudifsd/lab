(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b))))

(define (inc x)
  (+ x 1))

;;accuracy normal is 100 or 1000, it's calculate integral between low and up
;;respecting function f
(define (integral f low up accuracy)
  (let ((h (/ (- up low) accuracy)))
    (define (y k)
      (if (or (= k 0) (= k accuracy))
        (f (+ low (* k h)))
        (* (+ (* (remainder k 2) 2) 2) (f (+ low (* k h))))))
    (* (/ h 3) (sum y 0 inc accuracy))))
