package asst2;

/**
 * @author Jeff Kapp 0832671
 * @since 7 Nov 2014
 *
*/

public class HomeActivity extends Activity {

	/**
	 * Contructor for home activities
	*/
	public HomeActivity() {
		super();
	}

	/**
	 * Constructor with paramters
	*/ 
	public HomeActivity( String title, Time start, Time end, String comment ) {
		super( title, start, end, comment );
	} 

}