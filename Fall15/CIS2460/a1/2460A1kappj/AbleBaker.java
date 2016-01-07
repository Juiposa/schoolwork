/******************************
Jeffrey-David Kapp
0832671
CIS2460A1
14 October 2015
******************************/
import java.util.Scanner;
import java.lang.Integer;
import java.lang.Long;
import java.util.Random;


public class AbleBaker {

	private static int arrTime;
	private static int intArrTime;
	private static int tAvaiAble;
	private static int tAvaiBaker;
	private static int delay;
	private static char server;
	private static int servTime;
	private static int tservTime;

	public static void main(String[] args) {

		
		int i = 0;
		int[] delayArray = new int[10];
		long seed = Long.parseLong(args[0]);
		int callers = Integer.parseInt(args[1]);
		Random rand = new Random(seed);

		//values and their probablities
		int[] intArrValues = {1, 2, 3, 4};
		double[] intArrProb = {0.25, 0.40, 0.20, 0.15};

		int[] ableValues = {2, 3, 4, 5};
		double[] ableProb = {0.3, 0.28, 0.25, 0.17};

		int[] bakerValues = {3, 4, 5, 6};
		double[] bakerProb = {0.35, 0.25, 0.2, 0.2};

		System.out.println("Seed = " + seed );
		System.out.println("Number of Customers to simulate = " + callers );

		//setting up activity classes
		Activity intArrActivity = new Activity("Interarrival", intArrProb, intArrValues, rand);
		intArrActivity.out();
		Activity ableActivity = new Activity("Able's Service", ableProb, ableValues, rand);
		ableActivity.out();
		Activity bakerActivity = new Activity("Baker's Service", bakerProb, bakerValues, rand);
		bakerActivity.out();

		//inital values
		arrTime = 0;
		intArrTime = 0;
		tAvaiAble = 0;
		tAvaiBaker = 0;

		//master loop 
		for ( i = 1; i <= callers; i++ ) {
			System.out.println("Caller " + i );
			System.out.println("	Interarrival time = " + intArrTime );
			System.out.println("	Arrival time = " + arrTime );
			System.out.println("	Able available time = " + tAvaiAble );
			System.out.println("	Baker available time = " + tAvaiBaker );

			//determine which worker will talk call
			//able takes precendence if their times are equal
			if ( tAvaiAble <= tAvaiBaker ) {
				server = 'A';
				System.out.println("	Server = Able ");
				tservTime = tAvaiAble;
				servTime = ableActivity.generate();
			} else {
				server = 'B';
				System.out.println("	Server = Baker ");
				tservTime = tAvaiBaker;
				servTime = bakerActivity.generate();
			}

			//increasing when server will be next available
			if( server == 'A' ) 
				tAvaiAble += servTime;
			else
				tAvaiBaker += servTime;

			//service period
			System.out.println("	Service period = [" + tservTime + ", " + (tservTime+servTime) + "]" );
			//delay
			delay = tservTime - arrTime;
			if (delay < 0) delay = 0;
			System.out.println("	Caller delay = " + delay + " minute(s)" );
			//service time
			System.out.println("	Caller system time = " + (servTime + delay) + " minute(s)" );

			//recording delay
			delayArray[delay]++;

			//generate values for next call
			intArrTime = intArrActivity.generate();
			arrTime += intArrTime;

		}

		//outputting delays
		System.out.println("Caller delay:");
		System.out.println("   Minutes  Frequency  ");
		for( i = 0; i < 10; i++ ) {
			System.out.println("      " + i + "         " + delayArray[i] );
		}
	}
}