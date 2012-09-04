;;;this script test <SICP> execise 1.25 just invoke (test 1000), it's seems
;;;that the problem is just precise in float, two procedure is same
(define (square x)
  (* x x))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
          (remainder (* base (expmod base (- exp 1) m))
                     m))))

(define (fast-expt b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))

(define (aexpmod base exp m)
  (remainder (fast-expt base exp) m))

(define (testcase base exp m)
  (= (aexpmod base exp m) (expmod base exp m)))

(define (next base exp m times)
  (if (< m 25)
    (list base exp (+ m 1) (- times 1))
    (if (< exp 10)
      (list base (+ 1 exp) 1 (- times 1))
      (list (+ 1 base) 1 1 (- times 1)))))

(define (report base exp m)
  (display base)
  (display " ")
  (display exp)
  (display " ")
  (display m)
  (display " ")
  (newline))


;;invoke (test 1000) will test automatically
(define (test times)
  (define (loop-assert base exp m times)
    (if (> times 0)
      (begin
       (report base exp m)
       (assert (testcase base exp m))
       (apply loop-assert (next base exp m times)))
      'done))
  (loop-assert 1 1 1 times))
