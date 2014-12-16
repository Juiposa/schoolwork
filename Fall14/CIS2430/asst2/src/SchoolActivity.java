package asst2;

/**
 * @author Jeff Kapp 0832671
 * @since 7 Nov 2014
 *
*/

public class SchoolActivity extends Activity {

	/**
	 * Contructor for school activities
	*/
	public SchoolActivity() {
		super();
	}

	/**
	 * Constructor with paramters
	*/ 
	public SchoolActivity( String title, Time start, Time end, String comment ) {
		super( title, start, end, comment );
	} 
}