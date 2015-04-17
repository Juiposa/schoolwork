

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * button bar for common actions
 * @author Jeffrey-David Kapp
 * @since 9 Feb 2015
*/

public class ButtonBar extends JPanel {
	public ButtonBar( ActionListener listener ) {
		setLayout( new FlowLayout( FlowLayout.LEFT, 3, 3 ));

		DialogcJButton newFile = new DialogcJButton("New", 26, 26, new ImageIcon("../dat/icons/New24.gif"), listener );
		DialogcJButton openFile = new DialogcJButton("Open", 26, 26, new ImageIcon("../dat/icons/Open24.gif"), listener  );
		DialogcJButton saveFile = new DialogcJButton("Save", 26, 26, new ImageIcon("../dat/icons/Save24.gif"), listener );
		DialogcJButton saveAsFile = new DialogcJButton("Save As", 26, 26, new ImageIcon("../dat/icons/SaveAs24.gif"), listener );
		DialogcJButton compile = new DialogcJButton("Compile", 26, 26, new ImageIcon("../dat/icons/Refresh24.gif"), listener );
		DialogcJButton run = new DialogcJButton("Run", 26, 26, new ImageIcon("../dat/icons/Play24.gif"), listener );
		DialogcJButton stop = new DialogcJButton("Stop", 26, 26, new ImageIcon("../dat/icons/Stop24.gif"), listener  );

		add(newFile);
		add(openFile);
		add(saveFile);
		add(saveAsFile);
		add(compile);
		add(run);
		add(stop);
	}
}