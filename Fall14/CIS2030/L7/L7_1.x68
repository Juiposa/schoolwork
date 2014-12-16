
        ORG     $8000
START   MOVE.L  VAR1,D0
        MOVE.L  VAR2,D1
        CLR     D2

LOOP    BTST.L  #0,D1 ;TEST THE LAST BIT
        BEQ     MULT  ;IF ITS EVEN, SKIP ADDING 
        ADD.L   D0,D2 ;ADD IF ITS ODD
        CMP.L   #1,D1 ;MAKE SURE D1 DOESN'T CONTAIN 1
        BEQ     EXIT  ;IF IT DOES, EXIT
MULT    LSL     #1,D0 ;SHIFT OPERANDS
        LSR     #1,D1
        BRA     LOOP
EXIT    MOVE.L  D2,RESULT ;MOVE RESULT TO MEMORY
        TRAP    #14

       ORG     $9000
VAR1    DC.L    30
VAR2    DC.L    25
RESULT  DS.L    1
              
        END     START        

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
