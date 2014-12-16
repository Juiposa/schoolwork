    
	    ORG	$8000
	    
START  	LEA     MATRIX,A0
DO	    MOVE.W	#4,D2		  
	    MULU	D0,D2
        ADD.B   D1,D2
        MOVE.W  #4,D3
        MULU    D1,D3
        ADD.B   D0,D3		  
        MOVE.B  0(A0,D2.L),D4
        MOVE.B  0(A0,D3.L),0(A0,D2.L)
        MOVE.B  D4,(A0,D3.L)
        
        ADD.B   #1,D1
        CMP     #3,D1
       BLE     DO
        ADD.B   #1,D0
        MOVE.B  D0,D1
        CMP     #2,D0
       BLE     DO
DONE    TRAP	#14

	    ORG	$9000		
MATRIX	DC.B	1,2,3,4
	    DC.B	5,6,7,8
	    DC.B	9,10,11,12
	    DC.B	13,14,15,16
	    END	START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
