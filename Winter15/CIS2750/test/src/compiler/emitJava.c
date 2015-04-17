/*****************
Jeffrey-David Kapp
CIS2750
12 March 2015
Assignment 3
*****************/

#include "ParameterManager.h"
#include <unistd.h>
#include <sys/stat.h>

/* emitJava 
 * Emits java code to a file
 * Parameters:	tfb - title, fields, and buttons
 *				types - data types and action listeners
 *				fieldCount - number of fields
 *				buttonCount - number of buttons
 *				Cpn - projectName
 * Returns: nothing
*/
void emitJava( ParameterManager * tfb, ParameterManager * types, int fieldCount, int buttonCount, const char * Cpn ) {
	FILE * fp; //new or not new java file we are printing to; we dunno and it doesn't matter
	char * filename = malloc(sizeof(char)*100);
	char * curName = malloc(sizeof(char)*100);
	ParameterList * fields, * buttons;
	int i = 0;
	fields = PM_getValue( tfb, "fields").list_val;
	buttons = PM_getValue( tfb, "buttons").list_val;
	mkdir( Cpn, S_IRWXU ); //make the directory we need, it may fail, but only if directory already exists, in which case we dont care, we just need to to be there

	sprintf(filename, "%s/%sFieldEdit.java", Cpn, Cpn); //file we'll be opening, with its directory path
	fp = fopen(filename, "w");
	//TIME FOR THE FUN STUFF

	fputs("import java.awt.*;\nimport javax.swing.*;\nimport java.awt.event.ActionListener;\nimport java.awt.event.ActionEvent;\nimport java.lang.NumberFormatException;\n", fp);
	fputs("import java.lang.Integer;\nimport java.lang.Float;\nimport java.lang.Boolean;\n\n", fp);
	fprintf(fp, "public class %sFieldEdit extends JFrame implements ActionListener {\n\n", Cpn);

	for( i = 0; i < fieldCount; i++ ) {
		fprintf(fp, "\tprivate JTextArea %s;\n", PL_next(fields)  );
	}
	PL_reset(fields);

	for( i = 0; i < buttonCount; i++ ) {
		fprintf(fp, "\tprivate JButton %s;\n", PL_next(buttons) );
	}
	PL_reset(buttons);

	fputs("\tprivate JTextArea textArea;\n\n", fp);
	fprintf(fp, "\tprivate static final int NUM_FIELDS = %d;\n\tprivate static final int WIDTH = 450;\n\tprivate static final int HEIGHT = 250+(NUM_FIELDS*75);\n\n", fieldCount );
	fprintf(fp, "\tpublic %sFieldEdit() {\n\n", Cpn);

	fprintf(fp, "\t\tsuper(\"%s\");\n\t\tsetLayout(new GridLayout( 2, 1 ));\n\t\tsetSize(WIDTH,HEIGHT);\n\n", PM_getValue(tfb, "title").str_val );
	fputs("\t\t//field and button panel\n\t\tJPanel fieldAndButtonPanel =  new JPanel();\n\t\tfieldAndButtonPanel.setLayout( new GridLayout(NUM_FIELDS+1, 1));\n\n", fp);

	for( i = 0; i < fieldCount; i++ ) { //field building
		curName = PL_next(fields);
		fprintf(fp, "\t\t//%s\n", curName );
		fprintf(fp, "\t\tJPanel %sPanel = new JPanel();\n", curName);
		fprintf(fp, "\t\t%sPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));\n", curName);
		fprintf(fp, "\t\t%s = new JTextArea( 1, 25 );\n", curName);
		fprintf(fp, "\t\tJLabel %sLabel = new JLabel(\"%s\");\n", curName, curName);
		fprintf(fp, "\t\t%sPanel.add(%sLabel);\n", curName, curName);
		fprintf(fp, "\t\t%sPanel.add(%s);\n", curName, curName);
		fprintf(fp, "\t\t//end %s\n\n", curName);
	}
	PL_reset(fields);

	fputs("\t\t//button panel\n\t\tJPanel buttonPanel = new JPanel();\n\t\tbuttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));\n\n", fp);

	for( i = 0; i < buttonCount; i++ ) { //button building
		curName = PL_next(buttons);
		fprintf(fp, "\t\t//%s\n", curName);
		fprintf(fp, "\t\t%s = new JButton(\"%s\");\n", curName,curName);
		fprintf(fp, "\t\t%s.setPreferredSize(new Dimension(85 ,30));\n", curName);
		fprintf(fp, "\t\t%s.addActionListener(new %s(this));\n", curName, PM_getValue(types, curName).str_val );
		fprintf(fp, "\t\t//end %s\n\n", curName);
	}
	PL_reset(buttons);

	for( i = 0; i < buttonCount; i++ ) { //adding buttons to panel
		curName = PL_next(buttons);
		fprintf(fp, "\t\tbuttonPanel.add(%s);\n", curName );
	}
	PL_reset(buttons);
	fputs("\t\t//end button panel\n\n", fp);

	for( i = 0; i < fieldCount; i++ ) { //adding fields to main panel
		curName = PL_next(fields);
		fprintf(fp, "\t\tfieldAndButtonPanel.add(%sPanel);\n", curName);
	}
	PL_reset(fields);
	fputs("\t\tfieldAndButtonPanel.add(buttonPanel);\n\t\t//end field and button panel\n\n", fp );

	//status area
	fputs("\t\t//text area\n", fp);
	fputs("\t\ttextArea = new JTextArea(20, 50);\n", fp);
	fputs("\t\ttextArea.setEditable(false);\n", fp);
	fputs("\t\tJScrollPane textPane = new JScrollPane( textArea );\n", fp);
	fputs("\t\tJPanel textPanel = new JPanel();\n", fp);
	fputs("\t\ttextPanel.setLayout( new BorderLayout() );\n\n", fp);
	fputs("\t\tJLabel textLabel = new JLabel(\"STATUS\");\n", fp);
	fputs("\t\ttextPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);\n", fp);
	fputs("\t\ttextPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);\n", fp);
	fputs("\t\ttextPanel.add(textLabel, BorderLayout.NORTH);\n", fp);
	fputs("\t\ttextPanel.add(textPane, BorderLayout.CENTER);\n\n", fp);
	fputs("\t\ttextPanel.add(textLabel);\n", fp);
	fputs("\t\ttextPanel.add(textPane);\n", fp);
	fputs("\t\t//end text area\n\n", fp);
	fputs("\t\tadd(fieldAndButtonPanel);\n", fp);
	fputs("\t\tadd(textPanel);\n\t}\n\n", fp);

	//accessors and mutators
	fputs("\t//accessors and mutators\n", fp);
	for( i = 0; i < fieldCount; i++ ) {
		curName = PL_next(fields);
		fprintf(fp, "\tpublic void setDC%s( String instring ) {\n\t\t%s.setText(instring);\n\t}\n\n", curName, curName);		
		if ( strcmp( "string", PM_getValue(types, curName).str_val) == 0 ) {
			fprintf(fp, "\tpublic String getDC%s() {\n\t\treturn new String(%s.getText());\n\t}\n\n", curName, curName );
		} else if ( strcmp( "integer", PM_getValue(types, curName).str_val) == 0 ) {
			fprintf(fp, "\tpublic int getDC%s() throws IllegalFieldValueException {\n\t\tint i;\n", curName );
			fprintf(fp, "\t\ttry {\n\t\t\ti = Integer.parseInt(%s.getText());\n\t\t} catch ( NumberFormatException e ) {\n", curName);
			fprintf(fp, "\t\t\tthrow new IllegalFieldValueException(%s.getText());\n\t\t}\n\t\treturn i;\n\t}\n\n", curName);
		} else if ( strcmp( "float", PM_getValue(types, curName).str_val) == 0 ) {
			fprintf(fp, "\tpublic float getDC%s() throws IllegalFieldValueException {\n\t\tfloat f;\n", curName );
			fprintf(fp, "\t\ttry {\n\t\t\tf = Float.parseFloat(%s.getText());\n\t\t} catch ( NumberFormatException e ) {\n", curName);
			fprintf(fp, "\t\t\tthrow new IllegalFieldValueException(%s.getText());\n\t\t}\n\t\treturn f;\n\t}\n\n", curName);
		} else if ( strcmp( "boolean", PM_getValue(types, curName).str_val) == 0 ) {
			fprintf(fp, "\tpublic Boolean getDC%s() throws IllegalFieldValueException {\n\t\tBoolean b;\n", curName );
			fprintf(fp, "\t\ttry {\n\t\t\tb = Boolean.parseBoolean(%s.getText());\n\t\t} catch ( NumberFormatException e ) {\n", curName);
			fprintf(fp, "\t\t\tthrow new IllegalFieldValueException(%s.getText());\n\t\t}\n\t\treturn b;\n\t}\n\n", curName);
		}
	}

	//appendToStatusArea
	fputs("\tpublic void appendToStatusArea( String instring ) {\n\t\tString curContent = textArea.getText();\n\t\tcurContent += (instring + \"\\n\");\n\t\ttextArea.setText(curContent);\t\n}\n\n", fp);

	//actionPerformed
	fputs("\tpublic void actionPerformed( ActionEvent e ) {\n\t\tappendToStatusArea(e.getActionCommand() + \" button pressed\");\n\t}\n\n", fp);

	//main
	fprintf(fp, "\tpublic static void main( String[] args ) {\n\t\t%sFieldEdit runWindow = new %sFieldEdit();\n\t\trunWindow.setVisible(true);\n\t}\n}", Cpn, Cpn);
	
	//execption
	memset(filename, 0, strlen(filename));
	sprintf(filename, "%s/IllegalFieldValueException.java", Cpn);
	freopen(filename, "w", fp);

	fputs("import java.lang.Exception;\n\n", fp);
	fputs("public class IllegalFieldValueException extends Exception {\n\tpublic IllegalFieldValueException(String message) {\n\t\tsuper(\"Values not of defined type: \" + message );\n\t}\n}", fp);

	//mini makefile
	memset(filename, 0, strlen(filename));
	sprintf(filename, "%s/Makefile", Cpn);
	freopen(filename, "w", fp);

	fputs("all:\n", fp);
	fputs("\tjavac *.java\n", fp);

	//and thats it folks
	fclose(fp);
	free(filename);
}