package asst3;

/**
 * @author Jeffey Kapp
 * @since 7 Nov 2014
*/

public class Activity {

	private String title;
	private Time dateStart; 
	private Time dateEnd;
	private String comment;

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

	/**
	 * dummy accessor for loaction
	 * @return location
	*/
	public String getLocation() {
		return null;
	}

	/**
	 * Contructor for home activities
	*/
	public Activity() {
		title = "";
		dateStart = null;
		dateEnd = null;
		comment = "";
	}

	public Activity( String title, Time start, Time end, String comment ) {
		this.title = title;
		dateStart = start;
		dateEnd =  end;
		this.comment = comment;
	}


	public String toString() {
		return ( "Title: " + title + "\n"
			   + "Start time: " + dateStart.toString() + "\n"
			   + "End time: " + dateEnd.toString() + "\n" 
			   + "Comment: " + comment + "\n" );
	}
	
}