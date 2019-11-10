/* 
* To keep main clean, it only provides system initialisation and spawns a console.
* The console interfaces will have access user functions through this module.
*/


#pragma once

extern void print_buffer_status(cbuf_handle_t cbuf);
extern int buffer_test(void);
