(load "2.18.ss")

(define (same-parity first . other)
  (define (helper i o b)
    (if (= 0 (length i))
        o
        (if (= b (remainder (car i) 2))
            (helper (cdr i) (cons (car i) o) b)
            (helper (cdr i) o b))))
  (let ((b (remainder first 2)))
    (reverse (helper other (list first) b))))