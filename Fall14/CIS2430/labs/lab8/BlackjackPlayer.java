package cardgame;

public class BlackjackPlayer extends Player {
	
	@Override
	public int score() {
		int total = 0;
		Card activeCard;
		for ( int i = 0; i < getCardCount; i++ ) {
			activeCard = hand.get(i);
			total += activeCard.getRank();
		}
	}

	return total
}