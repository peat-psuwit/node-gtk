/* autogenerated by generator-font-face.js */

#include "../../debug.h"
#include "../../gi.h"
#include "../../util.h"
#include "path.h"
#include "font-face.h"
#include "matrix.h"
#include "surface.h"

using namespace v8;


namespace GNodeJS {

namespace Cairo {



Nan::Persistent<FunctionTemplate> FontFace::constructorTemplate;
Nan::Persistent<Function>         FontFace::constructor;


Nan::Persistent<FunctionTemplate> ToyFontFace::constructorTemplate;
Nan::Persistent<Function>         ToyFontFace::constructor;


Nan::Persistent<FunctionTemplate> FtFontFace::constructorTemplate;
Nan::Persistent<Function>         FtFontFace::constructor;


Nan::Persistent<FunctionTemplate> Win32FontFace::constructorTemplate;
Nan::Persistent<Function>         Win32FontFace::constructor;


Nan::Persistent<FunctionTemplate> QuartzFontFace::constructorTemplate;
Nan::Persistent<Function>         QuartzFontFace::constructor;



/*
 * Initialize
 */

FontFace::FontFace(cairo_font_face_t* data) : ObjectWrap() {
  _data = data;
}

/*
 * Destroy
 */

FontFace::~FontFace() {
  if (_data != NULL) {
    cairo_font_face_destroy (_data);
  }
}


/*
 * Template methods
 */


Local<FunctionTemplate> FontFace::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> FontFace::GetConstructor() {
  if (constructor.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void FontFace::SetupTemplate() {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(FontFace::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoFontFace").ToLocalChecked());


  SET_PROTOTYPE_METHOD(tpl, status);
  SET_PROTOTYPE_METHOD(tpl, getType);
  SET_PROTOTYPE_METHOD(tpl, getReferenceCount);

  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();

  SET_METHOD(ctor, create);
  SET_METHOD(ctor, createForFtFace);
  SET_METHOD(ctor, createForPattern);
  #ifdef PLATFORM_WIN
  SET_METHOD(ctor, createForLogfontw);
  #endif
  #ifdef PLATFORM_WIN
  SET_METHOD(ctor, createForHfont);
  #endif
  #ifdef PLATFORM_WIN
  SET_METHOD(ctor, createForLogfontwHfont);
  #endif
  #ifdef PLATFORM_MAC
  SET_METHOD(ctor, createForCgfont);
  #endif
  #ifdef PLATFORM_MAC
  SET_METHOD(ctor, createForAtsuFontId);
  #endif

  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);


  ToyFontFace::SetupTemplate(tpl);
  FtFontFace::SetupTemplate(tpl);
  Win32FontFace::SetupTemplate(tpl);
  QuartzFontFace::SetupTemplate(tpl);
}


Local<FunctionTemplate> ToyFontFace::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> ToyFontFace::GetConstructor() {
  if (constructor.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void ToyFontFace::SetupTemplate(Local<FunctionTemplate> parentTpl) {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(ToyFontFace::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoToyFontFace").ToLocalChecked());
  tpl->Inherit (parentTpl);

  SET_PROTOTYPE_METHOD(tpl, getFamily);
  SET_PROTOTYPE_METHOD(tpl, getSlant);
  SET_PROTOTYPE_METHOD(tpl, getWeight);

  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();



  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);

}


Local<FunctionTemplate> FtFontFace::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> FtFontFace::GetConstructor() {
  if (constructor.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void FtFontFace::SetupTemplate(Local<FunctionTemplate> parentTpl) {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(FtFontFace::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoFtFontFace").ToLocalChecked());
  tpl->Inherit (parentTpl);

  SET_PROTOTYPE_METHOD(tpl, getSynthesize);
  SET_PROTOTYPE_METHOD(tpl, setSynthesize);
  SET_PROTOTYPE_METHOD(tpl, unsetSynthesize);

  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();



  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);

}


Local<FunctionTemplate> Win32FontFace::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> Win32FontFace::GetConstructor() {
  if (constructor.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void Win32FontFace::SetupTemplate(Local<FunctionTemplate> parentTpl) {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(Win32FontFace::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoWin32FontFace").ToLocalChecked());
  tpl->Inherit (parentTpl);



  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();



  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);

}


Local<FunctionTemplate> QuartzFontFace::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> QuartzFontFace::GetConstructor() {
  if (constructor.IsEmpty())
    FontFace::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void QuartzFontFace::SetupTemplate(Local<FunctionTemplate> parentTpl) {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(QuartzFontFace::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoQuartzFontFace").ToLocalChecked());
  tpl->Inherit (parentTpl);



  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();



  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);

}



/*
 * Initialize method
 */


void FontFace::Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
  Nan::Set (target, Nan::New ("FontFace").ToLocalChecked(), FontFace::GetConstructor());
  Nan::Set (target, Nan::New ("ToyFontFace").ToLocalChecked(), ToyFontFace::GetConstructor());
  Nan::Set (target, Nan::New ("FtFontFace").ToLocalChecked(), FtFontFace::GetConstructor());
  Nan::Set (target, Nan::New ("Win32FontFace").ToLocalChecked(), Win32FontFace::GetConstructor());
  Nan::Set (target, Nan::New ("QuartzFontFace").ToLocalChecked(), QuartzFontFace::GetConstructor());
}



/*
 * Instance constructors
 */



NAN_METHOD(FontFace::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_font_face_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate FontFace: use static creators");
  }

  FontFace* instance = new FontFace(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



NAN_METHOD(ToyFontFace::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_font_face_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate ToyFontFace: use static creators");
  }

  ToyFontFace* instance = new ToyFontFace(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



NAN_METHOD(FtFontFace::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_font_face_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate FtFontFace: use static creators");
  }

  FtFontFace* instance = new FtFontFace(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



NAN_METHOD(Win32FontFace::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_font_face_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate Win32FontFace: use static creators");
  }

  Win32FontFace* instance = new Win32FontFace(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



NAN_METHOD(QuartzFontFace::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_font_face_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate QuartzFontFace: use static creators");
  }

  QuartzFontFace* instance = new QuartzFontFace(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



/*
 * Methods
 */

NAN_METHOD(FontFace::status) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FontFace>(self)->_data;

  // function call
  cairo_status_t result = cairo_font_face_status (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FontFace::getType) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FontFace>(self)->_data;

  // function call
  cairo_font_type_t result = cairo_font_face_get_type (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FontFace::getReferenceCount) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FontFace>(self)->_data;

  // function call
  unsigned int result = cairo_font_face_get_reference_count (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FontFace::create) {
  // in-arguments
  Nan::Utf8String family__value(info[0].As<String>()); auto family = *family__value;
  auto slant = (cairo_font_slant_t) Nan::To<int64_t>(info[1].As<Number>()).ToChecked();
  auto weight = (cairo_font_weight_t) Nan::To<int64_t>(info[2].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_toy_font_face_create (family, slant, weight);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (ToyFontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FontFace::createForFtFace) {
  // in-arguments
  auto face = (FT_Face) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();
  auto load_flags = Nan::To<int64_t>(info[1].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_ft_font_face_create_for_ft_face (face, load_flags);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (FtFontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FontFace::createForPattern) {
  // in-arguments
  auto pattern = (FcPattern *) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_ft_font_face_create_for_pattern (pattern);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (FtFontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}

#ifdef PLATFORM_WIN
NAN_METHOD(FontFace::createForLogfontw) {
  // in-arguments
  auto logfont = (LOGFONTW *) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_win32_font_face_create_for_logfontw (logfont);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (Win32FontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}
#endif // PLATFORM_WIN

#ifdef PLATFORM_WIN
NAN_METHOD(FontFace::createForHfont) {
  // in-arguments
  auto font = (HFONT) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_win32_font_face_create_for_hfont (font);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (Win32FontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}
#endif // PLATFORM_WIN

#ifdef PLATFORM_WIN
NAN_METHOD(FontFace::createForLogfontwHfont) {
  // in-arguments
  auto logfont = (LOGFONTW *) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();
  auto font = (HFONT) Nan::To<int64_t>(info[1].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_win32_font_face_create_for_logfontw_hfont (logfont, font);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (Win32FontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}
#endif // PLATFORM_WIN

#ifdef PLATFORM_MAC
NAN_METHOD(FontFace::createForCgfont) {
  // in-arguments
  auto font = (CGFontRef) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_quartz_font_face_create_for_cgfont (font);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (QuartzFontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}
#endif // PLATFORM_MAC

#ifdef PLATFORM_MAC
NAN_METHOD(FontFace::createForAtsuFontId) {
  // in-arguments
  auto font_id = (ATSUFontID) Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_font_face_t * result = cairo_quartz_font_face_create_for_atsu_font_id (font_id);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (QuartzFontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}
#endif // PLATFORM_MAC
NAN_METHOD(ToyFontFace::getFamily) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<ToyFontFace>(self)->_data;

  // function call
  const char * result = cairo_toy_font_face_get_family (font_face);

  // return
  Local<Value> returnValue = UTF8 (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ToyFontFace::getSlant) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<ToyFontFace>(self)->_data;

  // function call
  cairo_font_slant_t result = cairo_toy_font_face_get_slant (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ToyFontFace::getWeight) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<ToyFontFace>(self)->_data;

  // function call
  cairo_font_weight_t result = cairo_toy_font_face_get_weight (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}
NAN_METHOD(FtFontFace::getSynthesize) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FtFontFace>(self)->_data;

  // function call
  unsigned int result = cairo_ft_font_face_get_synthesize (font_face);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(FtFontFace::setSynthesize) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FtFontFace>(self)->_data;

  // in-arguments
  auto synth_flags = Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_ft_font_face_set_synthesize (font_face, synth_flags);
}

NAN_METHOD(FtFontFace::unsetSynthesize) {
  auto self = info.This();
  auto font_face = Nan::ObjectWrap::Unwrap<FtFontFace>(self)->_data;

  // in-arguments
  auto synth_flags = Nan::To<int64_t>(info[0].As<Number>()).ToChecked();

  // function call
  cairo_ft_font_face_unset_synthesize (font_face, synth_flags);
}



}; // Cairo

}; // GNodeJS