package asst1;

import java.util.Scanner;

/**
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class SchoolActivity {

	private String title = new String();
	private Time dateStart = new Time();
	private Time dateEnd =  new Time();
	private String comment = new String();

	/**
	 * Contructor for school activities
	*/

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
	 * accessor for comment
	 * @return comment
	*/
	public String getComment() {
		return comment;
	}

	public SchoolActivity() {
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter a title.");
		title = keyboard.nextLine();
		do {
			dateStart.userBuildDate();
			dateEnd.userBuildDate();
			if ( dateEnd.isLesser( dateStart ) ) {
				System.out.println("Start date must be before end date.\n");
			}
		} while ( dateEnd.isLesser( dateStart ) ); //looping until the user enters valid date
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
		System.out.println("Comment: " + comment );
		System.out.println();
	}

}