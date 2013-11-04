(define (accumulate combiner null-value term a next b)
  (if (> a b)
      null-value
      (combiner (term a) (accumulate combiner null-value term (next a) next b))))

(define (sum a b) (+ a b))

(define (multi a b) (* a b))

(define (pi x)
  (define (divide a b)
    (/ (- a (remainder a b)) b))
  (define (pro-next a)
    (/ (+ 2 (* 2 (divide (+ a 1) 2))) (+ 3 (* 2 (divide a 2)))))
  (define (inc a) (+ a 1))
  (* 4 (accumulate multi 1 pro-next 0 inc x)))

(define (sum-integers a b)
  (define (identity x) x)
  (define (inc x) (+ x 1))
  (accumulate sum 0 identity a inc b))