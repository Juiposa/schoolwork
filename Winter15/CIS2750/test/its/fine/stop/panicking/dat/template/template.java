package exampleConfig;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.lang.IllegalArgumentException;

public class exampleConfig extends JFrame implements ActionListener {

	private JTextArea field;
	private JButton button;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 1;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public exampleConfig() {
		super("windowName");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//field
		JPanel fieldPanel = new JPanel();
		fieldPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		field = new JTextArea( 1, 35 );
		JLabel fieldLabel = new JLabel("field");
		fieldPanel.add(fieldLabel);
		fieldPanel.add(field);
		//end field

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
		
		//button
		button = new JButton("button");
		button.setPreferredSize(new Dimension(85 ,30));
		button.addActionListener(this);
		//end button

		buttonPanel.add(button);
		//end button panel

		fieldAndButtonPanel.add(fieldPanel);
		fieldAndButtonPanel.add(buttonPanel);
		//end field and button panel

		//text area
		textArea = new JTextArea(20, 50);
		textArea.setEditable(false);
		JScrollPane textPane = new JScrollPane( textArea );
		JPanel textPanel = new JPanel();
		textPanel.setLayout( new BorderLayout() );

		JLabel textLabel = new JLabel("STATUS");
		textPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		textPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		textPanel.add(textLabel, BorderLayout.NORTH);
		textPanel.add(textPane, BorderLayout.CENTER);

		textPanel.add(textLabel);
		textPanel.add(textPane);
		//end text area

		add(fieldAndButtonPanel);
		add(textPanel);
	}

	public void setDCfield( String instring ) {
		field.setText(instring);
	}

	public String getDCfield() {
		try {
			float d = Float.parseFloat(field.getText());
		} catch ( NumberFormatExecption e ) {
			throw IllegalFieldValueExecption(field.getText());
		}
		return new String(field.getText());
	}

	public void appendToStatusArea( String instring ) {
		String curContent = textArea.getText();
		curContent += (instring + "\n");
		textArea.setText(curContent);
	}

	public void actionPerformed( ActionEvent e ) {
		appendToStatusArea(e.getActionCommand() + " button pressed");
	}

	public static void main( String[] args ) {
		exampleConfig example = new exampleConfig();
		example.setVisible(true);
	}
}
