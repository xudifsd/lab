(define (double x)
 (* x x))

(define (average x y)
 (/ (+ x y) 2))

(define (make-point x y)
 (cons x y))

(define (x-point p)
 (car p))

(define (y-point p)
 (cdr p))

(define (distance p1 p2)
 (sqrt (+ (double (- (x-point p1) (x-point p2)))
          (double (- (y-point p1) (y-point p2))))))

(define (make-rectangle p1 p2 p3)
 ; p1 --------- p3
 ;    |       |
 ;    |       |
 ; p2 ---------
 (list p1 p2 p3))

(define (point-a rec)
 (car rec))

(define (point-b rec)
 (cadr rec))

(define (point-c rec)
 (caddr rec))

(define (rectangle-length rec)
 (distance (point-a rec) (point-c rec)))

(define (rectangle-width rec)
 (distance (point-a rec) (point-b rec)))

;;answer
(define (perimeter rec)
 (* 2 (+ (rectangle-length rec) (rectangle-width rec))))

(define (area rec)
 (* (rectangle-length rec) (rectangle-width rec)))
