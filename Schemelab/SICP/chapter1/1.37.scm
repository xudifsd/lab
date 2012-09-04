;;recursive process
(define (cont-frac n d k)
  (define (helper n d i)
    (if (> i k)
      0
      (/ (n i) (+ (d i) (helper n d (+ i 1))))))
  (helper n d 1))

;;iterative process
(define (cont-frac n d k)
  (define (iter n d k result)
    (if (< k 1)
      result
      (iter n d (- k 1) (/ (n k) (+ (d k) result)))))
  (iter n d k 0))

(define golden-ratio 1.6180339887499)

(define (close-enough? guess)
  (< (abs (- guess (/ 1 golden-ratio))) 0.0001))

(define (answer-a)
  (define (helper times)
    (let ((guess (cont-frac (lambda (i) 1.0) (lambda (i) 1.0) times)))
      (if (close-enough? guess)
        times
        (helper (+ 1 times)))))
  (helper 1))
