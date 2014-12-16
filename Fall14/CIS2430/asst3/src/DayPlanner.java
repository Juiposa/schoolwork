package asst3;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.HashMap;
import java.lang.Integer;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Main control class
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class DayPlanner implements ActionListener {

	public ArrayList<Activity> activities;
	private static MainWindow mainWindow;
	private static String inputFile;
	private static String outputFile;
	
	public static void main( String[] args ) {

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

		DayPlanner ourDayPlanner = new DayPlanner();
		
		mainWindow = new MainWindow ( ourDayPlanner );
		mainWindow.setVisible(true);

	}

	/**
	 * Class constructor from a file
	*/
	private DayPlanner() {
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

		type = mainWindow.addMenu.getType();
		title = mainWindow.addMenu.getTitle();
		start = mainWindow.addMenu.getStartTime();
		end = mainWindow.addMenu.getEndTime();
		comment = mainWindow.addMenu.getComment();
		location = mainWindow.addMenu.getLocat();

		if ( title.length() == 0 ) {
			mainWindow.addMenu.setMessage("Title cannot be blank.");
			return;
		}

		if ( start.isGreater(end) ) {
			mainWindow.addMenu.setMessage("Start time must be before end time.");
			return;
		}

		if ( type == 1 ) {
			activities.add( new HomeActivity( title, start, end, comment ) );
		} else if ( type == 2 ) {
			activities.add( new SchoolActivity( title, start, end, comment ) );
		} else {
			activities.add( new OtherActivity( title, start, end, location, comment ) );
		}
		mainWindow.addMenu.setMessage(" ");
	}

	/**
	 * Will ask user for what they wish to search for start a search
	*/
	private void search() {

		Scanner keyboard = new Scanner(System.in);
		String outString;

		int type = 0;
		String keywords = null;
		Time start = null;
		Time end = null;

		type = mainWindow.searchMenu.getType();
		keywords = mainWindow.searchMenu.getKeywords();
		start = mainWindow.searchMenu.getStartTime();
		end = mainWindow.searchMenu.getEndTime();

		if ( keywords.length() == 0 ) { //no keywords have been entered
			keywords = null;
		}

		if ( start.isEqual(end) ) { //user may leave times as is to skip searching them
			start = null;
			end = null;
		}

		Search searcher = new Search( activities, type, keywords, start, end );
		outString = searcher.searchFunc();

		mainWindow.searchMenu.setMessage(outString);
	}

	/**
	 * will print to a file
	*/
	private void printToFile() {
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

		System.exit(0);
	} 

	public void actionPerformed( ActionEvent e ) {
		String command = e.getActionCommand();

		if ( command.equals("Enter") ) {
			addActivity();
		} else if ( command.equals("Search")) {
			search();
		} else if ( command.equals("Exit")) {
			printToFile();
		}
	}
} 