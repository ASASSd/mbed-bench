#include "mbed.h"
#include "stdarg.h"
extern "C" int coremark_main(void);
extern "C" int ee_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	for (; *format; format++) {
		if (*format == '%') {
			bool islong = false;
			format++;
			if (*format == '%') { printf(format); continue; }
			if (*format == '-') format++; // ignore size
			while (*format >= '0' && *format <= '9') format++; // ignore size
			if (*format == 'l') { islong = true; format++; }
			if (*format == '\0') break;
			if (*format == 's') {
				printf("%s", va_arg(args, int));
			} else if (*format == 'f') {
				printf("%f", va_arg(args, double));
			} else if (*format == 'd') {
				if (islong) printf("%d", va_arg(args, long));
				else printf("d", va_arg(args, int));
			} else if (*format == 'u') {
				if (islong) printf("%u", va_arg(args, unsigned long));
				else printf("%u", va_arg(args, unsigned int));
			} else if (*format == 'x') {
				if (islong) printf("%x", va_arg(args, unsigned long));
				else printf("%x", va_arg(args, unsigned int));
			} else if (*format == 'c' ) {
				printf("%c", va_arg(args, int));
			}
		} else {
			if (*format == '\n') printf("%c", '\r');
			printf("%c", *format);
		}
	}
	va_end(args);
	return 1;
}
extern "C" uint32_t Arduino_millis(void)
{
	return HAL_GetTick();
} 

int main()
{
    for(;;){
        printf("CoreMark Performance Benchmark\n\r\n\r");
    printf("CoreMark measures how quickly your processor can manage linked\n\rlists, compute matrix multiply, and execute state machine code.\n\r\n\r");
    printf("Iterations/Sec is the main benchmark result, higher numbers are better\n\r");
    printf("Running.... (usually requires 12 to 20 seconds)\n\r\n\r");
    coremark_main();
    thread_sleep_for(250);
    }
}

