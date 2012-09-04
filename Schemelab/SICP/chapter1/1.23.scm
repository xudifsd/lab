(define (square x)
  (* x x))

(define (smallest-divisor n)
  (define (find-divisor n test-divisor)
    (define (divides? a b)
      (= (remainder b a) 0))
    (define (next n)
      (if (= n 2)
        3
        (+ n 2)))
    (cond ((> (square test-divisor) n) n)
          ((divides? test-divisor n) test-divisor)
          (else (find-divisor n (next test-divisor)))))
  (find-divisor n 2))


(define (prime? n)
  (= n (smallest-divisor n)))


(define (report-elapsedtime oldtime)
  (display " *** ")
  (display (- (current-milliseconds) oldtime))
  (display " *** "))

(define (search-for-primes base count)
  (define (search-with-time base count time)
    (if (= count 0)
      (begin (report-elapsedtime time) '())
      (begin
       (if (prime? base)
         (cons base (search-with-time (+ base 1) (- count 1) time))
         (search-with-time (+ base 1) count time)))))
  (search-with-time base count (current-milliseconds)))
