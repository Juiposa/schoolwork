package gui;

import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * project class, managing file access, contents, compilation and modified status
 * @author Jeffrey-David Kapp
 * @since 10 Feb 2015
*/

public class Project {

	private String projectName = "new project";
	private String filePath;
	private String fileName = "new file";
	private File file = null;
	protected PrintWriter output;
	protected Scanner input;
	protected Boolean modified = false;

	public void setProjectName() {
		this.projectName = new StringTokenizer( new String(fileName), "." ).nextToken();
	}

	public String getProjectName() {
		return new String(projectName);
	}

	public void setFilePath( String filePath ) {
		this.filePath = new String( filePath ); 
	}

	public String getFilePath() {
		return new String(filePath);
	}

	public void setFile( File file ) {
		filePath = new String(file.getPath());
		this.file = file;
		fileName = file.getName();
		setProjectName();
	}

	public File getFile() {
		return file;
	}

	public void setFileName( String fileName ) {
		this.fileName = new String(fileName);
	} 

	public String getFileName() {
		return new String(fileName);
	}

	public void openInput() {
		try {
			input = new Scanner( new FileInputStream(filePath) );
		} catch ( FileNotFoundException e ) {
			System.out.println("File Error: " + e.getMessage() );
		}
	}

	public void openOutput() {
		try {
			output = new PrintWriter( new FileOutputStream(filePath) );
		} catch ( FileNotFoundException e ) {
			System.out.println("File Error: " + e.getMessage() );
		}
	}
}
