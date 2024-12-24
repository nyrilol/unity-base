#pragma once
#include <il2cpp.h>
#include <string>
#include <vector>

namespace sdk::il2cpp::gameobject
{
    // fn types 
    using find_t = void*( __stdcall* )( const char* );
    using find_with_tag_t = void*( __stdcall* )( const char* );
    using find_objects_with_tag_t = void**( __stdcall* )( const char*, int* );
    using get_component_t = void*( __stdcall* )( void*, const char* );

    void* find( const std::string& name )
    {
        find_t find = reinterpret_cast<find_t> (sdk::il2cpp::resolve_icall( "UnityEngine.GameObject::Find" ) );
        if ( !find )
        {
            printf( "[ gameobject ] find is nullptr\n" );
            return nullptr;
        }

        return find( name.c_str( ) );
    }

    void* find_with_tag( const std::string& tag )
    {
        find_with_tag_t find_with_tag = reinterpret_cast<find_with_tag_t>( sdk::il2cpp::resolve_icall( "UnityEngine.GameObject::FindWithTag" ) );
        if ( !find_with_tag )
        {
            printf( "[ gameobject ] find_with_tag is nullptr\n" );
            return nullptr;
        }

        return find_with_tag( tag.c_str( ) );
    }

    std::vector<void*> find_objects_with_tag( const std::string& tag )
    {
        find_objects_with_tag_t find_objects_with_tag = reinterpret_cast<find_objects_with_tag_t>( sdk::il2cpp::resolve_icall( "UnityEngine.GameObject::FindGameObjectsWithTag" ) );
        if ( !find_objects_with_tag )
        {
            printf( "[ gameobject ] find_objects_with_tag is nullptr\n" );
            return {};
        }

        int count = 0;
        void** objects = find_objects_with_tag( tag.c_str( ), &count );
        if ( !objects || count == 0 )
        {
            printf( "[ gameobject ] No objects found with tag: %s\n", tag.c_str() );
            return {};
        }

        return std::vector<void*>( objects, objects + count );
    }

    void* get_component( void* game_object, const std::string& component_name )
    {
        get_component_t get_component = reinterpret_cast<get_component_t>( sdk::il2cpp::resolve_icall( "UnityEngine.GameObject::GetComponent" ) );
        if ( !get_component )
        {
            printf( "[ gameobject ] get_component is nullptr\n" );
            return nullptr;
        }

        return get_component( game_object, component_name.c_str( ) );
    }
}