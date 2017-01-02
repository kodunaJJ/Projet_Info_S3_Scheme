; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test eval if wihout alternative tokens

;condition test with unsigned integer
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
;condition test with signed integer
(if -1 2)
;condition test with character
(if #\a 5)
;condition test with string
(if "abc" 6)
;condition test with boolean 
(if #t 7)
(if #f 8)

;;; Make sure you put a return at
;;; the end of the input file
