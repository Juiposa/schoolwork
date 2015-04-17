package testP1;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class testP1 extends JFrame implements ActionListener {

	private JTextArea Name;
	private JTextArea sID;
	private JTextArea A1;
	private JTextArea A2;
	private JTextArea A3;
	private JTextArea A4;
	private JButton Add;
	private JButton Update;
	private JButton Delete;
	private JButton Query;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 6;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public testP1() {

		super("testPro1");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//Name
		JPanel NamePanel = new JPanel();
		NamePanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		Name = new JTextArea( 1, 25 );
		JLabel NameLabel = new JLabel("Name");
		NamePanel.add(NameLabel);
		NamePanel.add(Name);
		//end Name

		//sID
		JPanel sIDPanel = new JPanel();
		sIDPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		sID = new JTextArea( 1, 25 );
		JLabel sIDLabel = new JLabel("sID");
		sIDPanel.add(sIDLabel);
		sIDPanel.add(sID);
		//end sID

		//A1
		JPanel A1Panel = new JPanel();
		A1Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		A1 = new JTextArea( 1, 25 );
		JLabel A1Label = new JLabel("A1");
		A1Panel.add(A1Label);
		A1Panel.add(A1);
		//end A1

		//A2
		JPanel A2Panel = new JPanel();
		A2Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		A2 = new JTextArea( 1, 25 );
		JLabel A2Label = new JLabel("A2");
		A2Panel.add(A2Label);
		A2Panel.add(A2);
		//end A2

		//A3
		JPanel A3Panel = new JPanel();
		A3Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		A3 = new JTextArea( 1, 25 );
		JLabel A3Label = new JLabel("A3");
		A3Panel.add(A3Label);
		A3Panel.add(A3);
		//end A3

		//A4
		JPanel A4Panel = new JPanel();
		A4Panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		A4 = new JTextArea( 1, 25 );
		JLabel A4Label = new JLabel("A4");
		A4Panel.add(A4Label);
		A4Panel.add(A4);
		//end A4

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

		//Add
		Add = new JButton("Add");
		Add.setPreferredSize(new Dimension(85 ,30));
		Add.addActionListener(this);
		//end Add

		//Update
		Update = new JButton("Update");
		Update.setPreferredSize(new Dimension(85 ,30));
		Update.addActionListener(this);
		//end Update

		//Delete
		Delete = new JButton("Delete");
		Delete.setPreferredSize(new Dimension(85 ,30));
		Delete.addActionListener(this);
		//end Delete

		//Query
		Query = new JButton("Query");
		Query.setPreferredSize(new Dimension(85 ,30));
		Query.addActionListener(this);
		//end Query

		buttonPanel.add(Add);
		buttonPanel.add(Update);
		buttonPanel.add(Delete);
		buttonPanel.add(Query);
		//end button panel

		fieldAndButtonPanel.add(NamePanel);
		fieldAndButtonPanel.add(sIDPanel);
		fieldAndButtonPanel.add(A1Panel);
		fieldAndButtonPanel.add(A2Panel);
		fieldAndButtonPanel.add(A3Panel);
		fieldAndButtonPanel.add(A4Panel);
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
	public void setDCName( String instring ) {
		Name.setText(instring);
	}

	public String getDCName() {
		return new String(Name.getText());
	}

	public void setDCsID( String instring ) {
		sID.setText(instring);
	}

	public String getDCsID() {
		return new String(sID.getText());
	}

	public void setDCA1( String instring ) {
		A1.setText(instring);
	}

	public String getDCA1() {
		return new String(A1.getText());
	}

	public void setDCA2( String instring ) {
		A2.setText(instring);
	}

	public String getDCA2() {
		return new String(A2.getText());
	}

	public void setDCA3( String instring ) {
		A3.setText(instring);
	}

	public String getDCA3() {
		return new String(A3.getText());
	}

	public void setDCA4( String instring ) {
		A4.setText(instring);
	}

	public String getDCA4() {
		return new String(A4.getText());
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
		testP1 runWindow = new testP1();
		runWindow.setVisible(true);
	}
}