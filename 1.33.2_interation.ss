(define (filtered-accumulate combiner null-value term a next b filter)
  (define (iter a result)
    (if (> a b)
        result
        (if (filter a b)
            (iter (next a) (combiner (term a) result))
            (iter (next a) result))))
  (iter a null-value))

(define (some-num x y)
  (define (gcd a b)
    (if (= b 0)
        a
        (gcd b (remainder a b))))
  (= 1 (gcd x y)))

(define (multi a b) (* a b))
(define (identity a) a)
(define (inc a) (+ a 1))
  
(define (func a)
  (filtered-accumulate multi 1 identity 1 inc a some-num))