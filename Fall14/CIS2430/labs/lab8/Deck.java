package cardgame;

import java.util.Collections;
import java.util.ArrayList;

public class Deck {

	private ArrayList<Card> deck = new ArrayList(0);
	
	public Deck() {
		Card activeCard;
		for ( Card.Suit suit: Card.Suit.values() ) {
			for ( int j = 0; j < 13; j++ ) {
				activeCard = new Card( suit, j );
				deck.add( activeCard );
			}
		}
	}

	public int getCardCount() {
		return deck.size();
	}

	public Card getCard( int pos ) {
		return new Card( deck.get( pos ) ); 
	}

	public Void addCard( Card card ) {
		deck.add(card);
	}

	public Card removeCard( int pos ) {
		Card temp = deck.get( pos ); 
		deck.remove( pos );
		return temp;
	}

	public ArrayList<Card> getCards() {
		return deck;
	}

	public void shuffle() {
		Collections.shuffle(deck);
	}
}