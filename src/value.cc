/*
 * Copyright (C) 2014 Endless Mobile
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by:
 *     Jasper St. Pierre <jstpierre@mecheye.net>
 */

#include "value.h"
#include "gobject.h"

namespace GNodeJS {

v8::Handle<v8::Value> GIArgumentToV8(GITypeInfo *type_info, GIArgument *arg) {
    GITypeTag type_tag = g_type_info_get_tag (type_info);

    switch (type_tag) {
    case GI_TYPE_TAG_VOID:
        return v8::Undefined ();

    case GI_TYPE_TAG_BOOLEAN:
        if (arg->v_boolean)
            return v8::True ();
        else
            return v8::False ();

    case GI_TYPE_TAG_INT32:
        return v8::Integer::New (arg->v_int);
    case GI_TYPE_TAG_UINT32:
        return v8::Integer::NewFromUnsigned (arg->v_uint);
    case GI_TYPE_TAG_INT16:
        return v8::Integer::New (arg->v_int16);
    case GI_TYPE_TAG_UINT16:
        return v8::Integer::NewFromUnsigned (arg->v_uint16);
    case GI_TYPE_TAG_INT8:
        return v8::Integer::New (arg->v_int8);
    case GI_TYPE_TAG_UINT8:
        return v8::Integer::NewFromUnsigned (arg->v_uint8);
    case GI_TYPE_TAG_FLOAT:
        return v8::Number::New (arg->v_float);
    case GI_TYPE_TAG_DOUBLE:
        return v8::Number::New (arg->v_double);

    /* For 64-bit integer types, use a float. When JS and V8 adopt
     * bigger sized integer types, start using those instead. */
    case GI_TYPE_TAG_INT64:
        return v8::Number::New (arg->v_int64);
    case GI_TYPE_TAG_UINT64:
        return v8::Number::New (arg->v_uint64);

    case GI_TYPE_TAG_UNICHAR:
        {
            char data[7];
            int size = g_unichar_to_utf8 (arg->v_uint32, data);
            return v8::String::New (data, size);
        }

    case GI_TYPE_TAG_UTF8:
        if (arg->v_pointer)
            return v8::String::New ((char *) arg->v_pointer);
        else
            return v8::Null ();

    case GI_TYPE_TAG_INTERFACE:
        {
            GIBaseInfo *interface_info = g_type_info_get_interface (type_info);
            GIInfoType interface_type = g_base_info_get_type (interface_info);

            switch (interface_type) {
            case GI_INFO_TYPE_OBJECT:
                return WrapperFromGObject ((GObject *) arg->v_pointer);
            default:
                g_assert_not_reached ();
            }
        }
        break;

    default:
        g_assert_not_reached ();
    }
}

static GArray * V8ToGArray(GITypeInfo *type_info, v8::Handle<v8::Value> value) {
    if (!value->IsArray ()) {
        ThrowException (v8::Exception::TypeError (v8::String::New ("Not an array.")));
        return NULL;
    }

    v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast (value->ToObject ());
    GITypeInfo *elem_info = g_type_info_get_param_type (type_info, 0);

    int length = array->Length ();
    GArray *garray = g_array_sized_new (TRUE, FALSE, sizeof (GIArgument), length);
    for (int i = 0; i < length; i++) {
        v8::Local<v8::Value> value = array->Get (i);
        GIArgument arg;

        V8ToGIArgument (elem_info, &arg, value, false);
        g_array_append_val (garray, arg);
    }

    g_base_info_unref ((GIBaseInfo *) elem_info);
    return garray;
}

void V8ToGIArgument(GITypeInfo *type_info, GIArgument *arg, v8::Handle<v8::Value> value, bool may_be_null) {
    GITypeTag type_tag = g_type_info_get_tag (type_info);

    if (value->IsNull ()) {
        if (may_be_null)
            arg->v_pointer = NULL;
        else
            ThrowException (v8::Exception::TypeError (v8::String::New ("Argument may not be null.")));

        return;
    }

    switch (type_tag) {
    case GI_TYPE_TAG_VOID:
        arg->v_pointer = NULL;
        break;
    case GI_TYPE_TAG_BOOLEAN:
        arg->v_boolean = value->BooleanValue ();
        break;
    case GI_TYPE_TAG_INT32:
        arg->v_int = value->Int32Value ();
        break;
    case GI_TYPE_TAG_UINT32:
        arg->v_uint = value->Uint32Value ();
        break;
    case GI_TYPE_TAG_INT64:
        arg->v_int64 = value->NumberValue ();
        break;
    case GI_TYPE_TAG_UINT64:
        arg->v_uint64 = value->NumberValue ();
        break;
    case GI_TYPE_TAG_FLOAT:
        arg->v_float = value->NumberValue ();
        break;
    case GI_TYPE_TAG_DOUBLE:
        arg->v_double = value->NumberValue ();
        break;

    case GI_TYPE_TAG_UTF8:
        {
            v8::String::Utf8Value str (value);
            const char *data = *str;
            arg->v_pointer = g_strdup (data);
        }
        break;

    case GI_TYPE_TAG_INTERFACE:
        {
            GIBaseInfo *interface_info = g_type_info_get_interface (type_info);
            GIInfoType interface_type = g_base_info_get_type (interface_info);

            switch (interface_type) {
            case GI_INFO_TYPE_OBJECT:
                arg->v_pointer = GObjectFromWrapper (value);
                break;
            default:
                g_assert_not_reached ();
            }

            g_base_info_unref (interface_info);
        }
        break;

    case GI_TYPE_TAG_ARRAY:
        {
            GIArrayType array_type = g_type_info_get_array_type (type_info);
            GArray *garray = V8ToGArray (type_info, value);

            switch (array_type) {
            case GI_ARRAY_TYPE_C:
                arg->v_pointer = g_array_free (garray, FALSE);
                break;
            case GI_ARRAY_TYPE_ARRAY:
                arg->v_pointer = garray;
                break;
            default:
                g_assert_not_reached ();
            }
        }
        break;

    default:
        g_assert_not_reached ();
    }
}

void FreeGIArgument(GITypeInfo *type_info, GIArgument *arg) {
    GITypeTag type_tag = g_type_info_get_tag (type_info);

    switch (type_tag) {
    case GI_TYPE_TAG_UTF8:
        g_free (arg->v_pointer);
        break;

    case GI_TYPE_TAG_ARRAY:
        {
            GIArrayType array_type = g_type_info_get_array_type (type_info);

            switch (array_type) {
            case GI_ARRAY_TYPE_C:
                g_free (arg->v_pointer);
                break;
            case GI_ARRAY_TYPE_ARRAY:
                g_array_free ((GArray *) arg->v_pointer, TRUE);
                break;
            default:
                g_assert_not_reached ();
            }
        }
        break;
    default:
        break;
    }
}

void V8ToGValue(GValue *gvalue, v8::Handle<v8::Value> value) {
    if (G_VALUE_HOLDS_BOOLEAN (gvalue)) {
        g_value_set_boolean (gvalue, value->BooleanValue ());
    } else if (G_VALUE_HOLDS_INT (gvalue)) {
        g_value_set_int (gvalue, value->Int32Value ());
    } else if (G_VALUE_HOLDS_UINT (gvalue)) {
        g_value_set_uint (gvalue, value->Uint32Value ());
    } else if (G_VALUE_HOLDS_FLOAT (gvalue)) {
        g_value_set_float (gvalue, value->NumberValue ());
    } else if (G_VALUE_HOLDS_DOUBLE (gvalue)) {
        g_value_set_double (gvalue, value->NumberValue ());
    } else if (G_VALUE_HOLDS_STRING (gvalue)) {
        v8::String::Utf8Value str (value);
        const char *data = *str;
        g_value_set_string (gvalue, data);
    } else {
        g_assert_not_reached ();
    }
}

};
