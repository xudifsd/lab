(load "unit-test.scm")
(load "derive.scm")

(define (test-pro expression value expect)
  (if (< (abs (- (algebre-eval expression value) expect)) 0.001)
    #t
    #f))

(define (test-pro1 expression sym value expect)
  (if (< (abs (- (algebre-eval (derive expression sym) value) expect)) 0.001)
    #t
    #f))

(define test-case (init-case))
(set! test-case (add-case '((log 2 2) () 1) test-case))
(set! test-case (add-case '((* x x) ((x 0)) 0) test-case))
(set! test-case (add-case '((- x 100) ((x 200)) 100) test-case))
(set! test-case (add-case '((+ x y) ((x 1) (y 2)) 3) test-case))
(set! test-case (add-case '((/ 1 x) ((x 3)) 0.33333333) test-case))
(set! test-case (add-case '((^ x 4) ((x 2)) 16) test-case))
(set! test-case (add-case '((log e 2) () 0.693147181) test-case))
(set! test-case (add-case '((* 2 pi r) ((r 2)) 12.5663706) test-case))
(set! test-case (add-case '((* 2 pi r) ((r 3)) 18.84955921) test-case))
(set! test-case (add-case '((/ (+ (* 2 (^ x 2)) (* 3 x)) (+ (* 4 (^ x 5)) (log e 7))) ((x 2)) 0.107737135) test-case))


(define test-case1 (init-case))
(set! test-case1 (add-case '((log e x) x ((x 2)) 0.5) test-case1))
(set! test-case1 (add-case '((+ 3 x) x ((x 100)) 1) test-case1))
(set! test-case1 (add-case '((* 3 x) x ((x 1000)) 3) test-case1))
(set! test-case1 (add-case '((* 3 (^ x 3)) x ((x 2)) 36) test-case1))
(set! test-case1 (add-case '((/ 1 x) x ((x 2)) -0.25) test-case1))
(set! test-case1 (add-case '((log 2 x) x ((x 4)) 0.36067376) test-case1))
(set! test-case1 (add-case '((- (^ x 3) (* 2 (^ x 1) (^ x 1))) x ((x -4)) 64) test-case1))
(set! test-case1 (add-case '((* 2 pi (^ x 2)) x ((x 2)) 25.1327408) test-case1))
(set! test-case1 (add-case '((/ (+ (* 2 (^ x 2)) (* 3 x)) (+ (* 4 (^ x 5)) (log e 7))) x ((x 2)) -0.180658883) test-case1))

(unit-test test-pro test-case)
(unit-test test-pro1 test-case1)
