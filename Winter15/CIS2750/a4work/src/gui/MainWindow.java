

import java.awt.*;
import javax.swing.*;
import java.lang.Integer;
import java.lang.NullPointerException;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;

/**
 * program's main JFrame
 * @author Jeffrey-David Kapp
 * @since 10 Feb 2015
 *
*/

public class MainWindow extends JFrame implements DocumentListener {

	public static final int WIDTH = 750;
	public static final int HEIGHT = 865;

	protected JTextArea textArea;
	protected JLabel textLabel;
	protected JLabel modifiedStatus;
	private Dialogc mainProg;

	public MainWindow( Dialogc mainProg	) {
		super("Dialogc");
		this.mainProg = mainProg;
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		addWindowListener(new CheckOnExit());
		setBackground(Color.LIGHT_GRAY);

		setLayout(new BorderLayout());
 
		//text area
		textArea = new JTextArea(53, 50);
		textArea.setEditable(true);
		textArea.getDocument().addDocumentListener(this);
		JScrollPane textPane = new JScrollPane( textArea );
		JPanel textPanel = new JPanel();
		textPanel.setLayout( new BorderLayout() );

		textLabel = new JLabel("new file");
		textPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		textPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		textPanel.add(textLabel, BorderLayout.NORTH);
		textPanel.add(textPane, BorderLayout.CENTER);

		add(textPanel, BorderLayout.CENTER);
		//end; text area

		//modified status bar
		modifiedStatus = new JLabel("new file");
		add(modifiedStatus, BorderLayout.SOUTH);
		//end; modified status bar

		//menu bar
		DialogcJMenuBar menuBar = new DialogcJMenuBar(new Dialogc());
		setJMenuBar( menuBar );
		//end; menu bar

		//button bar
		ButtonBar buttonBar = new ButtonBar(new Dialogc());
		add(buttonBar, BorderLayout.NORTH);
		//end; button bar
	}

	/**
	 * Updates status to indicate the file has been modded
	*/
	public void statusModded() {
		mainProg.project.modified = true;
		modifiedStatus.setText(mainProg.project.getFileName() + " (modified)");
	}

	public void statusUnmodded() {
		mainProg.project.modified = false;
		modifiedStatus.setText(mainProg.project.getFileName());
 	}
	public void insertUpdate(DocumentEvent e) {
		statusModded();
	}

	public void removeUpdate(DocumentEvent e) {
		statusModded();
	}

	public void changedUpdate(DocumentEvent e) {
		statusModded();
	}

	private class CheckOnExit implements WindowListener {

		public void windowClosing( WindowEvent e ) {
			ExitMenu exitMenu = new ExitMenu( new Dialogc() );
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
