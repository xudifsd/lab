(load "tree.scm")

(define (stream-cons a b)
  (cons a (delay b)))

(define (stream-car pair)
  (car pair))

(define (stream-cdr pair)
  (force (cdr pair)))



(define (string-part content)
  (car content))

(define (count-part content)
  (cdr content))

(define (constructor str-pair)
  (let ((str (car str-pair)))
    (cons str 1)))

(define (comparator node str-pair)
  (let ((str (car str-pair)))
    (cond
     ((string> (string-part node) str) 1)
     ((string< (string-part node) str) -1)
     ((string= (string-part node) str) 0))))

(define (incr-count! node str-pair)
  (let ((str (car str-pair)))
    (set! (cdr node) (+ 1 (count-part node)))))

;;;; below is application part, just for test

(define tree (make-tree constructor comparator incr-count!))

(define (print node)
  (display (string-part node))
  (display "\t")
  (display (count-part node))
  (newline))
