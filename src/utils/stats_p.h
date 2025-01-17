#pragma once
#include <Arduino.h>
#include "config.h"
#include "macro.h"
#include "stats.h"
#include "action.h"
#include "build.h"

// получить текстовое значение типа GHstate_t для вывода в порт
FSTR GHreadState(GHstate_t n);

// получить текстовое значение типа GHconn_t для вывода в порт
FSTR GHreadConn(GHconn_t n);

// получить текстовое значение типа GHaction_t для вывода в порт
FSTR GHreadAction(GHaction_t n);

// получить текстовое значение типа GHbuild_t для вывода в порт
FSTR GHreadBuild(GHbuild_t n);