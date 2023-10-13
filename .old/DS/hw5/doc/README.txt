HOMEWORK 5: LINKED TRAIN CARS


NAME:  Robert Zhu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

ur mom

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  -6



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.

Highly Optimal ShipFreight Logic:
Find the number of engines to use. First calculate the weight of all freight. Then incrementally add engines until the minimum speed is theoretically possible. (Optional: use 170 as the weight of each engine in this calculation, to ensure some buffer room.) If it is not possible to reach the minimum speed, then after adding all engines, remove freight cars one-by-one until we are able to reach the necessary speed. To choose the next freight car to remove, find the necessary weight to reach the minimum speed, and the difference from our current weight. Choose the freight car whose weight is closest to this difference. If there is the choice between a freight car that is less than the difference, and one that is more than the difference, always choose the one that is more than the difference. This choice only happens once. Subsequently, these freight cars will not be shipped.
We now know the number of engines we need to use, and we know that it is necessarily possible to achieve the minimum speed shipping all the non-filtered freight cars.
Distribute the correct number of engines that we just calculated prior into the vector, with each train having exactly one engine. Distribute freight cars to each train as evenly as possible, without regard for minimum speed requirements, but with regard for maximum cars per train requirements.
Find the train with the largest weight, and find the train with the smallest weight. Note the difference of their weights. Find the heaviest car in the train with the largest weight, and find the car in the lighter train where the difference in weight between the two cars is the closest to half but strictly less than the difference in weight between the two trains. Swap the two. Repeat this until it is no longer possible to find two cars to swap.
Now, if possible, join the train fragments into longer trains. A greedy approach works adequately here.


DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how
to prioritze between these goals.  Describe your priorization and your
implementation.


MISC. COMMENTS TO GRADER:
Optional, please be concise!

