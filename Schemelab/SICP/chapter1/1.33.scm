(define (filtered-accumulate combiner null-value term a next b pre)
 (define (iter a result)
  (if (> a b)
   result
   (iter (next a) (if (pre a)
				   (combiner result (term a))
				   result))))
 (iter a null-value))

(define (square x)
 (* x x))

(define (prime? n)
 (= n (smallest-divisor n)))

(define (smallest-divisor n)
 (find-divisor n 2))

(define (find-divisor n test-divisor)
 (cond ((> (square test-divisor) n) n)
  ((divides? test-divisor n) test-divisor)
  (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
 (= (remainder b a) 0))

(define (inc x)
 (+ x 1))

;; this calculate the sum of squares of the prime numbwes between a and b
(define (answer-a a b)
 (filtered-accumulate + 0 square a inc b prime?))

(define (relatively-prime-to-n n)
 (lambda (x)
  (= 1 (gcd x n))))

;; this calculate the product of all the positive integers less than n that
;; are relatively prime to n (ie. all positive integers i < n such that
;; GCD(i,n) = 1)
(define (answer-b a b)
 (filtered-accumulate * 1 identity a inc b (relatively-prime-to-n b)))
