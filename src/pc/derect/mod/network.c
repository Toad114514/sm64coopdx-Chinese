#include "./network.h"

#include "game/mario.h"
#include "game/level_update.h"
#include "pc/network/network_player.h"
#include "types.h"
#include "sm64.h"

#include "../module.h"
#include "../config.h"

// Player0HP
void player_hp_loop(void) {
    for (int i=0;i < MAX_PLAYERS;i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        struct MarioState* m = &gMarioStates[i];
        if (!m || !m->marioObj) continue;
        if (i == 0 || !np->connected) continue;
        
        m->health = 0x0000;
        m->invincTimer = 0;
    }
}

// fake client head
static char* game_name_ready = "sm64coopdx";
static bool if_pc = true; // 我将成为 PC
static bool if_android = false; // 我是拉完了安卓手机

static ConfigOption fch_option[] = {
    BIND_BOOL ("pc_head", "PC Client Header", &if_pc),
    BIND_BOOL ("android_head", "Android Client Header", &if_android),
};
#define FCH_CONF_COUNT (sizeof(fch_option) / sizeof(fch_option[0]))

char* fch_get_game_name (void) {
    return game_name_ready;
}

void fch_loop (void) {
    if (if_pc) {
        game_name_ready = "sm64coopdx";
    }
    else if (if_android) {
        game_name_ready = "sm64coop-android";
    }
}

void fch_configb(void) {
    Config_RenderOptions(fch_option, FCH_CONF_COUNT);
}

void module_network(void) {
    Module_Register("Player0HP",   CAT_WEB,  false,  NULL,  MOD_COLOR_RED, NULL, NULL, player_hp_loop);

    Module_Register("FakeClientHeader", CAT_WEB, false, NULL, MOD_COLOR_BLUE, NULL, NULL, fch_loop);
    Module_HookConfig("FakeClientHeader", fch_configb);
    Config_RegisterModuleOptions("FakeClientHeader", fch_option, FCH_CONF_COUNT);
}