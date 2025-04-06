#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // A red-black tree (see std::_Tree_node)
    template<class K, class V>
    struct TreeNode
    {
        TreeNode<K, V>* left;    //0x00
        TreeNode<K, V>* parent;  //0x04
        TreeNode<K, V>* right;   //0x08
        K key;                   //0x0C
        V value;                 //0x10, 0x2C (string)
        char color;              //0x14, 0x30
        bool isNil;              //0x15, 0x31
        // PAD(2)
        // 0x18, 0x32
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    template<class K, class V>
    struct SSyncMap
    {
        CRITICAL_SECTION cs;   //0x00
        PAD(24);
        TreeNode<K, V>* head;  //0x30
        int32_t count;         //0x34
        PAD(16);
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncMap<uint32_t, void>) == 0x48);
}
