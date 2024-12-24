#pragma once
#include <il2cpp.h>

namespace sdk::il2cpp::camera
{
    using get_main_t = void*( * )( );
    using get_fov_t = float( * )( void* );
    using set_fov_t = void( * )( void*, float );

    void* get_main_camera( )
    {
        get_main_t get_main = reinterpret_cast<get_main_t>( sdk::il2cpp::resolve_icall( "UnityEngine.Camera::get_main" ) );
        if ( !get_main )
        {
            printf( "[ il2cpp ] failed to resolve get_main (camera)\n" );
            return nullptr;
        }

        void* main_camera = get_main( );
        if ( !main_camera )
        {
            printf( "[ il2cpp ] get_main returned null, no active camera?\n" );
        }

        return main_camera;
    }

    float get_fov( )
    {
        get_fov_t get_fov = reinterpret_cast<get_fov_t>( sdk::il2cpp::resolve_icall( "UnityEngine.Camera::get_fieldOfView" ) );
        if ( !get_fov )
        {
            printf( "[ il2cpp ] failed to resolve get_fov\n" );
            return -1.0f;
        }

        void* main_camera = get_main_camera( );
        if ( !main_camera )
        {
            return -1.0f;
        }

        return get_fov( main_camera );
    }

    void set_fov( float fov )
    {
        set_fov_t set_fov = reinterpret_cast<set_fov_t>( sdk::il2cpp::resolve_icall( "UnityEngine.Camera::set_fieldOfView" ) );
        if ( !set_fov )
        {
            printf( "[ il2cpp ] failed to resolve set_fov\n" );
            return;
        }

        void* main_camera = get_main_camera( );
        if ( !main_camera )
        {
            return;
        }

        set_fov( main_camera, fov );
    }

    bool is_camera_active( )
    {
        void* main_camera = get_main_camera( );
        return main_camera != nullptr;
    }
}