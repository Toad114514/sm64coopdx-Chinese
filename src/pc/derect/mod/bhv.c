#include "../module.h"
#include "../config.h"

#include "bhv.h"

// gommba spawners
int goomba_spawner_count = 3;
int gs_mutiple = 30;

static ConfigOption s_gspawer_config[] = {
    BIND_INT("count", "Spawn Count", &goomba_spawner_count, 1, 50, "%d Goomba"),
    BIND_INT("mutiple", "Spawn Mutiple", &gs_mutiple, 1, 100, "%dx"),
};
#define GSPAWER_COUNT (sizeof(s_gspawer_config) / sizeof(s_gspawer_config[0]))

void gspawn_config(void) {
    Config_RenderOptions(s_gspawer_config, GSPAWER_COUNT);
}

int gspawn_get_count(void){
    return goomba_spawner_count*gs_mutiple;
}

void gspawn_disable(void) {
    goomba_spawner_count = 3;
}


// bobomb bomb timer
int bomb_time = 121;
static ConfigOption s_bomb_time[] = {
    BIND_INT("time", "Time", &bomb_time, 1, 500, "After %d to bomb")
};
#define BOBOME_COUNT (sizeof(s_bomb_time) / sizeof(s_bomb_time[0]))

void bob_config(void) {
    Config_RenderOptions(s_bomb_time, BOBOME_COUNT);
}

int bobomb_get_timer(void) {
    return bomb_time;
}

void bob_disable(void) {
    bomb_time = 121;
}

void module_bhv(void) {
    Module_Register("GoombaSpawners", CAT_BHV, false, NULL, MOD_COLOR_BLUE, NULL, gspawn_disable, NULL);
    Module_HookConfig("GoombaSpawners", gspawn_config);
    Config_RegisterModuleOptions("GoombaSpawners", s_gspawer_config, GSPAWER_COUNT);

    Module_Register("BobombTime", CAT_BHV, false, NULL, MOD_COLOR_BLUE, NULL, bob_disable, NULL);
    Module_HookConfig("BobombTime", bob_config);
    Config_RegisterModuleOptions("BobombTime", s_bomb_time, BOBOME_COUNT);
}