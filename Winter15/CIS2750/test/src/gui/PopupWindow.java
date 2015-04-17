
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Simple popup with dynamic error
 * Reused code from CIS2430
 * @author Jeff Kapp 0832671
 * @since 9 Mar 2015
 *
*/

public class PopupWindow extends JFrame implements ActionListener {

	public static final int WIDTH = 250;
	public static final int HEIGHT = 200;
	
	public PopupWindow( String title, String message ) {
		super(title);
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		setLayout( new GridLayout( 2, 1) );

		JLabel windowMessage = new JLabel( message );
		windowMessage.setHorizontalAlignment(JLabel.CENTER);
		add( windowMessage );
		JButton okayButton = new JButton("Okay");
		okayButton.addActionListener(this);
		add(okayButton);
	}

	public void actionPerformed( ActionEvent e ) {
		dispose();
	}
}