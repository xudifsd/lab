(define (f n)
 (define (f-iter a b c count)
  (cond ((= count 0) a)
   ((= count 1) b)
   ((= count 2) c)
   (else
	(f-iter b c (+ c (* 2 b) (* 3 a)) (- count 1)))))
 (f-iter 0 1 2 n))
