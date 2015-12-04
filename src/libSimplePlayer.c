#include "libSimplePlayer.h"
#include "checkMacros.h"
#include <vlc\libvlc.h>
#include <vlc\libvlc_media.h>
#include <vlc\libvlc_media_player.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum
{
    initialized = 0,
    playing = 1,
    pause = 2,
    stop = 3
}instance_state;

typedef struct _instance_context
{
    instance_state state;
    libvlc_instance_t* p_libvlc_instance_t;
    libvlc_media_t* p_libvlc_media_t;
    libvlc_media_player_t* p_libvlc_media_player_t;
}instance_context;

instance_context** global_instance_context_array;
uint32_t global_instance_context_array_size;

LIBSIMPLEPLAYER_API int LSP_initial(void)
{
    global_instance_context_array = calloc(1, 1);
    CHECK_MEMORY_ALLOC_RESULT(global_instance_context_array);
    global_instance_context_array_size = 0;
    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_get_idle_handle(uint32_t* handle)
{
    uint32_t i;
    instance_context** pp_instance_context_array_temp;

    CHECK_PARAMETER(handle);

    for(i = 0; i < global_instance_context_array_size; i++)
    {
        if(NULL == global_instance_context_array[i])
        {
            global_instance_context_array[i] = calloc(1, sizeof(instance_context));
            CHECK_MEMORY_ALLOC_RESULT(global_instance_context_array[i]);
            *handle = i;
            break;
        }
    }

    if(i == global_instance_context_array_size)
    {
        pp_instance_context_array_temp =
            realloc(
            global_instance_context_array,
            (global_instance_context_array_size + 10) * sizeof(instance_context*));
        CHECK_MEMORY_ALLOC_RESULT(pp_instance_context_array_temp);
        global_instance_context_array = pp_instance_context_array_temp;
        global_instance_context_array_size += 10;
        memset(&global_instance_context_array[i], 0x0, 10 * sizeof(instance_context*));

        global_instance_context_array[i] = calloc(1, sizeof(instance_context));
        CHECK_MEMORY_ALLOC_RESULT(global_instance_context_array[i]);
        *handle = i;
    }

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_set_filepath(uint32_t handle, char* filepath)
{
    CHECK_PARAMETER(filepath);
    CHECK_HANDLE(handle);
    CHECK_PLAYING_NO_SET(global_instance_context_array[handle]->state);

    global_instance_context_array[handle]->p_libvlc_instance_t = libvlc_new(0, NULL);
    global_instance_context_array[handle]->p_libvlc_media_t = libvlc_media_new_path(
        global_instance_context_array[handle]->p_libvlc_instance_t,
        filepath);
    global_instance_context_array[handle]->p_libvlc_media_player_t = libvlc_media_player_new_from_media(
        global_instance_context_array[handle]->p_libvlc_media_t);

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_set_hwnd(uint32_t handle, void* hWnd)
{
    CHECK_PARAMETER(hWnd);
    CHECK_HANDLE(handle);
    CHECK_PLAYING_NO_SET(global_instance_context_array[handle]->state);

    libvlc_media_player_set_hwnd(
        global_instance_context_array[handle]->p_libvlc_media_player_t,
        hWnd);

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_play(uint32_t handle)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_play(global_instance_context_array[handle]->p_libvlc_media_player_t);
    global_instance_context_array[handle]->state = playing;

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_pause(uint32_t handle)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_pause(global_instance_context_array[handle]->p_libvlc_media_player_t);
    global_instance_context_array[handle]->state = pause;

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_stop(uint32_t handle)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_stop(global_instance_context_array[handle]->p_libvlc_media_player_t);
    global_instance_context_array[handle]->state = stop;

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_set_speed(uint32_t handle, float speed)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_set_rate(global_instance_context_array[handle]->p_libvlc_media_player_t, speed);

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_close_handle(uint32_t handle)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_release(global_instance_context_array[handle]->p_libvlc_media_player_t);
    libvlc_media_release(global_instance_context_array[handle]->p_libvlc_media_t);
    libvlc_release(global_instance_context_array[handle]->p_libvlc_instance_t);

    free(global_instance_context_array[handle]);
    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_uninitial(void)
{
    free(global_instance_context_array);
    global_instance_context_array_size = 0;
    return LIB_SIMPLE_PLAYER_OK;
}
