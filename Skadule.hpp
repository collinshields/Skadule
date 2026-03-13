#ifndef SKADULE_HPP
#define SKADULE_HPP

#include <string>
#include <vector>

/***
* \brief	Represents an agent with a name and a desired schedule.
***/
struct ScheduleAgent {
	std::string name;
	int desired_time_slots[7][2]; // 7 days, desired start and end time for each day (24-hour format, e.g., 9 for 9 AM, 17 for 5 PM)
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
class Schedule {
protected:
	ScheduleAgent agents[100];
	std::vector<std::string> schedule;
public:
	/***
	* \brief	Adds an agent to the agent pool and returns the new schedule.
	* \param	agent	The agent to add to the pool.
	* \return	The new schedule after adding the agent.
	***/
	std::vector<std::string> add_agent(const ScheduleAgent agent) const;
	/***
	* BRIEF: Gets an afeb
	***/
	const ScheduleAgent* get_agent_desired_schedule(const std::string& name) const;
	std::vector<std::string> get_schedule() const;
	void update_schedule() const;
};
#endif