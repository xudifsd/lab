(load "derive.scm")

(define tolerance 0.00000001)

(define (get-iter-formula origin-function symbol)
  ;; Newton-Raphson method
  (make-sub symbol
            (make-div origin-function
                      (derive origin-function symbol))))

(define (calculate function symbol env init-value)
  ;; use like (calculate '(- (* 5 (log e x)) x) 'x '() 1)
  (define (change-value-in-env value lst)
    ;; we assume env has such structure: '((x 1) (y 2) (z 3))
    (map (lambda (element)
           (if (eq? (car element) symbol)
             (list symbol value)
             element)) lst))

  (define (add-symbol-value)
    (if (list? (assq symbol env))
      env;; already have value in env, do nothing
      (cons (list symbol 'dummy-value) env)));; add a placeholder

  (let ((iter-formula (get-iter-formula function symbol))
        (init-env (add-symbol-value)))
    (define (iter value)
      (let ((next-value (algebre-eval iter-formula (change-value-in-env value init-env))))
        (if (< (abs (- next-value value)) tolerance)
          next-value
          (iter next-value))))

    (iter init-value)))
