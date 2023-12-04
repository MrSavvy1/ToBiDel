#include <stdarg.h>
#include <stdio.h>

int custom_snprintf(char *buffer, size_t size, const char *format, ...) {
				if (!buffer || !format || size == 0) {
								return -1;  // Invalid input
				}

				va_list args;
				va_start(args, format);

				int written = 0;
				size_t i = 0;

				while (format[i] != '\0' && written < size - 1) {
								if (format[i] == '%' && format[i + 1] != '\0') {
												++i;

												// Handle format specifiers based on your needs
												switch (format[i]) {
																case 'd':
																				int num = va_arg(args, int);
																				int digits = 0;

																				// Count the number of digits in num
																				int temp = num;
																				do {
																								temp /= 10;
																								digits++;
																				} while (temp != 0);

																				// Write the digits to the buffer
																				int divisor = 1;
																				for (int j = 1; j < digits; j++) {
																								divisor *= 10;
																				}

																				do {
																								buffer[written++] = '0' + num / divisor;
																								num %= divisor;
																								divisor /= 10;
																				} while (divisor != 0);
																				break;

																case 's':
																				char *str = va_arg(args, char *);
																				while (*str != '\0' && written < size - 1) {
																								buffer[written++] = *str++;
																				}
																				break;

																// Add more cases for other specifiers as needed

																default:
																				// Handle unsupported specifier or error
																				va_end(args);
																				return -1;
												}
								} else {
												buffer[written++] = format[i];
								}

								++i;
				}

				va_end(args);

				buffer[written] = '\0';  // Null-terminate the string

				return written;
}

int main() {
				char output[50];  // Adjust size based on your needs
				int result = custom_snprintf(output, sizeof(output), "Custom snprintf example: %d %s/%s\n", 42, "God","Hello");

				if (result >= 0) {
								printf("Result: %s", output);
				} else {
								printf("Error: Insufficient buffer size or invalid input\n");
				}

				return 0;
}
