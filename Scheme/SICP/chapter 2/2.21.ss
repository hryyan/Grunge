(define (square x)
  (* x x))

(define (square-list items)
  (if (null? items)
      (list)
      (cons (square (car items))
            (square-list (cdr items)))))

(define (square-list-2 items)
  (map (lambda (x) (* x x)) items))