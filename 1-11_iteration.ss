(define (pro n)
  (if (< n 3)
      n
      (pro-iter 0 1 2 n)))

(define (pro-iter a b c count)
  (if (= count 2)
      c
      (pro-iter b c (+ c (* 2 b) (* 3 a)) (- count 1))))