package cardgame;

public class Card {

	public enum Suit { SPADES, HEARTS, CLUBS, DIAMONDS };
	private int rank;
	private Suit suit;
	private boolean faceup;
	private Object faceImage;
	private static Object backImage;

	public Card( Suit suit, int rank ) {
		this.rank = rank;
		this.suit = suit;
		this.faceup = false;
	}

	public int getRank() {
		return rank;
	}

	public Suit getSuit() {
		return suit;
	}

	public void setFaceup( boolean faceup ) {
		this.faceup = faceup;
	}

	public boolean getFaceup() {
		return faceup;
	}

	public Object getImage() {
		return faceImage;
	}

	public void setImage( Object image ) {
		faceImage = image;
	}

	public static void setBackImage( Object image ) {
		backImage = image;
	}

	public static Object getBackImage() {
		return backImage;
	}

	public String toString() {
		return Suit + rank;
	}

	public boolean equals(Card card) {
		if ( this.rank == card.rank ) {
			return true;
		}
		return false;
	}



}