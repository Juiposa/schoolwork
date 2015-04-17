
public class JNI_example {
	
	static { System.loadLibrary("JNI_Example");}

	native static void printHello();

	public static void main( String[] args ) {
		System.out.println("Hello Java world.");
		printHello();
	}
}