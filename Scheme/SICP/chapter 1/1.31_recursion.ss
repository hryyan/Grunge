(define (multi term a next b)
  (if (> a b)
      1
      (* (term a) (multi pro-next (next a) next b))))

(define (pi x)
  (define (divide a b)
    (/ (- a (remainder a b)) b))
  (define (pro-next a)
    (/ (+ 2 (* 2 (divide (+ a 1) 2))) (+ 3 (* 2 (divide a 2)))))
  (define (inc a) (+ a 1))
  (* 4 (multi pro-next 0 inc x)))