#ifndef BUFFER_MAP_H
#define BUFFER_MAP_H

#include <napi.h>
#include <unordered_map>

typedef u_int8_t byte;

struct KeyHash {
    std::size_t operator()(const std::array<byte, 8>& key) const {
        return 10;
    }
};

typedef std::unordered_map<
    std::array<byte, 8>,
    Napi::ObjectReference,
    KeyHash
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