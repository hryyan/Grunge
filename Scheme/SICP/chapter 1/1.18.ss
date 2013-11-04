(define (* a b)
  (multi a b 0))

(define (multi a b n)
  (cond ((= b 0) n)
        ((even? b) (multi (double a) (halve b) n))
        ((odd? b) (multi a (- b 1) (+ n a)))))

(define (halve n)
  (/ n 2))

(define (double n)
  (+ n n))