(define (assert condition)
  (if (eval condition)
    #t
    (begin
     (print "assert failed, condition is " condition)
     (exit 1))))

(define (less? a b)
  ;; This function is used to sort expression
  ;; for example: (sort '((* 2 x) 2 x 5 y) less?) --> '(2 5 x y (* 2 x))
  (cond ((constant? a) #t)
        ((constant? b) #f)
        ((variable? a) #t)
        ((variable? b) #f)
        ((list? a) #t)
        ((list? b) #f)
        (else #t)))

(define (all-argument expression)
  (cddr expression))

(define (first-argument expression)
  (cadr expression))

(define (rest-argument expression)
  ;; return all arguments expect first argument, if have more than two
  ;; arguments add operator to expression's head, which is useful for
  ;; add and mul
  (let ((symbol (car expression)))
    (if (= (length expression) 3)
      (caddr expression)
      (cons symbol (cddr expression)))))

(define (sub-rest-argument expression)
  ;; when we get rest-argument of expression when it's operator is '-
  ;; we should change it's operator to '+
  (let ((symbol (car expression)))
    (assert '(= symbol '-))
    (if (= (length expression) 3)
      (caddr expression)
      (cons '+ (cddr expression)))))

(define (variable? expression)
  (symbol? expression))

(define (same-variable? expression1 expression2)
  (eq? expression1 expression2))

(define (constant? expression)
  (number? expression))

(define (is-operator? expression symbol)
  (and (list? expression)
       (eq? (car expression) symbol)))

(define (add? expression)
  (is-operator? expression '+))

(define (sub? expression)
  (is-operator? expression '-))

(define (mul? expression)
  (is-operator? expression '*))

(define (div? expression)
  (is-operator? expression '/))

(define (exp? expression)
  (is-operator? expression '^))

(define (log? expression)
  (is-operator? expression 'log))

(define (sin? expression)
  (is-operator? expression 'sin))

(define (cos? expression)
  (is-operator? expression 'cos))

(define (tan? expression)
  (is-operator? expression 'tan))

(define (cot? expression)
  (is-operator? expression 'cot))

(define (make-add a b)
  ;; FIXME
  ;; 1. merge it if a, b is both add expression
  ;; 2. sort a and b
  (cond ((and (constant? a) (= a 0)) b)
        ((and (constant? b) (= b 0)) a)
        ((same-variable? a b) (make-mul 2 a))
        ((and (add? a) (add? b)) (append a (all-argument b)))
        ((and (sub? a) (sub? b)) (append a (all-argument b)))
        ((add? a) (append a (list b)))
        ((add? b) (append b (list a)))
        (else (list '+ a b))))

(define (make-sub a b)
  ;; FIXME optimize it
  (cond ((and (constant? a) (= a 0)) (list '- b))
        ((and (constant? b) (= b 0)) a)
        (else
          (list '- a b))))

(define (make-mul a b)
  ;; FIXME
  ;; 1. merge it if a, b is any of it is expo expression
  ;; 2. return (^ x 2) if a is x, b is x, instead of (* x x)
  ;; 3. sort a and b
  ;; 4. merge (^ x 2) (/ 1 x)
  (cond ((and (constant? a) (= a 1)) b)
        ((and (constant? a) (= a 0)) 0)
        ((and (constant? b) (= b 1)) a)
        ((and (constant? b) (= b 0)) 0)
        ;; FIXME if a == b return (^ a 2)
        ((and (mul? a) (mul? b)) (append a (all-argument b)))
        ((mul? a) (append a (list b)))
        ((mul? b) (append b (list a)))
        (else (list '* a b))))

(define (make-div a b)
  ;; FIXME optimize it
  (cond ((and (constant? b) (= b 1)) a)
        ((and (constant? b) (= b 0)) (print "dived by 0"))
        ((and (constant? a) (= a 0)) 0)
        ((and (constant? a) (= a 1) (div? b))
         (make-div (rest-argument b) (first-argument b)))
        (else
          (list '/ a b))))

(define (make-exp a b)
  ;; FIXME optimize it
  (cond ((and (constant? b) (= b 0)) 1)
        ((and (constant? b) (= b 1)) a)
        ((and (constant? a) (= a 1)) 1)
        ((and (constant? a) (= a 0)) 0)
        (else
          (list '^ a b))))

(define (make-log a b)
  ;; FIXME optimize it
  (cond ((and (eq? a 'e) (eq? b 'e)) 1)
        ((and (constant? b) (= b 1)) 0)
        (else
          (list 'log a b))))

(define (make-sin a)
  (list 'sin a))

(define (make-cos a)
  (list 'cos a))

(define (make-tan a)
  (list 'tan a))

(define (make-cot a)
  (list 'cot a))

(define (derive expression variable)
  ;; derive function expression written in lisp, ie
  ;; (derive '(+ (* x x) x) 'x) ==> '(+ (* 2 x) 1)
  ;; we now support:
  ;; 1. add
  ;; 2. sub
  ;; 3. mul
  ;; 4. div
  ;; 5. exp
  ;; 6. log
  ;; 7. sin
  ;; 8. cos
  ;; 9. tan
  ;; 10. cot
  ;; We preserve keywords: log e pi cos sin cos tan cot,
  ;; so they can't be used as variable
  
  (cond
   ((or
     (eq? variable 'log)
     (eq? variable 'e)
     (eq? variable 'pi)
     (eq? variable 'cos)
     (eq? variable 'sin)
     (eq? variable 'cos)
     (eq? variable 'tan)
     (eq? variable 'cot)) (print variable " is preserved word"))

   ((constant? expression) 0)

   ((variable? expression)
    (if (same-variable? expression variable) 1 0))
   ((or (not (list? expression)) (not (variable? variable)))
    (print "Error expression " expression " is not a list" #\newline
           "or variable " variable " is not a symbol"))

   ;; from now on expression can only be list
   ((add? expression)
    (make-add (derive (first-argument expression) variable)
              (derive (rest-argument expression) variable)))

   ((sub? expression)
    (make-sub (derive (first-argument expression) variable)
              (derive (sub-rest-argument expression) variable)))

   ((mul? expression)
    (make-add
     (make-mul (derive (first-argument expression) variable)
               (rest-argument expression))
     (make-mul (derive (rest-argument expression) variable)
               (first-argument expression))))

   ((div? expression)
    (make-div
     (make-sub (make-mul (derive (first-argument expression) variable)
                         (rest-argument expression))
               (make-mul (first-argument expression)
                         (derive (rest-argument expression) variable)))
     (make-exp (rest-argument expression) 2)))

   ((exp? expression)
    (assert '(= (length expression) 3));;make sure it contains only two args
    (make-mul
     (make-exp (first-argument expression) (rest-argument expression))
     (make-add
      (make-mul (derive (rest-argument expression) variable)
                (make-log 'e (first-argument expression)))
      (make-mul (derive (first-argument expression) variable)
                (make-div (rest-argument expression)
                          (first-argument expression))))))

   ((log? expression)
    (assert '(= (length expression) 3));;make sure it contains only two args
    (make-div
     (make-sub
      (make-mul
       (make-div 1 (rest-argument expression))
       (make-mul
        (derive (rest-argument expression) variable)
        (make-log 'e (first-argument expression))))
      (make-mul
       (make-div 1 (first-argument expression))
       (make-mul
        (derive (first-argument expression) variable)
        (make-log 'e (rest-argument expression)))))
     (make-exp (make-log 'e (first-argument expression)) 2)))

   ((sin? expression)
    (assert '(= (length expression) 2))
    (make-mul
     (derive (first-argument expression) variable)
     (make-cos (first-argument expression))))

   ((cos? expression)
    (assert '(= (length expression) 2))
    (make-sub 0 (make-mul
                 (derive (first-argument expression) variable)
                 (make-sin (first-argument expression)))))

   ((tan? expression)
    (assert '(= (length expression) 2))
    (make-div
     (derive (first-argument expression) variable)
     (make-exp (make-cos (first-argument expression)) 2)))

   ((cot? expression)
    (assert '(= (length expression) 2))
    (make-sub 0 (make-div
                 (derive (first-argument expression) variable)
                 (make-exp (make-sin (first-argument expression)) 2))))

   (else
     (print "Unknow expression: " expression))))

(define (algebre-eval expression env)
  ;; eval is evil, we all know it, so we use algebre-eval to eval algebre
  ;; expression, and we can also provide user with much more function, like
  ;; ^(exponent) and (log a b)
  ;; ATTENTION: all the symbol used in expression must have associated value
  ;; in env, for example, if we have x bind to 2, and y bind to 3, env should
  ;; be '((x 2) (y 3)), if no bind value, just pass '()
  ;; in summary algebre-eval provide a more safe way to eval algebre
  ;; expression.

  (define (^ base power)
    (cond ((= 0 power) 1)
          ((= 1 power) base)
          ((= 2 power) (* base base))
          ((even? power) (^ (^ base (/ power 2)) 2))
          (else
            (* base (^ base (- power 1))))))

  (define (mylog base up)
    (/ (log up) (log base)))

  (define (cot a)
    (/ 1 (tan a)))

  (cond
   ((constant? expression) expression)
   ((variable? expression)
    (cond ((eq? expression 'e) 2.71828182845905)
          ((eq? expression 'pi) 3.14159265358979)
          (else
            (if (list? env)
              (let ((value (assq expression env)))
                (if (list? value)
                  (algebre-eval (cadr value) env)
                  ;; so that we can use '((x (/ pi 4))) as env
                  (begin
                   (print expression " is not in env list")
                   (exit 1))))
              (begin
               (print env " is not a list")
               (exit 1))))))

   ((add? expression)
    (+ (algebre-eval (first-argument expression) env)
       (algebre-eval (rest-argument expression) env)))

   ((sub? expression)
    (if (= (length expression) 2) ;;(- 2)
      (- 0 (algebre-eval (first-argument expression) env))
      (- (algebre-eval (first-argument expression) env)
         (algebre-eval (sub-rest-argument expression) env))))

   ((mul? expression)
    (* (algebre-eval (first-argument expression) env)
       (algebre-eval (rest-argument expression) env)))

   ((div? expression)
    (/ (algebre-eval (first-argument expression) env)
       (algebre-eval (rest-argument expression) env)))

   ((exp? expression)
    (assert '(= (length expression) 3))
    (^ (algebre-eval (first-argument expression) env)
       (algebre-eval (rest-argument expression) env)))

   ((log? expression)
    (assert '(= (length expression) 3))
    (mylog (algebre-eval (first-argument expression) env)
           (algebre-eval (rest-argument expression) env)))

   ((sin? expression)
    (assert '(= (length expression) 2))
    (sin (algebre-eval (first-argument expression) env)))

   ((cos? expression)
    (assert '(= (length expression) 2))
    (cos (algebre-eval (first-argument expression) env)))

   ((tan? expression)
    (assert '(= (length expression) 2))
    (tan (algebre-eval (first-argument expression) env)))

   ((cot? expression)
    (assert '(= (length expression) 2))
    (cot (algebre-eval (first-argument expression) env)))))
