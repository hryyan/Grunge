(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(define (cubic a b c)
  (lambda (x) (+ (cube x) (* (square x) a) (* x b) c)))