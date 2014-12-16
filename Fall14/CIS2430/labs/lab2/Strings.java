/*
 * @author Jeffrey-David Kapp 0832671
**/
import java.util.Scanner;
import java.util.StringTokenizer;

public class Strings {

	public static void main(String[] args) {

		String inputVar = "";
		String inputString = "";

		Scanner scan = new Scanner(System.in);

		do {
	
			optionPrint();

			inputVar = scan.nextLine();

			switch(inputVar) {
				case "1": 
					System.out.println("Enter your string.");
					inputString = scan.nextLine();
					break;
				case "2":
					System.out.println(inputString);
					break;

				case "3": 
					for(int i = inputString.length()-1; i >= 0; i-- ) {
						System.out.print(inputString.charAt(i));
					}
					System.out.println();
					break;
				case "4": 
					StringTokenizer strTok = new StringTokenizer(inputString);
					for( int i = strTok.countTokens(); i > 0; i-- ) {
						System.out.println( strTok.nextToken() );
					} 
					break;
				case "5":
					int spaceCount = 0; 
					for (int i = 0; i < inputString.length(); i++ ) {
						if ( inputString.charAt(i) == ' ' ) {
							spaceCount++;
						}
					}
					System.out.println("There are " + spaceCount + " spaces in this string."); 
					break;
				case "6":
					String integers = "0123456789";
					boolean number = false;
					for(int i = 0; i < inputString.length(); i++ ) {
						if ( integers.indexOf(inputString.charAt(i)) != -1 ) {
							i = inputString.length() - 1;
							number = true;
						}
					}
					if ( number == true ) {
						System.out.println("True.");
					} else {
						System.out.println("False.");
					}
					break;
				case "7":
					String vowels = "aeiouAEIOU";
					int numVowels = 0;
					for(int i = 0; i < inputString.length(); i++ ) {
						if ( vowels.indexOf(inputString.charAt(i)) != -1 ) {
							numVowels++;
						}
					}

					System.out.println("There are " + numVowels + " vowels.");
					break;

				case "8":
					String vowels2 = "aeiouAEIOU";
					int numConsonants = 0;
					for(int i = 0; i < inputString.length(); i++ ) {
						if ( vowels2.indexOf(inputString.charAt(i)) == -1 ) {
							numConsonants++;
						}
					}

					System.out.println("There are " + numConsonants + " consonants.");
					break;
					
			}

		} while( inputVar.charAt(0) != '9' );

	}

	private static void optionPrint() {
		System.out.println("Please enter an option.");
		System.out.println("1. Enter a string.");
		System.out.println("2. Print string.");
		System.out.println("3. Reverse string.");
		System.out.println("4. Tokenise string.");
		System.out.println("5. Count spaces in string.");
		System.out.println("6. Check for a number in string.");
		System.out.println("7. Count vowels.");
		System.out.println("8. Count consonants.");
		System.out.println("9. Exit.");
	}
}
