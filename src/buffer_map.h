#ifndef BUFFER_MAP_H
#define BUFFER_MAP_H

#include <napi.h>
#include <unordered_map>

typedef std::unordered_map<std::string, Napi::ObjectReference> Map;

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