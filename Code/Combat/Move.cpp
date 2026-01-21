#include "Move.hpp"
#include <unordered_map>

std::unordered_map<MOVE_ID, Move> Move::moveDatabase;

void Move::InitMoveDatabase()
{
	moveDatabase.emplace(MOVE_BASIC_ATK, Move("Basic Attack", 0.2f, 0, "Attack a single enemy", "", Game::ENEMY));
	moveDatabase.emplace(MOVE_BURN_MOVE, Move("Scorch", 0.1f, 0.15f, "Attack an enemy and apply BURN", "", Game::ENEMY));
	moveDatabase[MOVE_BURN_MOVE].moveModifiers = std::vector <MODIFIER_ID>{GENERIC_DOT_BURN};
}