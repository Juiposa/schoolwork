/*
 * Jeffrey-David Kapp 0832671
 * CIS3090-A3
 * 2 December 2015
 * JRBThread.java
 * Thread class, where all work is done in parallel
 */
package jrb;

import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.BrokenBarrierException;
/**
 * JRBThread
 * @author kappj
 */
public class JRBThread implements Runnable {
    private final int index;
    private static int numP;
    private static int dB; //dimensions short hand
    private static int dT; //dimensions of tile short hand
    private static int steps; //iterations allowed
    private static int maxDensity = 0; //maximum density 
    private static final Object densityLock =  new Object(); //mutex ahoy
    private static int density = 0; //max allowed density in percentage
    private static int numDensity = 0; //max allowed density in number of cells
    private static int seed; //rand seed to reporting purposes
    private static int totalRed, totalBlue;
    private static Board board;
    private static Board oldBoard;
    private static CyclicBarrier barrier;
    
    
    public JRBThread( int index ) {
        this.index = index;
    }
    /**
     * initialises data the thread will need
     * @param board - board the thread will work on
     * @param numP - number of threads that will be working
     * @param dB - width of the board
     * @param dT - width of a viewing tile
     * @param steps - number of full steps the program will take
     * @param density - allowed maximum density
     * @param seed - used seed for reporting purposes
     */
    public void setData( Board board, int numP, int dB, int dT, int steps, int density, int seed ) {
        JRBThread.numP = numP;
        JRBThread.dB = dB;
        JRBThread.dT = dT;
        JRBThread.steps = steps;
        JRBThread.density = density;
        numDensity = dT*dT*density/100;
        JRBThread.seed = seed;
        JRBThread.board = board;
        JRBThread.oldBoard = new Board(board);
        barrier =  new CyclicBarrier(numP);
        
    }
    
    @Override
    public void run() {
        long startTime = 0;
        if( index == 0 ) { //thread 0 will keep track of timing
            startTime = System.currentTimeMillis();
        }
        int i, j, k;
        int myRed, myBlue;
        int largerVal = 0;
        int colMod; //modifiers for when a threads runs past the end of a row, wrapping to next row(s)
        //rowMod will only ever be used if the number of threads exceeds the dimensions of the board
        for( i = 0; numDensity >= maxDensity && i < steps; i++ ) {
            
            //Update first half step
            colMod = index;
            for( j = 0; index < dB && j < dB; j++ ) { //cyclic decompositiion, only executed if board isn't too small
                for( k = colMod; k < dB; k += numP ) {
                    //System.out.println("Testing:" + index + " x" + k + "y" + j);
                    if( oldBoard.field[j][k] == 1 ) { //if current cell is red
                        if( k == dB-1 ) { //in the last column
                            if(oldBoard.field[j][0] == 0) { //and this next cell is blank
                                board.field[j][k] = 0;
                                board.field[j][0] = 1;
                            }
                        } else {
                            if(oldBoard.field[j][k+1] == 0) { //and this next cell is blank
                                board.field[j][k] = 0;
                                board.field[j][k+1] = 1;
                            }
                        }
                    }
                }
                if(k >= dB) { //wrapping needed
                    colMod = k%dB;
                }
            }
            //Barrier
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ex) {
                return;
            }
            //System.out.println("RELEASE:"+index+" i:"+i);

            //Update old map
            colMod = index;
            for( j = 0; index < dB && j < dB; j ++ ) { //cyclic decompositiion
                for( k = colMod; k < dB; k += numP ) {
                    //System.out.println("Testing:" + index + " x" + k + "y" + j);
                    oldBoard.field[j][k] = board.field[j][k];
                }
                if(k >= dB) { //wrapping needed
                    colMod = k%dB;
                }
            }

            //Barrier
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ex) {
                return;
            }

            //Update second half step
            colMod = index;
            for( j = 0; index < dB && j < dB; j++ ) { //cyclic decompositiion, only executed if board isn't too small
                for( k = colMod; k < dB; k += numP ) {
                    //System.out.println("Testing:" + index + " x" + k + "y" + j);
                    if( oldBoard.field[j][k] == 2 ) { //if current cell is blue
                        if( j == dB-1 ) { //in the last row
                            if(oldBoard.field[0][k] == 0) { //and this next cell is blank
                                board.field[j][k] = 0;
                                board.field[0][k] = 2;
                            }
                        } else {
                            if(oldBoard.field[j+1][k] == 0) { //and this next cell is blank
                                board.field[j][k] = 0;
                                board.field[j+1][k] = 2;
                            }
                        }
                    }
                }
                if(k >= dB) { //wrapping needed
                    colMod = k%dB;
                }
            }

            //Barrier
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ex) {
                return;
            }

            //Update old map again
            colMod = index;
            for( j = 0; index < dB && j < dB; j ++ ) { //cyclic decompositiion
                for( k = colMod; k < dB; k += numP ) {
                    //System.out.println("Testing:" + index + " x" + k + "y" + j);
                    oldBoard.field[j][k] = board.field[j][k];
                }
                if(k >= dB) { //wrapping needed
                    colMod = k%dB;
                }
            }
            //Barrier
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ex) {
                return;
            }

            //Test Density
            colMod = index*dT;
            int rowMod = 0;
            
            do {
                myRed = 0;
                myBlue = 0;
                if( colMod >= dB ) {
                    rowMod += (colMod/dB);
                    colMod -= (colMod/dB)*dB;
                }
                if(rowMod*dT >= dB)
                    break;
                for(j = rowMod*dT; j < rowMod*dT+dT; j++ ) {
                    for( k = colMod; k < colMod+dT; k++ ) {
                        if(board.field[j][k] == 1) {
                            myRed++;
                        } else if ( board.field[j][k] == 2 ) {
                            myBlue++;
                        } 
                    }
                    //System.out.println("t"+index+" x"+j+"y"+i);
                }
                if(myRed >= myBlue) {
                    largerVal = myRed;
                } else {
                    largerVal = myBlue;
                }
                synchronized(densityLock) {
                    if( largerVal > maxDensity ) {
                        maxDensity = largerVal;
                    }
                }
                colMod += dT*numP;
            } while(true);
            
            if(index == 0)
                System.out.println(i);
            //Barrier
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ex) {
                return;
            }
            
        }
        int totalIterations = i;
        //only thread 0 will print to file, others will join
        if( index == 0 ) {
            long endTime = System.currentTimeMillis();
            double totalTime = ((double)endTime - (double)startTime) / 1000.0;
            try (PrintWriter writer = new PrintWriter("redblue.txt")) {
                char outChar = ' ';
                String[] outLine = new String[dB];
                for ( i = 0; i < dB; i++ ) {
                    for ( j = 0; j < dB; j++ ) {
                        switch( board.field[i][j] ) {
                            case 0: outChar = ' '; break;
                            case 1: outChar = '>'; break;
                            case 2: outChar = 'V'; break;
                        }
                        if( outLine[i] == null ) {
                            outLine[i] = "" + outChar;
                        } else {
                            outLine[i] = outLine[i]+ outChar;
                        }
                    }
                    writer.println(outLine[i]);
                }
                writer.print("p"+numP+" b"+dB+" t"+dT+" c"+density+" m"+steps+" s"+seed+" Iterations: "+totalIterations+" Termination Percent: "+(maxDensity*100)/(dT*dT)+" Time: "+totalTime);
            } catch( FileNotFoundException e ) {
                System.out.println(e.getMessage());
            }
        }
    }    
}
