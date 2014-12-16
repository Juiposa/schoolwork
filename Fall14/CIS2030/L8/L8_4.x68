
            ORG     $8000
START:      MOVE.W  X,-(SP)
            MOVE.W  Y,-(SP)
            PEA     Z
            MOVEA.L #$A6A6A6A6,A6
            JSR     squared
            LEA     8(SP),SP
            TRAP    #14


squared     
            LINK    A6,#-6
            MOVEM.L D0-D4,-(SP)
            MOVE.W  14(A6),D0
            MOVE.W  12(A6),D1
            MOVEA.L 8(A6),A0
            MOVE.W  D0,D2
            MOVE.W  D1,D3
            MULS    D2,D2
            MULS    D3,D3
            MOVE.W  D2,-2(A6)
            MOVE.W  D3,-4(A6)
            MULS    D1,D0
            MULS    #2,D0
            MOVE.W  D0,-6(A6)
            ADD.W   -6(A6),D4
            ADD.W   -4(A6),D4
            ADD.W   -2(A6),D4
            MOVE.W  D4,(A0)
            MOVEM.L (SP)+,D0-D4
            UNLK    A6
            RTS            
    
            ORG     $9000
X           DC.W    3
Y           DC.W    2
Z           DS.W    1
                   

           END     START       

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
