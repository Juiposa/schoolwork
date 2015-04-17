import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.lang.NumberFormatException;
import java.lang.Integer;
import java.lang.Float;
import java.lang.Boolean;

public class test1FieldEdit extends JFrame implements ActionListener {

	private JTextArea String1;
	private JTextArea Float1;
	private JTextArea Integer1;
	private JButton Get;
	private JButton Set;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 3;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public test1FieldEdit() {

		super("test1");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//String1
		JPanel String1Panel = new JPanel();
		String1Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		String1 = new JTextArea( 1, 25 );
		JLabel String1Label = new JLabel("String1");
		String1Panel.add(String1Label);
		String1Panel.add(String1);
		//end String1

		//Float1
		JPanel Float1Panel = new JPanel();
		Float1Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		Float1 = new JTextArea( 1, 25 );
		JLabel Float1Label = new JLabel("Float1");
		Float1Panel.add(Float1Label);
		Float1Panel.add(Float1);
		//end Float1

		//Integer1
		JPanel Integer1Panel = new JPanel();
		Integer1Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		Integer1 = new JTextArea( 1, 25 );
		JLabel Integer1Label = new JLabel("Integer1");
		Integer1Panel.add(Integer1Label);
		Integer1Panel.add(Integer1);
		//end Integer1

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

		//Get
		Get = new JButton("Get");
		Get.setPreferredSize(new Dimension(85 ,30));
		Get.addActionListener(new test1Get(this));
		//end Get

		//Set
		Set = new JButton("Set");
		Set.setPreferredSize(new Dimension(85 ,30));
		Set.addActionListener(new test1Set(this));
		//end Set

		buttonPanel.add(Get);
		buttonPanel.add(Set);
		//end button panel

		fieldAndButtonPanel.add(String1Panel);
		fieldAndButtonPanel.add(Float1Panel);
		fieldAndButtonPanel.add(Integer1Panel);
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
	public void setDCString1( String instring ) {
		String1.setText(instring);
	}

	public String getDCString1() {
		return new String(String1.getText());
	}

	public void setDCFloat1( String instring ) {
		Float1.setText(instring);
	}

	public float getDCFloat1() throws IllegalFieldValueException {
		float f;
		try {
			f = Float.parseFloat(Float1.getText());
		} catch ( NumberFormatException e ) {
			throw new IllegalFieldValueException(Float1.getText());
		}
		return f;
	}

	public void setDCInteger1( String instring ) {
		Integer1.setText(instring);
	}

	public int getDCInteger1() throws IllegalFieldValueException {
		int i;
		try {
			i = Integer.parseInt(Integer1.getText());
		} catch ( NumberFormatException e ) {
			throw new IllegalFieldValueException(Integer1.getText());
		}
		return i;
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
		test1FieldEdit runWindow = new test1FieldEdit();
		runWindow.setVisible(true);
	}
}