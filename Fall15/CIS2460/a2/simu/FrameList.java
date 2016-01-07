/*
Jeffrey Kapp 0832671
CIS2460 A2
13 Nomverber 2015
*/

import java.util.ArrayList;

public class FrameList {
	private ArrayList<Frame> frameList;

	public FrameList() {
		frameList = new ArrayList<Frame>();
	}

	//will return frame at a given index
	public Frame getFrame( int i ) {
		if( i == -1 )
			return null;
		return frameList.get(i);
	}

	//will append a frame onto the back of list
	public void addFrame( Frame frame ) {
		frameList.add(frame);
	}

	public int size() {
		return frameList.size();
	}
}