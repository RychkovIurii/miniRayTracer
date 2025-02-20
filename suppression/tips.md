### Generate Suppressions File

Run the following command to generate a suppression file using Valgrind:

```bash
valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=valgrind.log ./miniRT
```

### Launch Script to Remove Unnecessary Rows

Make the remove_eq_lines.sh script executable and then run it to remove unnecessary rows from the valgrind.log:

```bash
chmod +x remove_eq_lines.sh
./remove_eq_lines.sh valgrind.log
```

### Rename File to miniRT.supp
Finally, rename the processed file to miniRT.supp:

```bash
mv valgrind.log miniRT.supp
```
