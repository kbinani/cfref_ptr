cfref_ptr
=========

RAII for CFTypeRef.

example
=======

```cpp
#include <CoreFoundation/CoreFoundation.h>
#include "cfref_ptr.hpp"

// c++ -std=c++14 -framework CoreFoundation example.cpp -o example

int main() {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CFShow(str.get());

    cfref_ptr<CFStringRef> copy = str;

    // `str` is still valid here, because the copy operator behaves like `std::shared_ptr`
    CFShow(str.get());
    CFShow(copy.get());

    // We need not to call CFRelease for `str` and `copy` here.
}
```

license
=======

MIT
