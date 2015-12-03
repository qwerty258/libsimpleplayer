#pragma once
#ifndef _LIB_SIMPLE_PLAYER_CHECK_MACROS_H_
#define _LIB_SIMPLE_PLAYER_CHECK_MACROS_H_

#include "errorDefine.h"
#include <stdio.h>

#define CHECK_MEMORY_ALLOC_RESULT(pointer)  \
if(NULL == (pointer))                       \
{                                           \
    return LIB_SIMPLE_PLAYER_NO_MEMORY;     \
}

#define CHECK_PARAMETER(pointer)            \
if(NULL == (pointer))                       \
{                                           \
    return LIB_SIMPLE_PLAYER_BAD_PARAMETER; \
}

#define CHECK_HANDLE(handle)                            \
if((handle) >= global_instance_context_array_size ||    \
   NULL == global_instance_context_array[(handle)])     \
{                                                       \
    return LIB_SIMPLE_PLAYER_INVALID_HANDLE;            \
}

#define CHECK_PLAYING_NO_SET(state)             \
if(playing <= state)                            \
{                                               \
    return LIB_SIMPLE_PLAYER_ALREADY_PLAYING;   \
}

#endif // !_LIB_SIMPLE_PLAYER_CHECK_MACROS_H_
