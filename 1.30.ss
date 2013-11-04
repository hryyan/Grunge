(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (+ (term a) result))))
  (iter a 0))

(define (xinpusen f a b n)
  (define (next x) (+ x (/ (- b a) n)))
  (define (g x)
    (cond ((= 0 (/ (- x a) (/ (- b a) n))) (f x))
          ((= n (/ (- x a) (/ (- b a) n))) (f x))
          ((= 0 (remainder (/ (- x a) (/ (- b a) n)) 2)) (* 2 (f x)))
          ((= 1 (remainder (/ (- x a) (/ (- b a) n)) 2)) (* 4 (f x)))))
  (/ (* (sum g a next b) (/ (- b a) n)) 3))

(define (cube x) (* x x x))

(define (identity x) x)
(define (inc x) (+ x 1))