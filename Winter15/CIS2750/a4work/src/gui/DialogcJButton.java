

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * JButton with expanded constructor to keep code brief when setting up ButtonBar
 * @author Jeffrey-David Kapp
 * @since 9 Feb 2015
*/

public class DialogcJButton extends JButton{
	public DialogcJButton( String name, int width, int height, ImageIcon icon, ActionListener listener ) {
		super(name, icon);
		setText("");
		setActionCommand(name);
		setPreferredSize(new Dimension( width, height ));
		addActionListener(listener);
	}
}