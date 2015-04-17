/*****************
Jeffrey-David Kapp
CIS2750
13 February 2015
Assignment 2
*****************/


#include "ParameterManager.h"
#include "Dialogc.h"
#include <unistd.h>
#include <sys/stat.h>


/* compile
 * Accepts a file path of the file that needs to be compiled and compiles it
 * Parameter: 	filePath - file path of target file
 *				workingDirectory - working directory the folder containing the compiled java will be put in
 * 				projectName - project's name, used for file name and class name in emitted code
 * Returns: 1 on success, 0 otherwise
*/
JNIEXPORT jint JNICALL Java_Dialogc_compile(JNIEnv * env, jclass obj, jstring filePath, jstring workingDirectory, jstring projectName) {
	printStuff();
	const char * Cfp = (*env)->GetStringUTFChars(env, filePath, 0);
	const char * Cwd = (*env)->GetStringUTFChars(env, workingDirectory, 0);
	const char * Cpn = (*env)->GetStringUTFChars(env, projectName, 0);
	printf("Dialoc internal compiler.\n");
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

	if (!PM_parseFrom( tfb, fp, '#' ) || !checkRequired(tfb->param_ll)) {
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

	if (!PM_parseFrom( types, fp, '#' ) || !checkRequired(tfb->param_ll)) {
 		fclose(fp);
		PM_destroy(tfb);
		(*env)->ReleaseStringUTFChars(env, filePath, Cfp);
		(*env)->ReleaseStringUTFChars(env, workingDirectory, Cwd);
 		return 0; //parsing failure
	}

	PL_reset( PM_getValue( tfb, "buttons").list_val ); //lists are needed again
	PL_reset( PM_getValue( tfb, "fields").list_val );

	char curwd[1024]; //directory before writing
	getcwd( curwd, sizeof(curwd)); //get current directory
	chdir(Cwd); //change to project's working directory

	emitJava( tfb, types, fieldCount, buttonCount, Cpn ); //emit java

	chdir(curwd); //back to old directory
	fclose(fp);
	PM_destroy(tfb);
	(*env)->ReleaseStringUTFChars(env, filePath, Cfp);
	(*env)->ReleaseStringUTFChars(env, workingDirectory, Cwd);
	(*env)->ReleaseStringUTFChars(env, projectName, Cpn);
	return 1;
}

