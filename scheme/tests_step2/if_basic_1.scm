; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test eval quote tokens

(if 1 2)
(if 1 -2)
(if 1 #t)
(if 1 #f)
(if 1 a)
(if 1 toto)
(if 1 #\a)
(if 1 "abc")
(if 1 (2 3))
(if 1 (quote ok))
(if 1 (and 2 3))
(if 1 (or 5 6))

;;; Make sure you put a return at
;;; the end of the input file
