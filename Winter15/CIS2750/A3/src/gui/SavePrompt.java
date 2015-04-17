package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Prompting user for save on action that would discard modified project
 * @author Jeff Kapp 0832671
 * @since 8 Mar 2015
 *
*/

public class SavePrompt extends JFrame implements ActionListener {

	public static final int WIDTH = 325;
	public static final int HEIGHT = 175;
	
	public SavePrompt( ActionListener listener ) {
		super("Save");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new GridLayout( 2, 1 ) );

		JLabel windowMessage = new JLabel("<html>Project has been modified.<br>Save before continuing?</html>", SwingConstants.CENTER );
		windowMessage.setHorizontalAlignment(JLabel.CENTER);
		add( windowMessage );

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout( FlowLayout.CENTER, 10, 10 ));
		JButton save = new JButton("Save");
		JButton cont = new JButton("Continue");

		cont.setPreferredSize( new Dimension(100, 45) );
		save.setPreferredSize( new Dimension(100, 45) );

		save.addActionListener( listener );
		cont.addActionListener( this );
		save.addActionListener( this );

		buttonPanel.add(save);
		buttonPanel.add(cont);

		add(buttonPanel);
	}

	public void actionPerformed( ActionEvent e ) {
		dispose();
	}
}