#pragma once
#include <windows.h>
#include <stdio.h>
#include <globals.h>
#include <cstdint>
#include <mono.h>

namespace sdk::mono::camera
{
    using get_main_t = void*( __stdcall* )( void );
    using get_fov_t = float( __stdcall* )( void* );
    using set_fov_t = void( __stdcall* )( void*, float );

    void* get_main_camera( )
    {
        void* klass = sdk::mono::resolve_class(nullptr, "UnityEngine", "Camera");
        if (!klass)
        {
            printf("[ mono ] failed to resolve UnityEngine.Camera class\n");
            return nullptr;
        }

        void* method = sdk::mono::resolve_method_from_class(klass, "get_main", 0);
        if (!method)
        {
            printf("[ mono ] failed to resolve Camera::get_main\n");
            return nullptr;
        }

        void* exc = nullptr;
        void* main_camera = sdk::mono::invoke_method(method, nullptr, nullptr, &exc);

        if (exc)
        {
            printf("[ mono ] exception occurred during get_main_camera\n");
            return nullptr;
        }

        return main_camera;
    }

    float get_fov()
    {
        void* main_camera = get_main_camera();
        if (!main_camera)
        {
            printf("[ mono ] no active main camera\n");
            return -1.0f;
        }

        void* klass = sdk::mono::resolve_class(nullptr, "UnityEngine", "Camera");
        if (!klass)
        {
            printf("[ mono ] failed to resolve UnityEngine.Camera class\n");
            return -1.0f;
        }

        void* method = sdk::mono::resolve_method_from_class(klass, "get_fieldOfView", 0);
        if (!method)
        {
            printf("[ mono ] failed to resolve Camera::get_fieldOfView\n");
            return -1.0f;
        }

        void* exc = nullptr;
        float fov = *(float*)sdk::mono::invoke_method(method, main_camera, nullptr, &exc);

        if (exc)
        {
            printf("[ mono ] exception occurred during get_fov\n");
            return -1.0f;
        }

        return fov;
    }

    void set_fov(float fov)
    {
        void* main_camera = get_main_camera();
        if (!main_camera)
        {
            printf("[ mono ] no active main camera\n");
            return;
        }

        void* klass = sdk::mono::resolve_class(nullptr, "UnityEngine", "Camera");
        if (!klass)
        {
            printf("[ mono ] failed to resolve UnityEngine.Camera class\n");
            return;
        }

        void* method = sdk::mono::resolve_method_from_class(klass, "set_fieldOfView", 1);
        if (!method)
        {
            printf("[ mono ] failed to resolve Camera::set_fieldOfView\n");
            return;
        }

        void* params[1] = { &fov };
        void* exc = nullptr;
        sdk::mono::invoke_method(method, main_camera, params, &exc);

        if (exc)
        {
            printf("[ mono ] exception occurred during set_fov\n");
        }
    }

    bool is_camera_active()
    {
        void* main_camera = get_main_camera();
        return main_camera != nullptr;
    }
}