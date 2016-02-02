#include "..\..\include\GameAction\LatelyDestroyable.h"
#include <algorithm>

std::list<LatelyDestroyable*> DestructionManager::dead;

bool LatelyDestroyable::isAlive(void) const { return alive; }

void LatelyDestroyable::destroy(void) {
	if (alive) {
		alive = false;
		DestructionManager::Register(this);
	}
}

void LatelyDestroyable::Delete::operator()(LatelyDestroyable* o) const
{
	o->inDestruction = true; delete o;
}

void DestructionManager::Register(LatelyDestroyable* o) {
	assert(!o->isAlive());
	dead.push_back(o);
}

void DestructionManager::commit(void) {
	std::for_each(
		dead.begin(),
		dead.end(),
		LatelyDestroyable::Delete()
		);
	dead.clear();
}
