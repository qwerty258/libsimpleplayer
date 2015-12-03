#pragma once
#ifndef _LIB_SIMPLE_PLAYER_H_
#define _LIB_SIMPLE_PLAYER_H_

#include "libSimplePlayerExport.h"

C_EXPORT_BEGIN

#include <stdint.h>
#include "errorDefine.h"

LIBSIMPLEPLAYER_API int LSP_initial(void);

LIBSIMPLEPLAYER_API int LSP_get_idle_handle(uint32_t* handle);

LIBSIMPLEPLAYER_API int LSP_set_filepath(uint32_t handle, char* filepath);

LIBSIMPLEPLAYER_API int LSP_set_hwnd(uint32_t handle, void* hWnd);

LIBSIMPLEPLAYER_API int LSP_play(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_close_handle(uint32_t handle);

LIBSIMPLEPLAYER_API int LSP_uninitial(void);

C_EXPORT_END

#endif // !_LIB_SIMPLE_PLAYER_H_