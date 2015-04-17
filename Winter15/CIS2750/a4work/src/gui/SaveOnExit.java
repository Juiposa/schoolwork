

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Prompting user for save on exit
 * Modded ExitMessage.java
 * @author Jeff Kapp 0832671
 * @since 8 Mar 2015
 *
*/

public class SaveOnExit extends JFrame implements ActionListener {

	public static final int WIDTH = 250;
	public static final int HEIGHT = 200;
	
	public SaveOnExit( ActionListener listener ) {
		super("Save");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new GridLayout( 2, 1 ) );

		JLabel windowMessage = new JLabel("<html>Would you like to<br>save before exiting?</html>");
		windowMessage.setHorizontalAlignment(JLabel.CENTER);
		add( windowMessage );

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout( FlowLayout.CENTER, 10, 10 ));
		JButton save = new JButton("Save");
		JButton exit = new JButton("Exit");
		exit.setActionCommand("ForceExit");

		exit.setPreferredSize( new Dimension(95, 45) );
		save.setPreferredSize( new Dimension(95, 45) );

		exit.addActionListener( listener );
		save.addActionListener( listener );
		exit.addActionListener( this );
		save.addActionListener( this );

		buttonPanel.add(save);
		buttonPanel.add(exit);

		add(buttonPanel);
	}

	public void actionPerformed( ActionEvent e ) {
		dispose();
	}
}