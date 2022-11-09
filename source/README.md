## Gameplay:

The Potter (P) in blue appears at a random location on the map given by the user and his goal is to collect 10 yellow-colored gems (s) so that the yellow-coloured scroll (S) eventually appears and if he collects it he will win the game. His enemies are the Gnome(G) green and the beast of Traal(T) red.

### Gnome:
The Gnome will chase Potter across the track finding the shortest path where wherever he is until he catches him. If Potter decides to stand still the Gnome will eventually will find him and eat him.

### Traal:
Wander Mode: the Traal beast does not chase Potter but a 4 block interchangeable position distance with priority Up - Left - Down - Right. That is, if there is a 4 block position above Potter the Traal will try to reach that position, if there is no position it will search 4 blocks to the left of Potter, if it doesn't find it then it will go 4 blocks down and if again if he doesn't find it, he will go 4 blocks to the right.

**Chase Mode**: if the Traal is 7 blocks away from Potter then it will enter -Chase Mode- and start chasing him (Like the Gnome chases him) for 10 rounds. In case the 10 rounds are over then Traal will stop chasing him and enter -Wander Mode- again for 20 rounds. Note that if the Traal enters Chase Mode it will continue to chase Potter regardless of the distance between them.

When the game starts the Traal is in Wander Mode but Chase Mode is direct ready to be activated.

The Traal cannot move in the opposite direction from the direction it is facing (180 degrees). E.g. if the direction is Up it cannot move Down in the next turn or if it goes Right its next move cannot be Left. The only condition he is allowed to do to make such a move is if he is in a dead end.


### Implementation:
Both monsters share the same movement algorithm, and the way they compute the next move is as follows.
	<br>1. They accept parameters from Engine the Potter's position and the dimensions of the table
	<br>2. They create a table Y x X.
	<br>3. Fill the table with -1 values.
	<br>4. In the position they want to target they set the value 0. For Gnome position 0 is then Potter, for Traal it is the 4 block distance from Potter in Wander mode and Potter himself in Chase Mode.
	<br>5. In the position where they (the monsters) are they set the value 999.
	<br>6. They search the table for element 0 and set on the 4 sides the value 1 except if it's a wall (Distance 1 from Potter).
	<br>7. Then they search the table again for the elements 1 and set the sides to (If the values there are -1 which means they have not been processed) the value 2. This continues by increasing the value until one of the sides found is element 999 i.e. the monster. Depending on the side found, the appropriate side will be selected move.
	<br>8. At each Potter move steps 1-7 are repeated.

### Dept:
Monsters hold a mutable as an attribute which when it is 1 means that in the previous round they stepped over a stone or if it is 2 they stepped over a scroll. On their next round of movement, the monster's letter is deleted from the screen, s or S is written and the letter is printed in the next position.

### Only Way:
Traal's method that returns 1 if the only move possible is the one forbidden If the only move that is allowed is the one that is prohibited. This will allow Traal to move in the opposite direction from its direction.
