package asst1;

import java.util.Scanner;

/**
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class OtherActivity {

	private String title = new String();
	private Time dateStart = new Time();
	private Time dateEnd =  new Time();
	private String location = new String();
	private String comment = new String();

	/**
	 * accessor for title
	 * @return title
	*/
	public String getTitle() {
		return title;
	}

	/**
	 * accessor for dateStart
	 * @return dateStart
	*/
	public Time getDateStart() {
		return dateStart;
	}

	/**
	 * accessor for dateEnd
	 * @return dateEnd
	*/
	public Time getDateEnd() {
		return dateEnd;
	}

	/**
	 * accessor for location
	 * @return location
	*/
	public String getLocation() {
		return location;
	}

	/**
	 * accessor for comment
	 * @return comment
	*/
	public String getComment() {
		return comment;
	}

	/**
	 * Contructor for other activities
	*/
	public OtherActivity() {
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter a title.");
		title = keyboard.nextLine();
		do {
			dateStart.userBuildDate();
			dateEnd.userBuildDate();
			if ( dateEnd.isLesser( dateStart )) {
				System.out.println("Start date must be before end date.");
			}
		} while ( dateEnd.isLesser( dateStart ) ); //looping until the user enters valid date
		System.out.println("Enter where the activity is located.");
		location = keyboard.nextLine();
		System.out.println("Enter a comment is you wish.");
		comment = keyboard.nextLine();
	}

	/**
	 * prints the contents of the class
	*/
	public void print() {
		System.out.println("Activity title: " + title );
		System.out.println("Start date: " + dateStart.toString() );
		System.out.println("End date: " + dateEnd.toString() );
		System.out.println("Location: " + location );
		System.out.println("Comment: " + comment );
		System.out.println();
	}
}