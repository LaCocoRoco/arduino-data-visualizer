#ifndef ATMEL_DATA_GATEWAY_H
#define ATMEL_DATA_GATEWAY_H

#ifdef __has_include

#if __has_include(<Wire.h>)
#define GATEWAY_INCLUDED_TWI
#endif

#if __has_include(<Stream.h>)
#define GATEWAY_INCLUDED_UART
#endif

#if __has_include(<SPI.h>)
#define GATEWAY_INCLUDED_SPI
#endif

#else

#define GATEWAY_INCLUDED_UART
#define GATEWAY_INCLUDED_TWI
#define GATEWAY_INCLUDED_SPI

#endif

#endif