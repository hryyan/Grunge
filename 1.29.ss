(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))

(define (xinpusen f a b n)
  (define (next x) (+ x (/ (- b a) n)))
  (define (g x)
    (cond ((= 0 (/ (- x a) (/ (- b a) n))) (f x))
          ((= n (/ (- x a) (/ (- b a) n))) (f x))
          ((= 0 (remainder (/ (- x a) (/ (- b a) n)) 2)) (* 2 (f x)))
          ((= 1 (remainder (/ (- x a) (/ (- b a) n)) 2)) (* 4 (f x)))))
  (/ (* (sum g a next b) (/ (- b a) n)) 3))

(define (cube x) (* x x x))