(define (cube-iter guess x)
  (if (good-enough? guess x)
      guess
      (cube-iter (improve guess x)
        x)))

(define (cube x)
  (* x x x))

(define (square x)
  (* x x))

(define (improve y x)
  (/ (+ (/ x (square y)) (* 2 y))
   3))

(define (good-enough? guess x)
  (> 0.01
   (/ (abs (- (cube guess) x))
    (abs x))))

(define (cub x)
  (cube-iter 1 x))