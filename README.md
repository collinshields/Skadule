# Skadule
A library for automatically creating schedules given a set of agents with availabilities

## Plans
- [ ] More advanced and effecient scheduling algorithm
- [ ] Add support for multiple agents with the same name
- [ ] Access point for using the library (GUI interface, maybe hook into other system like google sheets)

## Idea - Pick method
For any given segment of time, it should be possible to rank agents through some kind of priority system. Probably factoring
the total hours they are scheduled for already, the total hours they are available, their ideal hours worked.

### A thought expirement
John
- Total available hours remaining: 37
- Total hours scheduled so far: 10
- Ideal hours: ~30

Maybe it would be possible to use a ratio system to determine how important it is that john is scheduled for more hours?\
(30-10)/37 = 2.86

Compare with another agent vying for the same segment of time\
Billy
- Total available hours remaining: 20
- Total hours scheduled so far: 15
- Ideal hours: ~20  
(20-15)/20 = 0.25)

Billy is much closer to fulfilling their ideal hours worked, so john would be prioritized.

BUT, this has a problem. If one agent has a lot of available hours they will never be chosen over an agent with fewer available hours. With multiple other agents
this could mean not getting scheduled at all. It's important to consider if an agent needs to slot to get close to their ideal hours, but balancing hours fairly
should be prioritized.

### Another avenue
Maybe a thresholding system can be used in conjunction with the ratios. If one agent is already scheduled for more than a certain threshold difference of hours
compared to another agent, the one with fewer hours is prioritized over the one that "needs" the hours more.

This threshold would need to be tweaked, but let's look at another example:
John
    - Total available hours remaining: 80
    - Total hours scheduled so far: 10
    - Ideal hours: ~30
(30-10)/80 = 0.25
Billy
    - Total available hours remaining: 20
    - Total hours scheduled so far: 20
    - Ideal hours: ~30
(30-20)/20 = 0.5

Billy would normally get priority, but John has much fewer hours so far, so a threshold of 5-10 hours could help john get the hours.
This issue would be more significant when available hours are more limited, so it might be best to have something like this only activate when both agents 
have a low amount of availble hours remaining. Just always prioritizing balance MIGHT be better though. Maybe there is an in-between ideal somewhere.


### Some other factors to consider
- Wage ratio = total wages in a day / total profit in a day. Wage ratio should be below a certain threshold (provided by user? Also need to provide predicted profits)
- Required assignments like a manager needing to do a task on a certain day (easy to implement)
- Agent preferences, from simple stuff like getting at least 2 days off to more complex things like preferred shift lengths and such