import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.lang.NumberFormatException;
import java.lang.Integer;
import java.lang.Float;
import java.lang.Boolean;

public class test2FieldEdit extends JFrame implements ActionListener {

	private JTextArea DefaultField;
	private JButton Click;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 1;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public test2FieldEdit() {

		super("test2");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//DefaultField
		JPanel DefaultFieldPanel = new JPanel();
		DefaultFieldPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		DefaultField = new JTextArea( 1, 25 );
		JLabel DefaultFieldLabel = new JLabel("DefaultField");
		DefaultFieldPanel.add(DefaultFieldLabel);
		DefaultFieldPanel.add(DefaultField);
		//end DefaultField

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

		//Click
		Click = new JButton("Click");
		Click.setPreferredSize(new Dimension(85 ,30));
		Click.addActionListener(new test2Click(this));
		//end Click

		buttonPanel.add(Click);
		//end button panel

		fieldAndButtonPanel.add(DefaultFieldPanel);
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

	//accessors and mutators
	public void setDCDefaultField( String instring ) {
		DefaultField.setText(instring);
	}

	public String getDCDefaultField() {
		return new String(DefaultField.getText());
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
		test2FieldEdit runWindow = new test2FieldEdit();
		runWindow.setVisible(true);
	}
}