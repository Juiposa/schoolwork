package asst3;

/**
 * @author Jeff Kapp 0832671
 * @since 7 Nov 2014
 *
*/

public class OtherActivity extends Activity {

	private String location;

	/**
	 * Contructor for other activities
	*/
	public OtherActivity() {
		super();
		location = "";
	}

	/**
	 * Constructor with paramters
	*/ 
	public OtherActivity( String title, Time start, Time end, String location, String comment ) {
		super( title, start, end, comment );
		this.location = location; 
	} 

	/**
	 * accessor for location
	 * @return location
	*/
	@Override
	public String getLocation() {
		return location;
	}

	@Override
	public String toString() {
		return (super.toString() + "Location: " + location + "\n");
	}

	
}