#!/bin/bash

# set_keep_flags.sh by Mike Todaro (c) 2015-2016, all rights reserved.

# To use, create as a job that looks like this: /path/to/script/set_keep_flags.sh "%CHANID%" "%STARTTIMEUTC%"

# The following values adjust the script parameters:


CONFIGXML="/home/mythtv/.mythtv/config.xml"

# Set this to where the pretty links should reside, making sure to include the trailing /.
PRETTYTVDIRNAME="/mediasrv/plex/tv/recorded/"
PRETTYMOVIEDIRNAME="/mediasrv/plex/movies/"

# Leave everything below this line alone unless you know what you're doing.
#
# Discover mysql username and password from mythtv config.xml. Alternatively you can manually enter them after the = sign.
DBUSER="$(awk -F '[<>]' '/UserName/{print $3}' $CONFIGXML)"
DBPASS="$(awk -F '[<>]' '/Password/{print $3}' $CONFIGXML)"

CHANID=$1 && STARTTIME=$2


# Populate recording information from sql database
TITLE=$(mysql mythconverg --user=$DBUSER --password=$DBPASS -se "SELECT title FROM recorded WHERE chanid=\"$CHANID\" AND starttime=\"$STARTTIME\";")
SEASON=$(mysql mythconverg --user=$DBUSER --password=$DBPASS -se "SELECT season FROM recorded WHERE chanid=\"$CHANID\" AND starttime=\"$STARTTIME\";")
TYPE=$(mysql mythconverg --user=$DBUSER --password=$DBPASS -se "SELECT category_type FROM recordedprogram WHERE chanid=\"$CHANID\" AND starttime=\"$STARTTIME\";")

if [ $TYPE = "movie" ];then
	TOUCHFILE="$PRETTYMOVIEDIRNAME$TITLE/.keep_flag"
elif [ $TYPE = "sports" ];then
	TOUCHFILE="$PRETTYTVDIRNAME$TITLE/.keep_flag"
else
	TOUCHFILE="$PRETTYTVDIRNAME$TITLE/.keep_flag"
fi

	touch "$TOUCHFILE"

