#include "core.h"
#include <PR/ultratypes.h>

#include "../module.h"
#include "../config.h"

#include "behavior_table.h"

///////////////////////////////////// RNG bhv control
// static u16 control_u16; //controls u16 define
// bool bhvrng_is_enable = false;

// u16 get_control_nums(u16 orig) {
//     if (bhvrng_is_enable) {
//         return control_u16;
//     } else {
//         return orig;
//     }
// }

bool s_oseed = false;
bool s_fseed = false;
u16 rngvalue;

static const ConfigOption s_bhvrng_options[] = {
    BIND_BOOL("rng_override", "RNG Override", &s_oseed),
    BIND_INT("rng_value", "RNG Value", &rngvalue, 0, 200000, "%d"),
    BIND_BOOL("rng_freeze", "RNG Freeze (beta)", &s_fseed),
};
#define BHVRNG_COUNT (sizeof(s_bhvrng_options) / sizeof(s_bhvrng_options[0]))

void bhvrng_config(void) {
    Config_RenderOptions(s_bhvrng_options, BHVRNG_COUNT);
}

void rng_loop(void) {
    g_override_seed_bool = s_oseed;
    g_override_seed = rngvalue;
    g_freeze_seed = s_fseed;
}

// void bhvrng_enable(void) {
//     bhvrng_is_enable = true;
// }

void rng_disable(void) {
    g_override_seed_bool = false;
    g_freeze_seed = false;
}

void module_core(void) {
    Module_Register("RNGControl", CAT_CORE, false, NULL, MOD_COLOR_BLUE, NULL, rng_disable, rng_loop);
    Module_HookConfig("RNGControl", bhvrng_config);
    Config_RegisterModuleOptions("RNGControl", s_bhvrng_options, BHVRNG_COUNT);
}