/* GStreamer
 * Copyright (C) 2016 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-gstsdlvideosink
 *
 * The sdlvideosink element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! sdlvideosink ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideosink.h>
#include "gstsdlvideosink.h"

#include <SDL.h>
#include <SDL_thread.h>
SDL_Window* g_screen = 0;
SDL_Renderer* g_renderer = 0;
SDL_Texture* g_texture = 0;

GST_DEBUG_CATEGORY_STATIC (gst_sdl_video_sink_debug_category);
#define GST_CAT_DEFAULT gst_sdl_video_sink_debug_category

/* prototypes */


static void gst_sdl_video_sink_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_sdl_video_sink_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_sdl_video_sink_dispose (GObject * object);
static void gst_sdl_video_sink_finalize (GObject * object);

static GstFlowReturn gst_sdl_video_sink_show_frame (GstVideoSink * video_sink,
    GstBuffer * buf);

enum
{
  PROP_0
};

/* pad templates */

/* FIXME: add/remove formats you can handle */
#define VIDEO_SINK_CAPS \
    GST_VIDEO_CAPS_MAKE("{ I420, Y444, Y42B, UYVY, RGBA }")


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstSdlVideoSink, gst_sdl_video_sink, GST_TYPE_VIDEO_SINK,
  GST_DEBUG_CATEGORY_INIT (gst_sdl_video_sink_debug_category, "sdlvideosink", 0,
  "debug category for sdlvideosink element"));

static void
gst_sdl_video_sink_class_init (GstSdlVideoSinkClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstVideoSinkClass *video_sink_class = GST_VIDEO_SINK_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_pad_template_new ("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
        gst_caps_from_string (VIDEO_SINK_CAPS)));

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_sdl_video_sink_set_property;
  gobject_class->get_property = gst_sdl_video_sink_get_property;
  gobject_class->dispose = gst_sdl_video_sink_dispose;
  gobject_class->finalize = gst_sdl_video_sink_finalize;
  video_sink_class->show_frame = GST_DEBUG_FUNCPTR (gst_sdl_video_sink_show_frame);

}

static void
gst_sdl_video_sink_init (GstSdlVideoSink *sdlvideosink)
{

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }

    g_screen = SDL_CreateWindow("SDL Overlay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_RESIZABLE);
    if (!g_screen) {
        fprintf(stderr, "Could not create window -exiting\n");
        exit(1);
    }

    g_renderer = SDL_CreateRenderer(g_screen, -1, SDL_RENDERER_SOFTWARE);
    //g_renderer = SDL_CreateRenderer(g_screen, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        fprintf(stderr, "Could not create renderer - exiting\n");
        exit(1);
    }

    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, 1920, 1080);
    if (!g_texture) {
        fprintf(stderr, "Could not create texture - exiting\n");
        exit(1);
    }
}

void
gst_sdl_video_sink_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstSdlVideoSink *sdlvideosink = GST_SDL_VIDEO_SINK (object);

  GST_DEBUG_OBJECT (sdlvideosink, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_sdl_video_sink_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstSdlVideoSink *sdlvideosink = GST_SDL_VIDEO_SINK (object);

  GST_DEBUG_OBJECT (sdlvideosink, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_sdl_video_sink_dispose (GObject * object)
{
  GstSdlVideoSink *sdlvideosink = GST_SDL_VIDEO_SINK (object);

  GST_DEBUG_OBJECT (sdlvideosink, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_sdl_video_sink_parent_class)->dispose (object);
}

void
gst_sdl_video_sink_finalize (GObject * object)
{
  GstSdlVideoSink *sdlvideosink = GST_SDL_VIDEO_SINK (object);

  GST_DEBUG_OBJECT (sdlvideosink, "finalize");

  /* clean up object here */
    SDL_DestroyTexture(g_texture);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_screen);
    SDL_Quit();

  G_OBJECT_CLASS (gst_sdl_video_sink_parent_class)->finalize (object);
}

static GstFlowReturn
gst_sdl_video_sink_show_frame (GstVideoSink * sink, GstBuffer * buf)
{
  GstMapInfo map;
  if (gst_buffer_map(buf, &map, GST_MAP_READ)) {
    Uint8* yPlane = map.data;
    Uint8* uPlane = yPlane + (1920 * 1080);
    Uint8* vPlane = uPlane + (1920 * 1080 / 4);
    SDL_UpdateYUVTexture(g_texture, NULL, yPlane, 1920, uPlane, 960, vPlane, 960);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);
    gst_buffer_unmap(buf, &map);
  }
  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "sdlvideosink", GST_RANK_NONE,
      GST_TYPE_SDL_VIDEO_SINK);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.0.FIXME"
#endif
#ifndef PACKAGE
#define PACKAGE "FIXME_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "FIXME_package_name"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    sdlvideosink,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)

