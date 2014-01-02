(load "2.18.ss")

(define (fringe-x l)
  (define (helper i o)
    (if (null? i)
        o
        (if (pair? (car i))
            (helper (cdr i) (append (fringe-x (car i)) o))
            (helper (cdr i) (cons (car i) o)))))
  (helper l '()))

(define (fringe l)
  (reverse (fringe-x l)))