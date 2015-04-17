package gui;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * menu bar for all actions offered by Dialogc
 * @author Jeffrey-David Kapp
 * @since 12 Feb 2014
*/

public class DialogcJMenuBar extends JMenuBar {
	public DialogcJMenuBar( ActionListener listener ) {
		//file menu
		JMenu fileMenu = new JMenu("File");
		JMenuItem newFile = new JMenuItem("New");
		JMenuItem openFile = new JMenuItem("Open");
		JMenuItem saveFile = new JMenuItem("Save");
		JMenuItem saveAsFile = new JMenuItem("Save As");
		JMenuItem exitFile = new JMenuItem("Exit"); //I know the spec says 'Quit', but I'm too lazy to edit my reused code 

		//set actions listeners
		newFile.addActionListener(listener);
		openFile.addActionListener(listener);
		saveFile.addActionListener(listener);
		saveAsFile.addActionListener(listener);
		exitFile.addActionListener(listener);

		fileMenu.add(newFile);
		fileMenu.add(openFile);
		fileMenu.add(saveFile);
		fileMenu.add(saveAsFile);
		fileMenu.add(exitFile);
		//end; file menu

		//compile menu
		JMenu compileMenu = new JMenu("Compile");
		JMenuItem compileCompile = new JMenuItem("Compile");
		JMenuItem compileRunCompile = new JMenuItem("Compile and Run");

		compileRunCompile.addActionListener(listener);
		compileCompile.addActionListener(listener);

		compileMenu.add(compileCompile);
		compileMenu.add(compileRunCompile);
		//end; compile menu

		//config menu
		JMenu configMenu = new JMenu("Config");
		JMenuItem configButton = new JMenuItem("Config");
		configButton.addActionListener(listener);
		configMenu.add(configButton);
		//end; config menu

		//help menu
		JMenu helpMenu = new JMenu("Help");
		JMenuItem helpHelp = new JMenuItem("Help");
		JMenuItem aboutHelp = new JMenuItem("About");

		helpHelp.addActionListener(listener);
		aboutHelp.addActionListener(listener);

		helpMenu.add(helpHelp);
		helpMenu.add(aboutHelp);
		//end; help menu

		add(fileMenu);
		add(compileMenu);
		add(configMenu);
		add(helpMenu);
		//end menu bar
	}
}