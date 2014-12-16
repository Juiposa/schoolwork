package asst1;

import java.util.Scanner;
import java.lang.Integer;

/**
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class Time {

	int minute;
	int hour;
	int day;
	int month;
	int year;

	public Time() {
		minute = 0;
		hour = 0;
		day = 0;
		month = 0;
		year = 0;
	}
	/**
	 * Compares object to another object to determine if this object is larger
	 * @param otherDate other object to be compared
	 * @return true/false  
	*/
	public boolean isGreater( Time otherDate ) {
		if ( this.year > otherDate.year ) {
			return true;
		} else if ( this.month > otherDate.month ) {
			return true;		
		} else if ( this.day > otherDate.day ) {
			return true;
		} else if ( this.hour > otherDate.hour ) {
			return true;
		} else if ( this.minute > otherDate.minute ) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Compares object to another object to determine if this object is smaller
	 * @param otherDate other object to be compared
	 * @return true/false  
	*/
	public boolean isLesser( Time otherDate ) {
		if ( this.year < otherDate.year ) {
			return true;
		} else if ( this.month < otherDate.month ) {
			return true;		
		} else if ( this.day < otherDate.day ) {
			return true;
		} else if ( this.hour < otherDate.hour ) {
			return true;
		} else if ( this.minute < otherDate.minute ) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * will walk user through entering all date elements
	*/
	public void userBuildDate() {

		System.out.println("Enter a date.");
		System.out.println("Year:");		
		this.year = getNumberRange( 0, 10000 );
		System.out.println("Month:");
		this.month = getNumberRange( 1, 12 );
		System.out.println("Day:");
		this.day = getNumberRange( 1, 31 );
		System.out.println("Hour:");
		this.hour = getNumberRange( 0, 23 );
		System.out.println("Minute:");
		this.minute = getNumberRange( 0, 59 );

	}

	/**
	 * Will get a number between a given range from the user
	 * @param 	lowerBound lower bound to compared
	 *   		upperBound upper bound to compared
	 * @return 	a number with the given range.
	*/
	private int getNumberRange( int lowerBound, int upperBound ) {
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);
		int tempDate = 0;

		do {
			inputVar = keyboard.nextLine();
			tempDate = Integer.parseInt( inputVar );
			if ( tempDate >= lowerBound && tempDate <= upperBound ) {
				return tempDate;
			} else {
				System.out.println("Number must be between " + lowerBound + " and " + upperBound );
			}
		} while( !( tempDate >= lowerBound && tempDate <= upperBound));

		return 0;
	} 

	/**
	 * will form data into a string an return it
	 * @return String of data
	*/
	public String toString() {
		return new String(year + "/" + month + "/" + day + " " + hour + ":" + minute ); 
	}
}