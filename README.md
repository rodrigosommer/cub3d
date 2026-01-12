# cub3D - My First RayCaster with miniLibX

A Wolfenstein 3D inspired raycasting game engine built in C using the miniLibX library.

## 🎮 About

This project recreates the classic first-person shooter experience using raycasting techniques. Navigate through a maze, interact with doors, battle enemies, and experience smooth 3D rendering - all from a first-person perspective!

## ✨ Features

### Mandatory
- ✅ **Raycasting Engine** - Real-time 3D rendering from 2D maps
- ✅ **Textured Walls** - Different textures for N/S/E/W walls
- ✅ **Colored Floors & Ceilings** - Customizable RGB colors
- ✅ **Smooth Movement** - WASD controls for navigation
- ✅ **Camera Rotation** - Arrow keys for looking around
- ✅ **Map Parsing** - Custom .cub file format
- ✅ **Error Handling** - Comprehensive validation

### Bonus
- ✅ **Wall Collisions** - Realistic movement physics
- ✅ **Minimap** - Real-time overview of your position
- ✅ **Interactive Doors** - Open and close with animations
- ✅ **Animated Sprites** - Multiple enemy types with AI
- ✅ **Mouse Support** - Look around with your mouse
- ✅ **Weapon System** - Katana with attack animations
- ✅ **Enemy AI** - Pathfinding and line-of-sight detection
- ✅ **Combat System** - Health and damage mechanics

## 🚀 Quick Start

### Prerequisites
- GCC compiler
- Make
- X11 libraries (for miniLibX)
- Linux or macOS

### Installation

```bash
# Clone the repository
git clone <your-repo-url> cub3D
cd cub3D

# Compile
make

# Run with a map
./cub3D maps/mandatory_simple.cub
```

## 🎯 Controls

### Movement
- `W` - Move forward
- `A` - Strafe left
- `S` - Move backward
- `D` - Strafe right

### Camera
- `←` - Rotate left
- `→` - Rotate right
- `Mouse` - Look around (bonus)

### Actions
- `E` - Interact with doors (bonus)
- `SPACE` - Attack with katana (bonus)
- `ESC` - Quit game

## 📁 Map Format

Maps use the `.cub` extension with the following format:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

### Map Characters
- `1` - Wall
- `0` - Empty space
- `N/S/E/W` - Player start position (facing North/South/East/West)
- `D` - Door (bonus)

## 🛠️ Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Recompile from scratch
make bonus  # Compile with bonuses (same as make)
```

## 📋 Technical Details

### Norminette Compliant
- All 54 source files pass norminette
- Functions < 25 lines
- Functions < 5 variables
- Functions < 4 parameters
- Files < 5 functions

### Libraries Used
- **miniLibX** - Graphics library
- **libft** - Custom C library
- **math** - Mathematical functions

### Key Algorithms
- **DDA Raycasting** - Core 3D rendering
- **Flood Fill** - Map validation
- **Z-Buffer** - Sprite depth sorting
- **A* Pathfinding** - Enemy AI (simplified)

## 🎨 Features in Detail

### Raycasting Engine
Uses the Digital Differential Analysis (DDA) algorithm to cast rays and calculate wall distances, creating the 3D perspective from a 2D map.

### Texture Mapping
Different textures are applied based on which side of the wall is hit (North, South, East, West), creating visual variety.

### Sprite System
Enemies are rendered as sprites using a Z-buffer for proper depth sorting, ensuring correct rendering order.

### Door Mechanics
Doors have four states: closed, opening, open, and closing, with smooth animations between states.

### Enemy AI
Enemies patrol randomly, detect the player within aggro range, and navigate towards the player using line-of-sight checks.

## 🧪 Testing

### Run Tests
```bash
# Test error handling
./cub3D                          # Should show usage error
./cub3D invalid.txt              # Should show extension error

# Test mandatory features
./cub3D maps/mandatory_simple.cub

# Test bonus features
./cub3D maps/map.cub

# Check for memory leaks
valgrind --leak-check=full ./cub3D maps/mandatory_simple.cub

# Verify norminette compliance
norminette src/*.c inc/*.h
```

## 📚 Project Structure

```
cub3D/
├── Makefile
├── inc/
│   └── cub3d.h
├── src/
│   ├── main.c
│   ├── parse*.c          # Map parsing
│   ├── render*.c         # Rendering engine
│   ├── raycasting*.c     # Raycasting algorithm
│   ├── movement*.c       # Player controls
│   ├── door*.c           # Door system (bonus)
│   ├── sprite*.c         # Sprite system (bonus)
│   ├── katana*.c         # Weapon system (bonus)
│   └── minimap*.c        # Minimap (bonus)
├── libft/                # Custom C library
├── minilibx-linux/       # Graphics library
├── maps/                 # Test maps
└── textures/             # Wall textures
```

## 🐛 Known Issues

None currently! If you find any, please let me know.

## 📖 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D](http://users.atw.hu/wolf3d/)
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## 👤 Author

**rsommer**
- 42 School: rsommer
- GitHub: [@yourusername](https://github.com/yourusername)

## 📝 License

This project is part of the 42 School curriculum.

## 🙏 Acknowledgments

- John Carmack and John Romero for Wolfenstein 3D
- Lode Vandevenne for the raycasting tutorial
- 42 School for the project subject
- All the testers and evaluators

---

**Grade**: Pending evaluation

Made with ❤️ at 42 School
