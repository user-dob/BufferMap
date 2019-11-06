#ifndef BUFFER_MAP_H
#define BUFFER_MAP_H

#include <napi.h>
#include <unordered_map>
#include <iostream>

typedef unsigned char byte;

struct KeyHash {
    std::size_t operator()(const Napi::Buffer<byte>& key) const {
        auto data = key.Data();
        unsigned long hash = 5381;
        byte c;

        while (c = *data++) {
            std::cout << "c " << static_cast<int>(c) << std::endl;
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        std::cout << "hash " << hash << std::endl;

        return hash;
    }
};

struct KeyEqual {
    bool operator()(const Napi::Buffer<byte>& lhs, const Napi::Buffer<byte>& rhs) const {
        return lhs.StrictEquals(rhs);
    }
};

typedef std::unordered_map<
    Napi::Buffer<byte>,
    Napi::ObjectReference,
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

        Map map;
};

#endif