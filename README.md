# Roguelite

## Debugger
The VSCode debugger is completely and utterly fucked. To debug, manually use gdb.

1. Run the command `make debug`
2. Run the command `gdb bin/main`
3. Run the gdb command `layout src`
4. Run the gdb command `break main`
5. Run the gdb command `run`
6. Debug the program

## Debugger Tests

### Memory Leaks
1. Start valgrind: `valgrind --vgdb=yes --vgdb-error=0 bin/main`
2. Copy the command valgrind gives (looks like `target remote | /usr/bin/vgdb --pid=159205`)
3. Open gdb: `gdb bin/main`. Skip the message.
4. Paste the command into gdb.
5. Run the command in gdb: `monitor leak_check`.
6. It should output `All heap blocks were freed -- no leaks are possible`
7. Run the command in gdb: `monitor v.kill`
8. Exit gdb.
