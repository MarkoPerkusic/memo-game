#include "Player.h"

Player::Player() 
{
	score = 0;
}

Player::~Player() {}

Player::Player(int player_id)
{
	name = "Player" + std::to_string(player_id);
	score = 0;
}

std::string Player::getName()
{
	return name;
}

void Player::selectCard(Card* selected)
{
	selected_cards.insert(selected_cards.begin(), selected);
}

void Player::checkCards()
{
	//printf("selected_cards.size %i \n", selected_cards.size());
	//if (selected_cards.size() == 2)
	//{
	//	isPlaying = selected_cards[0]->card_value == selected_cards[1]->card_value;
	//	//printf("SIZE = 2 \n");
	//	if (isPlaying)
	//	{
	//		addPoint();
	//		//printf("POINT\n");
	//		//selected_cards.clear();
	//	}
	//	else
	//	{
	//		printf("NOT PLAYING \n");
	//		selected_cards[0]->close();
	//		selected_cards[1]->close();
	//	}
	//}
	isPlaying = selected_cards[0]->card_value == selected_cards[1]->card_value;
	if (isPlaying)
		addPoint();
	selected_cards[0]->close();
	selected_cards[1]->close();
}

void  Player::closeCards()
{
	selected_cards[0]->close();
	selected_cards[1]->close();
	selected_cards.clear();
}

void Player::addPoint()
{
	score++;
}