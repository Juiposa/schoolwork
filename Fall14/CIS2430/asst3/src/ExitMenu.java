package asst3;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Exit comfirmation popup
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class ExitMenu extends JFrame  implements ActionListener {

	public static final int WIDTH = 250;
	public static final int HEIGHT = 200;
	
	public ExitMenu( DayPlanner dayplanner ) {
		super("Exit");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new GridLayout( 2, 1) );

		JLabel windowMessage = new JLabel("Are you sure you want to exit?");
		windowMessage.setHorizontalAlignment(JLabel.CENTER);
		add( windowMessage );

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout( new GridLayout( 1, 2 ));
		JButton exit = new JButton("Exit");
		JButton cancel = new JButton("Cancel");

		exit.addActionListener( dayplanner );
		cancel.addActionListener( this );

		buttonPanel.add(exit);
		buttonPanel.add(cancel);

		add(buttonPanel);
	}

	public void actionPerformed( ActionEvent e ) {
		dispose();
	}
}