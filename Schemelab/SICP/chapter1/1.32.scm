(define (accumulate combiner null-value term a next b)
  (if (> a b)
    null-value
    (combiner
     (term a)
     (accumulate combiner null-value term (next a) next b))))

(define (accumulate combiner null-value term a next b)
  (define (iter combiner term a next b result)
    (if (> a b)
      result
      (iter combiner term (next a) next b (combiner result (term a)))))
  (iter combiner term a next b null-value))

(define (sum term a next b)
  (accumulate + 0 term a next b))

(define (produce term a next b)
  (accumulate * 1 term a next b))
