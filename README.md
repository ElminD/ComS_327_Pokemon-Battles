# ComS_327_Pokemon-Battles

COM S 327, Spring 2022
Programming Project 1.08
Pokemon Battles ´
The most important part of this update is to add the Pokemon battle minigame. ´
If you are not familiar with Pokemon battles (or if you are), here’s a YouTube video of an example ´
battle: https://www.youtube.com/watch?v=Jpdy9pZyGH4. Please don’t ask me why this video has over 2.1
million views. I don’t know. Perhaps there are a lot of professors out there having their students write
Pokemon-inspired games? ´
In order to battle, a trainer must have at least one Pokemon. The PC will be given the choice of three ´
randomly generated level 1 Pokemon when the game starts. All generated trainers will be given at least one ´
random Pokemon. Assuming the trainer has n Pok ´ emon, there is a 60% probability that the trainer will get ´
an (n+1)th Pokemon, up to a maximum of 6 Pok ´ emon. The generated trainers’ Pok ´ emon will be generated ´
with levels and movesets as per the Pokemon generation rules for their map. ´
Pokemon battles are characterized by a turn-based interaction between two trainers or between a trainer ´
(the PC) and a wild Pokemon (the ones which appear in the tall grass). Battles with a wild Pok ´ emon end ´
with the capture of the wild Pokemon, with either the wild Pok ´ emon or the trainer fleeing the battle, or with ´
either the wild Pokemon or all of the trainer’s Pok ´ emon getting knocked out. Trainer battles end when all of ´
one trainer’s Pokemon are knocked out. Pok ´ emon are not available for capture in trainer battles. ´
A Pokemon is knocked out when it’s hitpoints fall to zero. A knocked out Pok ´ emon is unavailable for ´
battle until it is revived.
As with other areas of our game, we’ll be simplifying Pokemon game mechanics in implementing bat- ´
tling. The most important simplifications we’ll make are that we won’t be implementing status effects (there
are simply too many of them to make it a reasonable assignment; of course, you’re welcome to do it if you
want to) and we won’t implement Pokemon abilities. ´
Each party takes turns in a Pokemon battle, with each taking an action each turn. If a trainer’s chosen ´
action is anything other than a Pokemon move, this receives maximum priority. If both moves in a turn are ´
Pokemon moves, then the Pok ´ emon whose move has the higher priority (moves.priority) goes first; if both ´
moves have the same priority, then the Pokemon with the highest speed (level adjusted) goes first, and if that ´
is also equal, then choose one at random.. If a Pokemon is knocked out or captured before using its move, ´
its turn is forfeit.
Pokemon moves can miss. The chance of a Pok ´ emon evading a move is modified by status effects, ´
which we will ignore. This simplifies accuracy to be a simple percentage given by moves.accuracy. If rand()
mod 100 < moves.accuracy, the move hits; otherwise it misses.
Once a move hits, damage is given by the following formula:

2×Level
5 + 2
× P ower ×
Attack
Defense
50
+ 2!
× Critical × random × ST AB × T ype
where Level is the level of the attacking Pokemon, ´ P ower is the power of the move (moves.power); Attack
is the attacking Pokemon’s level-adjusted attack stat; ´ Defense is the defending Pokemon’s level-adjusted ´
defense stat; Critical is 1.5 if the attack is a critical hit, otherwise 1; random is a uniformly distributed
random number in [85, 100]; ST AB is the same type attack bonus of 1.5 if the move’s type matches the
attacking Pokemon’s type, else 1; and ´ T ype is the type effectiveness modifier of 0, .25, .5, 1, 2, or 4,
depending on both the move type and the target Pokemon’s type (implementation saved for 1.09; for now,  
you may use 1). The move’s damage is decremented from the defending Pokemon’s HP, and the defender is ´
knocked out if its HP reaches zero.
In order to calculate STAB, you’ll need the attacking Pokemon’s type. Parse in ´ pokemon types.csv
for pokemon type information. You’ll find that many pokemon have two types (are dual typed). A move
gets STAB if any of a Pokemon’s types matches the move’s type. ´
An attack earns a critical hit if it hits and a random number in the range [0, 255] is less than a threshold
value given by b
BaseSpeed
2
c (floor is just integer division!) where BaseSpeed is the base value (not leveladjusted) of the attacking Pokemon’s speed stat. ´
During battle, the PC has the following options, which should all be implemented in the battle placeholder(s) that were added the previous two weeks:
1. Fight - The active Pokemon uses one of its moves; player chooses the move if PC, otherwise the AI ´
chooses (see below).
2. Bag - Use an item from the trainer’s inventory. We will implement revives, potions, and Pokeballs ´
(more below)
3. Run - Attempt to flee the battle
4. Pokemon - Switch to a different active Pok ´ emon. A trainer may have up to 6 active Pok ´ emon. ´
The fight mechanic is described above.
The bag mechanic consumes an item from the trainer’s inventory. The trainer must be carrying the item
in order to use it. A revive will revive a knocked-out Pokemon and restore it to half its max HP. A potion ´
will restore up to 20 HP, never taking the Pokemon above its max HP value. Pok ´ eballs may only be used in ´
battles with wild Pokemon and will attempt to capture them. ´
The PC may only run from wild Pokemon. Battles with trainers must go until all of one trainer’s ´
Pokemon are knocked out. Attempts to run may fail. Escape is calculated by ´
OddsEscape =
$
SpeedT rainer × 32
b
SpeedW ild
4
cmod256%
+ 30 × Attempts
where SpeedT rainer is the level-adjusted speed to the trainer’s active Pokemon; ´ SpeedW ild is the leveladjusted speed to the wild Pokemon; and ´ Attempts is the number of times the trainer has attempted to
escape this battle (including the current attempt). OddsEscape is out of 256, thus if rand() mod 256 <
OddsEscape, the trainer escapes.
Only one Pokemon may be active in a battle at any time. Switching Pok ´ emon will change the active ´
Pokemon. A Pok ´ emon may only be switched in if it is not knocked out. A trainer may carry up to 6 Pok ´ emon ´
at a time. The first Pokemon (e.g., in the array) always starts the Pok ´ emon battle, and switching Pok ´ emon ´
uses the turn.
We’ll implement Pokemarts and Pok ´ emon centers in 1.09, so for now, simply start the PC with a small ´
number of potions, revives, and Pokeballs. These items are usable in battle (Pok ´ eballs are only available ´
in battles with wild Pokemon). Details of the catch mechanics will also be in 1.09. For now, if the PC has ´
fewer than 6 Pokemon, every attempt to catch succeeds, but if the PC has 6 Pok ´ emon, every attempt to catch ´
will cause the wild Pokemon to escape from the Pok ´ emon and flee. ´
The NPC side of Pokemon battles needs to be “AI” driven. I put this in quotes because you may make ´
your AI as simple or as complicated as you like. It would be sufficient to choose a random move from the
first Pokemon, switching Pok ´ emon only when the current Pok ´ emon is knocked out. ´
Pokemon are not restored to full health automatically after battle. In 1.09, they can be restored at ´
Pokemon centers for free, but for now the only want to restore them is to use revives and potions. Add the ´
’b’ command to allow bag access outside of battle so that your trainer can heal Pokemon at any time. ´
