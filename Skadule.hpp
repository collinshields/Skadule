#ifndef SKADULE_HPP
#define SKADULE_HPP

#include <string>
#include <vector>
#include <iostream>

/***
* \brief	Represents an agent with a name designated availability.
***/
struct ScheduleAgent {
	std::string name; // The name of the agent
	short availability[7][2]; // The shifts the agent is available for each day of the week

	ScheduleAgent(std::string name) : name(name) {}

	bool operator==(const ScheduleAgent& other) const {
		return name == other.name;
	}
};

/***
* \brief	Manages a schedule of agents, allowing for adding agents and retrieving their desired schedules.
*			Optimal schedule is determined by certain criteria:
* 				1. Total scheduled time for each agent should be 40 hours or less.
* 				2. Each agent should have at least 10 hours of rest between shifts.
*				3. The schedule should be balanced, ensuring that no agent is overburdened with consecutive shifts.
*				4. Ideally, at least two agents should be scheduled at the same time to ensure coverage. This is a high priority for weekends.
*				5. More than two agents should not be scheduled at the same time to avoid overcrowding. This is a high priority for weekdays.
***/
class Skadule {
// PUBLIC MEMBERS
public:
	/***
	* \brief	Represents a shift with a start and end time in 24-hour format.
	***/
	struct Shift {
		int start_time; // Start time in 24-hour format (e.g., 9 for 9 AM, 17 for 5 PM)
		int end_time;   // End time in 24-hour format
		ScheduleAgent* assigned_agent; // Pointer to the agent assigned to this shift (nullptr if unassigned)
	};

	struct AgentTracker {
		ScheduleAgent* agent; // Pointer to the agent being tracked
		int total_hours; // Total hours assigned to the agent for the week
		std::vector<Shift> assigned_shifts; // List of shifts assigned to the agent
	};

// PROTECTED MEMBERS
protected:
	std::vector<ScheduleAgent> agents;
	std::vector<ScheduleAgent> optimized_agents;

// PUBLIC METHODS
public:
	/***
	* \brief	Adds a ScheduleAgent to the pool.
	* \param	agent : The ScheduleAgent to add to the pool.
	***/
	void add_agent(ScheduleAgent agent);

	/***
	* \brief	Gets a pointer to the ScheduleAgent with the specified name from the pool.
	* \param	name : The name of the agent to retrieve from the pool.
	* \return	A pointer to the ScheduleAgent with the specified name, or nullptr if no such agent exists in the pool.
	***/
	ScheduleAgent* get_agent(std::string &name);

	/***
	* \brief	Gets the optimized schedule of agents based on the current pool of agents and their desired schedules.
	***/
	std::vector<ScheduleAgent> get_optimized_agents() const;

	/***
	* \brief	Removes an agent from the pool.
	* \param	agent : A reference to the agent to remove from the pool.
	***/
	void remove_agent(ScheduleAgent &agent);

	/***
	* \brief	Prints the schedule in a human-readable format, showing which agents are scheduled for each time slot.
	***/
	void print_schedule() const;

	/***
	* \brief	Generates an optimal schedule based on the current agents and their desired times.
	* \details	The optimized agents are stored seperately from the original agents to allow for changing availability.
	*			Seperated from returning so that the optimized agents can be accessed without needing to generate a new schedule each time.
	***/
	void optimize_agents();
};

// IMPLEMENTATION OF SCHEDULEAGENT METHODS
bool ScheduleAgent::operator==(const ScheduleAgent& other) const {
	return (name == other.name);
}

// IMPLEMENTATION OF SCHEDULE METHODS
void Skadule::add_agent(const ScheduleAgent agent) {
	agents.push_back(agent);
}

ScheduleAgent* Skadule::get_agent(std::string &name) {
	for (ScheduleAgent& agent : agents) {
		if (agent.name == name) {
			return &agent;
		}
	}
	return nullptr;
}

std::vector<ScheduleAgent> Skadule::get_optimized_agents() const {
	return optimized_agents;
}

void Skadule::remove_agent(ScheduleAgent &agent) {
	for (auto a = agents.begin(); a != agents.end(); ++a) {
		if (*a == agent) {
			agents.erase(a);
			return;
		}
	}
}

void Skadule::print_schedule() const {
	std::cout << "Schedule:\n";
	for (const ScheduleAgent& agent : optimized_agents) {
		std::cout << "Agent: " << agent.name << "\n";
		for (int day = 0; day < 7; ++day) {
			std::cout << "  Day " << day << ": ";
			for (int shift = 0; shift < 2; ++shift) {
				if (agent.availability[day][shift] == 1) {
					std::cout << (shift == 0 ? "Morning " : "Evening ");
				}
			}
			std::cout << "\n";
		}
	}
}

void Skadule::optimize_agents() {
	if (agents.empty()) {
		std::cout << "No agents to optimize.\n";
		return;
	}

	// Clear previous optimized agents
	optimized_agents.clear();

	// Initialize new vector of agent trackers, filled with new agents with copied names and empty schedules
	std::vector<AgentTracker> agent_trackers;
	for (const ScheduleAgent& agent : agents) {
		agent_trackers.push_back({ new ScheduleAgent(agent.name), 0, {} });
	}

	// Optimize	

	// Extract optimized agents from trackers and store in optimized_agents vector
	for (const AgentTracker& tracker : agent_trackers) {
		optimized_agents.push_back(*tracker.agent);
	}

	// Clean up dynamically allocated memory for agent trackers
	for (AgentTracker& tracker : agent_trackers) {
		delete tracker.agent;
	}
}
#endif