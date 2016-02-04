/* postprocess.c
   (c) 2016 Mike Todaro, not for commercial use, all rights reserved
   No warranties or gurantees, express or implied, are given by the author.
   Use this software at your own risk! Any effect(s) it has on your systems
   or anything else are not my responsibility!


   postprocess.c is a replacement for my BASH script that takes MythTV
   recordings and cleans them up and presents them to Plex for later
   viewing.
*/

#include <stdlib.h>
#include <stdio.h>
#include <glib/glib.h>
#include <string.h>
#include <unistd.h> /* for execlp */
#include <mysql.h> /* for talking to the MythTV DB */

struct show_info {
  char title[];
  char subtitle[];
  char date[];
  char filename[];
  char storagegroup[];
  char dirname[];
  int season;
  int episode;
  char type[];
  char airdate[];
}

GHashTable GetConfig(char *file[]);

int GetShowInfo(GHashTable hashtable, MYSQL conn, struct show_info info);

int main(int argc, char *argv[])
{
   /* command line variables */
   char[] chanid = argv[1];
   char[] starttime = argv[2];

   struct show_info recorded_show;
   struct *showptr = &recorded_show;

   GError error;

   /* config file */
   GKeyFile *config_file; = g_key_file_new();

   /* configuration dictionary */
   GHashTable* config = g_hash_table_new(g_str_hash, g_str_equal);

   config = GetConfig("./postprocess.conf");

  /* Connect to MythTV DB and retrieve show information. */
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;

  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, config["DBSERVER"], config["DBUSER"], config["DBPASS"], config["DATABASE"], 0, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  /* Run mythcommflag */

  /* Cut the commercials */

  /* run ffmpeg */

  /* Create symlink in the PMS directory */

   return 0;
}

GHashTable GetConfig(char *file[])
{

  GHashTable table = g_hash_table_new(g_str_hash, g_str_equal);

  if (!(g_key_file_load_from_file(config_file, file, G_KEY_FILE_NONE, error)))
  {
    fprintf(stderr, "Cannot load config file! Exiting.", __FILE__);
    exit(1);
  }

  char groups[][] = g_key_file_get_groups(config_files, NULL);

  for (int lcv = 0; lcv < sizeof(groups); lcv++)
  {
    /* Get the list of keys. */
    char keys[][] = g_key_file_get_keys(config_file, groups[lcv], NULL, error);

    /* Insert config file values into our config hash table. */
    for (int k = 0; k < sizeof(keys); k++)
    {
      g_hash_table_insert(table, keys[k], g_key_file_get_string(config_file, groups[lcv], keys[k], error));
    }
  }

  g_key_file_free(config_file); /* Release the keyfile and move on. */

  return table;
}

int GetShowInfo(GHashTable hashtable, MYSQL dbconn, struct show_info info)
{
  struct show_info show;

  return show;
}
