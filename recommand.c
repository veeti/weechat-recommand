/*
 * weechat-recommand
 * Copyright (C) 2014 Veeti Paananen <veeti.paananen@rojekti.fi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <weechat/weechat-plugin.h>

WEECHAT_PLUGIN_NAME("recommand");
WEECHAT_PLUGIN_DESCRIPTION("Resend the automatic command(s) for the current buffer's server");
WEECHAT_PLUGIN_AUTHOR("Veeti Paananen <veeti.paananen@rojekti.fi>");
WEECHAT_PLUGIN_VERSION("1.0-pre")
WEECHAT_PLUGIN_LICENSE("GPL3")

struct t_weechat_plugin *weechat_plugin = NULL;

int command_recommand(void *data, struct t_gui_buffer *buffer, int argc, char *argv[], char *argv_eol[]) {
    char *server = weechat_buffer_get_string(buffer, "localvar_server");
    if (server == NULL) {
        weechat_printf(buffer, "Not a server buffer.");
    } else {
        // format config key
        size_t length = strlen("irc.server..command") + strlen(server) + 1;
        char config[length];
        snprintf(config, length, "irc.server.%s.command", server);

        // get command
        struct t_config_option *option = weechat_config_get(config);
        const char *cmd;
        if (option != NULL && (cmd = weechat_config_string(option)) != NULL) {
            // execute
            weechat_command(buffer, cmd);
        } else {
            weechat_printf(buffer, "There is no command for the server %s.", server);
        }
    }

    return WEECHAT_RC_OK;
}

int weechat_plugin_init(struct t_weechat_plugin *plugin, int argc, char *argv[]) {
    weechat_plugin = plugin;

    weechat_hook_command("recommand", "Resend the automatic command(s) for the current buffer's server", "", "", "", &command_recommand, NULL);

    return WEECHAT_RC_OK;
}

int weechat_plugin_end(struct t_weechat_plugin *plugin) {
    weechat_plugin = NULL;
    return WEECHAT_RC_OK;
}

