(define (fun a b c)
  (define (square x)
    (* x x))
  (define (mid a b c)
    (if (> a b)
      (if (> b c)
        b
        (if (> a c)
          c
          a))
      (if (> a c)
        a
        (if (> b c)
          c
          b))))
  (+ (square (max a b c)) (square (mid a b c))))
