# ESP32 Dev for embedded C 

Starts a FreeRTOS task to print "Hello World"
Generate Random data.
Initialize ring buffer to transfer this data

# Console example

This example illustrates usage of `console` component to create an interactive shell.

## Configuring UART and VFS

``initialize_console`` function configures some aspects of UART and VFS relevant to the operation of console:

- By default `stdin` and `stdout` are buffered streams. This means that the text written to `stdout` will not be immediately sent to UART. This is not the desirable behavior for the console, so buffering for `stdin` and `stdout` is disabled using `setvbuf` function.

- Line endings are configured to match those expected/generated by common serial monitor programs, such as `screen`, `minicom`, and the `idf_monitor.py` included in the SDK. The default behavior for these commands is:
    - When 'enter' key is pressed on the keyboard, `CR` (0x13) code is sent to the serial device.
    - To move the cursor to the beginning of the next line, serial device needs to send `CR LF` (0x13 0x10) sequence.

- UART driver is initialized, and VFS is configured to use UART driver's interrupt-driver read and write functions.

## Line editing

The main source file of the example illustrates how to use `linenoise` library, including line completion, hints, and history.

## Commands

Several commands are registered using `esp_console_cmd_register` function. See `register_wifi` and `register_system` functions in `cmd_wifi.c` and `cmd_system.c` files.

## Command handling

Main loop inside `app_main` function illustrates how to use `linenoise` and `esp_console_run` to implement read/eval loop.

## Argument parsing

Several commands implemented in `cmd_wifi.c` and `cmd_system.c` use Argtable3 library to parse and check the arguments.

## Command history

Each time a new command line is obtained from `linenoise`, it is written into history and the history is saved into a file in flash memory. On reset, history is initialized from that file.

# Example output

Here is an sample session with the console example. GPIO15 is connected to GND to remove boot log output.

```
This is an example of ESP-IDF console component.
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
[esp32]> help
help 
  Print the list of registered commands

free 
  Get the total size of heap memory available

restart 
  Restart the program

deep_sleep  [-t <t>] [--io=<n>] [--io_level=<0|1>]
  Enter deep sleep mode. Two wakeup modes are supported: timer and GPIO. If no
  wakeup option is specified, will sleep indefinitely.
  -t, --time=<t>  Wake up time, ms
      --io=<n>  If specified, wakeup using GPIO with given number
  --io_level=<0|1>  GPIO level to trigger wakeup

join  [--timeout=<t>] <ssid> [<pass>]
  Join WiFi AP as a station
  --timeout=<t>  Connection timeout, ms
        <ssid>  SSID of AP
        <pass>  PSK of AP

[esp32]> free
257200
[esp32]> deep_sleep -t 1000
I (146929) deep_sleep: Enabling timer wakeup, timeout=1000000us
I (619) heap_init: Initializing. RAM available for dynamic allocation:
I (620) heap_init: At 3FFAE2A0 len 00001D60 (7 KiB): DRAM
I (626) heap_init: At 3FFB7EA0 len 00028160 (160 KiB): DRAM
I (645) heap_init: At 3FFE0440 len 00003BC0 (14 KiB): D/IRAM
I (664) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (684) heap_init: At 40093EA8 len 0000C158 (48 KiB): IRAM

This is an example of ESP-IDF console component.
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
[esp32]> join --timeout 10000 test_ap test_password
I (182639) connect: Connecting to 'test_ap'
I (184619) connect: Connected
[esp32]> free
212328
[esp32]> restart
I (205639) restart: Restarting
I (616) heap_init: Initializing. RAM available for dynamic allocation:
I (617) heap_init: At 3FFAE2A0 len 00001D60 (7 KiB): DRAM
I (623) heap_init: At 3FFB7EA0 len 00028160 (160 KiB): DRAM
I (642) heap_init: At 3FFE0440 len 00003BC0 (14 KiB): D/IRAM
I (661) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (681) heap_init: At 40093EA8 len 0000C158 (48 KiB): IRAM

This is an example of ESP-IDF console component.
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
[esp32]> 

```

---

See the README.md file in the upper level 'examples' directory for more information about examples.
