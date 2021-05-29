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

int Player::x_pos()
{
	int p_id = stoi(name.substr(6, name.length()));

	if (p_id <= 12)
	{
		return 20 + (p_id - 1) * 80;
	}
	else if (p_id > 12 && p_id <= 30)
	{
		return 900;
	}
	else if (p_id > 30 && p_id <= 41)
	{
		return 20 + (41 - p_id) * 80;
	}
	else
	{
		return 20;
	}
}

int Player::y_pos()
{
	int p_id = stoi(name.substr(6, name.length()));

	if (p_id <= 12)
	{
		return 20;
	}
	else if (p_id > 12 && p_id <= 30)
	{
		return 20 + (p_id - 12) * 30;
	}
	else if (p_id > 30 && p_id <= 41)
	{
		return 560;
	}
	else
	{
		return 20 + (59 - p_id) * 30;
	}
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