
        ORG     $8000
        
START   LEA     ptr1,A0
        LEA     ptr2,A1
        LEA     match,A2
        MOVE.B  (A2),D3
DO      MOVE.B  (A0)+,D0

        MOVE.B  (A1)+,D1
        CMP     D0,D1
        BEQ     WHILE
        MOVE.B  #$00,D3
        BRA     DONE
WHILE   CMPI    #$0D,D0
        BEQ     DONE
        CMPI    #$FF,D3
        BNE     DONE
        BRA     DO

DONE    MOVE.B  D3,(A2)       
        TRAP    #14
                
        ORG     $9000
ptr1    DC.B    'h','e','l','l','o',$0D       
        ORG     $9020    
ptr2    DC.B    'h','e','l',$0D
match   DC.B    $FF
                  
        END     START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
