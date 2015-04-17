package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;


/**
 * Help window displaying the contents of the README
 * @author Jeffrey-David Kapp
 * @since 11 Feb 2015
*/

public class HelpWindow extends JFrame implements ActionListener {

	public static final int WIDTH = 600;
	public static final int HEIGHT = 750;

	public HelpWindow() {

		super("Help");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new BorderLayout() );

		JTextArea textArea = new JTextArea(50, 50);
		textArea.setEditable(false);
		JScrollPane textPane = new JScrollPane( textArea );
		textPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		textPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

		add(textArea, BorderLayout.CENTER);

		JButton dispose = new JButton("Close");
		dispose.setPreferredSize( new Dimension(95, 45) );
		dispose.addActionListener(this);
		
		add(dispose, BorderLayout.SOUTH);

		String content = new String();
		Scanner input = null;
		try {
			input = new Scanner( new FileInputStream("README"));
		} catch (FileNotFoundException e) {}

		while ( input.hasNextLine() ) {
			content = content + input.nextLine() + "\n"; //reading file contents into a String
		}

		textArea.setText(content);
	}

	public void actionPerformed( ActionEvent e ) {
		dispose();
	}

	public static void main(String[] args) {
	 	HelpWindow test = new HelpWindow();
		test.setVisible(true);
	} 
}
