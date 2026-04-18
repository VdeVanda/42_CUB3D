*This project has been created as part of the 42 curriculum by vabatist, vaires-m.*

#

```text
 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 
```
<div align="center">
  <p><strong>A graphical representation project inspired by the world-famous Wolfenstein 3D game, built from scratch in C</strong></p>
  <br>
  <img src="https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c" alt="C">
  <img src="https://img.shields.io/badge/Graphics-MiniLibX-black?style=flat-square" alt="MiniLibX">
  <img src="https://img.shields.io/badge/Memory-Leak%20Free-brightgreen?style=flat-square" alt="No Memory Leaks">
  <img src="https://img.shields.io/badge/42-Norm%20Compliant-yellow?style=flat-square" alt="42 Norm">
</div>

## Description

cub3D is a 3D graphical representation project inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. This project uses ray-casting techniques to create a dynamic first-person view inside a maze. The goal is to explore realistic 3D projection, work with textures, colors, and implement basic game mechanics.

### Key Features

- **Ray-casting engine**: Renders a 3D perspective from a 2D map
- **Textured walls**: Different wall textures for North, South, East, and West orientations
- **Customizable colors**: Floor and ceiling colors configurable via RGB values
- **Smooth controls**: WASD for movement, arrow keys for camera rotation
- **Map parsing**: Validates and loads custom `.cub` map files

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will:
1. Build the MinilibX library
2. Build the libft library
3. Compile all source files with `-Wall -Wextra -Werror` flags
4. Generate the `cub3D` executable

### Cleaning

```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Recompile from scratch
```

### Execution

Run the program with a map file as argument:

```bash
./cub3D maps/map.cub
```

### Map File Format

The map file must have a `.cub` extension and contain:

1. **Texture paths** (one per line):
   - `NO ./path_to_north_texture.xpm`
   - `SO ./path_to_south_texture.xpm`
   - `WE ./path_to_west_texture.xpm`
   - `EA ./path_to_east_texture.xpm`

2. **Colors** (RGB format, range 0-255):
   - `F R,G,B` (Floor color)
   - `C R,G,B` (Ceiling color)

3. **Map** (composed of valid characters):
   - `0` - Empty space
   - `1` - Wall
   - `N`, `S`, `E`, `W` - Player start position and orientation
   - ` ` (space) - Void (map borders)

#### Map Rules

- Map must be closed/surrounded by walls
- Map must contain exactly **one** player start position
- All elements (textures and colors) must be defined before the map
- Empty lines are allowed

#### Example Map File

```
NO assets/north.xpm
SO assets/south.xpm
WE assets/west.xpm
EA assets/east.xpm

F 139,69,19
C 128,152,9

11111111111111111
100000000000000011
11111111111000000111111
1000N000000000000000001
10000000000000001111111
1000000111111111111111111111
1000000000000000000000000001
1111111111111111111111111111
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (Left Arrow) | Rotate camera left |
| `→` (Right Arrow) | Rotate camera right |
| `ESC` | Close window and exit |

You can also close the window by clicking the red cross.

### Error Handling

The program displays `Error\n` followed by an explicit error message when:
- Wrong number of arguments provided
- Invalid file format or extension
- Missing or invalid texture files
- Invalid RGB color values
- Map not enclosed by walls
- Missing or multiple player start positions
- Invalid characters in the map

## Resources

### Ray-Casting Theory

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting tutorial with mathematical explanations
- [Wolfenstein 3D on Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Historical context for the first FPS game

### MinilibX Documentation

- [42 Docs - MinilibX](https://harm-smits.github.io/42docs/libs/minilibx) - Unofficial MinilibX documentation
- [MinilibX Tutorial](https://github.com/keuhdall/images_example) - Practical examples for image manipulation

### Technical References

- **Trigonometry**: Used for calculating ray directions and player movement
- **DDA Algorithm**: Digital Differential Analyzer for ray-casting grid traversal
- **Bresenham's Line Algorithm**: Efficient line drawing for rendering

### Tools Used

- **MinilibX**: 42's graphics library for rendering
- **libft**: Custom C library with essential functions
- **Make**: Build automation
- **Norminette**: 42's coding standard checker

## Project Structure

```
.
├── Makefile              # Build configuration
├── README.md             # This file
├── cub3D.h               # Main header file
├── main.c               # Main program entry point
├── assets/               # Texture files (.xpm)
├── maps/                 # Map files (.cub)
├── includes/             # External libraries
│   ├── libft/            # Custom C library
│   └── minilibx-linux/   # Graphics library
└── srcs/                 # Source files
    ├── cleanup.c         # Memory management
    ├── create.c          # Image and texture creation
    ├── init.c            # Initialization functions
    ├── map.c             # Map rendering utilities
    ├── move.c            # Player movement and controls
    ├── player.c          # Player management
    ├── rays.c            # Ray-casting calculations
    ├── walls.c           # Wall rendering
    └── parsing/          # Map file parsing
        ├── check_map.c
        ├── map_loading.c
        ├── parse_colors.c
        ├── parse_header.c
        ├── parse_main.c
        └── parse_utils.c
```
