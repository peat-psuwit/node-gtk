/*
 * generator-font-face.js
 */

const fs = require('fs')
const path = require('path')
const util = require('util')
const removeTrailingSpaces = require('remove-trailing-spaces')
const { unindent } = require('./indent.js')

const {
  ENUM_TYPE,
  WRAP_TYPE,
  getInArgumentSource,
  getOutArgumentDeclaration,
  getFunctionCall,
  getReturn,
  parseFile,
  getInArguments,
  getOutArguments,
  getInOutArguments,
  getTypeName,
  getJSName,
} = require('./generator.js')


util.inspect.defaultOptions = { depth: 6 }

generateCairoFontFace()

function generateCairoFontFace() {
  const result = parseFile(path.join(__dirname, 'font-face.nid'))
  const declarations = result.declarations

  console.log(declarations)

  const namespaces = declarations.map((cur) => {
    const name = cur.namespace.name
    const options = {
      name,
      constructor: null,
      functions: null,
      isBase: name === 'FontFace',
      type: 'cairo_font_face_t'
    }

    const allFunctions =
      cur.namespace.declarations
        .filter(d => d.function)
        .map(d => {
          const fn = d.function
          fn.source = generateClassMethodSource(fn, options)
          return fn
        })

    options.constructor = allFunctions.find(fn => fn.attributes.constructor === true)
    options.functions = allFunctions.filter(fn => fn.attributes.constructor !== true)

    return options
  })


  /* ToyFontFace
   * FtFontFace
   * Win32FontFace
   * QuartzFontFace */

  const header = generateHeader(namespaces)
  const source = generateSource(namespaces)

  fs.writeFileSync(path.join(__dirname, 'font-face.h'),  header)
  fs.writeFileSync(path.join(__dirname, 'font-face.cc'), source)
}

// Helpers

function generateHeader(namespaces) {
  const classDeclarations = namespaces.map(generateClassDeclaration)
  return removeTrailingSpaces(unindent(`

    /* autogenerated by ${path.basename(__filename)} */

    #pragma once

    #include <nan.h>
    #include <node.h>
    #include <girepository.h>
    #include <glib.h>
    #include <cairo.h>
    #include <cairo-ft.h>
    #ifdef PLATFORM_WIN
    #   include <cairo-win32.h>
    #endif
    #ifdef PLATFORM_MAC
    #   include <cairo-quartz.h>
    #endif

    namespace GNodeJS {

    namespace Cairo {

    ${classDeclarations.join('\n    ')}

    }; // Cairo

    }; // GNodeJS

  `))
}

function generateSource(namespaces) {
  const base = namespaces.find(ns => ns.isBase)

  const classVariables    = namespaces.map(generateClassVariables)
  const templateMethods = namespaces.map(ns => generateTemplateMethods(ns, namespaces))
  const initializeMethod = generateInitializeMethod(base, namespaces)
  const newMethods = namespaces.map(generateNewMethod)
  const methods = namespaces.map(ns => ns.functions.map(fn => fn.source).join('\n'))

  return removeTrailingSpaces(unindent(`

    /* autogenerated by ${path.basename(__filename)} */

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


    ${classVariables.join('\n    ')}


    /*
     * Initialize font_face.
     */

    FontFace::FontFace(${base.type}* data) : ObjectWrap() {
      _data = data;
    }

    /*
     * Destroy font_face..
     */

    FontFace::~FontFace() {
      if (_data != NULL) {
        cairo_font_face_destroy (_data);
      }
    }


    /*
     * Template methods
     */

    ${templateMethods.join('\n    ')}


    /*
     * Initialize method
     */

    ${initializeMethod}


    /*
     * Instance constructors
     */

    ${newMethods.join('\n    ')}


    /*
     * Methods
     */

    ${methods.join('\n    ')}



    }; // Cairo

    }; // GNodeJS


  `))
}

function generateClassDeclaration(options) {

  return `
    class ${options.name}: public ${options.isBase ? 'Nan::ObjectWrap' : 'FontFace'} {
      public:
        static Nan::Persistent<v8::FunctionTemplate> constructorTemplate;
        static Nan::Persistent<v8::Function>         constructor;
        static void Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);${options.isBase ? `
        static void SetupTemplate();` : `
        static void SetupTemplate(Local<v8::FunctionTemplate> parentTpl);`}
        static Local<v8::FunctionTemplate> GetTemplate();
        static Local<v8::Function> GetConstructor();

        static NAN_METHOD(New);

        ${options.functions.map(fn =>
          (fn.attributes.ifdef ? `#ifdef ${fn.attributes.ifdef}\n        ` : '')
          + `static NAN_METHOD(${getFunctionJSName(fn)});`
          + (fn.attributes.ifdef ? `\n        #endif` : '')
          ).join('\n        ')}

        ${options.isBase ? `
        ${options.name}(cairo_font_face_t* data);
        ~${options.name}();

        cairo_font_face_t* _data;
` : `
        ${options.name}(cairo_font_face_t* data) : FontFace(data) {};
`}    };`
}

function generateClassVariables(options) {
  return `
    Nan::Persistent<FunctionTemplate> ${options.name}::constructorTemplate;
    Nan::Persistent<Function>         ${options.name}::constructor;
  `
}

function generateTemplateMethods(options, namespaces) {

  const base = namespaces.find(ns => ns.isBase)

  const staticMethods = options.functions.filter(fn => fn.attributes.static)
  const methods = options.functions.filter(fn => fn.attributes.static !== true)

  return `
    Local<FunctionTemplate> ${options.name}::GetTemplate() {
      if (constructorTemplate.IsEmpty())
        ${base.name}::SetupTemplate();
      return Nan::New<FunctionTemplate> (constructorTemplate);
    }

    Local<Function> ${options.name}::GetConstructor() {
      if (constructor.IsEmpty())
        ${base.name}::SetupTemplate();
      return Nan::New<Function> (constructor);
    }

    void ${options.name}::SetupTemplate(${!options.isBase ?  `Local<FunctionTemplate> parentTpl` : '' }) {

      // Constructor
      auto tpl = Nan::New<FunctionTemplate>(${options.name}::New);
      tpl->InstanceTemplate()->SetInternalFieldCount(1);
      tpl->SetClassName(Nan::New("Cairo${options.name}").ToLocalChecked());
${!options.isBase ?  `      tpl->Inherit (parentTpl);` : '' }

      ${methods.map(fn => `SET_PROTOTYPE_METHOD(tpl, ${getFunctionJSName(fn)});`).join('\n      ')}

      auto ctor = Nan::GetFunction (tpl).ToLocalChecked();

      ${staticMethods.map(fn =>
        (fn.attributes.ifdef ? `#ifdef ${fn.attributes.ifdef}\n      ` : '')
        + `SET_METHOD(ctor, ${getFunctionJSName(fn)});`
        + (fn.attributes.ifdef ? `\n      #endif` : '')
      ).join('\n      ')}

      constructorTemplate.Reset(tpl);
      constructor.Reset(ctor);

${options.isBase ? `
      ${namespaces.filter(ns => ns.name !== 'FontFace').map(ns =>
        `${ns.name}::SetupTemplate(tpl);`).join('\n      ')}
` : ''}    }
  `
}

function generateInitializeMethod(options, namespaces) {
  return `
    void ${options.name}::Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
      ${namespaces.map(ns =>
        `Nan::Set (target, Nan::New ("${ns.name}").ToLocalChecked(), ${ns.name}::GetConstructor());`).join('\n      ')}
    }
  `
}

function generateClassMethodSource(fn, options) {
  const selfArgument = fn.attributes.static !== true ? fn.parameters[0] : undefined
  const inArguments  = getInArguments(fn, options.type)
  const outArguments = getOutArguments(fn, options.type)
  const inoutArguments = getInOutArguments(fn, options.type)
  const outAndInoutArguments = outArguments.concat(inoutArguments)
  const hasResult = getTypeName(fn.type) !== 'void' || outAndInoutArguments.length > 0

  return `
    ${fn.attributes.ifdef ?  `
    #ifdef ${fn.attributes.ifdef}` : '' }
    NAN_METHOD(${options.name}::${getFunctionJSName(fn)}) {${selfArgument ? `
        auto self = info.This();
        auto ${selfArgument.name} = Nan::ObjectWrap::Unwrap<${options.name}>(self)->_data;
` : ''}${inArguments.length > 0 ? `
        // in-arguments
        ${inArguments.map(getInArgumentSource).join('\n        ')}
` : ''}${inoutArguments.length > 0 ? `
        // in-out-arguments
        ${inoutArguments.map(getInArgumentSource).join('\n        ')}
` : ''}${outArguments.length > 0 ? `
        // out-arguments
        ${outArguments.map(getOutArgumentDeclaration).join('\n        ')}
` : ''}
        // function call
        ${getFunctionCall(fn)}
${hasResult ? `
        // return
        ${getReturn(fn, outAndInoutArguments)}
` : ''}    }${fn.attributes.ifdef ?  `
    #endif // ${fn.attributes.ifdef}` : '' }`
}

function generateNewMethod(options) {
  const constructor = options.constructor

  return `

    NAN_METHOD(${options.name}::New) {
      if (!info.IsConstructCall()) {
        return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
      }

      cairo_font_face_t* data = NULL;

      if (info[0]->IsExternal()) {
        data = (cairo_font_face_t*) External::Cast (*info[0])->Value ();
      }${constructor ? `
      else if (info.Length() == ${constructor.parameters.length}) {
        ${constructor.parameters.map(getInArgumentSource).join('\n        ')}

        data = ${constructor.name} (${constructor.parameters.map(p => p.name).join(', ')});
      }
      else {
        return Nan::ThrowError("Cannot instantiate ${options.name}: requires ${constructor.parameters.length} arguments");
      }` : `
      else {
        return Nan::ThrowError("Cannot instantiate ${options.name}: use static creators");
      }`}

      ${options.name}* font_face = new ${options.name}(data);
      font_face->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }
  `
}

function getFunctionJSName(fn) {
  return getJSName(fn.name, /cairo_(([a-z0-9]+_)?font_face)?/)
}
