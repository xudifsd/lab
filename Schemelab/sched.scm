;; father who do fork get 1, child get 0
(define tasklist '())

(define (in-task! task)
  (set! tasklist (append tasklist (list task)))
  1)

(define (out-task!)
  (if (null? tasklist)
    #f
    (let ((task (car tasklist)))
      (set! tasklist (cdr tasklist))
      task)))

(define (sched)
  (let ((next-task (out-task!)))
    (if (procedure? next-task)
      (next-task 'dummy)
      (begin
       (print "All task is done")
       (exit 0)))))

(define (yeild)
  (call/cc (lambda (context) (in-task! context) (sched))))

(define (get-current)
  (call/cc (lambda (current) current)))

(define (fork)
  (let ((context (get-current)))
    (if (procedure? context)
      (begin
       (in-task! context)
       1)
      0)))

(define (range top)
  (define (iter cur acc)
    (if (= cur top)
      acc
      (iter (+ cur 1) (cons cur acc))))
  (reverse (iter 0 '())))

(define (thread1)
  ;; demo function
  (for-each (lambda (element)
              (print "in thread1 " element)
              (yeild))
            (range 100))
  (sched))

(define (thread2)
  ;; demo function
  (for-each (lambda (element)
              (print "in thread2 " element)
              (yeild))
            (range 100))
  (sched))

(define (init)
  ;; init function bring system up
  (if (= (fork) 0)
    (thread1)
    (if (= (fork) 0)
      (thread2)
      (sched))))

(init)
