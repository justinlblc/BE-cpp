# **C++ Project for IMT Atlantique Advanced C++ programming course**

This is a C++ project created for the Advanced C++ programming course at the french top engineering school IMT Atlantique.

## What is the Project Goal?

### What we started from:

This project simulates the evolution of *animals* in an environment. Those animals move in this environment accordind to their speed and orientation.

### Features we added:

We added many features to the animals behaviors:

- Accessory: each animal can have a shell, a fin and/or camouflage. Thos can affect the animals speed, resistance to collisions and stealth.
- Sensors: each animal can have ears and eyes, which allow them to detect or not other animals in a certain area around them.
- Behaviors: each animal can have one of the 5 different behaviors we created: gregarious (their orientation is bases on the avergae orientation of their neighbours),
kamikaze (who always target their nearest neighbours), shy (who flee at full speed whenever they are surrounded by too much animals), farsighted (who tend
to avoid collisions) and MultiBestiole (those animals will change their behaviors along the simulation).
- Initial Population: at each execution of our code, you can change which behaviors you want your animals to have or not, and how many animals you want to begin the 
simulation.
- At each step of the simulation, an animal can make an identical clone of himself.
- At each collisions, an animal can either die or survive and go to the opposite direction.
- At each step of the simuation, an animal with a random behavior can born, but always according to the inital choices of the user.

## The simulation:

### How to download the code (Linux users):

Get the code on your local machine:

```
git init
git clone https://github.com/justinlblc/BE-cpp.git
```

Create the executable file:

```
cd BE-cpp
make
./main
```

### What type of simulations can you launch?

At each simuation, you will be asked to enter the pourcentage of each behaviors you want for the initial population, with the inital number of animals. For the rest of the simulation,
no other behaviors than those you selected will be reachable for the animals.

## Further possibilities:

You can also change the default settings of the simulation, inside the *Milieu.cpp*. The static attributes declared in the first lines are the limits for the different
characteristics of the animals: maximum speed, maximum resistance for the shell etc...

You will be able to see how the population evolves according to theses modifications!
