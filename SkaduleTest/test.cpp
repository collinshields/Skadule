#include "pch.h"
#include "../Skadule.hpp"

TEST(SkaduleTest, AddAgent) {
	// Adding agents
	ScheduleAgent agent1("Alice");
	ScheduleAgent agent2("Jim");
	Skadule skadule;
	skadule.add_agent(agent1);
	EXPECT_TRUE(skadule.num_agents() == 1);
	skadule.add_agent(agent2);
	EXPECT_TRUE(skadule.num_agents() == 2);

	// Retrieving agents
	std::string name = "Alice";
	ScheduleAgent* retrieved_agent = skadule.get_agent(name);
	EXPECT_TRUE(retrieved_agent != nullptr);
	EXPECT_TRUE(retrieved_agent->name == "Alice");
}

TEST(SkaduleTest, RemoveAgent) {
	ScheduleAgent agent1("Alice");
	ScheduleAgent agent2("Jim");
	Skadule skadule;
	skadule.add_agent(agent1);
	skadule.add_agent(agent2);

	// Removing agents
	std::string name = "Alice";
	skadule.remove_agent(agent1);
	EXPECT_TRUE(skadule.num_agents() == 1);
	EXPECT_TRUE(skadule.get_agent(name) == nullptr);
}