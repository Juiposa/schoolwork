package weatherForcast;

import java.util.Scanner; 


public class Weather 
{
	public static void main( String[] args )
	{

		float inputFloat = 0;
		String inputVal =  new String();

		Temperature[] tempArray = new Temperature[7];

		Scanner keyboard = new Scanner(System.in); 

		System.out.println("Please enter seven temperatures in Celsius.");

		for ( int i = 0; i < 7; i++ ) {
			inputFloat = keyboard.nextFloat();

			tempArray[i] = new Temperature( inputFloat );

		}

		keyboard.nextLine();

		do {
			printOption();

			int inputInt;

			inputVal = keyboard.nextLine();

			switch( inputVal.charAt(0) ) {
				case '1': 
					for ( int i = 0; i < 7; i++ ){
						System.out.println("Day of the week: " + (i+1) + " " + tempArray[i].toString() );
					}
					break;
				case '2': 
					System.out.println("Change to: 0) Celsius, 1) Fahrenheit, 2) Kelvin ");
					inputInt = keyboard.nextInt();
					for (int i = 0; i < 7; i++ ) {
						tempArray[i].changeUnit( inputInt );
					}
					keyboard.nextLine();
					break;
				case '3':
					System.out.println("Which day do you want to change? ");
					inputInt = keyboard.nextInt();
					System.out.println("To what temperature?");
					tempArray[inputInt-1].setTemp( keyboard.nextInt() );
					keyboard.nextLine();
					break;
				case '4': 
						for( int i = 0; i < 7; i++ ){
							for( int j = i; j < 7; j++ ) {
								if ( tempArray[i].equals(tempArray[j]) && i != j) {
									System.out.println("Day " + (i + 1) + " and " + "Day " + (j + 1) + " have the same weather." );
								}
							}
						}
					break;
				case 'q':
				case 'Q': break;
				default:
					System.out.println("Invalid input.");
					break;
			}

		} while( inputVal.charAt(0) != 'q' && inputVal.charAt(0) != 'Q');


	}

	private static void printOption() {
		System.out.println("Enter an option.");
		System.out.println("1) Print forcast.");
		System.out.println("2) Convert temperature unit.");
		System.out.println("3) Change day forcast.");
		System.out.println("4) Which days have the same weather.");
		System.out.println("Q) Quit");
	}

}