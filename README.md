# **Raycast 2D Maze Game**

## **Introduction**
The **2D Raycasting Maze Game** is a first-person 3D maze game similar to early titles like Wolfenstein 3D. It is developed using the C programming language and the SDL2 library to render a 3D world from a 2D map via raycasting. The player navigates through mazes while avoiding obstacles, with a goal of reaching the maze's endpoint. The game runs on both macOS and Linux.

### **Project Links**
- **Project Landing Page**: [https://peplin-2d-maze.mystrikingly.com]
- **Author LinkedIn**: [https://www.linkedin.com/in/chidiebube-oluoma]

## **Installation**
1. Clone the repository:
   ```bash
   git clone https://github.com/Peplinn/Maze-Game.git
   ```
2. Navigate to the project directory:
   ```bash
   cd 2D-Raycasting-Maze-Game
   ```
3. Install SDL2 if it's not already installed:
   - On macOS:
     ```bash
     brew install sdl2
     ```
   - On Ubuntu:
     ```bash
     sudo apt-get install libsdl2-dev
     ```

4. Compile the code:
   ```bash
   	gcc src/*.c -Wall -Werror -Wextra -pedantic -o main.exe -lmingw32 -lSDL2main -lSDL2
   ```

5. Alternatively, compile the project using `make`:
   ```bash
   make
   ```

## **Usage**
1. Run the game with a provided map:
   ```bash
   ./maze defaultMap
   ```

2. Navigate the maze using:
   - **Arrow keys**: Rotate and move forward/backward.
   
3. Create custom maps to play by following the map file format.

### **Map File Format**
- `0`: Floor/walkable space
- `1`: Red Wall
- `2`: Green Wall
- `3`: Blue Wall
- `4`: Yellow Wall
- `p`: Player start position
- `w`: End goal

## **Contributing**
If you'd like to contribute to this project:
1. Fork the repository.
2. Create your feature branch:
   ```bash
   git checkout -b feature/AmazingFeature
   ```
3. Commit your changes:
   ```bash
   git commit -m 'Add some AmazingFeature'
   ```
4. Push to the branch:
   ```bash
   git push origin feature/AmazingFeature
   ```
5. Open a pull request.

## **Related Projects**
- **Wolfenstein 3D** - Inspiration for this project.
- **Lodev's Raycasting Tutorial** - Core algorithms for raycasting.
- **Lazy Foo' SDL Tutorials** - SDL2 tutorials used in development.

## **Licensing**
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
