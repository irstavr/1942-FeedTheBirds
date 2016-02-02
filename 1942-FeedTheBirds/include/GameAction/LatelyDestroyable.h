#ifndef LATELYDESTROYABLE_H
#define LATELYDESTROYABLE_H

#include <cassert>
#include <list>

class LatelyDestroyable;

class DestructionManager {
	static std::list<LatelyDestroyable*> dead;
public:
	static void Register(LatelyDestroyable* o);
	static void commit(void);
};

class LatelyDestroyable {
	friend class DestructionManager;
	bool alive;
	bool inDestruction;

	virtual ~LatelyDestroyable() { assert(inDestruction); }

	class Delete : public std::unary_function<LatelyDestroyable*, void>
	{
		public: void operator()(LatelyDestroyable* o) const;
	};

	friend class Delete;

public:
	bool isAlive(void) const;
	void destroy(void);
	
	LatelyDestroyable(void) : alive(true), inDestruction(false) {
	} //savvy say it should be virtual, I beg to differ...
};

#endif