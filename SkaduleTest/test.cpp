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

TEST(SkaduleTest, OptimizeAgents) {
	ScheduleAgent agent1("Alice");
	agent1.availability[0][0] = 9; // Monday morning
	agent1.availability[0][1] = 17; // Monday evening
	ScheduleAgent agent2("Jim");
	agent2.availability[0][0] = 13; // Monday afternoon
	agent2.availability[0][1] = 21; // Monday night

	Skadule skadule;
	skadule.add_agent(agent1);
	skadule.add_agent(agent2);
	skadule.optimize_agents();
	std::vector<ScheduleAgent> optimized_agents = skadule.get_optimized_agents();
	skadule.print_schedule();

	EXPECT_TRUE(optimized_agents.size() == 2);
	EXPECT_TRUE(optimized_agents[0].name == "Alice");
	EXPECT_TRUE(optimized_agents[1].name == "Jim");

	EXPECT_TRUE(optimized_agents[0].availability[0][0] == 9);
	EXPECT_TRUE(optimized_agents[1].availability[0][1] == 21);
}