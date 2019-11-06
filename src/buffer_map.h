#ifndef BUFFER_MAP_H
#define BUFFER_MAP_H

#include <napi.h>
#include <unordered_map>
#include <iostream>

typedef unsigned char byte;

struct KeyHash {
    std::size_t operator()(const Napi::Buffer<byte>& key) const {

        // std::cout << "std::hash<int>()(key.Length())" << std::endl;
        // std::cout << std::hash<int>()(key.Length()) << std::endl;

        return std::hash<int>()(key.Length());
    }
};

struct KeyEqual {
    bool operator()(const Napi::Buffer<byte>& lhs, const Napi::Buffer<byte>& rhs) const {

        // std::cout << "lhs.StrictEquals(rhs) " << lhs.StrictEquals(rhs) << std::endl;

        return lhs.StrictEquals(rhs);
    }
};

typedef std::unordered_map<
    Napi::Buffer<byte>,
    Napi::Value,
    KeyHash,
    KeyEqual
> Map;

class BufferMap : public Napi::ObjectWrap<BufferMap> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        BufferMap(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;

        Napi::Value Get(const Napi::CallbackInfo& info);
        Napi::Value Set(const Napi::CallbackInfo& info);

        Map items;
};

#endif