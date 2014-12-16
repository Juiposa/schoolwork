package cardgame;

public class Game {

	private Deck deck;
	private int numPlayers;
	private ArrayList<Player> players = new ArrayList(0);

	public Game( int numPlayers ) {
		deck = new Deck();
		this.numPlayers = numPlayers;
		for ( int i = 0; i < numPlayers ) {
			player.add( new Player( "Player" + i, HUMAN, 0 ) );
		}
	}

	public Deck getDeck() {
		return deck;
	}

	public int getPlayerCount() {
		return numPlayers;
	}

	public Player getPlayer( int pos ) {
		return players.get(i);
	}

	public distributeCards( int rounds ) {
		Player activePlayer;
		if ( rounds == 0 ) {
			int j = 0;
			for ( int i = 0, i < deck.getCardCount, i++ ) {
				activePlayer = players.get(j);
				activePlayer.receiveCard(deck.getCard(i));
				j++
				if ( j == numPlayers ) { j = 0; }
			}
		} else {
			for ( int i = 0, i < rounds, i++ ) {
				activePlayer = players.get(j);
				activePlayer.receiveCard(deck.getCard(i));
				j++
				if ( j == numPlayers ) { j = 0; }
			}		
		}	
	}

	public void collectCards() {
		Player activePlayer;
		for ( int i = 0, i < numPlayers, i++ ) {
			activePlayer =  players.get(i);
			activePlayer.clearHand()
			for ( int j = 0, i < activePlayer.getPlayedCardCount(), j++ ) {
				deck.addCard( activePlayer.collectPlayedCard(i) );
			}
		}
	}

	public void play() {

	}
}