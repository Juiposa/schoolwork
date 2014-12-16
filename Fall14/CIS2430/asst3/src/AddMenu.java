package asst3;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * add menu panel
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class AddMenu extends JPanel implements ActionListener {
	
	private DayPlanner activeDayPlanner;
	private JTextArea messageArea;
	private JScrollPane messagePane;
	private JComboBox typeMenu = new JComboBox();
	private	JTextField activityTitleText = new JTextField("Title", 30 );
	private JTextField locationText = new JTextField("Location", 30 );
	private	JTextField commentText = new JTextField("Comment", 30 );
	private TimeComboBox startComboBox = new TimeComboBox(); 
	private TimeComboBox endComboBox = new TimeComboBox(); 

	/**
	 * Get activity type
	*/
	public int getType() {
		int returnI = 0;
		if ( typeMenu.getSelectedItem().equals("Home") ) {
			returnI = 1;
		} else if ( typeMenu.getSelectedItem().equals("School") ) {
			returnI = 2;
		} else if ( typeMenu.getSelectedItem().equals("Other") ) {
			returnI = 3;
		}

		return returnI;
	}

	/**
	 * Get activity title
	*/
	public String getTitle() {
		return activityTitleText.getText();
	}

	/**
	 * Get activity location
	*/
	public String getLocat() {
		return locationText.getText();
	}

	/**
	 * Get activity comment
	*/
	public String getComment() {
		return commentText.getText();
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

	public AddMenu( DayPlanner dayplanner ) {
		activeDayPlanner = dayplanner;
		setLayout( new BorderLayout() );

		//add menu; buttons
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout( new GridLayout( 2, 1 ));

		JButton reset = new JButton("Reset");
		reset.addActionListener(this);
		JButton enter = new JButton("Enter");
		enter.addActionListener(activeDayPlanner);

		buttonPanel.add( reset );
		buttonPanel.add( enter );

		add( buttonPanel, BorderLayout.EAST);
		//end add menu; buttons

		//add menu; messages
		messageArea = new JTextArea(6, 50);
		messageArea.setEditable(false);
		messagePane = new JScrollPane( messageArea );
		JPanel messagePanel = new JPanel();
		messagePanel.setLayout( new BorderLayout() );

		JLabel messageLabel = new JLabel("Messages:");
		messagePane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		messagePane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		messagePanel.add(messageLabel, BorderLayout.NORTH);
		messagePanel.add(messagePane, BorderLayout.SOUTH);

		add(messagePanel, BorderLayout.SOUTH);
		//end add menu; messages

		//add menu; user input
		JPanel inputArea = new JPanel();
		inputArea.setLayout( new GridLayout( 9, 1 ));

		JLabel title = new JLabel("Adding an activity:"); //title

		JPanel typePanel = new JPanel(); //type menu
		typePanel.setLayout( new GridLayout( 1, 2 ));
		JLabel typeLabel = new JLabel("Type:");
		String[] typeString = {"Home", "School", "Other"};
		typeMenu = new JComboBox( typeString );
		typePanel.add(typeLabel);
		typePanel.add(typeMenu);

		JPanel activityTitlePanel = new JPanel(); //title panel
		activityTitlePanel.setLayout(new GridLayout(1, 2));
		activityTitlePanel.add( new JLabel("Title: "));
		activityTitlePanel.add(activityTitleText);

		JLabel startLabel = new JLabel("Starting Time"); //starting time
		
		JLabel endLabel = new JLabel("End Time"); //end time

		JPanel locationPanel = new JPanel(); //location panel
		locationPanel.setLayout(new GridLayout(1, 2));
		locationPanel.add( new JLabel("Location: "));
		locationPanel.add(locationText);

		JPanel commentPanel = new JPanel(); //comment panel
		commentPanel.setLayout(new GridLayout(1, 2));
		commentPanel.add( new JLabel("Comment: "));
		commentPanel.add(commentText);

		inputArea.add(typePanel);
		inputArea.add(activityTitlePanel);
		inputArea.add(startLabel);
		inputArea.add(startComboBox);
		inputArea.add(endLabel);
		inputArea.add(endComboBox);
		inputArea.add(locationPanel);
		inputArea.add(commentPanel);

		add(inputArea, BorderLayout.CENTER);
		//end input area
	}

	public void actionPerformed( ActionEvent e ) { 
		activityTitleText.setText("Title");
		commentText.setText("Comment");
		locationText.setText("Location");
		startComboBox.reset();
		endComboBox.reset();
	}

	
}