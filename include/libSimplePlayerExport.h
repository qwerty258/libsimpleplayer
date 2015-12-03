#pragma once
#ifndef _LIB_SIMPLE_PLAYER_EXPORT_H_
#define _LIB_SIMPLE_PLAYER_EXPORT_H_

#ifdef _MSC_VER
#ifdef LIBSIMPLEPLAYER_EXPORTS
#define LIBSIMPLEPLAYER_API __declspec(dllexport)
#else
#define LIBSIMPLEPLAYER_API __declspec(dllimport)
#endif
#else
#define LIBSIMPLEPLAYER_API
#endif // _WIN32

#ifdef __cplusplus
#define C_EXPORT_BEGIN extern "C" {
#define C_EXPORT_END }
#else
#define C_EXPORT_BEGIN
#define C_EXPORT_END
#endif // __cplusplus

#endif // !_LIB_SIMPLE_PLAYER_EXPORT_H_