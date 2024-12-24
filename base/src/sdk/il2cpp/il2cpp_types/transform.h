#pragma once
#include <il2cpp.h>
#include <types/vec3.h>

namespace sdk::il2cpp::transform
{
    // fn types
    using get_position_t = vec3_t (__stdcall*)(void*);
    using set_position_t = void (__stdcall*)(void*, const vec3_t&);
    using get_rotation_t = vec3_t (__stdcall*)(void*);
    using set_rotation_t = void (__stdcall*)(void*, const vec3_t&);

    vec3_t get_position( void* transform )
    {
        get_position_t get_position = reinterpret_cast<get_position_t>( sdk::il2cpp::resolve_icall( "UnityEngine.Transform::get_position" ) );
        if ( !get_position )
        {
            printf( "[ transform ] get_position is nullptr\n" );
            return vec3_t( );
        }

        return get_position( transform );
    }

    void set_position( void* transform, const vec3_t& new_position )
    {
        set_position_t set_position = reinterpret_cast<set_position_t>(sdk::il2cpp::resolve_icall( "UnityEngine.Transform::set_position" ));
        if ( !set_position )
        {
            printf( "[ transform ] set_position is nullptr\n" );
            return;
        }

        set_position( transform, new_position );
    }

    vec3_t get_rotation( void* transform )
    {
        get_rotation_t get_rotation = reinterpret_cast<get_rotation_t>(sdk::il2cpp::resolve_icall( "UnityEngine.Transform::get_rotation" ));
        if ( !get_rotation )
        {
            printf( "[ transform ] get_rotation is nullptr\n" );
            return vec3_t();
        }

        return get_rotation( transform );
    }

    void set_rotation( void* transform, const vec3_t& new_rotation )
    {
        set_rotation_t set_rotation = reinterpret_cast<set_rotation_t>(sdk::il2cpp::resolve_icall( "UnityEngine.Transform::set_rotation" ));
        if ( !set_rotation )
        {
            printf( "[ transform ] set_rotation is nullptr\n" );
            return;
        }

        set_rotation( transform, new_rotation );
    }
}