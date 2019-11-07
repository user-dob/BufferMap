#include "buffer_map.h"
#include <iostream>

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
    auto key = info[0].As<Napi::Buffer<char>>();

    std::string str(key.Data(), 3);

    std::cout << "Get" << str << std::endl;

    auto iterator = map.find(str);

    if (iterator == map.end()) {
       return info.Env().Undefined();
    }

    return iterator->second.Value();
}

Napi::Value BufferMap::Set(const Napi::CallbackInfo& info) {
    auto key = info[0].As<Napi::Buffer<char>>();
    auto value = info[1].As<Napi::Object>();

    std::string str(key.Data(), 3);

    std::cout << "Set" << str << std::endl;

    map.insert({ str, Napi::Persistent(value) });

    return info.Env().Undefined();
}
