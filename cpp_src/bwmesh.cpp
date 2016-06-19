
#include "bwmesh.h"

#pragma once

using namespace ngm;

Persistent<Function> Ngm::constructor;

Ngm::Ngm()
    :m_mesh(0)
{}

Ngm::~Ngm() {
    delete m_mesh;
}


void Ngm::Init(v8::Handle<v8::Object> exports) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, New);
    tpl->SetClassName(v8::String::NewFromUtf8(isolate, "Ngm"));

    tpl->InstanceTemplate()->SetInternalFieldCount(2);

    NODE_SET_PROTOTYPE_METHOD(tpl, "loadFile", loadFile);
    NODE_SET_PROTOTYPE_METHOD(tpl, "setConfig", setConfig);

    Ngm::constructor.Reset(isolate, tpl->GetFunction());

    exports->Set(v8::String::NewFromUtf8(isolate, "Ngm"), tpl->GetFunction());
}

void Ngm::New(const FunctionCallbackInfo<Value>& args) {

    v8::Isolate * isolate = v8::Isolate::GetCurrent();
    v8::HandleScope handle_scope(isolate);

    if(args.IsConstructCall()) {
        /* int fm = args[0]->IsUndefined()? 0: args[0]->NumberValue(); */
        Ngm *obj = new Ngm();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void Ngm::setConfig(const v8::FunctionCallbackInfo<v8::Value>& args) {

    /* v8 isolate and the HandleScope, is the main imporant */
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    if(args[0]->IsObject()) {
        /* covert args[0] to Handle<Object> */
        v8::Handle<v8::Object> conf = v8::Handle<v8::Object>::Cast(args[0]);
        v8::Handle<v8::Boolean> isSecondOrder = conf->Get(
                v8::String::NewFromUtf8(isolate, "isSecondOrder"));
        v8::Handle<v8::Boolean> isRefinement = conf->Get(
                v8::String::NewFromUtf8(isolate, "isRefinement"));
        Ngm *obj = node::ObjectWrap::Unwrap<Ngm>(args.Holder());
        obj->m_isRefinement = isRefinement->BooleanValue();
        obj->m_isSecondOrder = isSecondOrder->BooleanValue();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } 
}

/* void Ngm::PlusOne(const FunctionCallbackInfo<Value>& args) {
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope handle_scope(isolate);
    Ngm *obj = node::ObjectWrap::Unwrap<Ngm>(args.Holder());
    obj->value_ += 1;
    args.GetReturnValue().Set(Number::New(isolate, obj->value_));
} */

void Ngm::loadFile(const FunctionCallbackInfo<Value>& args) {
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope handle_scope(isolate);

    Ngm *obj = node::ObjectWrap::Unwrap<Ngm>(args.Holder());
    obj->value_ += 1;
    args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}
