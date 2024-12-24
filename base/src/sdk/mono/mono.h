#pragma once
#include <windows.h>
#include <stdio.h>
#include <globals.h>
#include <cstdint>

namespace sdk::mono
{
    // @note: mono_get_method - used to retrieve method info from a domain/assembly
    using mono_get_method_t = void* ( __stdcall* ) ( void* image, std::uint32_t token, void* context );
    mono_get_method_t mono_get_method = nullptr;

    // @note: mono_method_get_name - retrieves the name of a Mono method
    using mono_method_get_name_t = const char* ( __stdcall* ) ( void* method );
    mono_method_get_name_t mono_method_get_name = nullptr;

    // @note: mono_class_from_name - retrieves a Mono class from a namespace and class name
    using mono_class_from_name_t = void* ( __stdcall* ) ( void* image, const char* namespace_name, const char* class_name );
    mono_class_from_name_t mono_class_from_name = nullptr;

    // @note: mono_class_get_method_from_name - retrieves a method from a class by name
    using mono_class_get_method_from_name_t = void* ( __stdcall* ) ( void* klass, const char* name, int param_count );
    mono_class_get_method_from_name_t mono_class_get_method_from_name = nullptr;

    // @note: mono_runtime_invoke - invokes a method on an object
    using mono_runtime_invoke_t = void* ( __stdcall* ) ( void* method, void* obj, void** params, void** exc );
    mono_runtime_invoke_t mono_runtime_invoke = nullptr;

    // @usage: resolve_method( image, token )
    void* resolve_method( void* image, std::uint32_t token )
    {
        if ( !mono_get_method )
        {
            printf( "[ mono ] mono_get_method is null\n" );
            return nullptr;
        }

        void* method = mono_get_method( image, token, nullptr );
        if ( !method )
        {
            printf( "[ mono ] failed to resolve method with token: 0x%X\n", token );
        }
        else
        {
            const char* method_name = mono_method_get_name ? mono_method_get_name( method ) : "unknown";
            printf( "[ mono ] resolved method: %s ( token: 0x%X )\n", method_name, token );
        }

        return method;
    }

    // @usage: resolve_class( image, namespace, class_name )
    void* resolve_class( void* image, const char* namespace_name, const char* class_name )
    {
        if ( !mono_class_from_name )
        {
            printf( "[ mono ] mono_class_from_name is null\n" );
            return nullptr;
        }

        void* klass = mono_class_from_name( image, namespace_name, class_name );
        if ( !klass )
        {
            printf( "[ mono ] failed to resolve class: %s.%s\n", namespace_name, class_name );
        }
        else
        {
            printf( "[ mono ] resolved class: %s.%s\n", namespace_name, class_name );
        }

        return klass;
    }

    // @usage: resolve_method_from_class( klass, method_name, param_count )
    void* resolve_method_from_class( void* klass, const char* method_name, int param_count )
    {
        if ( !mono_class_get_method_from_name )
        {
            printf( "[ mono ] mono_class_get_method_from_name is null\n" );
            return nullptr;
        }

        void* method = mono_class_get_method_from_name( klass, method_name, param_count );
        if ( !method )
        {
            printf( "[ mono ] failed to resolve method: %s\n", method_name );
        }
        else
        {
            printf( "[ mono ] resolved method: %s\n", method_name );
        }

        return method;
    }

    // @usage: invoke_method( method, obj, params, exc )
    void* invoke_method( void* method, void* obj, void** params, void** exc )
    {
        if ( !mono_runtime_invoke )
        {
            printf( "[ mono ] mono_runtime_invoke is null\n" );
            return nullptr;
        }

        void* result = mono_runtime_invoke( method, obj, params, exc );
        if ( !result && exc && *exc )
        {
            printf( "[ mono ] exception occurred during method invocation\n" );
        }

        return result;
    }

    // initialize
    inline bool initialize( )
    {
        if ( !core::globals::h_game )
        {
            printf( "[ mono ] core::globals::h_game is null\n" );
            return false;
        }

        mono_get_method = reinterpret_cast<mono_get_method_t>( GetProcAddress( core::globals::h_game, "mono_get_method" ) );
        mono_method_get_name = reinterpret_cast<mono_method_get_name_t>( GetProcAddress( core::globals::h_game, "mono_method_get_name" ) );
        mono_class_from_name = reinterpret_cast<mono_class_from_name_t>( GetProcAddress( core::globals::h_game, "mono_class_from_name" ) );
        mono_class_get_method_from_name = reinterpret_cast<mono_class_get_method_from_name_t>( GetProcAddress( core::globals::h_game, "mono_class_get_method_from_name" ) );
        mono_runtime_invoke = reinterpret_cast<mono_runtime_invoke_t>( GetProcAddress( core::globals::h_game, "mono_runtime_invoke" ) );

        if ( !mono_get_method )
        {
            printf( "[ mono ] failed to find mono_get_method\n" );
            return false;
        }

        if ( !mono_method_get_name )
        {
            printf( "[ mono ] failed to find mono_method_get_name\n" );
        }

        if ( !mono_class_from_name )
        {
            printf( "[ mono ] failed to find mono_class_from_name\n" );
        }

        if ( !mono_class_get_method_from_name )
        {
            printf( "[ mono ] failed to find mono_class_get_method_from_name\n" );
        }

        if ( !mono_runtime_invoke )
        {
            printf( "[ mono ] failed to find mono_runtime_invoke\n" );
        }

        printf( "[ mono ] mono_get_method : %p\n", mono_get_method );
        printf( "[ mono ] mono_method_get_name : %p\n", mono_method_get_name );
        printf( "[ mono ] mono_class_from_name : %p\n", mono_class_from_name );
        printf( "[ mono ] mono_class_get_method_from_name : %p\n", mono_class_get_method_from_name );
        printf( "[ mono ] mono_runtime_invoke : %p\n", mono_runtime_invoke );

        return true;
    }
}
