(define (* b n)
  (cond ((= n 0) 0)
        ((even? n) (* (double b) (halve n)))
        (else (+ b (* b (- n 1))))))

(define (even? n)
  (= (remainder n 2) 0))

(define (halve n)
  (/ n 2))

(define (double n)
  (+ n n))