#include "buffer_map.h"
#include <iostream>

void printBuffer(std::string title, const Napi::Buffer<byte>& buffer) {
    auto length = buffer.Length();
    auto data = buffer.Data();

    std::cout << title << std::endl;
    for (size_t i = 0; i < length; i++) {
        std::cout << i << ": " << static_cast<int>(data[i]) << std::endl;
    }
}

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
    Napi::Buffer<byte> key = info[0].As<Napi::Buffer<byte>>();
    auto iterator = items.find(key);

    if (iterator == items.end()) {
       return info.Env().Undefined();
    }

    std::cout << iterator->second << std::endl;

    return Napi::Value(info.Env(), iterator->second);
}

Napi::Value BufferMap::Set(const Napi::CallbackInfo& info) {
    Napi::Buffer<byte> key = info[0].As<Napi::Buffer<byte>>();
    Napi::Value value = info[1].As<Napi::Value>();

    items.insert({ key, value });

    return info.Env().Undefined();
}
