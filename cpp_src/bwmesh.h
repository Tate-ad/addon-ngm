#ifndef BWMESH_H_
#define BWMESH_H_

#include <node/node.h>
#include <node/node_object_wrap.h>
#include "model/lwMesh.h"

namespace ngm {

    using namespace v8;

    class Ngm: public node::ObjectWrap {
        public:
            /* init v8 */
            static void Init(Handle<Object> exports);

        private:
            Ngm();
            ~Ngm();

            /* use in v8 */
            static void New(const FunctionCallbackInfo<Value>& args);
            /* static void PlusOne(const FunctionCallbackInfo<Value>& args); */
            static void loadFile(const FunctionCallbackInfo<Value>& args);
            static void setConfig(const FunctionCallbackInfo<Value>& args);
            static Persistent<Function> constructor;

        private:
            lwMesh *m_mesh;
            bool m_isSecondOrder;
            bool m_isRefinement;
    };
};

#endif
