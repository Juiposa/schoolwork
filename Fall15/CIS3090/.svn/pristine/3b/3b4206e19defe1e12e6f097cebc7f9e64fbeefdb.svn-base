/*
 * Jeffrey-David Kapp 0832671
 * CIS3090-A3
 * 2 December 2015
 * Board.java
 * Class representing a board, contains its fields and dimensions 
 */
package jrb;

import java.util.Random;

/**
 * Board
 * @author kappj
 */
public class Board {
    private final int dimensionsB;
    private final Random rand;
    public int[][] field;
    
    public Board( int dimensionsB, Random rand ) {
        this.dimensionsB = dimensionsB;
        this.rand = rand;
        initialise();
    }
    
    public Board( Board board ) {
        this.dimensionsB = board.getDimensions();
        rand = null;
        this.field = new int[dimensionsB][dimensionsB];
        for( int i = 0; i < dimensionsB; i++ ) {
            System.arraycopy(board.field[i], 0, this.field[i], 0, dimensionsB);
        }
    }
    
    private void initialise() {
        field = new int[dimensionsB][dimensionsB];
        for ( int i = 0; i < dimensionsB; i++ ) {
            for ( int j = 0; j < dimensionsB; j++ ) {
                field[i][j] = rand.nextInt(3);
            }
            //System.out.println(Arrays.toString(field[i]));
        }
    }
    public int getDimensions() {
        return dimensionsB;
    }
}
