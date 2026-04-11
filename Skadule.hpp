#ifndef SKADULE_HPP
#define SKADULE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/***
* \brief	Represents an agent with a name designated availability.
***/
struct ScheduleAgent {
	std::string name; // The name of the agent
	short availability[7][2]; // The shifts the agent is available for each day of the week [day of week][start time, end time]
	short ideal_hours;
	short total_hours; // Maybe it makes more sense to just store this here?
	short wage;

	ScheduleAgent(std::string name) {
		this->name = name;
		this->ideal_hours = 40; // Default ideal hours per week
		this->total_hours = 0;
		this->wage = -1; // Implies wage is not set. If found when optimizing and wage ratios are being factored, needs to exit with error.
		for (int i = 0; i < 7; ++i) {
			availability[i][0] = -1; // -1 indicates no availability
			availability[i][1] = -1;
		}
	}

	ScheduleAgent(std::string name, short wage) {
		this->name = name;
		this->ideal_hours = 40; // Default ideal hours per week
		this->total_hours = 0;
		this->wage = wage;
		for (int i = 0; i < 7; ++i) {
			availability[i][0] = -1; // -1 indicates no availability
			availability[i][1] = -1;
		}
	}

	ScheduleAgent(std::string name, short wage, short ideal_hours) {
		this->name = name;
		this->ideal_hours = ideal_hours;
		this->total_hours = 0;
		this->wage = wage;
		for (int i = 0; i < 7; ++i) {
			availability[i][0] = -1; // -1 indicates no availability
			availability[i][1] = -1;
		}
	}

	ScheduleAgent(std::string name, short wage, short ideal_hours, short availability[7][2]) {
		this->name = name;
		this->ideal_hours = ideal_hours;
		this->total_hours = 0;
		this->wage = wage;
		for (int i = 0; i < 7; ++i) {
			this->availability[i][0] = availability[i][0];
			this->availability[i][1] = availability[i][1];
		}
	}

	bool operator==(const ScheduleAgent& other) const;
};

/***
* \brief	Manages a schedule of agents, allowing for adding agents and retrieving their desired schedules.
*			Optimal schedule is determined by certain criteria (***NEEDS UPDATE***):
* 				1. Total scheduled time for each agent should be 40 hours or less.
* 				2. Each agent should have at least 10 hours of rest between shifts (across days).
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

	/***
	*  \brief	Helper struct to track agent assignments and hours during optimization.
	***/
	struct AgentTracker {
		ScheduleAgent* agent; // Pointer to the agent being tracked
		int total_hours; // Total hours assigned to the agent for the week
		std::vector<Shift> assigned_shifts; // List of shifts assigned to the agent
	};

	/***
	*  \brief	Represents the ideal wage ratio for optimizing schedules based on agent wages. Needs to be set with previous sales data.
	***/
	float ideal_wage_ratio;
	/***
	*  \brief	Represents the previous sales data for each day of the week, used to optimize schedules based on expected demand. Needs to be set with wage ratio.
	***/
	int previous_sales[7];

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
	* \brief	Returns a matrix representation of the schedule, where each row represents a day of the week and each column represents a time slot.
	*			Also, each cell contains the names of every agent scheduled for that time slot, or "None" if no agents are scheduled.
	* \return	A 2D vector of strings, where each string represents the name of the agent scheduled for that time slot, or "None" if no agent is scheduled.
	***/
	std::vector<std::vector<std::string>> get_schedule_matrix() const;

	/***
	* \brief	Generates an optimal schedule based on the current agents and their desired times.
	* \details	The optimized agents are stored seperately from the original agents to allow for changing availability.
	*			Seperated from returning so that the optimized agents can be accessed without needing to generate a new schedule each time.
	***/
	void optimize_agents();

	/***
	* \brief	New implementation of optimize_agents. Replace this if new implementation is successful and better.
	* \details	The optimized agents are stored seperately from the original agents to allow for changing availability.
	*			Seperated from returning so that the optimized agents can be accessed without needing to generate a new schedule each time.
	***/
	void optimize();

	/***
	* \brief	Returns the number of agents currently in the schedule pool.
	***/
	int num_agents() const;
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

int Skadule::num_agents() const {
	return agents.size();
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

std::vector<std::vector<std::string>> Skadule::get_schedule_matrix() const {
	std::vector<std::vector<std::string>> matrix(7, std::vector<std::string>(24, "None"));
	for (const ScheduleAgent& agent : optimized_agents) {
		for (int day = 0; day < 7; ++day) {
			int start = agent.availability[day][0];
			int end = agent.availability[day][1];
			for (int hour = start; hour < end; ++hour) {
				if (matrix[day][hour] == "None") {
					matrix[day][hour] = agent.name;
				} else {
					matrix[day][hour] += ", " + agent.name;
				}
			}
		}
	}
	return matrix;
}

void Skadule::print_schedule() const {
	std::vector<std::vector<std::string>> matrix = get_schedule_matrix();
	std::cout << "Schedule:\n";
	std::cout << "Time  | Mon       | Tue       | Wed       | Thu       | Fri       | Sat       | Sun       \n";
	std::cout << "-----------------------------------------------------------------------------------------\n";
	for (int hour = 0; hour < 24; ++hour) {
		std::cout << (hour < 10 ? " " : "") << hour << ":00 | ";
		for (int day = 0; day < 7; ++day) {
			std::cout << matrix[day][hour] << " | ";
		}
		std::cout << "\n";
	}
}

void Skadule::optimize() {
	/***
	* Step 1: Collect all the time boundaries from agent availability
	***/

	/***
	* Step 2: Identify ideal shift segments based on time boundaries and some criteria
	*	- Shifts should be between 5 and 8 hours long, ideally around 6 hours
	*	- Shifts CANNOT be shorter than 4 hours
	***/

	/***
	* Step 3: Assign agents to shifts based on priority system
	***/
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
	for (int day = 0; day < 7; ++day) {

		// Collect time boundaries
		std::vector<int> boundaries;
		for (const ScheduleAgent& agent : agents) {
			int start = agent.availability[day][0];
			int end = agent.availability[day][1];

			if (start < end) {
				boundaries.push_back(start);
				boundaries.push_back(end);
			}
		}

		if (boundaries.empty()) continue;

		std::sort(boundaries.begin(), boundaries.end());
		boundaries.erase(std::unique(boundaries.begin(), boundaries.end()), boundaries.end());

		// Create segments
		for (size_t i = 0; i + 1 < boundaries.size(); ++i) {

			int seg_start = boundaries[i];
			int seg_end = boundaries[i + 1];
			int seg_len = seg_end - seg_start;

			if (seg_len <= 0) continue;

			std::vector<int> candidates;

			// Find available agents
			for (size_t a = 0; a < agents.size(); ++a) {

				int start = agents[a].availability[day][0];
				int end = agents[a].availability[day][1];

				if (seg_start >= start && seg_end <= end) {

					if (agent_trackers[a].total_hours + seg_len > 40)
						continue;

					bool rest_ok = true;

					if (!agent_trackers[a].assigned_shifts.empty()) {
						const Shift& last =
							agent_trackers[a].assigned_shifts.back();

						int rest = (day * 24 + seg_start) - (last.end_time);

						// Allow back-to-back segments (rest == 0)
						if (rest > 0 && rest < 10) {
							rest_ok = false;
						}
					}

					if (rest_ok)
						candidates.push_back(a);
				}
			}

			// Sort candidates by least hours worked
			std::sort(candidates.begin(), candidates.end(),
				[&](int a, int b) {
					return agent_trackers[a].total_hours <
						agent_trackers[b].total_hours;
				});

			int assigned = 0;

			for (int idx : candidates) {

				if (assigned >= 2) break;

				Shift shift;
				shift.start_time = day * 24 + seg_start;
				shift.end_time = day * 24 + seg_end;
				shift.assigned_agent = agent_trackers[idx].agent;

				agent_trackers[idx].assigned_shifts.push_back(shift);
				agent_trackers[idx].total_hours += seg_len;

				assigned++;
			}
		}
	}

	// Extract optimized agents from trackers and store in optimized_agents vector
	for (AgentTracker& tracker : agent_trackers) {
		// Initialize with "no shift"
		for (int d = 0; d < 7; ++d) {
			tracker.agent->availability[d][0] = -1;
			tracker.agent->availability[d][1] = -1;
		}

		for (const Shift& shift : tracker.assigned_shifts) {
			short day = shift.start_time / 24;
			short start = shift.start_time % 24;
			short end = shift.end_time % 24;

			if (tracker.agent->availability[day][0] == -1) {
				// first shift of the day
				tracker.agent->availability[day][0] = start;
				tracker.agent->availability[day][1] = end;
			}
			else {
				// expand range
				tracker.agent->availability[day][0] = std::min(tracker.agent->availability[day][0], start);
				tracker.agent->availability[day][1] = std::max(tracker.agent->availability[day][1], end);
			}
		}

		optimized_agents.push_back(*tracker.agent);
	}

	// Clean up dynamically allocated memory for agent trackers
	for (AgentTracker& tracker : agent_trackers) {
		delete tracker.agent;
	}
}
#endif