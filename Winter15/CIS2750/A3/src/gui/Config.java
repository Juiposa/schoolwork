package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Dialogc configuration
 * @author Jeffrey-David Kapp
 * @since 13 Mar 2015
*/

public class Config implements ActionListener {
	protected String compiler; //file path to the java compiler
	protected String compilerOptions; //arguments to the compiler
	protected String runtime; //file path to jvm being used, or some alternative
	protected String runtimeOptions; //arguments to the jvm
	protected String workingDirectory; //directory compiled java code is put into
	protected int selectedParser = 0;
	private ConfigWindow configWindow;

	public Config( Scanner inputStream ) { //config file input
		configWindow = new ConfigWindow(this);
		compiler = inputStream.nextLine();
		compilerOptions = inputStream.nextLine();
		runtime = inputStream.nextLine();
		runtimeOptions = inputStream.nextLine();
		workingDirectory = inputStream.nextLine();
		inputStream.close();
		setupWindow();
	}

	public Config() {
		configWindow = new ConfigWindow(this);
		compiler = "javac";
		compilerOptions = "";
		runtime = "java";
		runtimeOptions = "";
		workingDirectory = ".";
		setupWindow();
	}

	public void display() {
		configWindow.setVisible(true);
	}

	public void save() {
		PrintWriter writer = null;
		try {
			writer = new PrintWriter( new FileOutputStream( "dat/dialogc.config") );
		} catch( FileNotFoundException e ) {
			//NOOP; it creates the file if it doesn't find in anyway, jeez
		}
		writer.println(compiler);
		writer.println(compilerOptions);
		writer.println(runtime);
		writer.println(runtimeOptions);
		writer.print(workingDirectory);
		writer.close();
		System.out.println("Config saved to file");
	}

	private void setupWindow() {
		configWindow.setCompiler(compiler);
		configWindow.setCompilerOptions(compilerOptions);
		configWindow.setRuntime(runtime);
		configWindow.setRuntimeOptions(runtimeOptions);
		configWindow.setWorkingDirectory(workingDirectory);
	}

	public void actionPerformed( ActionEvent e ) {
		String command = e.getActionCommand();
		if ( command.equals("Save") ) { //save fields to config
			compiler = configWindow.getCompiler();
			compilerOptions = configWindow.getCompilerOptions();
			runtime = configWindow.getRuntime();
			runtimeOptions = configWindow.getRuntimeOptions();
			workingDirectory = configWindow.getWorkingDirectory();
			configWindow.dispose();
			System.out.println("Config saved"); //debug output to terminal
		} else if ( command.equals("Cancel") ) {
			setupWindow(); //restoring window fields to match config 
			configWindow.dispose();
			System.out.println("Config canceled"); //debug output to terminal
		} else if ( command.equals("yadc") ) {
			selectedParser = 0;
		} else if ( command.equals("Dialogc") ) {
			selectedParser = 1;
		}
	}

	public static void main(String[] args) {
		Config testConfig = new Config();
		testConfig.display();
	}
}