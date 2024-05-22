# Documentation

This library is for the **dbAgent** service. It is required for episode 6.4 clients. It adds support for the character list packet and the name availability packet. Expose the `SHAIYA_EP6_4_PT` macro; otherwise, the character list packet will be incorrect.

```cpp
// sdev/include/shaiya/common.h
//#define SHAIYA_EP6
#define SHAIYA_EP6_4_PT
```
