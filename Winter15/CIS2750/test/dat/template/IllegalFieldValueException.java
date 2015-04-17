package example;

import java.lang.Exception;

public class IllegalFieldValueException extends Exception {
	public IllegalFieldValueException(String message) {
		super("Values not of defined type: " + message );
	}
}