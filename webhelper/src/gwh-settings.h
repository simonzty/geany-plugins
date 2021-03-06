/*
 *  
 *  Copyright (C) 2010-2011  Colomban Wendling <ban@herbesfolles.org>
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 */

#ifndef H_GWH_SETTINGS
#define H_GWH_SETTINGS

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS


#define GWH_TYPE_SETTINGS        (gwh_settings_get_type ())
#define GWH_SETTINGS(o)          (G_TYPE_CHECK_INSTANCE_CAST ((o), GWH_TYPE_SETTINGS, GwhSettings))
#define GWH_SETTINGS_CLASS(ko)   (G_TYPE_CHECK_CLASS_CAST ((k), GWH_TYPE_SETTINGS, GwhSettingsClass))
#define GWH_IS_SETTINGS(b)       (G_TYPE_CHECK_INSTANCE_TYPE ((b), GWH_TYPE_SETTINGS))
#define GWH_IS_SETTINGS_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), GWH_TYPE_SETTINGS))


/**
 * GwhSettingsNotifyFlags:
 * @GWH_SETTINGS_NOTIFY_NONE: 0, no flags
 * @GWH_SETTINGS_NOTIFY_ON_CONNEXION: Call user callback just after widget
 *                                    creation.
 * 
 * Notification flags for gwh_settings_widget_new_full().
 */
typedef enum _GwhSettingsNotifyFlags
{
  GWH_SETTINGS_NOTIFY_NONE          = 0,
  GWH_SETTINGS_NOTIFY_ON_CONNEXION  = 1<<0
} GwhSettingsNotifyFlags;

typedef struct _GwhSettings         GwhSettings;
typedef struct _GwhSettingsClass    GwhSettingsClass;
typedef struct _GwhSettingsPrivate  GwhSettingsPrivate;
typedef void (*GwhSettingsWidgetBooleanNotify)  (GwhSettings *settings,
                                                 gboolean     value,
                                                 gpointer     data);
typedef void (*GwhSettingsWidgetEnumNotify)     (GwhSettings *settings,
                                                 gint         value,
                                                 gpointer     data);
typedef void (*GwhSettingsWidgetIntNotify)      (GwhSettings *settings,
                                                 gint         value,
                                                 gpointer     data);
typedef void (*GwhSettingsWidgetStringNotify)   (GwhSettings *settings,
                                                 const gchar *value,
                                                 gpointer     data);

struct _GwhSettings
{
  GObject parent;
  
  GwhSettingsPrivate *priv;
};

struct _GwhSettingsClass
{
  GObjectClass parent_class;
};


G_GNUC_INTERNAL
GType           gwh_settings_get_type                 (void) G_GNUC_CONST;
G_GNUC_INTERNAL
GwhSettings    *gwh_settings_get_default              (void);
G_GNUC_INTERNAL
void            gwh_settings_install_property         (GwhSettings *self,
                                                       GParamSpec  *pspec);
G_GNUC_INTERNAL
gboolean        gwh_settings_save_to_file             (GwhSettings *self,
                                                       const gchar *filename,
                                                       GError     **error);
G_GNUC_INTERNAL
gboolean        gwh_settings_load_from_file           (GwhSettings *self,
                                                       const gchar *filename,
                                                       GError     **error);
G_GNUC_INTERNAL
GtkWidget      *gwh_settings_widget_new_full          (GwhSettings           *self,
                                                       const gchar           *prop_name,
                                                       GCallback              setting_changed_callback,
                                                       gpointer               user_data,
                                                       GwhSettingsNotifyFlags notify_flags);
G_GNUC_INTERNAL
GtkWidget      *gwh_settings_widget_new               (GwhSettings *self,
                                                       const gchar *prop_name);
G_GNUC_INTERNAL
void            gwh_settings_widget_sync_v            (GwhSettings *self,
                                                       ...) G_GNUC_NULL_TERMINATED;
G_GNUC_INTERNAL
void            gwh_settings_widget_sync              (GwhSettings *self,
                                                       GtkWidget   *widget);



G_END_DECLS

#endif /* guard */
