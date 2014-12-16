        ORG     $8000
        
START:  PEA     W
        MOVE.W  X,-(SP)
        MOVE.W  Y,-(SP)
        MOVE.W  Z,-(SP)
        JSR     main
        LEA     6(SP),SP
        TRAP    #14
        

main    MOVE.L  10(SP),-(SP)
        MOVE.W  12(SP),-(SP)
        MOVE.W  12(SP),-(SP)
        MOVE.W  12(SP),-(SP)
        JSR     solveQuad
        LEA     10(SP),SP    
        RTS
        
solveQuad   MOVE.W  4(SP),D1 ;Z
            MOVE.W  6(SP),D2 ;Y
            MOVE.W  8(SP),D3 ;X
            MOVEA.L 10(SP),A0
            MOVE.W  D3,D4
            MULS    D4,D4
            MULS    #5,D4
            MULS    #2,D3
            MULS    D2,D3
            MULS    D1,D1
            SUB.W   D3,D4
            ADD.W   D1,D4
            MOVE.W  D4,(A0)
            RTS  
            
 
        ORG     $9000
W       DS.W    1
X       DC.W    $5
Y       DC.W    $6
Z       DC.W    $7        

        END     START



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
