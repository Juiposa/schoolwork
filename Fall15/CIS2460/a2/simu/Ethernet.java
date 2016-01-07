/*
Jeffrey Kapp 0832671
CIS2460 A2
13 Nomverber 2015
I apologise in advance
This kind of got away from me
I don't even have an idea what's going here anymore
*/

import java.util.Scanner;
import java.lang.Integer;
import java.lang.Long;
import java.lang.Float;
import java.util.Random;
import java.util.ArrayList;

public class Ethernet {
	
	public enum Cable { 
		QUIET, 
		BUSY 
	}

	public static Cable[] cable;

	private static FrameList frameList = new FrameList();
	private static EventList eventList = new EventList();

	private static long argRandSeed = 0;
	private static long randSeed;
	private static int numSenders;
	private static int numFrames;
	private static float framesPer100;
	private static float interarrivalTime;

	private static int totalBytesSent = 0;
	private static int droppedFrames = 0;
	private static ArrayList<Integer> avaiSenders = new ArrayList<Integer>();
	private static int[] sendersFrames; //list of senders and the frames they are in charge of

	private static double bitsPerSecond = 0.0;

	private static float slotTime = (float)25.6;
	private static float time = 0;

	public static void main(String[] args) {
		int i = 0;
		int framesDelivered = 0;
		Random rand;

		//command line argument handling
		argRandSeed = Long.parseLong(args[0]);
		if( argRandSeed == 0 ) {
			Random newRand = new Random();
			randSeed = (long)newRand.nextInt(150000000);
		} else {
			randSeed = argRandSeed;
		}
		rand = new Random(randSeed);
		numSenders = Integer.parseInt(args[1]);
		numFrames = Integer.parseInt(args[2]);
		framesPer100 = Float.parseFloat(args[3]);

		interarrivalTime = (100 * slotTime) / framesPer100;

		outStart();

		//initialising list of senders
		for ( i = 0; i < numSenders; i++ ) {
			avaiSenders.add(new Integer(i));
		}

		//initialising the cable
		sendersFrames = new int[numSenders];
		cable = new Cable[numSenders];
		for ( i = 0; i < numSenders; i++ ) {
			sendersFrames[i] = -1;
			cable[i] = Cable.QUIET;
		}

		Frame newFrame;
		Event newEvent;
		for( i = 0; i < numFrames; i++ ) {
			newFrame = new Frame(i); 
			newFrame.deliveryTime = slotTime*(newFrame.length/36);
			newFrame.timeRemaining = newFrame.deliveryTime;
			newFrame.transmitting = 0;
			if ( i == 0 ) {
				newFrame.arrivalTime = 0;
			} else {
				newFrame.arrivalTime = frameList.getFrame(i-1).arrivalTime + (float)(rand.nextFloat()*(interarrivalTime*2));
			}
			frameList.addFrame(newFrame);
			newEvent = new Event( newFrame.arrivalTime, "arrival", i );
			eventList.addEvent(newEvent);
		}

		Event currEvent;
		Frame currFrame;
		while ( eventList.size() != 0 ) { //simulation loop
			currEvent = eventList.getNext();
			currFrame = frameList.getFrame(currEvent.frame);
			time = currEvent.time;
			if( currEvent.eventType.equals("arrival") ) { //frame arrival
				if( avaiSenders.size() == 0 ) { //no available senders
					currEvent.time += 150; //wait thirty more mus and try to see if there are available senders
					eventList.addEvent(currEvent);
				} else {
					int j = rand.nextInt(avaiSenders.size());
					currFrame.sender = avaiSenders.remove(j);
					sendersFrames[j] = currFrame.number;
					System.out.println("Frame " + currEvent.frame + " arrives @ " + currEvent.time + " mus " );
					System.out.println("	F" + currFrame.number + ": len=" + currFrame.length + " dlvmt=" + currFrame.deliveryTime + " sdr=" + currFrame.sender + " listen arr@" + currFrame.arrivalTime + " col=0" );
					newEvent = new Event( currEvent.time + 1, "listen", currFrame.number );
					eventList.addEvent(newEvent);
				}
			} else if ( currEvent.eventType.equals("listen") ) { //sender listens to the cable
				System.out.print("Frame " + currFrame.number + " sender listens @ " + currEvent.time + " mus");
				if( currFrame != null && currFrame.completed != true && cable[currFrame.sender] == Cable.QUIET ) { //cable seems to be quiet, start sending data
					System.out.println(" ... quiet: sends");
					currFrame.transmitting = 1;
					if ( currFrame.first72 == false ) {
						currFrame.seventyTwoTime = currEvent.time + 2 * slotTime; //recording when the first 2 bytes are supposde to be done
						newEvent = new Event( currEvent.time + 2 * slotTime, "72b", currFrame.number );
					} else {
						newEvent = new Event( currEvent.time + currFrame.timeRemaining, "complete", currFrame.number );
					}
					eventList.addEvent(newEvent);
					for ( i = 0; i < numSenders; i++ ) { //set up event for when the other devices will see the message we are sending
						if ( i != currFrame.sender.intValue() ) { //skips itself
							float diff;
							if ( i > currFrame.sender )
								diff = i - currFrame.sender;
							else 
								diff = currFrame.sender - i; 
							newEvent = new Event(currEvent.time + (slotTime * diff), "busy", i );
							eventList.addEvent(newEvent);
						}
					}
				} else {
					System.out.println(" ... busy"); 
				}
			} else if ( currEvent.eventType.equals("72b") ) { //first 72 bytes sent
				System.out.println("Frame " + currEvent.frame + " 1st 72 bytes delivered @ " + currEvent.time + " mus");
				currFrame.first72 = true;
				totalBytesSent += 72;
				currFrame.bytesLeft -= 72;
				currFrame.timeRemaining -= slotTime*2;
				newEvent = new Event(currEvent.time + currFrame.timeRemaining, "complete", currEvent.frame);
				eventList.addEvent(newEvent);
				//collision checking
			} else if ( currEvent.eventType.equals("busy") ) { //device with a given frame can now hear the data being transmitted by someone else
				//Event.frame is assumed to be the index of the device in this case, not the frame

				currFrame = frameList.getFrame(sendersFrames[currEvent.frame]);
				
				//System.out.println("CURRFRAME " + currFrame.number + " DEVICE " + currEvent.frame );
				if ( currFrame == null || currFrame.transmitting == 0 ) { //no collision, just forced to wait
					cable[currEvent.frame] = Cable.BUSY;
				} else if ( currFrame.transmitting == 1 && currFrame.completed == false ) { //*************COLLISION*************
					cable[currEvent.frame] = Cable.BUSY;
					System.out.println("FRAME " + currFrame.number + " COLLISION at " + currEvent.time);
					if( currFrame.first72 == true ) { //immediately backoff if at least 72 bytes have been sent
						newEvent = new Event( currEvent.time, "collision", currFrame.number );
					} else {
						newEvent = new Event( currFrame.seventyTwoTime, "collision", currFrame.number );
					}
					eventList.addEvent(newEvent);
				}
			} else if ( currEvent.eventType.equals("quiet") ) { //the cable under a device has gone quiet
				currFrame = frameList.getFrame(sendersFrames[currEvent.frame]);
				cable[currEvent.frame] = Cable.QUIET;
				
				if ( currFrame != null && currFrame.transmitting == 0 ) {
					newEvent = new Event( currEvent.time, "listen", currFrame.number ); //start trying to send again
					eventList.addEvent(newEvent);
				}
			} else if ( currEvent.eventType.equals("collision") ) {
				currFrame.collisions++;
				System.out.println("Frame " + currFrame.number + " sender detects collision " + currFrame.collisions	+ " at " + currEvent.time + " mus ");
				if (currFrame.completed != true && currFrame.collisions == 2) {
					System.out.println("Frame " + currFrame.number + " dropped @ " + currEvent.time + " mus\n");
					avaiSenders.add(currFrame.sender);
					sendersFrames[currFrame.sender] = -1;
					currFrame.completed = true;
					droppedFrames++;
					for ( i = 0; i < numSenders; i++ ) { //sends events that the cable is going to be quiet
						if ( i != currFrame.sender ) { //skips itself
							float diff;
							if ( i > currFrame.sender )
								diff = (i - currFrame.sender)/(numSenders-1);
							else 
								diff = (currFrame.sender - i)/(numSenders-1); 
							newEvent = new Event(currEvent.time + (slotTime * diff), "quiet", i );
							eventList.addEvent(newEvent);
						}
					}
					currFrame.sender = null;
				} else {
					int backoff = rand.nextInt(2); 
					System.out.println("		Backs off for " + slotTime * backoff + " mus");
					newEvent = new Event( currEvent.time + (backoff*slotTime), "listen", currFrame.number );
					eventList.addEvent(newEvent);
				}
			} else if ( currEvent.eventType.equals("complete") ) { //completion of a frame
				if ( currFrame.completed != true ) {
					System.out.println("Frame " + currEvent.frame + " sending is complete @ " + currEvent.time + " mus\n");
					totalBytesSent += currFrame.bytesLeft;
					avaiSenders.add(currFrame.sender);
					sendersFrames[currFrame.sender] = -1;
					currFrame.completed = true;

					for ( i = 0; i < numSenders; i++ ) { //sends events that the cable is going to be quiet
						if ( i != currFrame.sender ) { //skips itself
							float diff;
							if ( i > currFrame.sender )
								diff = (i - currFrame.sender)/(numSenders-1);
							else 
								diff = (currFrame.sender - i)/(numSenders-1); 
							newEvent = new Event(currEvent.time + (slotTime * diff), "quiet", i );
							eventList.addEvent(newEvent);
						}
					}
					currFrame.sender = null;
				}	
			}
		}

		bitsPerSecond = (totalBytesSent / time*1000000)*8;
		outEnd();
	}

	private static void outStart() {
		System.out.println("Input:   Seed from user = " + argRandSeed);
		System.out.println("	 Seed to use = " + randSeed);
		System.out.println("	 # devices = " + numSenders);
		System.out.println("	 # frames to simulate = " + numFrames);
		System.out.println("	 Mean # of frames/100 slot times = " + framesPer100);
		System.out.println("	 Mean interarrival time = " + interarrivalTime + " microseconds (mus)");
	}

	private static void outEnd() {
		System.out.println("Performance Report:");
		System.out.println("	# simulated frames = " + numFrames + " frame(s) ");
		System.out.println("	# bytes successfully sent = " + totalBytesSent + " bytes ");
		System.out.println(" 	# dropped frames = " + droppedFrames + " frame(s) ");
		System.out.println(" 	Ethernet throughput = " + bitsPerSecond + " bps = " + bitsPerSecond/1000000 + " Mbps");
	}
}