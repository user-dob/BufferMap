#include "buffer_map.h"
#include <iostream>
#include <array>

Napi::FunctionReference BufferMap::constructor;

Napi::Object BufferMap::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "BufferMap", {
        InstanceMethod("get", &BufferMap::Get),
        InstanceMethod("set", &BufferMap::Set)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("BufferMap", func);

    return exports;
}

BufferMap::BufferMap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<BufferMap>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
}

Napi::Value BufferMap::Get(const Napi::CallbackInfo& info) {
    auto buffer = info[0].As<Napi::Buffer<byte>>();

    std::array<byte, 8> key;

    std::memcpy(key.data(), buffer.Data(), 8);

    auto iterator = map.find(key);

    if (iterator == map.end()) {
       return info.Env().Undefined();
    }

    return iterator->second.Value();
}

Napi::Value BufferMap::Set(const Napi::CallbackInfo& info) {
    auto buffer = info[0].As<Napi::Buffer<byte>>();
    auto value = info[1].As<Napi::Object>();

    std::array<byte, 8> key;

    std::memcpy(key.data(), buffer.Data(), 8);

    map.insert({ key, Napi::Persistent(value) });

    return info.Env().Undefined();
}
