(load "2.17.ss")

(define (reverse l)
  (define (rest l r)
    (if (null? l)
        r
        (rest (cdr l) (cons (car l) r))))
  (rest l '()))