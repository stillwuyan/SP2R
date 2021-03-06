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
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_SDL_VIDEO_SINK_H_
#define _GST_SDL_VIDEO_SINK_H_

#include <gst/video/video.h>
#include <gst/video/gstvideosink.h>

G_BEGIN_DECLS

#define GST_TYPE_SDL_VIDEO_SINK   (gst_sdl_video_sink_get_type())
#define GST_SDL_VIDEO_SINK(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_SDL_VIDEO_SINK,GstSdlVideoSink))
#define GST_SDL_VIDEO_SINK_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_SDL_VIDEO_SINK,GstSdlVideoSinkClass))
#define GST_IS_SDL_VIDEO_SINK(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SDL_VIDEO_SINK))
#define GST_IS_SDL_VIDEO_SINK_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SDL_VIDEO_SINK))

typedef struct _GstSdlVideoSink GstSdlVideoSink;
typedef struct _GstSdlVideoSinkClass GstSdlVideoSinkClass;

struct _GstSdlVideoSink
{
  GstVideoSink base_sdlvideosink;
  int dlevel;
};

struct _GstSdlVideoSinkClass
{
  GstVideoSinkClass base_sdlvideosink_class;
};

GType gst_sdl_video_sink_get_type (void);

G_END_DECLS

#endif
