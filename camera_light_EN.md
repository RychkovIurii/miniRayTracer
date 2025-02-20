# Camera and Light Initialization

## Camera Initialization (init_camera)

### Function Overview
```c
t_camera init_camera(double x, double y, double z, t_tuple forward, double fov, int hsize, int vsize)
```
- **x, y, z** → Camera's position in world coordinates.
- **forward** → The direction the camera is looking.
- **fov** → Field of View (in degrees).
- **hsize, vsize** → Horizontal and vertical resolution of the image.

### Key Concepts
- The camera is placed at (x, y, z).
- The "forward" vector determines where the camera is pointing.
- The "up" vector is set to (0,1,0), meaning "world up" is aligned with the Y-axis.
- The `view_transform()` function ensures the camera is correctly oriented.

### Common Camera Positions
| Scenario            | Position (x, y, z) | Forward (dx, dy, dz) | Effect                                |
|---------------------|--------------------|----------------------|---------------------------------------|
| Front View          | (0, 0, 10)         | (0, 0, -1)           | Directly in front of the object       |
| Top-Down View       | (0, 10, 0)         | (0, -1, 0)           | Looks down from above                 |
| Side View           | (10, 0, 0)         | (-1, 0, 0)           | Looks at the object from the side     |
| Perspective (Angle) | (5, 5, 10)         | (-0.5, -0.5, -1)     | Looks at the object from a diagonal angle |
| Over-the-Shoulder   | (0, 1.5, 5)        | (0, -0.2, -1)        | Looks slightly downward, like a first-person camera |

### Example: Over-the-Shoulder Camera
```c
scene.camera = init_camera(0.0, 1.5, 5.0, vector(0.0, -0.2, -1.0), 90.0, WIDTH, HEIGHT);
```

## Light Initialization (init_light)

### Function Overview
```c
t_light init_light(t_tuple position, t_tuple color, double brightness)
```
- **position** → Where the light is located.
- **color** → The color of the light.
- **brightness** → Intensity multiplier (0.0 = off, 1.0 = full brightness).

### Common Light Positions
| Scenario      | Position (x, y, z) | Effect                          |
|---------------|--------------------|---------------------------------|
| Overhead Sun  | (0, 10, 0)         | Creates natural shadows downward|
| Front Light   | (0, 5, 10)         | Illuminates the scene evenly    |
| Side Light    | (10, 5, 0)         | Creates dramatic side shadows   |
| Backlight     | (0, 5, -10)        | Creates a silhouette effect     |
| Corner Light  | (5, 10, 5)         | Balanced, realistic shadows     |

### Example: Sunlight from Above
```c
scene.light = init_light(point(0.0, 10.0, 0.0), create_color(1.0, 1.0, 1.0), 0.7);
```
