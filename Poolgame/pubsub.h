#pragma once
#include "utils.h"

class Subject;

/**
 * @brief The Observer - gets updated when something happen in the subject
 * will need to look into the state of the subject to find out
 * what changed
 */
class Observer {
public:
	virtual void update(Subject* s) = 0;
};

/**
 * @brief The Subject - notifies observers when something happens
 */
class Subject {
protected:
	// weak reference do not delete
	std::vector<Observer*> m_observers;
public:
	virtual ~Subject() {}
	void attach(Observer* o) { m_observers.push_back(o); }
	void detach(Observer* o) { m_observers.erase(std::find(m_observers.cbegin(), m_observers.cend(), o), m_observers.cend()); }
	void notify() { for (Observer* o : m_observers) o->update(this); }
};
