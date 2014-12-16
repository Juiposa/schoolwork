package asst3;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * search menu panel
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class SearchMenu extends JPanel implements ActionListener {

	private DayPlanner activeDayPlanner;
	private JTextArea messageArea;
	private JScrollPane messagePane;
	private JComboBox typeMenu = new JComboBox();
	private	JTextField activityKeywordText = new JTextField("", 30 );
	private TimeComboBox startComboBox = new TimeComboBox(); 
	private TimeComboBox endComboBox = new TimeComboBox(); 

	public int getType() {
		int returnI = 0;
		if ( typeMenu.getSelectedItem().equals("Home") ) {
			returnI = 1;
		} else if ( typeMenu.getSelectedItem().equals("School") ) {
			returnI = 2;
		} else if ( typeMenu.getSelectedItem().equals("Other") ) {
			returnI = 3;
		} else if ( typeMenu.getSelectedItem().equals("All") ) {
			returnI = 4;
		}

		return returnI;
	}

	/**
	 * Get activity keywords
	*/
	public String getKeywords() {
		return activityKeywordText.getText();
	}

	/**
	 * Get activity start time
	*/
	public Time getStartTime() {
		return startComboBox.getTime();
	}

	/**
	 * Get activity end time
	*/
	public Time getEndTime() {
		return endComboBox.getTime();
	}

	/**
	 * Settign the message displayed in the message area
	*/
	public void setMessage( String message ) {
		messageArea.setText(message);
	}


	public SearchMenu( DayPlanner dayplanner ) {
		activeDayPlanner = dayplanner;
		setLayout( new BorderLayout() );

		//add menu; buttons
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout( new GridLayout( 2, 1 ));

		JButton reset = new JButton("Reset");
		reset.addActionListener(this);
		JButton enter = new JButton("Search");
		enter.addActionListener(activeDayPlanner);

		buttonPanel.add( reset );
		buttonPanel.add( enter );

		add( buttonPanel, BorderLayout.EAST);
		//end add menu; buttons

		//add menu; messages
		messageArea = new JTextArea(10, 50);
		messageArea.setEditable(false);
		messageArea.setText("Leave dates equal to skip searching by date.");
		messagePane = new JScrollPane( messageArea );
		JPanel messagePanel = new JPanel();
		messagePanel.setLayout( new BorderLayout() );

		JLabel messageLabel = new JLabel("Search Results:");
		messagePane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		messagePane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		messagePanel.add(messageLabel, BorderLayout.NORTH);
		messagePanel.add(messagePane, BorderLayout.SOUTH);

		add(messagePanel, BorderLayout.SOUTH);
		//end add menu; messages

		//add menu; user input
		JPanel inputArea = new JPanel();
		inputArea.setLayout( new GridLayout( 7, 1 ));

		JLabel title = new JLabel("Searching activities:"); //title

		JPanel typePanel = new JPanel(); //type menu
		typePanel.setLayout( new GridLayout( 1, 2 ));
		JLabel typeLabel = new JLabel("Type:");
		String[] typeString = {"Home", "School", "Other", "All"};
		typeMenu = new JComboBox( typeString );
		typePanel.add(typeLabel);
		typePanel.add(typeMenu);

		JPanel activityKeywordPanel = new JPanel(); //keyword panel
		activityKeywordPanel.setLayout(new GridLayout(1, 2));
		activityKeywordPanel.add( new JLabel("Keywords: "));
		activityKeywordPanel.add(activityKeywordText);

		JLabel startLabel = new JLabel("Starting Time"); //starting time
		
		JLabel endLabel = new JLabel("End Time"); //end time

		inputArea.add(typePanel);
		inputArea.add(activityKeywordPanel);
		inputArea.add(startLabel);
		inputArea.add(startComboBox);
		inputArea.add(endLabel);
		inputArea.add(endComboBox);

		add(inputArea, BorderLayout.CENTER);
		//end input area
	}

	public void actionPerformed( ActionEvent e ) { 
		messageArea.setText("Leave dates equal to skip searching by date.");
		startComboBox.reset();
		endComboBox.reset();
	}

}