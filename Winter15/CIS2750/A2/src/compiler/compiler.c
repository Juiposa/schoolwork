#include "ParameterManager.h"
#include "gui_Dialogc.h"
#include <unistd.h>
#include <sys/stat.h>


/* compile
 * Accepts a file path of the file that needs to be compiled and compiles it
 * Parameter: 	filePath - file path of target file
 *				workingDirectory - working directory the folder containing the compiled java will be put in
 * Returns: 1 on success, 0 otherwise
*/
JNIEXPORT jint JNICALL Java_gui_Dialogc_compile(JNIEnv * env, jclass obj, jstring filePath, jstring workingDirectory, jstring projectName) {
	printStuff();
	const char * Cfp = (*env)->GetStringUTFChars(env, filePath, 0);
	const char * Cwd = (*env)->GetStringUTFChars(env, workingDirectory, 0);
	const char * Cpn = (*env)->GetStringUTFChars(env, projectName, 0);
	printf("\nFILE: %s\nwd: %s\n", Cfp, Cwd);
	FILE * fp = fopen(Cfp, "r");

	ParameterManager * tfb; //title, fields, buttons
	ParameterManager * types; //fields and their types; buttons and their action listeners
	ParameterList * cur_item;
	char * curChar;
	int fieldCount = 0;
	int buttonCount = 0;
	int i = 0;

	tfb = PM_create(3);

	PM_manage( tfb, "title", STRING_TYPE, 1);
	PM_manage( tfb, "fields", LIST_TYPE, 1);
	PM_manage( tfb, "buttons", LIST_TYPE, 1);

	if (!PM_parseFrom( tfb, fp, '#' )) {
 		fclose(fp);
		PM_destroy(tfb);
		(*env)->ReleaseStringUTFChars(env, filePath, Cfp);
		(*env)->ReleaseStringUTFChars(env, workingDirectory, Cwd);
 		return 0; //parsing failure
	}

	fieldCount = PL_reset( PM_getValue( tfb, "fields").list_val ); //PL_reset both resets the list and counts how many items there are
	buttonCount = PL_reset( PM_getValue( tfb, "buttons").list_val );

	types = PM_create(buttonCount+fieldCount); //PM large enough to accomodate what we expect

	//looping for fields, registering them
	cur_item = PM_getValue( tfb, "fields").list_val;
	for( i = 0; i < fieldCount; i++ ) {
		curChar = PL_next(cur_item);
		PM_manage( types, curChar, STRING_TYPE, 1 );
	}

	//looping for buttons, registering them
	cur_item = PM_getValue( tfb, "buttons").list_val;
	for( i = 0; i < buttonCount; i++ ) {
		curChar = PL_next(cur_item);
		PM_manage( types, curChar, STRING_TYPE, 1 );
	}

	freopen( Cfp, "r", fp); //reopening the file for another pass

	if (!PM_parseFrom( types, fp, '#' )) {
 		fclose(fp);
		PM_destroy(tfb);
		(*env)->ReleaseStringUTFChars(env, filePath, Cfp);
		(*env)->ReleaseStringUTFChars(env, workingDirectory, Cwd);
 		return 0; //parsing failure
	}

	PL_reset( PM_getValue( tfb, "buttons").list_val ); //lists are needed again
	PL_reset( PM_getValue( tfb, "fields").list_val );

	char curwd[1024]; //directory before writing
	getcwd( curwd, sizeof(curwd));
	chdir(Cwd);

	emitJava( tfb, types, fieldCount, buttonCount, Cpn );

	chdir(curwd);
	fclose(fp);
	PM_destroy(tfb);
	(*env)->ReleaseStringUTFChars(env, filePath, Cfp);
	(*env)->ReleaseStringUTFChars(env, workingDirectory, Cwd);
	(*env)->ReleaseStringUTFChars(env, projectName, Cpn);
	return 1;
}

void emitJava( ParameterManager * tfb, ParameterManager * types, int fieldCount, int buttonCount, const char * Cpn ) {
	FILE * fp; //new or not new java file we are printing to; we dunno and it doesn't matter
	char * filename = malloc(sizeof(char)*100);
	char * curName = malloc(sizeof(char)*100);
	ParameterList * fields, * buttons;
	int i = 0;
	fields = PM_getValue( tfb, "fields").list_val;
	buttons = PM_getValue( tfb, "buttons").list_val;
	mkdir( Cpn, S_IRWXU ); //make the directory we need, it may fail, but only if directory already exists, in which case we dont care, we just need to to be there

	sprintf(filename, "%s/%s.java", Cpn, Cpn); //file we'll be opening, with its directory path
	fp = fopen(filename, "w");
	//TIME FOR THE FUN STUFF

	fprintf(fp, "package %s;\n\n", Cpn );
	fputs("import java.awt.*;\nimport javax.swing.*;\nimport java.awt.event.ActionListener;\nimport java.awt.event.ActionEvent;\n\n", fp);
	fprintf(fp, "public class %s extends JFrame implements ActionListener {\n\n", Cpn);

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
	fprintf(fp, "\tpublic %s() {\n\n", Cpn);

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
		fprintf(fp, "\t\t%s.addActionListener(this);\n", curName);
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
		fprintf(fp, "\tpublic String getDC%s() {\n\t\treturn new String(%s.getText());\n\t}\n\n", curName, curName );
	}

	//appendToStatusArea
	fputs("\tpublic void appendToStatusArea( String instring ) {\n\t\tString curContent = textArea.getText();\n\t\tcurContent += (instring + \"\\n\");\n\t\ttextArea.setText(curContent);\t\n}\n\n", fp);

	//actionPerformed
	fputs("\tpublic void actionPerformed( ActionEvent e ) {\n\t\tappendToStatusArea(e.getActionCommand() + \" button pressed\");\n\t}\n\n", fp);

	//main
	fprintf(fp, "\tpublic static void main( String[] args ) {\n\t\t%s runWindow = new %s();\n\t\trunWindow.setVisible(true);\n\t}\n}", Cpn, Cpn);
	//and thats it folks

	fclose(fp);
	free(filename);
}