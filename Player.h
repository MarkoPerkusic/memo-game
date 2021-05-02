#pragma once
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
		void pick_card(Card selected);
		bool isPlaying;
		void checkCards();
		void addPoint();
		std::vector<int> selected_cards;

	private:
		std::string name;
		int score;
};
