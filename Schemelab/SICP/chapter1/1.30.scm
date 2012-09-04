(define (sum term a next b)
  (define (iter a reslut)
    (if (> a b)
      reslut
      (iter (next a) (+ (term a) reslut))))
  (iter a 0))
