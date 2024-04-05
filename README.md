About this project
===
細胞分裂(Cell Division) is a game that both player and enemies(computers) are cells that can chase or eat each other while in the gameplay. 
Player can eat the red dots on the map to gain cell mass and avoid being eaten by enemies, and player needs to find the way out to win in the game.
The program is written in C/C++ using Object-Oriented Programming concept.

Motivation
===
Agar.io is a well known massive multiplayer online action game created by Brazilian developer Matheus Valadares in 2015, this game went viral in 2015-2021 because of online content creators such as YouTubers and Twitch streamers. In this game, players control one or more circular cells in a map representing a Petri dish. The goal is to gain as much mass as possible by eating cells and player cells smaller than the player's cell while avoiding larger ones which can eat the player's cells. This easy-to-play gaming experience contributes to the success of this online game. In fact, inspired by Agar.io's success, Steven Howse released the snake-themed Slither.io in March 2016, which also went viral instantly.

Therefore, we decided to use Agar.io as our OOP final project benchmark and tried to add new elements that Agar.io didn't have. For simplicity, we only allowed 1-player playing at the same time.

Detail of the game
===
- Player controls the red cell
- Player can split the cell into at most 16 sub-cells
- Enemies control the blue cells
- Enemies will either chased you or away from you depends on your cell mass and their cell mass
- The game map is based on randomly-generated maze, player needs to figured out the exit of maze in order to win the game
- There is plenty of red dots on the map, which increase the player's cell mass if it touches
- Red dots will continue generating during the gameplay
- Besides the cells are included, the canons are randomly added to map's wall during the gameplay as well
- The canons will shoot players with small blue dots, which decrease the player's cell mass if it touches

Here are some of gameplay screen shot:
![image](<https://github.com/barrenshore/OOP-Final-Project/blob/main/screen1.jpg>)
![image](<https://github.com/barrenshore/OOP-Final-Project/blob/main/screen2.jpg>)

Here are some of algorithms or methods we used:
![image](<https://github.com/barrenshore/OOP-Final-Project/blob/main/algorithm.jpg>)
![image](<https://github.com/barrenshore/OOP-Final-Project/blob/main/active_state.jpg>)

