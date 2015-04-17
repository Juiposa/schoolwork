

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.*;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
import java.awt.event.WindowEvent;

/**
 * Main class
 * @author Jeffrey-David Kapp
 * @since 3 April 2015
*/

public class Dialogc implements ActionListener {

	static private JFileChooser fileChooser;
	static protected Project project;
	static private MainWindow mainWindow;
	static private Config config = null;
	static private String content;
	static private Dialogc mainProg;
	static private HelpWindow help;
	static private AboutWindow about;
	static private Process buildProcess;

	static { System.loadLibrary("compiler");}

	native static int compile(String fileName, String workingDirectroy, String projectName);

	/**
	 * Saves file to disk
	*/
	private void saveFile() {
		project.openOutput(); //opening output stream!
		project.output.print(mainWindow.textArea.getText()); //print that stuff to the file!
		mainWindow.statusUnmodded(); //no longer modifeid!
		System.out.println("Saved as:" + project.getFilePath()); //debug output to the terminal!
		project.output.close(); //close that file stream!
		//saving files is so exciting :D
	}


	/**
	 * function that calls compiler, saves file and sets up project variables
	 * @return true on success, false otherwise
	*/
	private Boolean compileJ() {
		if ( project.getFile() == null ) { //new project, aka not yet saved
			if(JFileChooser.APPROVE_OPTION == fileChooser.showSaveDialog(mainWindow)) { //choosing file to creating a new one
				project.setFile(fileChooser.getSelectedFile()); //set prjects file to that
				saveFile(); //save away buddy
				System.out.println("Compilation started");

				if (1 == config.selectedParser && 0 == compile( project.getFilePath(), config.workingDirectory, project.getProjectName() )) //internal
					return false;
				else { //yadc
					try {
						System.out.println("./yadc " + project.getFilePath() + " " + config.workingDirectory + " " + project.getProjectName());
						buildProcess = Runtime.getRuntime().exec( "./yadc " + project.getFilePath() + " " + config.workingDirectory + " " + project.getProjectName() );	
						buildProcess.waitFor();
					} catch ( Exception e ) {
						e.printStackTrace();
					}
					if( buildProcess.exitValue() == 0 ) {
						return false;
					}
				}
			} else {
				System.out.println("Save canceled - not compiling");
				return false;
			}
		} else {
			saveFile(); //else we already have a file we're workign with, save it buddy
			System.out.println("\nCompilation started****");
			if (1 == config.selectedParser && 0 == compile( project.getFilePath(), config.workingDirectory, project.getProjectName() )) //internal
				return false;
			else {
				try { //yadc
					System.out.println("./yadc " + project.getFilePath() + " " + config.workingDirectory + " " + project.getProjectName());
					buildProcess = Runtime.getRuntime().exec( "./yadc " + project.getFilePath() + " " + config.workingDirectory + " " + project.getProjectName() );	
					buildProcess.waitFor();
				} catch ( Exception e ) {
					e.printStackTrace();
				}
				if( buildProcess.exitValue() == 0 ) {
					return false;
				}
			}
		}
		try {
			System.out.println("/usr/bin/make -C " + config.workingDirectory + "/" + project.getProjectName());
			buildProcess = Runtime.getRuntime().exec("/usr/bin/make -C " + config.workingDirectory + "/" + project.getProjectName());
			buildProcess.waitFor();
		} catch ( Exception e ) {
			e.printStackTrace();
		}
		return true;
	}

	/**
	 * Running compiled java code
	*/
	private void run() {
		try {
			System.out.println(config.runtime + " " + config.runtimeOptions + " -cp " + config.workingDirectory + "/" + project.getProjectName() + " " + project.getProjectName() + "FieldEdit");
			buildProcess = Runtime.getRuntime().exec(config.runtime + " " + config.runtimeOptions + " -cp " + config.workingDirectory + "/" + project.getProjectName() + " " + project.getProjectName() + "FieldEdit");
		} catch ( Exception e ) {
			e.printStackTrace();
		}
	}

	/**
	 * Handles action events for buttons and menus
	*/
	public void actionPerformed( ActionEvent e ) {
		String command = e.getActionCommand();
		if ( command.equals("ForceExit") ) { //forced exit
			config.save(); //save our IDE configuration
			System.exit(0);
		} else if ( command.equals("Exit") ) {
			if ( project.modified == true ) { //if the file has been changed
				SaveOnExit savePrompt = new SaveOnExit(mainProg); //confirm with user
				savePrompt.setVisible(true);
			} else { 
				ExitMenu exitPrompt = new ExitMenu(mainProg); //else the usual confirmation window
				exitPrompt.setVisible(true);
			}
		} else if ( command.equals("New") ) {
			if ( project.modified == true ) { //if the file has been changed
				SavePrompt savePrompt = new SavePrompt(mainProg); //confirm with user
				savePrompt.setVisible(true);
			}
			project = new Project(); //new prpject
			mainWindow.textLabel.setText("new file");
			mainWindow.textArea.setText("");
			mainWindow.statusUnmodded();
		} else if ( command.equals("Save") ) { //saving file
			if ( project.getFile() == null ) { //new project, aka not yet saved
				if(JFileChooser.APPROVE_OPTION == fileChooser.showSaveDialog(mainWindow)) { //choosing file to creating a new one
					project.setFile(fileChooser.getSelectedFile()); //set prjects file to that
					saveFile(); //save away buddy
				}
			} else {
				saveFile(); //else we already have a file we're workign with, save it buddy
			}
		} else if ( command.equals("Save As") ) { //save as
			if (JFileChooser.APPROVE_OPTION == fileChooser.showSaveDialog(mainWindow)) {
				project.setFile(fileChooser.getSelectedFile());
				saveFile();
			}
		} else if ( command.equals("Open") ) { //opening file and outputting to window
			if ( project.modified == true ) { //if the file has been changed
				SavePrompt savePrompt = new SavePrompt(mainProg); //confirm with user
				savePrompt.setVisible(true);
			}
			if(JFileChooser.APPROVE_OPTION == fileChooser.showOpenDialog(mainWindow)) {
				project.setFile(fileChooser.getSelectedFile()); //setting user selected file
				project.openInput(); //opening in stream
				content = ""; //reseting value of contents
				System.out.println("Opened: " + project.getFile().getPath()); //debug output to terminal
				while ( project.input.hasNextLine() ) {
					content = content + project.input.nextLine() + "\n"; //reading file contents into a String
				}
				mainWindow.textLabel.setText(project.getProjectName()); //push filename to lable
				mainWindow.textArea.setText(content); //add contents to text area
				mainWindow.statusUnmodded(); //file is unmodified by defult
				project.input.close(); //close input stream
			} 
		} else if ( command.equals("Compile") ) {
			if (!compileJ()) {
				PopupWindow err = new PopupWindow("Error", "Error - see terminal");
				err.setVisible(true);
			} else {
				PopupWindow suc = new PopupWindow("Success", "Compilation successful");
				suc.setVisible(true);
			}
		} else if ( command.equals("Run") ) {
			run();
		} else if ( command.equals("Compile and Run") ) {
			if (!compileJ()) {
				PopupWindow err = new PopupWindow("Error", "Error - see terminal");
				err.setVisible(true);
			} else {
				PopupWindow suc = new PopupWindow("Success", "Compilation successful");
				suc.setVisible(true);
				run();
			}
		} else if ( command.equals("Stop") ) {
			buildProcess.destroy();			
		} else if ( command.equals("Config") ) {
			System.out.println("Configuration Menu"); //debug output to terminal
			config.display();
		} else if ( command.equals("Help")) {
			System.out.println("Help Window"); //debug output to terminal
			help.setVisible(true);
		} else if ( command.equals("About")) {
			System.out.println("About Window"); //you get it now
			about.setVisible(true);
		}
	}

	public static void main( String[] args ) {
		mainProg = new Dialogc();
		fileChooser = new JFileChooser();
		project = new Project();
		mainWindow = new MainWindow(mainProg);
		content = new String();
		help = new HelpWindow();
		about = new AboutWindow();
		Scanner configInput = null;
		try {
			configInput = new Scanner( new FileInputStream( "../dat/dialogc.config") );
		} catch( FileNotFoundException e ) {
			config = new Config();
		}
		if ( config == null && configInput != null ) {
			config = new Config(configInput);
		}
		mainWindow.setVisible(true);
	}
}
