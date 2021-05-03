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

void Player::pick_card(Card selected)
{
	selected_cards.insert(selected_cards.begin(),selected.card_value);
}

void Player::checkCards()
{
	if (selected_cards.size() == 1 || selected_cards.size() == 0)
		isPlaying = true;
	else
	{
		isPlaying = selected_cards[0] == selected_cards[1];
		selected_cards.clear();
	}
}

void Player::addPoint()
{
	score++;
}