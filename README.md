# cub3D Project

cub3D is a 42 School project that introduces computer graphics through the implementation of a simple 3D game engine using raycasting. The project uses the Digital Differential Analyzer (DDA) algorithm to calculate ray–wall intersections and render a 3D view from a 2D map, all powered by the MiniLibX graphical library.

## Usage

```bash
make
./cub3D <map.cub>
```

## Understanding Raycasting and the DDA Algorithm

Raycasting is a technique used to render a 3D perspective from a 2D map. It works by casting rays from the player's position and determining where these rays intersect with walls in the game world. The Digital Differential Analyzer (DDA) algorithm is used to efficiently calculate these intersections.

### How Raycasting Works
1. **Casting Rays**: Rays are cast from the player's position, one for each vertical stripe of the screen. The direction of each ray is determined by the player's viewing angle and the screen's width.
2. **Finding Intersections**: For each ray, the DDA algorithm is used to step through the grid cells of the map until a wall is hit. This involves calculating the distance to the next grid boundary in both the x and y directions and stepping in the direction of the smallest distance.
3. **Calculating Wall Distance**: Once a wall is hit, the perpendicular distance from the player to the wall is calculated. This distance is used to determine the height of the wall slice to be drawn on the screen.
4. **Rendering**: The wall slice is drawn with the appropriate texture, and the process is repeated for all rays to complete the frame.

### The DDA Algorithm
The DDA algorithm is a grid traversal algorithm that efficiently finds the intersection of a ray with a grid-based map. Here's how it works:

1. **Initialization**: The starting position of the ray and its direction are initialized. The distance to the next x and y grid lines (`side_dist_x` and `side_dist_y`) is calculated based on the ray's direction.
2. **Stepping**: The algorithm determines whether to step in the x or y direction based on which distance is smaller. The `delta_dist_x` and `delta_dist_y` values, which represent the distance between successive x or y grid lines, are added to the respective side distances.
3. **Wall Hit Detection**: The algorithm continues stepping through the grid until a wall is hit. This is determined by checking the map data at the current grid cell.

### Why Use DDA?
The DDA algorithm is highly efficient for raycasting because it avoids the need for floating-point arithmetic in the main loop. Instead, it uses simple additions and comparisons, making it well-suited for real-time applications like games.

### Visualizing the Process
Imagine the game world as a grid, with the player at the center. Rays are cast outward, and the DDA algorithm steps through the grid cells, checking for walls. When a wall is hit, the distance is calculated, and the corresponding slice of the wall is drawn on the screen.

By combining raycasting with the DDA algorithm, cub3D creates a 3D perspective from a 2D map, providing an immersive gaming experience.