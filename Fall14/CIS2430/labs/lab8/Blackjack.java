package cardgame;

public class Blackjack {

	@Override
	public Game( int numPlayers ) {
		deck = new Deck();
		this.numPlayers = numPlayers;
		for ( int i = 0; i < numPlayers ) {
			player.add( new BlackjackPlayer( "Player" + i, HUMAN, 0 ) );
		}
	}

	@Override
	public void play() {
		 
	}
}