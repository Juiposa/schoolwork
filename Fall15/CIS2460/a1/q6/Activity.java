import java.util.Random;
import java.util.Arrays;


public class Activity {

	private String name;
	private Random rand;
	private int[] values; //array of all values
	private double[] probabilities; //array of probabilities, in order respective to their values 
	private double[] cumulativeProb;
	private int numValue = 0; //number of possible values

	//assigns passed probability values to object variables, build cumulative totals
	public Activity(String name, double[] probabilities, int[] values, Random rand ) {
		//set object variables
		this.name = new String(name);
		this.rand = rand;
		this.probabilities = probabilities;
		this.values = values;
		numValue = values.length;
		cumulativeProb = new double[numValue];

		//determine cumulative values
		cumulativeProb[0] = probabilities[0];
		for( int i = 1; i < numValue; i++ ) {
			cumulativeProb[i] = cumulativeProb[i-1] + probabilities[i];
		}
	}

	//generates a random number and returns the corresponding value
	//returns -1 on error
	public int generate() {
		double num = rand.nextDouble();

		for( int i = 0; i < numValue; i++ ) {
			if( num <= cumulativeProb[i] ) {
				return values[i];
			}
		}
		return -1;
	}
	
	//prints out this object's values
	public void out() {
		System.out.println(name + " Time distribution:");
		System.out.println("   Time (minutes) " + Arrays.toString(values) );
		System.out.println("   Probability    " + Arrays.toString(probabilities) );
		System.out.println("   Cumulative pb  " + Arrays.toString(cumulativeProb) );
	}
}