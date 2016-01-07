/*
Jeffrey Kapp 0832671
CIS2460 A2
13 Nomverber 2015
I keep adding more and more variables to this
It's getting kinda gross
*/

import java.util.Random;
import java.lang.Integer;

public class Frame {


	public int number;
	public int length;
	public boolean completed = false;
	public int transmitting = 0;
	public boolean first72 = false;
	public boolean collisionDetected = false;
	public float deliveryTime;
	public float arrivalTime;
	public float seventyTwoTime;
	public Integer sender;
	public int collisions = 0;
	public int bytesLeft;
	public float timeRemaining;

	public Frame(int number) {
		Random rand = new Random();
		this.number = number;
		length = (int)(rand.nextInt(1455)+72);
		bytesLeft = length;
		transmitting = 0;
	}
}