/* autogenerated by generator-scaled-font.js */

#include "../../debug.h"
#include "../../gi.h"
#include "../../util.h"
#include "scaled-font.h"
#include "font-extents.h"
#include "font-face.h"
#include "font-options.h"
#include "glyph.h"
#include "matrix.h"
#include "text-cluster.h"
#include "text-extents.h"

using namespace v8;


namespace GNodeJS {

namespace Cairo {



Nan::Persistent<FunctionTemplate> ScaledFont::constructorTemplate;
Nan::Persistent<Function>         ScaledFont::constructor;



/*
 * Initialize
 */

ScaledFont::ScaledFont(cairo_scaled_font_t* data) : ObjectWrap() {
  _data = data;
}

/*
 * Destroy
 */

ScaledFont::~ScaledFont() {
  if (_data != NULL) {
    cairo_scaled_font_destroy (_data);
  }
}


/*
 * Template methods
 */


Local<FunctionTemplate> ScaledFont::GetTemplate() {
  if (constructorTemplate.IsEmpty())
    ScaledFont::SetupTemplate();
  return Nan::New<FunctionTemplate> (constructorTemplate);
}

Local<Function> ScaledFont::GetConstructor() {
  if (constructor.IsEmpty())
    ScaledFont::SetupTemplate();
  return Nan::New<Function> (constructor);
}

void ScaledFont::SetupTemplate() {

  // Constructor
  auto tpl = Nan::New<FunctionTemplate>(ScaledFont::New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(Nan::New("CairoScaledFont").ToLocalChecked());


  SET_PROTOTYPE_METHOD(tpl, status);
  SET_PROTOTYPE_METHOD(tpl, extents);
  SET_PROTOTYPE_METHOD(tpl, textExtents);
  SET_PROTOTYPE_METHOD(tpl, glyphExtents);
  SET_PROTOTYPE_METHOD(tpl, textToGlyphs);
  SET_PROTOTYPE_METHOD(tpl, getFontFace);
  SET_PROTOTYPE_METHOD(tpl, getFontOptions);
  SET_PROTOTYPE_METHOD(tpl, getFontMatrix);
  SET_PROTOTYPE_METHOD(tpl, getCtm);
  SET_PROTOTYPE_METHOD(tpl, getScaleMatrix);
  SET_PROTOTYPE_METHOD(tpl, getType);
  SET_PROTOTYPE_METHOD(tpl, getReferenceCount);

  auto ctor = Nan::GetFunction (tpl).ToLocalChecked();

  SET_METHOD(ctor, create);

  constructorTemplate.Reset(tpl);
  constructor.Reset(ctor);



}



/*
 * Initialize method
 */


void ScaledFont::Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
  Nan::Set (target, Nan::New ("ScaledFont").ToLocalChecked(), ScaledFont::GetConstructor());
}



/*
 * Instance constructors
 */



NAN_METHOD(ScaledFont::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
  }

  cairo_scaled_font_t* data = NULL;

  if (info[0]->IsExternal()) {
    data = (cairo_scaled_font_t*) External::Cast (*info[0])->Value ();
  }
  else {
    return Nan::ThrowError("Cannot instantiate ScaledFont: use static creators");
  }

  ScaledFont* instance = new ScaledFont(data);
  instance->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}



/*
 * Methods
 */

NAN_METHOD(ScaledFont::create) {
  // in-arguments
  auto font_face = Nan::ObjectWrap::Unwrap<FontFace>(info[0].As<Object>())->_data;
  auto font_matrix = Nan::ObjectWrap::Unwrap<Matrix>(info[1].As<Object>())->_data;
  auto ctm = Nan::ObjectWrap::Unwrap<Matrix>(info[2].As<Object>())->_data;
  auto options = Nan::ObjectWrap::Unwrap<FontOptions>(info[3].As<Object>())->_data;

  // function call
  cairo_scaled_font_t * result = cairo_scaled_font_create (font_face, font_matrix, ctm, options);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (ScaledFont::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::status) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // function call
  cairo_status_t result = cairo_scaled_font_status (scaled_font);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::extents) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // out-arguments
  auto extents = Nan::NewInstance(
            Nan::New<Function>(FontExtents::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_extents (scaled_font, Nan::ObjectWrap::Unwrap<FontExtents>(extents)->_data);

  // return
  Local<Value> returnValue = extents;
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::textExtents) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // in-arguments
  auto utf8__value = info[0].As<String>(); auto utf8 = *Nan::Utf8String(utf8__value);

  // out-arguments
  auto extents = Nan::NewInstance(
            Nan::New<Function>(TextExtents::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_text_extents (scaled_font, utf8, Nan::ObjectWrap::Unwrap<TextExtents>(extents)->_data);

  // return
  Local<Value> returnValue = extents;
  info.GetReturnValue().Set(returnValue);
}

/* HAND-MODIFIED: glyphExtents(glyphs) */
NAN_METHOD(ScaledFont::glyphExtents) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // in-arguments
  auto glyphs = Nan::ObjectWrap::Unwrap<Glyph>(info[0].As<Object>());

  // out-arguments
  auto extents = Nan::NewInstance(
          Nan::New<Function>(TextExtents::constructor),
          0,
          NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_glyph_extents (scaled_font, glyphs->_data, glyphs->_length, Nan::ObjectWrap::Unwrap<TextExtents>(extents)->_data);

  // return
  Local<Value> returnValue = extents;
  info.GetReturnValue().Set(returnValue);
}

/* HAND-MODIFIED: textToGlyphs(x, y, utf8, getClusters: boolean) */
NAN_METHOD(ScaledFont::textToGlyphs) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // in-arguments
  auto x = Nan::To<double>(info[0].As<Number>()).ToChecked();
  auto y = Nan::To<double>(info[1].As<Number>()).ToChecked();
  auto utf8__value = info[2].As<String>(); auto utf8 = *Nan::Utf8String(utf8__value);
  auto utf8_len = info[2].As<String>()->Length();
  auto get_clusters = info.Length() == 4 ? Nan::To<bool>(info[3].As<v8::Boolean>()).ToChecked() : false;

  // out-arguments
  cairo_glyph_t *glyphs = NULL;
  int num_glyphs = 0;
  cairo_text_cluster_t *clusters = NULL;
  int num_clusters = 0;
  cairo_text_cluster_flags_t cluster_flags = (cairo_text_cluster_flags_t) 0;

  // function call
  cairo_status_t result = cairo_scaled_font_text_to_glyphs (scaled_font,
      x,
      y,
      utf8,
      utf8_len,
      &glyphs,
      &num_glyphs,
      get_clusters ? &clusters : NULL,
      get_clusters ? &num_clusters : NULL,
      get_clusters ? &cluster_flags : NULL);

  // return
  Local<Array> returnValue = Nan::New<Array> (get_clusters ? 2 : 1);
  Local<Value> glyphsArgs[] = { Nan::New<External> (glyphs), Nan::New<Number> (num_glyphs) };
  auto glyphsObject = Nan::NewInstance(
      Nan::New<Function>(Glyph::constructor), 2, glyphsArgs).ToLocalChecked();
  Nan::Set (returnValue, 0, glyphsObject);
  if (get_clusters) {
    Local<Value> clustersArgs[] = {
          Nan::New<External> (clusters),
          Nan::New<Number> (num_clusters),
          Nan::New<Number> ((int64_t) cluster_flags) };
    auto clustersObject = Nan::NewInstance(
        Nan::New<Function>(TextCluster::constructor), 3, clustersArgs).ToLocalChecked();
    Nan::Set (returnValue, 1, clustersObject);
  }
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getFontFace) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // function call
  cairo_font_face_t * result = cairo_scaled_font_get_font_face (scaled_font);

  // return
  Local<Value> args[] = { Nan::New<External> (result) };
  Local<Function> constructor = Nan::New<Function> (FontFace::constructor);
  Local<Value> returnValue = Nan::NewInstance(constructor, 1, args).ToLocalChecked();
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getFontOptions) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // out-arguments
  auto options = Nan::NewInstance(
            Nan::New<Function>(FontOptions::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_get_font_options (scaled_font, Nan::ObjectWrap::Unwrap<FontOptions>(options)->_data);

  // return
  Local<Value> returnValue = options;
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getFontMatrix) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // out-arguments
  auto font_matrix = Nan::NewInstance(
            Nan::New<Function>(Matrix::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_get_font_matrix (scaled_font, Nan::ObjectWrap::Unwrap<Matrix>(font_matrix)->_data);

  // return
  Local<Value> returnValue = font_matrix;
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getCtm) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // out-arguments
  auto ctm = Nan::NewInstance(
            Nan::New<Function>(Matrix::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_get_ctm (scaled_font, Nan::ObjectWrap::Unwrap<Matrix>(ctm)->_data);

  // return
  Local<Value> returnValue = ctm;
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getScaleMatrix) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // out-arguments
  auto scale_matrix = Nan::NewInstance(
            Nan::New<Function>(Matrix::constructor),
            0,
            NULL).ToLocalChecked();

  // function call
  cairo_scaled_font_get_scale_matrix (scaled_font, Nan::ObjectWrap::Unwrap<Matrix>(scale_matrix)->_data);

  // return
  Local<Value> returnValue = scale_matrix;
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getType) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // function call
  cairo_font_type_t result = cairo_scaled_font_get_type (scaled_font);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(ScaledFont::getReferenceCount) {
  auto self = info.This();
  auto scaled_font = Nan::ObjectWrap::Unwrap<ScaledFont>(self)->_data;

  // function call
  unsigned int result = cairo_scaled_font_get_reference_count (scaled_font);

  // return
  Local<Value> returnValue = Nan::New (result);
  info.GetReturnValue().Set(returnValue);
}



}; // Cairo

}; // GNodeJS
