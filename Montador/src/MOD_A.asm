;Codigo fonte do modulo A
MOD_A: BEGIN
SECTION TEXT
	Y: EXTERN
	MOD_B: EXTERN
		PUBLIC VAL
		PUBLIC L1
		INPUT	Y
		LOAD	VAL
		ADD		Y
		STORE	Y+2
		JMPP	MOD_B
		L1:		STOP
SECTION DATA
	VAL: CONST	5
END