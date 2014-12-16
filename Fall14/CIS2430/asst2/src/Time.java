package asst2;

import java.util.Scanner;
import java.lang.Integer;

/**
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class Time {

	private int minute;
	private int hour;
	private int day;
	private int month;
	private int year;

	public Time() {
		minute = 0;
		hour = 0;
		day = 0;
		month = 0;
		year = 0;
	}

	public Time( int year, int month, int day, int hour, int minute ) {
		boolean validityFlag = true;
		if ( numberIsInRange( 0, 10000, year ) ) {
			this.year = year;
		} else {
			validityFlag = false;
		}
		if ( numberIsInRange( 1, 12, month ) ) {
			this.month = month;
		} else {
			validityFlag = false;
		}
		if ( numberIsInRange( 1, 31, day ) ) {
			this.day = day;
		} else {
			validityFlag = false;
		}
		if ( numberIsInRange( 0, 23 , hour ) ) {
			this.hour = hour;
		} else {
			validityFlag = false;
		}
		if ( numberIsInRange( 0, 59, minute  ) ) {
			this.minute = minute;
		} else {
			validityFlag = false;
		}

		if ( !validityFlag ) {
			System.out.println("Invalid date; defaulting values to 0");
			this.minute = 0;
			this.hour = 0;
			this.day = 0;
			this.month = 0;
			this.year = 0;
		}
	}

	/**
	 * Getting value for year
	 */
	public int getYear() {
		return year;
	}
	
	/**
	 * Getting value for month
	 */
	public int getMonth() {
		return month;
	}
	
	/**
	 * Getting value for day
	 */
	public int getDay() {
		return day;
	}
	
	/**
	 * Getting value for hour
	 */
	public int getHour() {
		return hour;
	}
	
	/**
	 * Getting value for minute
	 */
	public int getMinute() {
		return minute;
	}

	/**
	 * Compares object to another object to determine if this object is larger
	 * @param otherDate other object to be compared
	 * @return true/false  
	*/
	public boolean isGreater( Time otherDate ) {
		if ( otherDate == null ) {
			return false;
		} else if ( this.year < otherDate.year ) {
			return false;
		} else if ( this.month < otherDate.month ) {
			return false;		
		} else if ( this.day < otherDate.day ) {
			return false;
		} else if ( this.hour < otherDate.hour ) {
			return false;
		} else if ( this.minute < otherDate.minute ) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Compares object to another object to determine if this object is smaller
	 * @param otherDate other object to be compared
	 * @return true/false  
	*/
	public boolean isLesser( Time otherDate ) {
		if ( otherDate == null ) {
			return false;
		} else if ( this.year > otherDate.year ) {
			return false;
		} else if ( this.month > otherDate.month ) {
			return false;		
		} else if ( this.day > otherDate.day ) {
			return false;
		} else if ( this.hour > otherDate.hour ) {
			return false;
		} else if ( this.minute > otherDate.minute ) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Compares object to another object to determine if this object is equal
	 * @param otherDate other object to be compared
	 * @return true/false  
	*/
	public boolean isEqual( Time otherDate ) {
		if ( otherDate == null ) {
			return false;
		} else if ( this.year != otherDate.year ) {
			return false;
		} else if ( this.month != otherDate.month ) {
			return false;		
		} else if ( this.day != otherDate.day ) {
			return false;
		} else if ( this.hour != otherDate.hour ) {
			return false;
		} else if ( this.minute != otherDate.minute ) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Checking if a time given is valid
	 * @return true or false
	*/
	public static boolean isTimeValid( int year, int month, int day, int hour, int minute ) {
		if ( !numberIsInRange( 0, 10000, year ) ) {
			return false;
		} else if ( !numberIsInRange( 1, 12, month ) ) {
			return false;
		} else if ( !numberIsInRange( 1, 31, day ) ) {
			return false;
		} else if ( !numberIsInRange( 0, 23 , hour ) ) {
			return false;
		} else if ( !numberIsInRange( 0, 59, minute  ) ) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Check if a number is in range.
	 * @param 	lowerBound lower bound to compared
	 *   		upperBound upper bound to compared
	 * 			number number to be checked
	 * @return 	true or false
	*/
	private static boolean numberIsInRange( int lowerBound, int upperBound, int number ) {
		return ( number >= lowerBound && number <= upperBound );
	} 

	/**
	 * will form data into a string an return it
	 * @return String of data
	*/
	public String toString() {
		return new String(year + "/" + month + "/" + day + " " + hour + ":" + minute ); 
	}
}