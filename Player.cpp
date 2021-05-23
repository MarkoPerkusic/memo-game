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
	isPlaying = selected_cards[0]->card_value == selected_cards[1]->card_value;
	if (isPlaying)
	{
		addPoint();
		selected_cards[0]->is_open = true;
		selected_cards[1]->is_open = true;
	}
}

void  Player::closeCards()
{
	printf("\nCLOSING SELECTED CARD");
	selected_cards[0]->close();
	selected_cards[1]->close();
	selected_cards.clear();
}

void Player::addPoint()
{
	score++;
}