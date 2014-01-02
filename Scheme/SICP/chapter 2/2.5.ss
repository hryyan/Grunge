(define (cons a b)
  (* (expt 2 a)
     (expt 3 b)))

(define (car z)
  (carhelp z 0))

(define (carhelp z num)
  (if (integer? (/ z 2))
      (carhelp (/ z 2) (+ 1 num))
      num))

(define (cdr z)
  (cdrhelp z 0))

(define (cdrhelp z num)
  (if (integer? (/ z 3))
      (cdrhelp (/ z 3) (+ 1 num))
      num))