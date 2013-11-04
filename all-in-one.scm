(define (sqrt x)
  (define (sqrt-iter guess x)
    (if (good-enough? guess x)
        guess
        (sqrt-iter (improve guess x)
          x)))
  
  (define (improve guess x)
    (average guess (/ x guess)))
  
  (define (square x)
    (* x x))
  
  (define (good-enough? guess x)
    (> 0.01
     (/ (abs (- (square guess) x))
      x)))
  
  (sqrt-iter 1 x))