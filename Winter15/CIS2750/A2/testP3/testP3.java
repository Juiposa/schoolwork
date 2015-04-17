package testP3;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class testP3 extends JFrame implements ActionListener {

	private JTextArea F_Name;
	private JTextArea L_Name;
	private JButton Add;
	private JButton Clean;
	private JButton Submit;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 2;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public testP3() {

		super("testPro3");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//F_Name
		JPanel F_NamePanel = new JPanel();
		F_NamePanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		F_Name = new JTextArea( 1, 25 );
		JLabel F_NameLabel = new JLabel("F_Name");
		F_NamePanel.add(F_NameLabel);
		F_NamePanel.add(F_Name);
		//end F_Name

		//L_Name
		JPanel L_NamePanel = new JPanel();
		L_NamePanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		L_Name = new JTextArea( 1, 25 );
		JLabel L_NameLabel = new JLabel("L_Name");
		L_NamePanel.add(L_NameLabel);
		L_NamePanel.add(L_Name);
		//end L_Name

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

		//Add
		Add = new JButton("Add");
		Add.setPreferredSize(new Dimension(85 ,30));
		Add.addActionListener(this);
		//end Add

		//Clean
		Clean = new JButton("Clean");
		Clean.setPreferredSize(new Dimension(85 ,30));
		Clean.addActionListener(this);
		//end Clean

		//Submit
		Submit = new JButton("Submit");
		Submit.setPreferredSize(new Dimension(85 ,30));
		Submit.addActionListener(this);
		//end Submit

		buttonPanel.add(Add);
		buttonPanel.add(Clean);
		buttonPanel.add(Submit);
		//end button panel

		fieldAndButtonPanel.add(F_NamePanel);
		fieldAndButtonPanel.add(L_NamePanel);
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
	public void setDCF_Name( String instring ) {
		F_Name.setText(instring);
	}

	public String getDCF_Name() {
		return new String(F_Name.getText());
	}

	public void setDCL_Name( String instring ) {
		L_Name.setText(instring);
	}

	public String getDCL_Name() {
		return new String(L_Name.getText());
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
		testP3 runWindow = new testP3();
		runWindow.setVisible(true);
	}
}