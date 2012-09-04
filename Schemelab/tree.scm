(define (tree-insert! tree-dispatcher . args)
  (tree-dispatcher 'insert! args))

(define (tree-walker tree-dispatcher fun)
  (tree-dispatcher 'walker fun))

;;; constructor is used to construct a node when reach leaf-node
;;; comparator is used when inserting somehing, it's argument is node
;;; setter! is called when comparator return 0

(define (make-tree constructor comparator setter!)
  (let ((head '()) (insert-times 0))
    
    (define (make-node fn)
      (list '() (fn) '()))
    (define (left-leaf node)
      (car node))
    (define (right-leaf node)
      (caddr node))
    (define (tree-content node)
      (cadr node))
    
    (define (insert! node args);;;args now is pair
      (if (null? head)
        (set! head (make-node (lambda () (apply constructor args))))
        (let ((compare-result (apply comparator (cons (tree-content node) args))))
          (set! insert-times (+ 1 insert-times))
          (cond ((eq? compare-result 0)
                 (apply setter! (cons (tree-content node) args)))
                ((eq? compare-result 1)
                 (if (null? (left-leaf node))
                   (set! (car node) (make-node (lambda () (apply constructor args))))
                   (insert! (left-leaf node) args)))
                ((eq? compare-result -1)
                 (if (null? (right-leaf node))
                   (set! (caddr node) (make-node (lambda () (apply constructor args))))
                   (insert! (right-leaf node) args)))))))
    
    (define (walker node fun)
      (if (not (null? (left-leaf node)))
        (walker (left-leaf node) fun)
        )
      (fun (tree-content node))
      (if (not (null? (right-leaf node)))
        (walker (right-leaf node) fun)
        ))
    
    (define (tree-dispatcher sym . args)
      (cond ((eq? sym 'insert!) (insert! head args))
            ((eq? sym 'walker) (walker head (car args)))
            (else (error tree-dispatcher "Unsupport method"))))
    
    tree-dispatcher))
