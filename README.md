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

Maybe it would be possible to use a ratio system to determine how important it is that john is scheduled for more hours?
(30-10)/37 = 2.86

Compare with another agent vying for the same segment of time
Billy
    - Total available hours remaining: 20
    - Total hours scheduled so far: 15
    - Ideal hours: ~20
(20-15)/20 = 0.25)

Billy is much closer to fulfilling their ideal hours worked, so they would be chosen over john.

### Some other factors to consider
- Wage ratio = total wages in a day / total profit in a day. Wage ratio should be below a certain threshold (provided by user? Also need to provide predicted profits)
- Required assignments like a manager needing to do a task on a certain day (easy to implement)
- Agent preferences, from simple stuff like getting at least 2 days off to more complex things like preferred shift lengths and such