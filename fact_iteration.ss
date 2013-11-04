(define (factorial n)
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> couter max-count)
      product
      (fact-iter (* counter product)
                 (+ count 1)
                 max-count)))