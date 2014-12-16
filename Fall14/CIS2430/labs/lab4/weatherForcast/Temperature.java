package weatherForcast;

public class Temperature
{

	private float temp; //initally in Celsius
	private int unit; // 0 C, 1 F, 2 K

	public Temperature() {
		temp = 0;
		unit = 0;
	}

	public Temperature( float temp ) {
		this.temp = temp;
		unit = 0;
	}

	public float getTemp() {
		return temp;
	}

	public void setTemp( float temp ) {
		this.temp  = temp;
	}

	public String toString() {
		return " Temperature: " + temp;
	}

	public boolean equals( Temperature tempClass ) {
		if ( tempClass.temp == this.temp ) {
			return true;
		} else {
			return false;
		}
	}

	public void changeUnit ( int unit ) {
		if ( unit == this.unit ) {
			System.out.println("Already using that unit.");
		} else if ( unit == 0 ) {
			changeToCelsius(); 
		} else if ( unit == 1 ) {
			changeToFahrenheit();
		} else if ( unit == 2 ) {
			changeToKelvin();
		}
		this.unit = unit;
	}

	private void changeToCelsius() {
		if ( unit == 1 ) {
			temp -= 32;
			temp /= 1.8;
		} else if ( unit == 2 ) {
			temp -= 273.15;
		}
	}

	private void changeToFahrenheit() {
		if ( unit == 0 ) {
			temp *= 1.8;
			temp += 32;
		} else if ( unit == 2 ){
			temp -= 273.15;
			temp *= 1.8;
			temp += 32;
		}
	}

	private void changeToKelvin() {
		if ( unit == 0 ) {
			temp += 273.15;
		} else if ( unit == 1 ) {
			temp -= 32;
			temp /= 1.8;
			temp += 273.15;
		}
	}
}