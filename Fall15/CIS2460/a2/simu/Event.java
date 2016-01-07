/*
Jeffrey Kapp 0832671
CIS2460 A2
13 Nomverber 2015
*/

public class Event {

	public float time; //the time it occurs at
	public String eventType; //what kind of event it is
	public int frame; //frame the event is tied to if applicable

	public Event( float time, String eventType, int frame ) {
		this.time = time;
		this.eventType = new String(eventType);
		this.frame = frame;
	}
}