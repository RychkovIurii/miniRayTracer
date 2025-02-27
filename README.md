# miniRayTracer
RayTracer with MLX42

### Launch with Valgrind and Suppressions

To run the program with Valgrind and suppressions, use the following command:

```bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppression/miniRT.supp ./miniRT
```

# Control Key Bindings

This document provides an overview of the key bindings used in the code.

- **Escape Key (ESC):** Closes the window.
- **Right Mouse Button:** Selects an object in the scene.
- **Arrow Keys (Up, Down, Left, Right):** Move the camera up and down and rotate along the Y axe.
- **W, S, A, D Keys:** Move the camera forward and backward, left and right.
- **Numerical Keypad Keys (KP 4, 5, 6, 7, 8, 9, 0, 1, =, /):** Translate selected shapes along the X, Y, and Z axes. Rotations. Translate selected shapes.
- **KP Add ( + ) and Subtract ( - ):** Scale the selected shape by 2x or 0.5x (if constraints are met).
- **Right Shift and Control Keys:** Adjust light brightness.
- **Left Shift and Control Keys:** Move the light in the Y direction (up or down).
- **Home and End Keys, Page Down and Delete Keys:** Move the light forward and backward, left and right.
- **Left Shift and Left Control Keys:** Move the light in the Z direction (forward or backward).