(load "filter_accumulate_enumerate.ss")

(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      `()
      (cons (accumulate op init (map (lambda (x) (car x)) seqs))
            (accumulate-n op init (map (lambda (x) (cdr x)) seqs)))))