// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Vayu - an experimental wlroots based wayland compositor.
 * Copyright (C) 2026  Shashwat Agrawal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <stdio.h>
#include <wlr/util/log.h>

#include "vayu/server.h"

int main() {
    int result = 0;
    wlr_log_init(WLR_DEBUG, NULL);
    printf("Vayu - an experimental wlroots based wayland compositor.\n");

    struct vayu_server server = {0};

    server.display = wl_display_create();
    if (!server.display) {
        wlr_log(WLR_ERROR, "failed to create wl_display");
        result = 1;
        goto cleanup;
    }

    server.backend =
        wlr_backend_autocreate(wl_display_get_event_loop(server.display), NULL);
    if (!server.backend) {
        wlr_log(WLR_ERROR, "failed to create wlr_backend");
        result = 1;
        goto cleanup;
    }

    server.renderer = wlr_renderer_autocreate(server.backend);
    if (!server.renderer) {
        wlr_log(WLR_ERROR, "failed to create wlr_renderer");
        result = 1;
        goto cleanup;
    }

    wlr_renderer_init_wl_display(server.renderer, server.display);

    server.allocator =
        wlr_allocator_autocreate(server.backend, server.renderer);
    if (!server.allocator) {
        wlr_log(WLR_ERROR, "failed to create wlr_allocator");
        result = 1;
        goto cleanup;
    }

    server.scene = wlr_scene_create();
    if (!server.scene) {
        wlr_log(WLR_ERROR, "failed to create wlr_scene");
        result = 1;
        goto cleanup;
    }

    if (!wlr_backend_start(server.backend)) {
        result = 1;
        goto cleanup;
    }

    // wl_display_run(server.display);

cleanup:
    wlr_scene_node_destroy(&server.scene->tree.node);
    wlr_allocator_destroy(server.allocator);
    wlr_renderer_destroy(server.renderer);
    wlr_backend_destroy(server.backend);
    wl_display_destroy_clients(server.display);
    wl_display_destroy(server.display);
    return result;
}
