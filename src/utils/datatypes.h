#pragma once
#include <Arduino.h>
#include <Stamp.h>

#include "config.h"
#include "macro.h"
#include "color.h"
#include "flags.h"

enum GHdata_t {
    GH_NULL,

    GH_STR,
    GH_CSTR,

    GH_BOOL,
    GH_INT8,
    GH_UINT8,
    GH_INT16,
    GH_UINT16,
    GH_INT32,
    GH_UINT32,

    GH_FLOAT,
    GH_DOUBLE,

    GH_COLOR,
    GH_FLAGS,
    GH_STAMP,
};

void GHtypeToStr(String* s, void* val, GHdata_t type);
void GHtypeFromStr(const char* s, void* val, GHdata_t type);