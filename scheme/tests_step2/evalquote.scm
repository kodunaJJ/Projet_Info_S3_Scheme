; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test eval quote tokens

(quote symbol)
(quote 1)
(quote "string")
(quote #\a)
(quote #t)
(quote (1 2))
(quote ())





;;; Make sure you put a return at
;;; the end of the input file
