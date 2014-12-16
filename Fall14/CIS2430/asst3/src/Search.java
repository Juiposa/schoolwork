package asst3;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.HashMap;
import java.lang.Integer;

/**
 * search class
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class Search {
	
	private int type = 0;
	private String keywords = null;
	private Time start = null;
	private Time end = null;
	private ArrayList<Activity> activities;
	private HashMap<String,ArrayList<Integer>> hashMap = new HashMap<String,ArrayList<Integer>>();

	public Search( ArrayList<Activity> activities, int type, String keywords, Time start, Time end ) {
		this.type = type;
		this.keywords = keywords;
		this.start = start;
		this.end  = end;
		this.activities = activities;
		HashMap<String,ArrayList<Integer>> hashMap = getHash( activities );
	}
	/**
	 * Will search the hash map and return a constructed output string
	*/
	public String searchFunc() {

		ArrayList<Integer> searchIndex = null; //our list of indices of activities which contain the keywords
		//^^will contain indices of activities that contain our keywords or will default to every element if we dont ahve keywords
		String outputString = new String();
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
					outputString = outputString + "\n" + acvNd.toString();
				} 

			}
		}
		return outputString;
	}
	
	/**
	 * will build a hash map from all the elements in the activities list
	 * @return A completed hash map
	*/
	private HashMap<String,ArrayList<Integer>> getHash( ArrayList<Activity> activities ) {
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
}