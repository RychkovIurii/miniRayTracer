# Mini Ray Tracer Notes

## Understanding the `t_material` Structure

```c
typedef struct	s_material
{
	t_tuple		color;             // Base color of the material
	double		ambient;           // Ambient lighting (0.0 - 1.0)
	double		diffuse;           // Diffuse reflection (0.0 - 1.0)
	double		specular;          // Specular reflection (0.0 - 1.0)
	double		shininess;         // Shininess (higher = smaller, brighter highlights)
	t_pattern	pattern;           // Texture pattern (if any)
	int			has_pattern;       // Flag: 1 if a pattern is used, 0 otherwise
	double		reflective;        // Reflectivity (0.0 - 1.0, 1.0 = mirror)
	double		transparency;      // Transparency (0.0 - 1.0)
	double		refractive_index;  // Refractive index (1.0 = air, 1.5 = glass, 2.4 = diamond)
}			t_material;
```

## Best Values for Different Materials

| Material       | Ambient | Diffuse | Specular | Shininess | Reflective | Transparency | Refractive Index |
|----------------|---------|---------|----------|-----------|------------|--------------|------------------|
| Plastic        | 0.1-0.2 | 0.7-0.9 | 0.2-0.4  | 50-100    | 0.1-0.2    | 0.0          | 1.0              |
| Metal          | 0.2-0.3 | 0.3-0.6 | 0.7-1.0  | 100-500   | 0.7-1.0    | 0.0          | 1.0              |
| Glass          | 0.1-0.2 | 0.1-0.3 | 0.9-1.0  | 200-500   | 0.0-0.1    | 0.9-1.0      | 1.5              |
| Water          | 0.1     | 0.1-0.3 | 0.3-0.6  | 100-200   | 0.0        | 1.0          | 1.33             |
| Ceramic        | 0.2     | 0.8     | 0.3      | 100       | 0.1-0.2    | 0.0          | 1.0              |
| Diamond        | 0.1     | 0.1     | 1.0      | 300-500   | 0.1-0.3    | 1.0          | 2.42             |
| Frosted Glass  | 0.1     | 0.3-0.5 | 0.3-0.5  | 50-150    | 0.0-0.1    | 0.8-1.0      | 1.5              |
| Mirror         | 0.0     | 0.1     | 1.0      | 250-500   | 1.0        | 0.0          | 1.0              |

## Code Examples for Different Materials

### Matte Plastic (Sphere)

```c
sphere->material = (t_material){
	.color = create_color(1.0, 0.0, 0.0),  // Red
	.ambient = 0.1,
	.diffuse = 0.9,
	.specular = 0.3,
	.shininess = 50,
	.reflective = 0.1,
	.transparency = 0.0,
	.refractive_index = 1.0
};
```

### Polished Metal (Golden Sphere)

```c
sphere->material = (t_material){
	.color = create_color(1.0, 0.8, 0.0),  // Gold-like color
	.ambient = 0.2,
	.diffuse = 0.3,
	.specular = 1.0,
	.shininess = 300,
	.reflective = 0.9,
	.transparency = 0.0,
	.refractive_index = 1.0
};
```

### Glass Sphere

```c
sphere->material = (t_material){
	.color = create_color(1.0, 1.0, 1.0),  // Transparent
	.ambient = 0.1,
	.diffuse = 0.1,
	.specular = 1.0,
	.shininess = 500,
	.reflective = 0.1,
	.transparency = 1.0,
	.refractive_index = 1.5  // Glass
};
```

### Mirror

```c
mirror->material = (t_material){
	.color = create_color(1.0, 1.0, 1.0),  // White (color doesn’t matter)
	.ambient = 0.0,
	.diffuse = 0.1,
	.specular = 1.0,
	.shininess = 400,
	.reflective = 1.0,
	.transparency = 0.0,
	.refractive_index = 1.0
};
```

## Key Takeaways

- `diffuse` controls how much light is scattered across the surface.
  - Higher `diffuse` (0.8-0.9) for matte objects (plastic, stone).
  - Lower `diffuse` (0.2-0.5) for polished surfaces (metal, wet objects).
- If the object is transparent, `diffuse` should be low, and `transparency` should be high.
- Mirrors and metals rely more on specular reflection than diffuse.
Understanding the t_material Structure
