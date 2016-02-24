#pragma once
#ifndef _LIB_SIMPLE_PLAYER_H_
#define _LIB_SIMPLE_PLAYER_H_

#include "libSimplePlayerExport.h"

C_EXPORT_BEGIN

#include <stdint.h>
#include "errorDefine.h"

typedef void(*function_play_end_event)(void* user_data);

LIBSIMPLEPLAYER_API int LSP_initial(void);

LIBSIMPLEPLAYER_API int LSP_get_idle_handle(uint32_t* handle);

LIBSIMPLEPLAYER_API int LSP_set_RTSP_username(uint32_t handle, char* username);

LIBSIMPLEPLAYER_API int LSP_set_RTSP_password(uint32_t handle, char* password);

LIBSIMPLEPLAYER_API int LSP_set_MUL(uint32_t handle, char* MUL);

LIBSIMPLEPLAYER_API int LSP_set_filepath(uint32_t handle, char* filepath);

LIBSIMPLEPLAYER_API int LSP_set_hwnd(uint32_t handle, void* hWnd);

LIBSIMPLEPLAYER_API int LSP_set_play_end_event_callback(uint32_t handle, function_play_end_event p_function_play_end_event, void* user_data);

LIBSIMPLEPLAYER_API int LSP_play(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_pause(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_stop(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_set_speed(uint32_t handle, float speed);

LIBSIMPLEPLAYER_API int LSP_get_playing_percentage(uint32_t handle, float* percentage);

LIBSIMPLEPLAYER_API int LSP_set_playing_percentage(uint32_t handle, float percentage);

LIBSIMPLEPLAYER_API int LSP_get_snapshot(uint32_t handle, char* savepath);

LIBSIMPLEPLAYER_API int LSP_close_handle(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_uninitial(void);

C_EXPORT_END

#endif // !_LIB_SIMPLE_PLAYER_H_