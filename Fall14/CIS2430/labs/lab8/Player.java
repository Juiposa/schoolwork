package cardgame;

public class Player {

	public enum ROLE { HUMAN, COMPUTER };
	private String name;
	private ROLE role;
	private int credit;

	protected ArraryList<Card> hand = new ArraryList(0);
	protected ArraryList<Card> playedCards = new ArraryList(0);

	public Player( String name, ROLE role, int credit ) {
		this.name = new String( name );
		this.role = role;
		this.credit = credit;
	} 

	public String getName() {
		return new String( name );
	}

	public void setName( String name ) {
		this.name = new String( name ); 
	}

	public ROLE getRole() {
		return role;
	}

	public void setRole( ROLE role ) {
		this.role = role;
	}

	public int getCredit() {
		return credit;
	}

	public void setCredit( int credit ) {
		this.credit = credit;
	} 

	public int getCardCount() {
		return hand.size();
	}

	public Card getCard( int pos ) {
		return new Card( hand.get( pos ) );
	}

	public void receiveCard( Card card ) {
		hand.add( card );
	}


	public int getPlayedCardCount() {
		return playedCard.size();
	}

	public void playCards( ArraryList<Card> cards ) {

		Card temp;
		for ( int i = 0; i < cards.size(); i++ ) {
			temp = hand.get(card.get(i));
			playedCards.add(temp);
			hand.remove(card.get(i));
		}
	}

	public int score() {
		return 0;
	}

	public void clearHand() {
		Card temp;
		for ( int i = 0; i < hand.size(); i++ ) {
			temp = hand.get(i;
			playedCards.add(temp);
			hand.remove(i);
		}
	}

	public Card collectPlayedCard ( int pos ) {
		Card temp;
		temp = playedCards.get(i);
		playedCards.remove(i);
		return temp;
	} 
}
