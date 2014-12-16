package asst2;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.HashMap;
import java.lang.Integer;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

/**
 * Main control class
 * @author Jeff Kapp 0832671
 * @since Oct 15 2014
 *
*/

public class DayPlanner {

	public ArrayList<Activity> activities;
	
	public static void main( String[] args ) {

		String inputFile = "";
		String outputFile = "";

		if ( args.length == 0 ) { //only one command, default file
			inputFile = "doc/saveFile.dat";
			outputFile = "doc/saveFile.dat";
		} else if ( args.length == 1 ) { //only and input file was given
			inputFile = "doc/saveFile.dat";
			outputFile = new String(args[1]);
		} else if ( args.length == 2 ) {
			inputFile = new String(args[1]);
			outputFile = new String(args[2]);
		} else {
			System.out.println("Too many arguments.");
			System.exit(0);
		}

		DayPlanner ourDayPlanner = new DayPlanner( inputFile );
		
		String inputVar = new String();
		Scanner keyboard = new Scanner(System.in);

		do {
			printOptions(0);
			inputVar = keyboard.nextLine();
			if ( inputVar.isEmpty() ) {
				inputVar = "?";
			}
			
			switch( inputVar.charAt(0) ) {
				case 'a': case 'A': //add activity
					ourDayPlanner.addActivity();
					break;
				case 's': case 'S': //search activity
					ourDayPlanner.search();
					break;
				case 'q': case 'Q':
					ourDayPlanner.printToFile(outputFile);
					break;
				default: System.out.println("Invalid input."); break;
			}
		} while( inputVar.charAt(0) != 'q' && inputVar.charAt(0) != 'Q' );

	}

	/**
	 * Class constructor
	*/
	private DayPlanner() {
		activities = new ArrayList<Activity>();
	}

	/**
	 * Class constructor from a file
	*/
	private DayPlanner( String inputFile ) {
		activities = new ArrayList<Activity>();
		int type;
		String title;
		int year, month, day, hour, minute;
		Time start, end;
		String comment, location;
		Scanner inputStream = null;
		try {
			inputStream = new Scanner( new FileInputStream(inputFile));
		} catch (FileNotFoundException e) {
			System.out.println("File not found: " + inputFile );
			System.exit(0);
		}

		while ( inputStream.hasNextLine() ) {
			type = Integer.parseInt( inputStream.nextLine() );
			title = inputStream.nextLine();
			year = Integer.parseInt( inputStream.nextLine() );
			month = Integer.parseInt( inputStream.nextLine() );
			day = Integer.parseInt( inputStream.nextLine() );
			hour = Integer.parseInt( inputStream.nextLine() );
			minute = Integer.parseInt( inputStream.nextLine() );

			start = new Time( year, month, day, hour, minute );

			year = Integer.parseInt( inputStream.nextLine() );
			month = Integer.parseInt( inputStream.nextLine() );
			day = Integer.parseInt( inputStream.nextLine() );
			hour = Integer.parseInt( inputStream.nextLine() );
			minute = Integer.parseInt( inputStream.nextLine() );

			end = new Time( year, month, day, hour, minute );

			comment = inputStream.nextLine();

			if ( type == 1 ) {
				activities.add( new HomeActivity( title, start, end, comment ) );
			} else if ( type == 2 ) {
				activities.add( new SchoolActivity( title, start, end, comment ) );
			} else {
				location = inputStream.nextLine();
				activities.add( new OtherActivity( title, start, end, location, comment ) );
			}
		}
		inputStream.close();
	}

	/**
	 * Handles addtion of a new activity
	*/
	private void addActivity() {
		int type = -1;
		String typeStr = "";
		String title = null;
		Time start  = null;
		Time end  = null;
		String comment = "";
		String location = ""; 

		Scanner keyboard = new Scanner(System.in);

		System.out.println("Enter an activity type.");
		printOptions( 1 );
		do {
			typeStr = keyboard.nextLine();
			if ( !typeStr.isEmpty() ) {
				type = Integer.parseInt( typeStr );			
			}
		} while ( type != 1 && type != 2 && type != 3 );

		System.out.println("Enter a title.");
		do {
			title = keyboard.nextLine();
		} while ( title.isEmpty() || title == null );

		System.out.println("Enter a start date.");
		do {
			start = getNewTime();
		} while ( start == null );

		System.out.println("Enter an end date."); 
		do {
			end  = getNewTime();
			if ( start.isGreater(end) ) {
				System.out.println("End date must be after or at the same time as the start.");
			}
		} while ( end == null || start.isGreater(end) );

		if ( type == 3 ) {
			System.out.println("Enter a location.");
			location = keyboard.nextLine();
		}

		System.out.println("Enter a comment if you wish.");
		comment = keyboard.nextLine();

		if ( type == 1 ) {
			activities.add( new HomeActivity( title, start, end, comment ) );
		} else if ( type == 2 ) {
			activities.add( new SchoolActivity( title, start, end, comment ) );
		} else {
			activities.add( new OtherActivity( title, start, end, location, comment ) );
		}
	}

	/**
	 * Will take user input for a new time
	 * @return new Time class, or null if input is invalid
	*/
	private Time getNewTime() {
		String year, month, day, hour, minute;
		Scanner keyboard =  new Scanner(System.in);
		
		System.out.print("Year: ");
		year = keyboard.nextLine();
		System.out.print("Month: ");
		month = keyboard.nextLine();
		System.out.print("Day: ");
		day = keyboard.nextLine();
		System.out.print("Hour: ");
		hour = keyboard.nextLine();
		System.out.print("Minute: ");
		minute = keyboard.nextLine();

		if ( year.isEmpty() || month.isEmpty() || day.isEmpty() || hour.isEmpty() || minute.isEmpty() ) {
			return null;
		} else if ( Time.isTimeValid( Integer.parseInt(year), Integer.parseInt(month) , Integer.parseInt(day), Integer.parseInt(hour), Integer.parseInt(minute) ) ) {
			return new Time( Integer.parseInt(year), Integer.parseInt(month) , Integer.parseInt(day), Integer.parseInt(hour), Integer.parseInt(minute) );
		} else {
			return null;
		}
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
				System.out.println("1) Home Activity");
				System.out.println("2) School Activity");
				System.out.println("3) Other Activity");
				break;
		}
	}

	/**
	 * Will ask user for what they wish to search for start a search
	*/
	private void search() {
		HashMap<String,ArrayList<Integer>> hashMap = getHash();

		Scanner keyboard = new Scanner(System.in);

		int type = 0;
		String keywords = null;
		Time start = null;
		Time end = null;

		System.out.println("Enter an activity type.");
		printOptions( 1 );
		System.out.println("4) All Activities");
		do {
			type = Integer.parseInt( keyboard.nextLine() );
		} while ( type != 1 && type != 2 && type != 3 && type != 4 );

		System.out.println("Enter keywords to search (or leave blank):");
		keywords = keyboard.nextLine();
		if ( keywords.isEmpty() ) {
			keywords = null;
		} else {
			keywords = keywords.toLowerCase();
		}

		System.out.println("Enter a lower bound date (or leave blank):");
		start = getNewTime();

		System.out.println("Enter an upper bound date (or leave blank):");
		end = getNewTime();
		if ( start != null && start.isGreater(end) ) {
			System.out.println("End date must be after or at the same time as the start.");
			System.out.println("Defaulting date to null (you will not have an upper bound)");
			end = null;
		}

		ArrayList<Integer> searchIndex = null; //our list of indices of activities which contain the keywords
		//^^will contain indices of activities that contain our keywords or will default to every element if we dont ahve keywords
		if ( keywords != null ) { //only if we do have key words
			StringTokenizer tokeniser = new StringTokenizer( keywords );
			int numTokens = tokeniser.countTokens();
			searchIndex = hashMap.get( tokeniser.nextToken() ); //first keywords defines our bases indices
			if (  searchIndex != null && searchIndex.size() > 1 ) {
				for ( int i = 1; i < numTokens; i++ ) { //for every other token, if any	
					searchIndex.retainAll( hashMap.get(tokeniser.nextToken())); //toss any value not included in the maps of subsequent keywords
				}	
			}
		} else { //we have no keywords
			searchIndex = new ArrayList<Integer>();
			for ( int j = 0; j < activities.size(); j++ ) { //make an array list indexing every member of the activities list
				searchIndex.add( j );
			}
		}

		System.out.println();

		//dummy classes for class type comparision
		HomeActivity home = new HomeActivity();
		SchoolActivity school = new SchoolActivity();
		OtherActivity other = new OtherActivity();

		if ( searchIndex != null ) {
			for ( int k = 0; k < searchIndex.size(); k++ ) { //for every member of the search index as defined above.
				Activity acvNd = activities.get(searchIndex.get(k));
				if ( ( type == 4 //if were looing for any activity type
				   	|| ( type == 1 && home.getClass() == acvNd.getClass() ) //or just home
				   	|| ( type == 2 && school.getClass() == acvNd.getClass() ) //or school
				   	|| ( type == 3 && other.getClass() == acvNd.getClass() ) ) //or others
					&& ( start == null || !start.isGreater(acvNd.getDateStart()) ) //start date is before or equal
					&& ( end == null || !end.isLesser(acvNd.getDateEnd())) ) {
					System.out.println( acvNd.toString() );
				} 

			}
		}
	}
	
	/**
	 * will build a hash map from all the elements in the activities list
	 * @return A completed hash map
	*/
	private HashMap<String,ArrayList<Integer>> getHash() {
		StringTokenizer tokeniser = null;
		Activity activeNode = null;
		ArrayList<Integer> activeList = null;
		String activeToken;

		HashMap<String,ArrayList<Integer>> newHash = new HashMap<String,ArrayList<Integer>>();

		for ( int i = 0; i < activities.size(); i++ )  { //for the full length of the activities list 
			activeNode = activities.get(i); //get our active node from list
			String tempString = activeNode.getTitle(); //put title to tempString
			tempString = tempString.toLowerCase(); //lower case it so we can ignore case
			tokeniser = new StringTokenizer( tempString ); //tokenise its title as lower case
			int numTokens = tokeniser.countTokens(); //number of tokens this tokeniser has
			for ( int j = 0; j < numTokens; j++ ) { //for the number of tokens
				activeToken = tokeniser.nextToken(); //set active token to the next token
				activeList = newHash.get( activeToken ); //get array list of integers mapped to that string
				if ( activeList == null ) { //if null, this token is not yet a key in the hash map
					activeList = new ArrayList<Integer>(); //new array list
					activeList.add(i); //with the current activities list index as the first element
				} else { //this key is already mapped
					activeList.add(i); //simply push the current index onto the list
				}
				newHash.put( activeToken, activeList ); //push it back in the hash map
			}
		}
		return newHash;
	}

	/**
	 * will print to a file
	 * @param outputFile file to write to
	*/
	private void printToFile( String outputFile ) {
		PrintWriter outputStream = null;
		try {
			outputStream = new PrintWriter( new FileOutputStream(outputFile));
		} catch (FileNotFoundException e) {
			System.out.println("File not found: " + outputFile );
			System.exit(0);
		}

		//dummy classes for class type comparision
		HomeActivity home = new HomeActivity();
		SchoolActivity school = new SchoolActivity();
		OtherActivity other = new OtherActivity();

		for ( int i  = 0; i < activities.size(); i++ ) {
			if ( home.getClass() == activities.get(i).getClass() ) {
				outputStream.println("1");
			} else if ( school.getClass() == activities.get(i).getClass() ) {
				outputStream.println("2");
			} else if ( other.getClass() == activities.get(i).getClass() ) {
				outputStream.println("3");
			}

			outputStream.println(activities.get(i).getTitle());

			outputStream.println(activities.get(i).getDateStart().getYear());
			outputStream.println(activities.get(i).getDateStart().getMonth());
			outputStream.println(activities.get(i).getDateStart().getDay());
			outputStream.println(activities.get(i).getDateStart().getHour());
			outputStream.println(activities.get(i).getDateStart().getMinute());

			outputStream.println(activities.get(i).getDateEnd().getYear());
			outputStream.println(activities.get(i).getDateEnd().getMonth());
			outputStream.println(activities.get(i).getDateEnd().getDay());
			outputStream.println(activities.get(i).getDateEnd().getHour());
			outputStream.println(activities.get(i).getDateEnd().getMinute());

			outputStream.println(activities.get(i).getComment());

			if ( other.getClass() == activities.get(i).getClass() ) {
				outputStream.println(activities.get(i).getLocation());
			}
		}
		outputStream.close();

	} 
} 