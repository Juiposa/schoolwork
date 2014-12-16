package asst3;

import java.awt.*;
import javax.swing.*;
import java.lang.Integer;

/**
 * series of five combo boxes with the dates as a choice
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class TimeComboBox extends JPanel {

	private static final String[] monthString = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	private JComboBox yearBox = new JComboBox();
	private JComboBox monthBox = new JComboBox();
	private JComboBox dayBox = new JComboBox();	
	private JComboBox hourBox = new JComboBox();	
	private JComboBox minuteBox = new JComboBox();

	public TimeComboBox() {
		setLayout( new GridLayout( 2, 5 ));
		for ( int i = 2010; i <= 2018; i++ ) {
			yearBox.addItem( new Integer(i));
		}
		monthBox = new JComboBox( monthString );
		for ( int i = 1; i <= 31; i++ ) {
			dayBox.addItem( new Integer(i));
		}
		for ( int i = 0; i <= 23; i++ ) {
			hourBox.addItem( new Integer(i));
		}
		for ( int i = 0; i <= 59; i++ ) {
			minuteBox.addItem( new Integer(i));
		}
		add( new JLabel("Year:"));
		add( new JLabel("Month:"));
		add( new JLabel("Day:"));
		add( new JLabel("Hour:"));
		add( new JLabel("Minute:"));
		add( yearBox );
		add( monthBox );
		add( dayBox );
		add( hourBox );
		add( minuteBox );
	}

	/**
	 * will reset the combobox items
	*/

	public void reset() {
		yearBox.setSelectedItem( new Integer(2010));
		monthBox.setSelectedItem( new String("January"));
		dayBox.setSelectedItem( new Integer(1));
		hourBox.setSelectedItem( new Integer(0));
		minuteBox.setSelectedItem( new Integer(0));
	}

	/**
	 * Will get the time represented by the combo boxes
	 * @return time class of the time
	*/
	public Time getTime() {
		int year = (int)yearBox.getSelectedItem();
		int month = 0;
		for ( int i = 0; i < 12; i++ ) {
			if ( monthString[i].equals( monthBox.getSelectedItem())) {
				month = i+1;
			}
		}
		int day = (int)dayBox.getSelectedItem();
		int hour = (int)hourBox.getSelectedItem();
		int minute = (int)minuteBox.getSelectedItem();

		Time returnTime = new Time( year, month, day, hour, minute );

		return returnTime;
	}
}