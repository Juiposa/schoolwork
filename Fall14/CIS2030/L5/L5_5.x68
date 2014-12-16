*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
            ORG     $8000
START:      MOVE.W  num1,D0
            MOVE.W  num2,D1
            MOVE.W  num3,D2
            CMP     D1,D0
            BLO     ELSE
            CMP     D2,D0
            BLO     ELSE
            BRA     NUM1BIG
ELSE        CMP     D0,D1
            BLO     NUM3BIG
            CMP     D2,D1
            BLO     NUM3BIG
            BRA     NUM2BIG              
NUM1BIG     MOVE.W  D0,biggest
            TRAP    #14
NUM2BIG     MOVE.W  D1,biggest
            TRAP    #14
NUM3BIG     MOVE.W  D2,biggest
            TRAP    #14


            ORG     $9000
num1        DC.W    $12
num2        DC.W    $18
num3        DC.W    $54
biggest     DS.W    1
   
            END     START        
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
