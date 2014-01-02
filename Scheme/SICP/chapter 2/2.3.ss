(load "/home/vincent/Downloads/2.2.ss")

(define dx 0.00001)

(define tolerance 0.00001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))

(define (deriv g)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
     dx)))

(define (newton-transform g)
  (lambda (x)
    (- x (/ (g x) ((deriv g) x)))))

(define (newtons-method g guess)
  (fixed-point (newton-transform g) guess))

(define (square x)
  (* x x))

(define (sqrt x)
  (newtons-method (lambda (y) (- (square y) x))
    1.0))

(define (rect a b c d)
  (cons a
    (cons b
      (cons c d))))
   
(define (distance p1 p2)
  (sqrt (+ (square (- (x-point p1) (x-point p2)))
           (square (- (y-point p1) (y-point p2))))))

(define (length r)
  (* 2
   (+ (distance (car r) (cadr r))
      (distance (caddr r) (cdddr r)))))

(define (area r)
  (* (distance (car r) (cadr r))
   (distance (caddr r) (cdddr r))))

(define (make-rect s1 s2)
  (cons (start-segment s1)
    (cons (end-segment s1)
      (cons (start-segment s2) (end-segment s2)))))