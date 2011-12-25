(define (cons a b)
 (* (expt 2 a) (expt 3 b)))

(define (logb b n)
 (floor (/ (log n) (log b))))

(define (car x)
 (logb 2 (/ x (gcd x (expt 3 (logb 3 x))))))

(define (cdr x)
 (logb 3 (/ x (gcd x (expt 2(logb 2 x))))))
