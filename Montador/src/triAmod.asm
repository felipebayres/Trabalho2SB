MOD_A: BEGIN

SECTION DATA
A: SPACE
B: SPACE
SECTION TEXT
R: EXTERN
MOD_B: EXTERN
    PUBLIC A
    PUBLIC B
    PUBLIC L1
    INPUT A
    INPUT B
    JMP MOD_B
L1: OUTPUT R+1
    STOP
END
