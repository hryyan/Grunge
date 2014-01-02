(define (deep-reverse l)
  (define (helper i o)
    (if (null? i)
        o
        (if (pair? (car i))
            (helper (cdr i) (cons (deep-reverse (car i)) o))
            (helper (cdr i) (cons (car i) o)))))
  (helper l (list)))