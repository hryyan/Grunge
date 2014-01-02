(define (cons x y)
  (lambda (m) (m x y)))

(define (car z)
  (z (lambda (p g) p)))

(define (cdr z)
  (z (lambda (p g) g)))