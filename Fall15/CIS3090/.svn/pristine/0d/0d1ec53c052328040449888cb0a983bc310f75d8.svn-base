/*
 * Jeffrey-David Kapp 0832671
 * CIS3090-A3
 * 2 December 2015
 * Jrb.java
 * Main class, contains main function and completes initialisation
 */
package jrb;

import java.util.Random;
/**
 * Jrb
 * @author kappj
 */
public class Jrb {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int numP = 0; //number of processors/threads to use
        int widthB = 0;
        int widthT = 0;
        int colourD = 0;
        int maxSteps = 0;
        int seed = 0;
        JRBThread[] jrbthreads;
        Thread[] threads;
        Board board;
        Random rand = null; //friendly neighbourhood rng
        
        //argument handling
        if(args.length != 5 && args.length != 6) {
            System.out.println("Invalid number of arguments");
            System.exit(0);
        } else {
            for (String arg : args) {
                switch (arg.charAt(0)) {
                    case 'p':
                        numP = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break;
                    case 'b':
                        widthB = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break;
                    case 't':
                        widthT = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break;
                    case 'c':
                        colourD = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break; 
                    case 'm':
                        maxSteps = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break;
                    case 's':
                        seed = Integer.parseInt(arg.replaceAll("[\\D]", ""));
                        break;
                    default:
                        break;
                }
            }
            if ( args.length == 5 && seed != 0 ) { //when there are only 5 args but a seed has been set
                System.out.println("Seed given but only 5 arguments found");
                System.exit(0);
            } else if ( seed  == 0 ) { //if seed is 0, give it a random value
                Random newRand = new Random();
                rand = new Random((long)newRand.nextInt(150000000));
            } else {
                rand = new Random(seed);
            }
            
            if( widthB%widthT != 0 ) {
               System.out.println("Invalid tile size");
                System.exit(0); 
            }
            
            System.out.println("Thread # " + numP);
            System.out.println("Board width " + widthB);
            System.out.println("T value " + widthT);
            System.out.println("Colour density " + colourD);
            System.out.println("Max steps " + maxSteps );
            System.out.println("Seed " + seed);
            
        }
        //END; argument handling
        
        //initialise the board
        board  =  new Board( widthB, rand );
        
        //build thread calls
        jrbthreads = new JRBThread[numP];
        threads = new Thread[numP];
        for(int i = 0; i < numP; i++ ) {
            jrbthreads[i] = new JRBThread(i);
        }
        jrbthreads[0].setData(board, numP, widthB, widthT, maxSteps, colourD, seed );
        
        //start threads
        for ( int i = 0; i < numP; i++ ) {
            threads[i] = new Thread(jrbthreads[i]);
            threads[i].start();
        }
        
        //wait for them to finish
        for ( int i = 0; i < numP; i++ ) {
            try {
                threads[i].join();
            } catch ( InterruptedException e ) {/*NOOP*/}
        }
        
    }
    
}
