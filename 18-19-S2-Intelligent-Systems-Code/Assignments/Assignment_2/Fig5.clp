; Christopher Sahadeo
; 816000772
; christophersahadeo@gmail.com
; COMP 3608

; (deffacts database (A TRUE) (B TRUE) (C TRUE) (D TRUE) (E TRUE))

; (clear)

(defrule R1 
	(Y TRUE)
	(D TRUE)
	=>
	(assert (Z TRUE))
	(printout t "Z is true" crlf))


(defrule R2
	(X TRUE)
	(B TRUE)
	(E TRUE)
	=>
	(assert (Y TRUE))
	(printout t "Y is true" crlf))


(defrule R3
	(A TRUE)
	=>
	(assert (X TRUE))
	(printout t "X is true" crlf))


; (assert (A TRUE) (B TRUE) (C TRUE) (D TRUE) (E TRUE))

; (reset)

; (agenda)

; (run)