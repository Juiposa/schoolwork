package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * popup about window
 * @author Jeffrey-David Kapp
 * @since 9 Feb 2015
*/

public class AboutWindow extends JFrame implements ActionListener {

	public static final int WIDTH = 250;
	public static final int HEIGHT = 175;

	public AboutWindow() {
		super("About");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new BorderLayout() );

		JTextArea textArea = new JTextArea(50, 50);
		textArea.setEditable(false);
		JScrollPane textPane = new JScrollPane( textArea );

		add(textArea, BorderLayout.CENTER);

		JButton dispose = new JButton("Close");
		dispose.setPreferredSize( new Dimension(95, 45) );
		dispose.addActionListener(this);

		add(dispose, BorderLayout.SOUTH);

		textArea.setText("Dialogc\nJeffrey-David Kapp 0832671\n13 March2015\nCIS2750_W15\n");
	}
	
	public void actionPerformed( ActionEvent e ) {
		dispose();
	}

	public static void main(String[] args) {
		AboutWindow test = new AboutWindow();
		test.setVisible(true);
	} 
}