#include <napi.h>
#include "buffer_map.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return BufferMap::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
