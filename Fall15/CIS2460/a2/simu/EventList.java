/*
Jeffrey Kapp 0832671
CIS2460 A2
13 Nomverber 2015
*/

import java.util.ArrayList;

public class EventList {

	private ArrayList<Event> eventList;

	public EventList() {
		eventList = new ArrayList<Event>();
	}

	//will get and return the next event in the queue
	public Event getNext() {
		return eventList.remove(0);
	}

	//will insert the event into the list based on its time of occurance
	public void addEvent(Event event) {
		int i;
		if( eventList.size() == 0 ) {
			eventList.add(event);
			return;
		}
		for( i = 0; i < eventList.size(); i++ ) {
			if( event.time < eventList.get(i).time ) {
				eventList.add(i, event);
				return;
			}
		}
		eventList.add(event);
	}

	public int size() {
		return eventList.size();
	}

}