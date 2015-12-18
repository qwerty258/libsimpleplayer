#include "libSimplePlayer.h"
#include "checkMacros.h"
#include <vlc\libvlc.h>
#include <vlc\libvlc_media.h>
#include <vlc\libvlc_media_player.h>
#include <vlc\libvlc_events.h>
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
    libvlc_event_manager_t* p_libvlc_event_manager_t;
    int width;
    int height;
    function_play_end_event p_function_play_end_event;
    void* user_data;
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
    global_instance_context_array[handle]->width = libvlc_video_get_width(
        global_instance_context_array[handle]->p_libvlc_media_player_t);
    global_instance_context_array[handle]->height = libvlc_video_get_height(
        global_instance_context_array[handle]->p_libvlc_media_player_t);
    // don't handle mouse input for upper layer app
    // https://forum.videolan.org/viewtopic.php?f=32&t=92568&p=307102&hilit=fullscreen#p307102
    // Re: i can't Catch mouse events vlc 1.1.5 in Qt,please help m
    // Post by erwan10       04 Aug 2011 22:43
    // I just committed a patch for the vlc1.1 and vlc1.2 series that does this job of disabling
    // vlc windows when libvlc developper specifies both mouse and keyboard support to be disabled
    // via the libvlc api. So no more need for this hack in future versions.
    libvlc_video_set_mouse_input(global_instance_context_array[handle]->p_libvlc_media_player_t, false);
    libvlc_video_set_key_input(global_instance_context_array[handle]->p_libvlc_media_player_t, false);

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

void libvlc_playend_callback(const struct libvlc_event_t* p_libvlc_event_t, void* user_data)
{
    instance_context* p_instance_context = user_data;
    p_instance_context->p_function_play_end_event(
        p_instance_context->user_data);
}

LIBSIMPLEPLAYER_API int LSP_set_play_end_event_callback(uint32_t handle, function_play_end_event p_function_play_end_event, void* user_data)
{
    CHECK_PARAMETER(p_function_play_end_event);
    CHECK_HANDLE(handle);
    CHECK_PLAYING_NO_SET(global_instance_context_array[handle]->state);

    global_instance_context_array[handle]->user_data = user_data;
    global_instance_context_array[handle]->p_function_play_end_event = p_function_play_end_event;

    global_instance_context_array[handle]->p_libvlc_event_manager_t = libvlc_media_player_event_manager(
        global_instance_context_array[handle]->p_libvlc_media_player_t);

    libvlc_event_attach(
        global_instance_context_array[handle]->p_libvlc_event_manager_t,
        libvlc_MediaPlayerEndReached,
        libvlc_playend_callback,
        global_instance_context_array[handle]);

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

LIBSIMPLEPLAYER_API int LSP_get_playing_percentage(uint32_t handle, float* percentage)
{
    CHECK_HANDLE(handle);
    CHECK_PARAMETER(percentage);

    *percentage = libvlc_media_player_get_position(
        global_instance_context_array[handle]->p_libvlc_media_player_t);

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_set_playing_percentage(uint32_t handle, float percentage)
{
    CHECK_HANDLE(handle);

    if(percentage < 0.0 || 1.0 < percentage)
    {
        return LIB_SIMPLE_PLAYER_INVALID_PERCENTAGE;
    }

    libvlc_media_player_set_position(
        global_instance_context_array[handle]->p_libvlc_media_player_t,
        percentage);

    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_get_snapshot(uint32_t handle, char* savepath)
{
    CHECK_HANDLE(handle);
    CHECK_PARAMETER(savepath);

    libvlc_video_take_snapshot(
        global_instance_context_array[handle]->p_libvlc_media_player_t,
        0,
        savepath,
        global_instance_context_array[handle]->width,
        global_instance_context_array[handle]->height);

    return LIB_SIMPLE_PLAYER_OK;
}


LIBSIMPLEPLAYER_API int LSP_close_handle(uint32_t handle)
{
    CHECK_HANDLE(handle);

    libvlc_media_player_release(global_instance_context_array[handle]->p_libvlc_media_player_t);
    libvlc_media_release(global_instance_context_array[handle]->p_libvlc_media_t);
    libvlc_release(global_instance_context_array[handle]->p_libvlc_instance_t);

    free(global_instance_context_array[handle]);
    global_instance_context_array[handle] = NULL;
    return LIB_SIMPLE_PLAYER_OK;
}

LIBSIMPLEPLAYER_API int LSP_uninitial(void)
{
    for(uint32_t i = 0; i < global_instance_context_array_size; i++)
    {
        if(NULL != global_instance_context_array[i])
        {
            LSP_close_handle(i);
        }
    }
    free(global_instance_context_array);
    global_instance_context_array_size = 0;
    return LIB_SIMPLE_PLAYER_OK;
}
