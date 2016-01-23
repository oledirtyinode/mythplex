# mythplex

Scripts to facility integrating MythTV recording into the Plex Media Server.

This is a branch of my BASH MythTV to Plex Media Server integration scripts that
are written in C. Mostly for the experience. The BASH scripts are to be considered
the recommended version for deployment. Consider anything in this branch to not
only be not recommended, but actively discouraged.

## Installation

This program requires GLib 2.0 or better. Also required is gcc (I think) and a
reasonably recent version of glibc.

1. Compile the program and place in a directory that is readable by the MythTV
   user.
2. In your MythTV setup, create a user job that points to the compiled program,
   with the command line arguments of "%CHANID%" "%STARTTIMEUTC%". It should
   look something like this:

   /path/to/program/postprocess "%CHANID%" "%STARTTIMEUTC%"

3. Test.
