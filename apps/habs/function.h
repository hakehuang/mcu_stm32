#pragma once

#include <stdio.h>
#include "board.h"

void reset_board(void * param);

void delay_to_reset(void * param);

void sreset(void * param);

void tim_capture(void * param);

void gpio_2_operation(void * param);

void gpio_1_operation(void * param);

int _strncmp(const char * in, const char * cm, size_t len);

char * _strstr(const char * in, const char * cm);

int _strlen(const char * in);

void _memset(void * in, int val, size_t size);