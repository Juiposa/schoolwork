package asst3;

import java.awt.*;
import javax.swing.*;
import java.lang.Integer;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;

/**
 * program's main JFrame
 * @author Jeff Kapp 0832671
 * @since 27 Nov 2014
 *
*/

public class MainWindow extends JFrame implements ActionListener {

	public static final int WIDTH = 850;
	public static final int HEIGHT = 650;
	private DayPlanner activeDayPlanner;
	public AddMenu addMenu;
	public SearchMenu searchMenu;

	public MainWindow( DayPlanner dayplanner ) {
		super("Day Planner");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		addWindowListener(new CheckOnExit());
		setBackground(Color.LIGHT_GRAY);
		activeDayPlanner = dayplanner;

		addMenu = new AddMenu(dayplanner);
		searchMenu = new SearchMenu(dayplanner);

		//command menu
		JMenu commands = new JMenu("Commands");
		JMenuItem add = new JMenuItem("Add");
		JMenuItem search = new JMenuItem("Search");
		JMenuItem exit = new JMenuItem("Exit");

		add.addActionListener(this);
		search.addActionListener(this);
		exit.addActionListener(this);

		commands.add(add);
		commands.add(search);
		commands.add(exit);

		JMenuBar menuBar = new JMenuBar();
		menuBar.add(commands);
		setJMenuBar( menuBar );
		//end command menu
	}

	/**
	 * Displays interface for adding activities
	*/
	private void displayAdd() {
		getContentPane().removeAll();
		getContentPane().add(addMenu);
		getContentPane().validate();
		getContentPane().repaint();
	}

	/**
	 * Displays interface for searching activities
	*/
	private void displaySearch() {
		getContentPane().removeAll();
		getContentPane().add(searchMenu);
		getContentPane().validate();
		getContentPane().repaint();
	}
	public void actionPerformed( ActionEvent e ) {
		String command = e.getActionCommand();
		if ( command.equals("Add") ) {
			displayAdd();
		} else if ( command.equals("Search") ) {
			displaySearch();
		} else if ( command.equals("Exit") ) {
			ExitMenu exitMenu = new ExitMenu( activeDayPlanner );
			exitMenu.setVisible(true);
		}
	}

	private class CheckOnExit implements WindowListener {

		public void windowClosing( WindowEvent e ) {
			ExitMenu exitMenu = new ExitMenu( activeDayPlanner );
			exitMenu.setVisible(true);
		}

		public void windowOpened( WindowEvent e ) {}
		public void windowClosed( WindowEvent e ) {}
		public void windowIconified( WindowEvent e ) {}
		public void windowDeiconified( WindowEvent e ) {}
		public void windowActivated( WindowEvent e ) {}
		public void windowDeactivated( WindowEvent e ) {}
	}
}
