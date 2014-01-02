(load "2.28.ss")

(define (count-leaves t)
  (accumulate (lambda (x y) (+ 1 y)) 0 (fringe t)))

(define (count-leaves-x t)
  (accumulate + 0 (map (lambda (sub-tree)
                         (if (pair? sub-tree)
                             (count-leaves sub-tree)
                             1))
                    t)))