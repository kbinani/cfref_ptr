#include "./cfref_ptr.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("move-constructor") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CHECK(CFGetRetainCount(str.get()) == 1);

    uintptr_t ptr = (uintptr_t)str.get();
    cfref_ptr<CFStringRef> moved(std::move(str));

    CHECK(str.get() == nullptr);
    CHECK((uintptr_t)moved.get() == ptr);
    CHECK(CFGetRetainCount(moved.get()) == 1);
}


TEST_CASE("self-assignment") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CHECK(CFGetRetainCount(str.get()) == 1);

    uintptr_t ptr = (uintptr_t)str.get();
    str = std::move(str);
    CHECK((uintptr_t)str.get() == ptr);
    CHECK(CFGetRetainCount(str.get()) == 1);
}


TEST_CASE("move-assignment") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CHECK(CFGetRetainCount(str.get()) == 1);

    uintptr_t ptr = (uintptr_t)str.get();
    cfref_ptr<CFStringRef> moved = std::move(str);

    CHECK(str.get() == nullptr);
    CHECK((uintptr_t)moved.get() == ptr);
    CHECK(CFGetRetainCount(moved.get()) == 1);
}


TEST_CASE("copy-assignment") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);

    CFIndex refcount = CFGetRetainCount(str.get());
    cfref_ptr<CFStringRef> copy = str;

    CHECK(str.get() != nullptr);
    CHECK(copy.get() == str.get());

    CHECK(refcount + 1 == CFGetRetainCount(str.get()));
}


TEST_CASE("copy-constructor") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);

    CFIndex refcount = CFGetRetainCount(str.get());
    cfref_ptr<CFStringRef> copy(str);

    CHECK(str.get() != nullptr);
    CHECK(copy.get() == str.get());

    CHECK(refcount + 1 == CFGetRetainCount(str.get()));
}


TEST_CASE("destructor") {
    cfref_ptr<CFStringRef> original = CFStringCreateWithCString(kCFAllocatorDefault,
                                                                "test",
                                                                kCFStringEncodingUTF8);
    assert(CFGetRetainCount(original.get()) == 1);
    {
        cfref_ptr<CFStringRef> str(original);
        CHECK((uintptr_t)original.get() == (uintptr_t)str.get());
        CHECK(CFGetRetainCount(original.get()) == 2);

        cfref_ptr<CFStringRef> copy = str;
        CHECK((uintptr_t)original.get() == (uintptr_t)copy.get());
        CHECK(CFGetRetainCount(original.get()) == 3);
    }
    CHECK(CFGetRetainCount(original.get()) == 1);
}


TEST_CASE("release") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    uintptr_t ptr = (uintptr_t)str.get();
    CHECK(CFGetRetainCount(str.get()) == 1);
    CFStringRef released = str.release();
    CHECK(str.get() == nullptr);
    CHECK((uintptr_t)released == ptr);
    CHECK(CFGetRetainCount(released) == 1);
    CFRelease(released);
}


TEST_CASE("reset to NULL") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CFStringRef ptr = str.get();
    CFRetain(ptr);
    CHECK(CFGetRetainCount(ptr) == 2);
    str.reset();
    CHECK(str.get() == nullptr);
    CHECK(CFGetRetainCount(ptr) == 1);
    CFRelease(ptr);
}


TEST_CASE("reset by other") {
    cfref_ptr<CFStringRef> str = CFStringCreateWithCString(kCFAllocatorDefault,
                                                           "test",
                                                           kCFStringEncodingUTF8);
    CFStringRef ptr = str.get();
    CFRetain(ptr);
    CHECK(CFGetRetainCount(ptr) == 2);

    CFStringRef other = CFStringCreateWithCString(kCFAllocatorDefault,
                                                  "test",
                                                  kCFStringEncodingUTF8);

    str.reset(other);
    CHECK((uintptr_t)str.get() == (uintptr_t)other);
    CHECK(CFGetRetainCount(ptr) == 1);
    CFRelease(ptr);
    CHECK(CFGetRetainCount(other) == 1);
}
