#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    using String = CharArray<32>;

    // see std::_Tree_node

    #pragma pack(push, 1)
    template<class K, class V>
    // red-black tree
    struct TreeNode
    {
        TreeNode<K, V>* left;    //0x00
        TreeNode<K, V>* parent;  //0x04
        TreeNode<K, V>* right;   //0x08
        K key;                   //0x0C
        V value;                 //0x10
        char color;              //0x14 (String: 0x30)
        bool isNil;              //0x15 (String: 0x31)
        // PAD(2)
        // 0x18 (String: 0x32)
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    template<class K, class V>
    struct FindResult
    {
        PAD(4);                //0x38
        TreeNode<K, V>* node;  //0x3C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    template<class K, class V>
    struct SSyncMap
    {
        CRITICAL_SECTION cs;   //0x00
        PAD(24);
        TreeNode<K, V>* head;  //0x30
        UINT32 count;          //0x34
        // 0x38
        FindResult<K, V> findResult;
        PAD(8);
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(SSyncMap<ULONG, void*>) == 0x48);
}
