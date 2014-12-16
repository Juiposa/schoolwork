        ORG     $8000
        
START:  MOVE.W  X,D0
        JSR     main
        TRAP    #14
        
main    MOVE.W  D0,-(SP)
        MOVE.W  #0,-(SP)
        JSR     solveQuad
        MOVE.W  (SP)+,D1
        LEA     2(SP),SP
        RTS
        
solveQuad   MOVE.W  6(SP),D2
            MOVE.W  6(SP),D3
            MULS    D3,D3
            MULS    #5,D3
            MULS    #2,D2
            SUB.W   D2,D3
            ADD.W   #6,D3
            MOVE.W  D3,4(SP)
            RTS  
            
 
        ORG     $9000
X       DC.W    $5        

        END     START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
