#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/utils/smlua_misc_utils.h"

static char sInfo[512] = { 0 };

void djui_panel_info_create(struct DjuiBase *caller) {
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(INFORMATION, INFORMATION_TITLE), false);
    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        snprintf(sInfo, 512, "Welcome to using Derect Client!\nbytoadXtech64\nThanks Dear ImGUI/cimgui Library (both MIT Lisence)\n\n本客户端仅用于学习使用，禁止用于非法盈利、违法行为！\n请在24小时内删除本资源！\n此客户端完全遵守Minecraft EULA协议\n\n本客户端基于上善若、梅塔的长名字的汉化版本 1.0.1");

        struct DjuiText* text = djui_text_create(body, sInfo);
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 512);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
