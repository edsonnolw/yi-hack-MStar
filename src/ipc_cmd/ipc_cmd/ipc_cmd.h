/*
 * This file is part of libipc (https://github.com/TheCrypt0/libipc).
 * Copyright (c) 2019 roleo.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <mqueue.h>

#define IPC_QUEUE_NAME          "/ipc_dispatch"
#define IPC_MESSAGE_MAX_SIZE    512

#define NONE -1

#define IPC_SENS_HIGH   "\x01\x00\x00\x00\x08\x00\x00\x00\x27\x10\x01\x00\x04\x00\x00\x00\x00\x00\x00\x00"
#define IPC_SENS_MEDIUM "\x01\x00\x00\x00\x08\x00\x00\x00\x27\x10\x01\x00\x04\x00\x00\x00\x01\x00\x00\x00"
#define IPC_SENS_LOW    "\x01\x00\x00\x00\x08\x00\x00\x00\x27\x10\x01\x00\x04\x00\x00\x00\x02\x00\x00\x00"

#define SENSITIVITY_HIGH 0
#define SENSITIVITY_MEDIUM 1
#define SENSITIVITY_LOW 2

#define IPC_LED_OFF "\x02\x00\x00\x00\x08\x00\x00\x00\x77\x00\x01\x00\x00\x00\x00\x00"
#define IPC_LED_ON  "\x02\x00\x00\x00\x08\x00\x00\x00\x76\x00\x01\x00\x00\x00\x00\x00"

#define LED_OFF 0
#define LED_ON  1

#define IPC_SAVE_ALWAYS "\x02\x00\x00\x00\x08\x00\x00\x00\x79\x00\x01\x00\x00\x00\x00\x00"
#define IPC_SAVE_DETECT "\x02\x00\x00\x00\x08\x00\x00\x00\x78\x00\x01\x00\x00\x00\x00\x00"

#define SAVE_ALWAYS 0
#define SAVE_DETECT 1

#define IPC_IR_OFF "\x02\x00\x00\x00\x08\x00\x00\x00\x24\x10\x01\x00\x04\x00\x00\x00\x02\x00\x00\x00"
#define IPC_IR_ON  "\x02\x00\x00\x00\x08\x00\x00\x00\x24\x10\x01\x00\x04\x00\x00\x00\x01\x00\x00\x00"

#define IR_OFF 0
#define IR_ON  1

#define IPC_ROTATE_OFF "\x02\x00\x00\x00\x08\x00\x00\x00\x7b\x00\x01\x00\x00\x00\x00\x00"
#define IPC_ROTATE_ON  "\x02\x00\x00\x00\x08\x00\x00\x00\x7a\x00\x01\x00\x00\x00\x00\x00"

#define ROTATE_OFF 0
#define ROTATE_ON  1