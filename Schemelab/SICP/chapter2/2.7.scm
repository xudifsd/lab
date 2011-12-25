(define (make-interval a b)
 (cons a b))

(define (upper-bound a)
 (car a))

(define (lower-bound a)
 (cdr a))
