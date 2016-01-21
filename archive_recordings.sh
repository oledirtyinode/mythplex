#!/bin/bash

# archive_recordings.sh
# (c) 2015-2016 Mike Todaro

# This script traverses the plex directories looking for flags telling it to keep DVR recordings beyond MythTV's autoexpire settings. The script services this requirement by identifying any associated symbolic links and copying the original file over them. The originals can then age out normally and be deleted without the loss of the recording.

# Find the .keep_flag flag files in directories, then locate all links in the directory and copy the original data over them.

find /mediasrv/plex -type f -iname .keep_flag -exec bash -c 'var={}; var=${var%/*}; for f in $(find $var -type l);do cp --remove-destination $(readlink $f) $f;done;' \; 2> /mediasrv/plex/logs/archive_recordings_`date +%Y%m%d`.log
