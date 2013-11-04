(define (multi term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (* (term a) result))))
  (iter a 1))

(define (pi x)
  (define (divide a b)
    (/ (- a (remainder a b)) b))
  (define (pro-next a)
    (/ (+ 2 (* 2 (divide (+ a 1) 2))) (+ 3 (* 2 (divide a 2)))))
  (define (inc a) (+ a 1))
  (* 4 (multi pro-next 0 inc x)))