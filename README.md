# miniRayTracer
RayTracer with MLX42

### Launch with Valgrind and Suppressions

To run the program with Valgrind and suppressions, use the following command:

```bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppression/miniRT.supp ./miniRT
