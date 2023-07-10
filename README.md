### Step for build process
1. Specify ARM toolchain path.
2. Specify STM32 Library source path
3. Specify code path (*.c) files for
   - Device
   - Core (processor)
   - Peripheral Driver
4. Include all library source files paths.
5. Set various compilation flags.
6. Set various linking flags.

### Commands to load program to chip
```shell
st-util
```

```shell
gdb-multiarch demo.elf
(gdb) target extended-remote :4242
(gdb) load
(gdb) break main
(gdb) break main
(gdb) break inc
(gdb) continue 
```