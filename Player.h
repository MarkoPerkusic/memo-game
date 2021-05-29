#include <string>
#include <vector>
#include "Card.h"

class Player
{
	public:
		Player();
		Player(int player_id);
		~Player();
		std::string getName();
		void selectCard(Card* selected);
		bool isPlaying;
		void checkCards();
		void addPoint();
		std::vector<Card*> selected_cards;
		int score;
		void closeCards();
		int x_pos();
		int y_pos();

	private:
		std::string name;
		
};
