#include <node/node.h>
#include "bwmesh.h"

using namespace test;


void Init(v8::Handle<v8::Object> exports) {
    Test::Init(exports);
}

NODE_MODULE(addon, Init);
