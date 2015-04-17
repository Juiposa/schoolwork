package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Config Window
 * @author Jeffrey-David Kapp
 * @since 11 Feb 2015
*/

public class ConfigWindow extends JFrame implements ActionListener {

	private JTextArea compilerField;
	private JTextArea compilerOptionsField;
	private JTextArea runtimeField;
	private JTextArea runtimeOptionsField;
	private JTextArea workingDirectoryField;
	private JFileChooser configFileChooser;

	private static final int HEIGHT = 450;
	private static final int WIDTH = 750;

	public ConfigWindow( ActionListener listener ) {
		super("Configuration");
		setSize(WIDTH, HEIGHT);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBackground(Color.LIGHT_GRAY);
		configFileChooser = new JFileChooser();

		setLayout(new GridLayout(6, 1));

		//compiler selection
		JPanel compilerPanel  = new JPanel();
		compilerPanel.setLayout( new FlowLayout( FlowLayout.LEFT, 10, 10));
		JLabel compilerLabel = new JLabel("Compiler: ");
		JButton compilerButton = new JButton("Browse");
		compilerButton.setActionCommand("BrowseCompiler");
		compilerButton.addActionListener(this);
		compilerField = new JTextArea(1, 50);
		compilerPanel.add(compilerLabel);
		compilerPanel.add(compilerField);
		compilerPanel.add(compilerButton);
		//end; compiler selection

		//compiler options
		JPanel compilerOptionsPanel  = new JPanel();
		compilerOptionsPanel.setLayout( new FlowLayout( FlowLayout.LEFT, 10, 10));
		JLabel compilerOptionsLabel = new JLabel("Compiler options: ");
		compilerOptionsField = new JTextArea(1, 50);
		compilerOptionsPanel.add(compilerOptionsLabel);
		compilerOptionsPanel.add(compilerOptionsField);
		//end; compiler options

		//runtime selection
		JPanel runtimePanel  = new JPanel();
		runtimePanel.setLayout( new FlowLayout( FlowLayout.LEFT, 10, 10));
		JLabel runtimeLabel = new JLabel("Runtime: ");
		JButton runtimeButton = new JButton("Browse");
		runtimeButton.setActionCommand("BrowseRumtime");
		runtimeButton.addActionListener(this);
		runtimeField = new JTextArea(1, 50);
		runtimePanel.add(runtimeLabel);
		runtimePanel.add(runtimeField);
		runtimePanel.add(runtimeButton);
		//end; runtime selection

		//runtime options
		JPanel runtimeOptionsPanel  = new JPanel();
		runtimeOptionsPanel.setLayout( new FlowLayout( FlowLayout.LEFT, 10, 10));
		JLabel runtimeOptionsLabel = new JLabel("Runtime options: ");
		runtimeOptionsField = new JTextArea(1, 50);
		runtimeOptionsPanel.add(runtimeOptionsLabel);
		runtimeOptionsPanel.add(runtimeOptionsField);
		//end; runtime options

		//working directory
		JPanel workingDirectoryPanel  = new JPanel();
		workingDirectoryPanel.setLayout( new FlowLayout( FlowLayout.LEFT, 10, 10));
		JLabel workingDirectoryLabel = new JLabel("Working directory: ");
		workingDirectoryField = new JTextArea(1, 50);
		workingDirectoryPanel.add(workingDirectoryLabel);
		workingDirectoryPanel.add(workingDirectoryField);
		//end; working directory

		//command buttons
		JPanel commandButtonPanel  = new JPanel();
		commandButtonPanel.setLayout( new FlowLayout( FlowLayout.CENTER, 10, 10));
		JButton saveButton = new JButton("Save");
		saveButton.addActionListener(listener);
		JButton cancelButton = new JButton("Cancel");
		cancelButton.addActionListener(listener);
		saveButton.setPreferredSize( new Dimension(95, 45) );
		cancelButton.setPreferredSize( new Dimension(95, 45) );
		commandButtonPanel.add(saveButton);
		commandButtonPanel.add(cancelButton);
		//end; command button panel

		add(compilerPanel);
		add(compilerOptionsPanel);
		add(runtimePanel);
		add(runtimeOptionsPanel);
		add(workingDirectoryPanel);
		add(commandButtonPanel);
	}

	//boring accessors and mutators
	public void setCompiler( String compiler ) {
		compilerField.setText(compiler);
	}

	public String getCompiler() {
		return new String(compilerField.getText());
	}

	public void setCompilerOptions( String compilerOptions ) {
		compilerOptionsField.setText(compilerOptions);
	}

	public String getCompilerOptions() {
		return new String(compilerOptionsField.getText());
	}

	public void setRuntime( String runtime ) {
		runtimeField.setText(runtime);
	}

	public String getRuntime() {
		return new String(runtimeField.getText());
	}

	public void setRuntimeOptions( String runtimeOptions ) {
		runtimeOptionsField.setText(runtimeOptions);
	}

	public String getRuntimeOptions() {
		return new String(runtimeOptionsField.getText());
	}

	public void setWorkingDirectory( String workingDirectory ) {
		workingDirectoryField.setText(workingDirectory);
	}

	public String getWorkingDirectory() {
		return new String(workingDirectoryField.getText());
	}

	public void actionPerformed( ActionEvent e ) {
		String command = e.getActionCommand();
		if ( command.equals("BrowseCompiler")) {
			if ( JFileChooser.APPROVE_OPTION == configFileChooser.showOpenDialog(compilerField) ) {
				compilerField.setText(configFileChooser.getSelectedFile().getPath());
			}
		} else if ( command.equals("BrowseRumtime")) {
			if ( JFileChooser.APPROVE_OPTION == configFileChooser.showOpenDialog(runtimeField) ) {
				runtimeField.setText(configFileChooser.getSelectedFile().getPath());
			}
		}
	}
}