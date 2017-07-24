#pragma once

#include <stdio.h>
#include "board.h"

void reset_board(void * param);

void delay_to_reset(void * param);

void sreset(void * param);

void tim_capture();