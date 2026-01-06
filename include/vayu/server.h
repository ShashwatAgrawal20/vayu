// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2026 Shashwat Agrawal

#ifndef SERVER_H
#define SERVER_H

#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/render/allocator.h>
#include <wlr/types/wlr_scene.h>

struct vayu_server {
    struct wl_display *display;
    struct wlr_backend *backend;
    struct wlr_renderer *renderer;
    struct wlr_allocator *allocator;
    struct wlr_scene *scene;

    struct wl_listener new_output;
};

#endif // !SERVER_H
