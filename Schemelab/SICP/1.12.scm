(define (triangle i j)
 (cond ((= i j) 1)
  		((= j 1) 1)
		(else
		 (+ (triangle (- i 1) j)
		  (triangle (- i 1) (- j 1))))))
