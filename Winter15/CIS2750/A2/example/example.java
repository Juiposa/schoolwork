package example;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class example extends JFrame implements ActionListener {

	private JTextArea W;
	private JTextArea E;
	private JTextArea R;
	private JButton Thresh;
	private JButton Leblanc;
	private JButton Lucian;
	private JButton Vi;
	private JTextArea textArea;

	private static final int NUM_FIELDS = 3;
	private static final int WIDTH = 450;
	private static final int HEIGHT = 250+(NUM_FIELDS*75);

	public example() {

		super("ChampionTime");
		setLayout(new GridLayout( 2, 1 ));
		setSize(WIDTH,HEIGHT);

		//field and button panel
		JPanel fieldAndButtonPanel =  new JPanel();
		fieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));

		//W
		JPanel WPanel = new JPanel();
		WPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		W = new JTextArea( 1, 25 );
		JLabel WLabel = new JLabel("W");
		WPanel.add(WLabel);
		WPanel.add(W);
		//end W

		//E
		JPanel EPanel = new JPanel();
		EPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		E = new JTextArea( 1, 25 );
		JLabel ELabel = new JLabel("E");
		EPanel.add(ELabel);
		EPanel.add(E);
		//end E

		//R
		JPanel RPanel = new JPanel();
		RPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
		R = new JTextArea( 1, 25 );
		JLabel RLabel = new JLabel("R");
		RPanel.add(RLabel);
		RPanel.add(R);
		//end R

		//button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

		//Thresh
		Thresh = new JButton("Thresh");
		Thresh.setPreferredSize(new Dimension(85 ,30));
		Thresh.addActionListener(this);
		//end Thresh

		//Leblanc
		Leblanc = new JButton("Leblanc");
		Leblanc.setPreferredSize(new Dimension(85 ,30));
		Leblanc.addActionListener(this);
		//end Leblanc

		//Lucian
		Lucian = new JButton("Lucian");
		Lucian.setPreferredSize(new Dimension(85 ,30));
		Lucian.addActionListener(this);
		//end Lucian

		//Vi
		Vi = new JButton("Vi");
		Vi.setPreferredSize(new Dimension(85 ,30));
		Vi.addActionListener(this);
		//end Vi

		buttonPanel.add(Thresh);
		buttonPanel.add(Leblanc);
		buttonPanel.add(Lucian);
		buttonPanel.add(Vi);
		//end button panel

		fieldAndButtonPanel.add(WPanel);
		fieldAndButtonPanel.add(EPanel);
		fieldAndButtonPanel.add(RPanel);
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
	public void setDCW( String instring ) {
		W.setText(instring);
	}

	public String getDCW() {
		return new String(W.getText());
	}

	public void setDCE( String instring ) {
		E.setText(instring);
	}

	public String getDCE() {
		return new String(E.getText());
	}

	public void setDCR( String instring ) {
		R.setText(instring);
	}

	public String getDCR() {
		return new String(R.getText());
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
		example runWindow = new example();
		runWindow.setVisible(true);
	}
}