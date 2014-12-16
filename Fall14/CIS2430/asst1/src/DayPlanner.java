package asst1;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.StringTokenizer;

/**
 * Main control class
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class DayPlanner {

	public ArrayList<HomeActivity> homeActivity;
	public ArrayList<SchoolActivity> schoolActivity;
	public ArrayList<OtherActivity> otherActivity;

	public static void main( String[] args ) {

		DayPlanner ourDayPlanner = new DayPlanner();
		
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);

		do {
			printOptions(0);
			inputVar = keyboard.nextLine();
			
			switch( inputVar.charAt(0) ) {
				case 'a': //add activity
				case 'A':
					ourDayPlanner.addActivity();
					break;
				case 's': //search activity
				case 'S':
					ourDayPlanner.search();
					break;
				case 'q':
				case 'Q':
					break;
				default: System.out.println("Invalid input."); break;
			}
		} while( inputVar.charAt(0) != 'q' && inputVar.charAt(0) != 'Q' );

	}

	/**
	 * Class constructor
	*/

	private DayPlanner() {
		homeActivity = new ArrayList<HomeActivity>(100);
		schoolActivity =  new ArrayList<SchoolActivity>(100);
		otherActivity = new ArrayList<OtherActivity>(100);
	}

	/**
	 * Handles addtion of a new activity
	*/
	private void addActivity() {
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);
		int validInput = 0;

		do {
			printOptions(1);

			inputVar = keyboard.nextLine();

			switch( inputVar.charAt(0) ) {
				case '1':
					homeActivity.add( new HomeActivity() ); //call class constructor and adds to the array
					validInput = 1;
					break;
				case '2':
					schoolActivity.add( new SchoolActivity() ); //ditto
					validInput = 1;
					break;
				case '3':
					otherActivity.add( new OtherActivity() ); //ditto
					validInput = 1;
					break;
				default: System.out.println("Invalid input.");
			}

		} while ( validInput == 0 );


	}

	/**
	 * Prints list of options for the user at the control loop
	 * @param options - Which set of options to print
	*/
	private static void printOptions( int options ) {
		System.out.println("Choose an option.");
		
		switch( options ) {
			case 0:
				System.out.println("Add) Add a new activity.");
				System.out.println("Search) Search activities.");
				System.out.println("Quit) Quit program.");
				break;
			case 1:
				System.out.println("1) Home activity");
				System.out.println("2) School activity");
				System.out.println("3) Other Activity");
				break;
		}
	}

	/**
	 * Will ask user for what they wish to search for start a search
	*/
	private void search() {
		String inputVar  = new String(); //input variable/string
		Scanner keyboard = new Scanner(System.in);
		int validInput = 0;

		System.out.println("Which list of activities would you like to search?");
		printOptions(1);

		do {
			inputVar = keyboard.nextLine();
			switch ( inputVar.charAt(0) ) {
				case '1':
						searchHomeList();
						validInput = 1;
					break;
				case '2':
						searchSchoolList();
						validInput = 1;	
					break;
				case '3':
						searchOtherList();
						validInput = 1;
					break;
				default: System.out.println("Invalid input.");
			}
		} while ( validInput == 0 );
	}
	
	/**
     * searching the home activities list
	*/
	private void searchHomeList() {
		ArrayList<HomeActivity> searchList = this.homeActivity;
		HomeActivity curNode;

		int numTokens = 0; // number of tokens in a tokenised string, used for comparison
		int matchCount = 0; //count of the number of times a token matches a string
		Time lowerBoundDate = new Time(); //lower bound date
		Time upperBoundDate = new Time(); //upper bound date

		String inputVar  = new String(); //input variable/string
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter your key words for search.");
		inputVar = keyboard.nextLine();
		StringTokenizer tokeniser = new StringTokenizer(inputVar);
		numTokens = tokeniser.countTokens();

		System.out.println("Enter a upper bound for a date.");
		upperBoundDate.userBuildDate();

		System.out.println("Enter a lower bound for a date.");
		lowerBoundDate.userBuildDate();

		for ( int i = 0; i < searchList.size(); i++ ) { //iterate for ever member of the list
			curNode = searchList.get(i); //get the current node
			if ( lowerBoundDate.isLesser( curNode.getDateStart() ) && upperBoundDate.isGreater( curNode.getDateEnd()) ) { // if it matches to the upper and lower bounds
				for ( int j = 0; j < numTokens; j++ ) { //for the number of tokens the search string has
					String comStr = new String( curNode.getTitle() ); // string to be compared to the tokens
					if ( comStr.indexOf( tokeniser.nextToken() ) != -1 ) {
						matchCount++;
					} 
				}
				if ( matchCount == numTokens ) {
					curNode.print();
				}
			}
		}
	}

	/**
     * searching the school activities list
	*/
	private void searchSchoolList() {
		ArrayList<SchoolActivity> searchList = this.schoolActivity;
		SchoolActivity curNode;

		int numTokens = 0; // number of tokens in a tokenised string, used for comparison
		int matchCount = 0; //count of the number of times a token matches a string
		Time lowerBoundDate = new Time(); //lower bound date
		Time upperBoundDate = new Time(); //upper bound date

		String inputVar  = new String(); //input variable/string
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter your key words for search.");
		inputVar = keyboard.nextLine();
		StringTokenizer tokeniser = new StringTokenizer(inputVar);
		numTokens = tokeniser.countTokens();

		System.out.println("Enter a upper bound for a date.");
		upperBoundDate.userBuildDate();

		System.out.println("Enter a lower bound for a date.");
		lowerBoundDate.userBuildDate();

		for ( int i = 0; i < searchList.size(); i++ ) { //iterate for ever member of the list
			curNode = searchList.get(i); //get the current node
			if ( lowerBoundDate.isLesser( curNode.getDateStart() ) && upperBoundDate.isGreater( curNode.getDateEnd()) ) { // if it matches to the upper and lower bounds
				for ( int j = 0; j < numTokens; j++ ) { //for the number of tokens the search string has
					String comStr = new String( curNode.getTitle() ); // string to be compared to the tokens
					if ( comStr.indexOf( tokeniser.nextToken() ) != -1 ) {
						matchCount++;
					} 
				}
				if ( matchCount == numTokens ) {
					curNode.print();
				}
			}
		}
	}

	/**
     * searching the others activities list
	*/
	private void searchOtherList() {
		ArrayList<OtherActivity> searchList = this.otherActivity;
		OtherActivity curNode;

		int numTokens = 0; // number of tokens in a tokenised string, used for comparison
		int matchCount = 0; //count of the number of times a token matches a string
		Time lowerBoundDate = new Time(); //lower bound date
		Time upperBoundDate = new Time(); //upper bound date

		String inputVar  = new String(); //input variable/string
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter your key words for search.");
		inputVar = keyboard.nextLine();
		StringTokenizer tokeniser = new StringTokenizer(inputVar);
		numTokens = tokeniser.countTokens();

		System.out.println("Enter a upper bound for a date.");
		upperBoundDate.userBuildDate();

		System.out.println("Enter a lower bound for a date.");
		lowerBoundDate.userBuildDate();

		for ( int i = 0; i < searchList.size(); i++ ) { //iterate for ever member of the list
			curNode = searchList.get(i); //get the current node
			if ( lowerBoundDate.isLesser( curNode.getDateStart() ) && upperBoundDate.isGreater( curNode.getDateEnd()) ) { // if it matches to the upper and lower bounds
				for ( int j = 0; j < numTokens; j++ ) { //for the number of tokens the search string has
					String comStr = new String( curNode.getTitle() ); // string to be compared to the tokens
					if ( comStr.indexOf( tokeniser.nextToken() ) != -1 ) {
						matchCount++;
					} 
				}
				if ( matchCount == numTokens ) {
					curNode.print();
				}
			}
		}
	}
} 