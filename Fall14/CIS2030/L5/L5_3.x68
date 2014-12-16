*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
            ORG     $8000
   
START       MOVE.B  hexVal,D0
            MOVE.B  hexVal,D1
            ADD.B   $30,D0
            CMPI    #$39,D1
            BHI     IF
            TRAP    #14
IF          ADD.B   #$7,D0
            MOVE.B  D0,charCode
            TRAP #14


            ORG     $9000
charCode    DS.B    1
hexVal      DC.B    $42
           



            END     START 


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
