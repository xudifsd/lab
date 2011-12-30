;; Author : xudifsd, Date : 2011-12-30
;; This is the utils for unit test
;;
;; case is a list whose elements also are list which used to applied to pro
;; pro is a user specified procedure to test if case is passed the test,
;; if pro returns true, case is passed, otherwise case is failed.

(define (unit-test pro case)
 (define (empty-case? case)
  (null? case))
 (define (first-case case)
  (car case))
 (define (next-case case)
  (cdr case))
 (define (report-finished)
  (display "unit-test finished")
  (newline))
 (define (report-failure case)
  (display "unit-test fail at: ")
  (display case)
  (newline))

 (if (empty-case? case)
  (report-finished)
  (if (apply pro (first-case case))
   (unit-test pro (next-case case))
   (begin
	(report-failure (first-case case))
	(unit-test pro (next-case case))))))

;; add new case to acc
(define (add-case case acc)
 (cons case acc))

(define (init-case . cases)
 (define (iter cases acc)
  (if (null? cases)
   acc
   (iter (cdr cases) (cons (car cases) acc))))
 (iter cases empty-case))

(define empty-case '())
