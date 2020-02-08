/* Copyright (c) 1997-2004 Miller Puckette.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

/*
 * this file implements a mechanism for storing and retrieving preferences.
 * Should later be renamed "preferences.c" or something.
 *
 * In unix this is handled by the "~/.pd_ceammc_settings" file, in windows by
 * the registry, and in MacOS by the Preferences system.
 */

#include "m_pd.h"
#include "s_stuff.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <io.h>
#endif
#ifdef _MSC_VER  /* This is only for Microsoft's compiler, not cygwin, e.g. */
#define snprintf _snprintf
#endif

void sys_doflags(void);

static PERTHREAD char *sys_prefbuf;
static PERTHREAD int sys_prefbufsize;
static PERTHREAD FILE *sys_prefsavefp;

#define UNIX_CONFIG_FILENAME ".pd_ceammc_settings"
static const char* WIN_CONFIG_REGNAME = "Software\\Pd-ceammc";
static const char* WIN_CONFIG_KEYNAME = "Pd-ceammc";
static const char* MACOSX_CONFIG_NAME = "com.ceammc.pd";

static void sys_initloadpreferences_file(const char *filename)
{
    int fd;
    long length;
    if ((fd = open(filename, 0)) < 0)
    {
        if (sys_verbose)
            perror(filename);
        return;
    }
    length = lseek(fd, 0, 2);
    if (length < 0)
    {
        if (sys_verbose)
            perror(filename);
        close(fd);
        return;
    }
    lseek(fd, 0, 0);
    if (!(sys_prefbuf = malloc(length + 2)))
    {
        error("couldn't allocate memory for preferences buffer");
        close(fd);
        return;
    }
    sys_prefbuf[0] = '\n';
    if (read(fd, sys_prefbuf+1, length) < length)
    {
        perror(filename);
        sys_prefbuf[0] = 0;
        close(fd);
        return;
    }
    sys_prefbuf[length+1] = 0;
    close(fd);
    if (sys_verbose)
        post("success reading preferences from: %s", filename);
}

static int sys_getpreference_file(const char *key, char *value, int size)
{
    char searchfor[80], *where, *whereend;
    if (!sys_prefbuf)
        return (0);
    sprintf(searchfor, "\n%s:", key);
    where = strstr(sys_prefbuf, searchfor);
    if (!where)
        return (0);
    where += strlen(searchfor);
    while (*where == ' ' || *where == '\t')
        where++;
    for (whereend = where; *whereend && *whereend != '\n'; whereend++)
        ;
    if (*whereend == '\n')
        whereend--;
    if (whereend > where + size - 1)
        whereend = where + size - 1;
    strncpy(value, where, whereend+1-where);
    value[whereend+1-where] = 0;
    return (1);
}

static void sys_doneloadpreferences_file(void)
{
    if (sys_prefbuf)
        free(sys_prefbuf);
}

static void sys_initsavepreferences_file(const char *filename)
{
    if ((sys_prefsavefp = fopen(filename, "w")) == NULL)
        pd_error(0, "%s: %s", filename, strerror(errno));
}

static void sys_putpreference_file(const char *key, const char *value)
{
    if (sys_prefsavefp)
        fprintf(sys_prefsavefp, "%s: %s\n",
            key, value);
}

static void sys_donesavepreferences_file(void)
{
    if (sys_prefsavefp)
    {
        fclose(sys_prefsavefp);
        sys_prefsavefp = 0;
    }
}


/*****  linux/android/BSD etc: read and write to ~/.pd_ceammc_settings file ******/
#if !defined(_WIN32) && !defined(__APPLE__)

static void sys_initloadpreferences(void)
{
    char filenamebuf[MAXPDSTRING], *homedir = getenv("HOME");
    int fd, length;
    char user_prefs_file[MAXPDSTRING]; /* user prefs file */
        /* default prefs embedded in the package */
    char default_prefs_file[MAXPDSTRING];
    struct stat statbuf;

    snprintf(default_prefs_file, MAXPDSTRING, "%s/default.pdsettings",
        sys_libdir->s_name);
    snprintf(user_prefs_file, MAXPDSTRING, "%s/%s",
        (homedir ? homedir : "."), UNIX_CONFIG_FILENAME);
    if (stat(user_prefs_file, &statbuf) == 0)
        strncpy(filenamebuf, user_prefs_file, MAXPDSTRING);
    else if (stat(default_prefs_file, &statbuf) == 0)
        strncpy(filenamebuf, default_prefs_file, MAXPDSTRING);
    else return;
    filenamebuf[MAXPDSTRING-1] = 0;
    sys_initloadpreferences_file(filenamebuf);
}

static int sys_getpreference(const char *key, char *value, int size)
{
    return (sys_getpreference_file(key, value, size));
}

static void sys_doneloadpreferences(void)
{
    sys_doneloadpreferences_file();
}

static void sys_initsavepreferences(void)
{
    char filenamebuf[MAXPDSTRING],
        *homedir = getenv("HOME");
    FILE *fp;

    if (!homedir)
        return;
    snprintf(filenamebuf, MAXPDSTRING, "%s/%s", homedir, UNIX_CONFIG_FILENAME);
    filenamebuf[MAXPDSTRING-1] = 0;
    sys_initsavepreferences_file(filenamebuf);
}

static void sys_putpreference(const char *key, const char *value)
{
    sys_putpreference_file(key, value);
}

static void sys_donesavepreferences(void)
{
    sys_donesavepreferences_file();
}

#else  /* !defined(_WIN32) && !defined(__APPLE__) */

static void sys_initloadpreferences(void)
{
    if (sys_prefbuf)
        bug("sys_initloadpreferences");
}
static void sys_doneloadpreferences( void)
{
    if (sys_prefbuf)
        sys_doneloadpreferences_file();
}
static void sys_initsavepreferences( void)
{
    if (sys_prefsavefp)
        bug("sys_initsavepreferences");
}
static void sys_donesavepreferences( void)
{
    if (sys_prefsavefp)
        sys_donesavepreferences_file();
}

static int sys_getpreference(const char *key, char *value, int size)
{
    if (sys_prefbuf)
        return (sys_getpreference_file(key, value, size));
    else
    {
#ifdef _WIN32
        HKEY hkey;
        DWORD bigsize = size;
        LONG err = RegOpenKeyEx(HKEY_CURRENT_USER,
            WIN_CONFIG_REGNAME, 0,  KEY_QUERY_VALUE, &hkey);
        if (err != ERROR_SUCCESS)
            return (0);
        err = RegQueryValueEx(hkey, key, 0, 0, value, &bigsize);
        if (err != ERROR_SUCCESS)
        {
            RegCloseKey(hkey);
            return (0);
        }
        RegCloseKey(hkey);
        return (1);
#endif /* _WIN32 */
#ifdef __APPLE__
        char cmdbuf[256];
        int nread = 0, nleft = size;
        char embedded_prefs[MAXPDSTRING];
        char user_prefs[MAXPDSTRING];
        char *homedir = getenv("HOME");
        struct stat statbuf;
       /* the 'defaults' command expects the filename without .plist at the
            end */
        snprintf(embedded_prefs, MAXPDSTRING, "%s/../%s",
            sys_libdir->s_name, MACOSX_CONFIG_NAME);
        snprintf(user_prefs, MAXPDSTRING,
            "%s/Library/Preferences/%s.plist", homedir, MACOSX_CONFIG_NAME);
        if (stat(user_prefs, &statbuf) == 0)
            snprintf(cmdbuf, 256, "defaults read %s %s 2> /dev/null\n",
                MACOSX_CONFIG_NAME, key);
        else snprintf(cmdbuf, 256, "defaults read %s %s 2> /dev/null\n",
                embedded_prefs, key);
        FILE *fp = popen(cmdbuf, "r");
        while (nread < size)
        {
            int newread = fread(value+nread, 1, size-nread, fp);
            if (newread <= 0)
                break;
            nread += newread;
        }
        pclose(fp);
        if (nread < 1)
            return (0);
        if (nread >= size)
            nread = size-1;
        value[nread] = 0;
        if (value[nread-1] == '\n')     /* remove newline character at end */
            value[nread-1] = 0;
        return(1);
#endif /* __APPLE__ */
    }
}

static void sys_putpreference(const char *key, const char *value)
{
    if (sys_prefsavefp)
        sys_putpreference_file(key, value);
    else
    {
#ifdef _WIN32
        HKEY hkey;
        LONG err = RegCreateKeyEx(HKEY_CURRENT_USER,
            WIN_CONFIG_REGNAME, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE,
            NULL, &hkey, NULL);
        if (err != ERROR_SUCCESS)
        {
            error("unable to create registry entry: %s\n", key);
            return;
        }
        err = RegSetValueEx(hkey, key, 0, REG_EXPAND_SZ, value, strlen(value)+1);
        if (err != ERROR_SUCCESS)
            error("unable to set registry entry: %s\n", key);
        RegCloseKey(hkey);
#endif /* _WIN32 */
#ifdef __APPLE__
        char cmdbuf[MAXPDSTRING];
        snprintf(cmdbuf, MAXPDSTRING,
            "defaults write %s %s \"%s\" 2> /dev/null\n", MACOSX_CONFIG_NAME, key, value);
        system(cmdbuf);
#endif /* __APPLE__ */
    }
}
#endif  /* !defined(_WIN32) && !defined(__APPLE__) */

void sys_loadpreferences(const char *filename, int startingup)
{
    int naudioindev, audioindev[MAXAUDIOINDEV], chindev[MAXAUDIOINDEV];
    int naudiooutdev, audiooutdev[MAXAUDIOOUTDEV], choutdev[MAXAUDIOOUTDEV];
    int nmidiindev, midiindev[MAXMIDIINDEV];
    int nmidioutdev, midioutdev[MAXMIDIOUTDEV];
    int i, rate = 0, advance = -1, callback = 0, blocksize = 0,
        api, midiapi, nolib, maxi;
    char prefbuf[MAXPDSTRING], keybuf[80];

    if (*filename)
        sys_initloadpreferences_file(filename);
    else sys_initloadpreferences();
        /* load audio preferences */
    if (!sys_externalschedlib
        && sys_getpreference("audioapi", prefbuf, MAXPDSTRING)
        && sscanf(prefbuf, "%d", &api) > 0)
            sys_set_audio_api(api);
            /* JMZ/MB: brackets for initializing */
    if (sys_getpreference("noaudioin", prefbuf, MAXPDSTRING) &&
        (!strcmp(prefbuf, ".") || !strcmp(prefbuf, "True")))
            naudioindev = 0;
    else
    {
        for (i = 0, naudioindev = 0; i < MAXAUDIOINDEV; i++)
        {
                /* first try to find a name - if that matches an existing
                device use it.  Otherwise fall back to device number. */
            int devn;
                /* read in device number and channel count */
            sprintf(keybuf, "audioindev%d", i+1);
            if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
                break;
            if (sscanf(prefbuf, "%d %d", &audioindev[i], &chindev[i]) < 2)
                break;
                /* possibly override device number if the device name was
                also saved and if it matches one we have now */
            sprintf(keybuf, "audioindevname%d", i+1);
            if (sys_getpreference(keybuf, prefbuf, MAXPDSTRING)
                && (devn = sys_audiodevnametonumber(0, prefbuf)) >= 0)
                    audioindev[i] = devn;
            naudioindev++;
        }
            /* if no preferences at all, set -1 for default behavior */
        if (naudioindev == 0)
            naudioindev = -1;
    }
        /* JMZ/MB: brackets for initializing */
    if (sys_getpreference("noaudioout", prefbuf, MAXPDSTRING) &&
        (!strcmp(prefbuf, ".") || !strcmp(prefbuf, "True")))
            naudiooutdev = 0;
    else
    {
        for (i = 0, naudiooutdev = 0; i < MAXAUDIOOUTDEV; i++)
        {
            int devn;
            sprintf(keybuf, "audiooutdev%d", i+1);
            if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
                break;
            if (sscanf(prefbuf, "%d %d", &audiooutdev[i], &choutdev[i]) < 2)
                break;
            sprintf(keybuf, "audiooutdevname%d", i+1);
            if (sys_getpreference(keybuf, prefbuf, MAXPDSTRING)
                && (devn = sys_audiodevnametonumber(1, prefbuf)) >= 0)
                    audiooutdev[i] = devn;
            naudiooutdev++;
        }
        if (naudiooutdev == 0)
            naudiooutdev = -1;
    }
    if (sys_getpreference("rate", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &rate);
    if (sys_getpreference("audiobuf", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &advance);
    if (sys_getpreference("callback", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &callback);
    if (sys_getpreference("blocksize", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &blocksize);
    sys_set_audio_settings(naudioindev, audioindev, naudioindev, chindev,
        naudiooutdev, audiooutdev, naudiooutdev, choutdev, rate, advance,
        callback, blocksize);

        /* load MIDI preferences */
    if (sys_getpreference("midiapi", prefbuf, MAXPDSTRING)
        && sscanf(prefbuf, "%d", &midiapi) > 0)
            sys_set_midi_api(midiapi);
        /* JMZ/MB: brackets for initializing */
    if (sys_getpreference("nomidiin", prefbuf, MAXPDSTRING) &&
        (!strcmp(prefbuf, ".") || !strcmp(prefbuf, "True")))
            nmidiindev = 0;
    else for (i = 0, nmidiindev = 0; i < MAXMIDIINDEV; i++)
    {
            /* first try to find a name - if that matches an existing device
            use it.  Otherwise fall back to device number. */
        int devn;
        sprintf(keybuf, "midiindevname%d", i+1);
        if (sys_getpreference(keybuf, prefbuf, MAXPDSTRING)
            && (devn = sys_mididevnametonumber(0, prefbuf)) >= 0)
                midiindev[i] = devn;
        else
        {
            sprintf(keybuf, "midiindev%d", i+1);
            if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
                break;
            if (sscanf(prefbuf, "%d", &midiindev[i]) < 1)
                break;
        }
        nmidiindev++;
    }
        /* JMZ/MB: brackets for initializing */
    if (sys_getpreference("nomidiout", prefbuf, MAXPDSTRING) &&
        (!strcmp(prefbuf, ".") || !strcmp(prefbuf, "True")))
            nmidioutdev = 0;
    else for (i = 0, nmidioutdev = 0; i < MAXMIDIOUTDEV; i++)
    {
        int devn;
        sprintf(keybuf, "midioutdevname%d", i+1);
        if (sys_getpreference(keybuf, prefbuf, MAXPDSTRING)
            && (devn = sys_mididevnametonumber(1, prefbuf)) >= 0)
                midioutdev[i] = devn;
        else
        {
            sprintf(keybuf, "midioutdev%d", i+1);
            if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
                break;
            if (sscanf(prefbuf, "%d", &midioutdev[i]) < 1)
                break;
        }
        nmidioutdev++;
    }
    sys_open_midi(nmidiindev, midiindev, nmidioutdev, midioutdev, 0);

        /* search path */
    if (sys_getpreference("npath", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &maxi);
    else maxi = 0x7fffffff;
    for (i = 0; i<maxi; i++)
    {
        sprintf(keybuf, "path%d", i+1);
        if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
            break;
        STUFF->st_searchpath =
            namelist_append_files(STUFF->st_searchpath, prefbuf);
    }
    if (sys_getpreference("standardpath", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &sys_usestdpath);
    if (sys_getpreference("verbose", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &sys_verbose);

        /* startup settings */
    if (sys_getpreference("nloadlib", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &maxi);
    else maxi = 0x7fffffff;
    for (i = 0; i<maxi; i++)
    {
        sprintf(keybuf, "loadlib%d", i+1);
        if (!sys_getpreference(keybuf, prefbuf, MAXPDSTRING))
            break;
        STUFF->st_externlist = namelist_append_files(STUFF->st_externlist, prefbuf);
    }
    if (sys_getpreference("defeatrt", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &sys_defeatrt);
    if (sys_getpreference("flags", prefbuf, MAXPDSTRING) &&
        strcmp(prefbuf, "."))
    {
        sys_flags = gensym(prefbuf);
        if (startingup)
            sys_doflags();
    }
    if (sys_defeatrt)
        sys_hipriority = 0;
    else
#if defined(__linux__) || defined(__CYGWIN__)
        sys_hipriority = 1;
#else
#if defined(_WIN32) || defined(ANDROID)
        sys_hipriority = 0;
#else
        sys_hipriority = 1;
#endif
#endif
    if (sys_getpreference("zoom", prefbuf, MAXPDSTRING))
        sscanf(prefbuf, "%d", &sys_zoom_open);

    sys_doneloadpreferences();
}

void sys_savepreferences(const char *filename)
{
    int naudioindev, audioindev[MAXAUDIOINDEV], chindev[MAXAUDIOINDEV];
    int naudiooutdev, audiooutdev[MAXAUDIOOUTDEV], choutdev[MAXAUDIOOUTDEV];
    int i, rate, advance, callback, blocksize;
    char buf1[MAXPDSTRING], buf2[MAXPDSTRING];
    int nmidiindev, midiindev[MAXMIDIINDEV];
    int nmidioutdev, midioutdev[MAXMIDIOUTDEV];

    if (filename && *filename)
        sys_initsavepreferences_file(filename);
    else sys_initsavepreferences();
        /* audio settings */
    sprintf(buf1, "%d", sys_audioapi);
    sys_putpreference("audioapi", buf1);

    sys_get_audio_params(&naudioindev, audioindev, chindev,
        &naudiooutdev, audiooutdev, choutdev, &rate, &advance, &callback,
            &blocksize);

    sys_putpreference("noaudioin", (naudioindev <= 0 ? "True" : "False"));
    for (i = 0; i < naudioindev; i++)
    {
        sprintf(buf1, "audioindev%d", i+1);
        sprintf(buf2, "%d %d", audioindev[i], chindev[i]);
        sys_putpreference(buf1, buf2);
        sprintf(buf1, "audioindevname%d", i+1);
        sys_audiodevnumbertoname(0, audioindev[i], buf2, MAXPDSTRING);
        if (! *buf2)
            strcat(buf2, "?");
        sys_putpreference(buf1, buf2);
    }
    sys_putpreference("noaudioout", (naudiooutdev <= 0 ? "True" : "False"));
    for (i = 0; i < naudiooutdev; i++)
    {
        sprintf(buf1, "audiooutdev%d", i+1);
        sprintf(buf2, "%d %d", audiooutdev[i], choutdev[i]);
        sys_putpreference(buf1, buf2);
        sprintf(buf1, "audiooutdevname%d", i+1);
        sys_audiodevnumbertoname(1, audiooutdev[i], buf2, MAXPDSTRING);
        if (! *buf2)
            strcat(buf2, "?");
        sys_putpreference(buf1, buf2);
   }

    sprintf(buf1, "%d", advance);
    sys_putpreference("audiobuf", buf1);

    sprintf(buf1, "%d", rate);
    sys_putpreference("rate", buf1);

    sprintf(buf1, "%d", callback);
    sys_putpreference("callback", buf1);

    sprintf(buf1, "%d", blocksize);
    sys_putpreference("blocksize", buf1);

        /* MIDI settings */
    sprintf(buf1, "%d", sys_midiapi);
    sys_putpreference("midiapi", buf1);

    sys_get_midi_params(&nmidiindev, midiindev, &nmidioutdev, midioutdev);
    sys_putpreference("nomidiin", (nmidiindev <= 0 ? "True" : "False"));
    for (i = 0; i < nmidiindev; i++)
    {
        sprintf(buf1, "midiindev%d", i+1);
        sprintf(buf2, "%d", midiindev[i]);
        sys_putpreference(buf1, buf2);
        sprintf(buf1, "midiindevname%d", i+1);
        sys_mididevnumbertoname(0, midiindev[i], buf2, MAXPDSTRING);
        if (! *buf2)
            strcat(buf2, "?");
        sys_putpreference(buf1, buf2);
    }
    sys_putpreference("nomidiout", (nmidioutdev <= 0 ? "True" : "False"));
    for (i = 0; i < nmidioutdev; i++)
    {
        sprintf(buf1, "midioutdev%d", i+1);
        sprintf(buf2, "%d", midioutdev[i]);
        sys_putpreference(buf1, buf2);
        sprintf(buf1, "midioutdevname%d", i+1);
        sys_mididevnumbertoname(1, midioutdev[i], buf2, MAXPDSTRING);
        if (! *buf2)
            strcat(buf2, "?");
        sys_putpreference(buf1, buf2);
    }
        /* file search path */

    for (i = 0; 1; i++)
    {
        const char *pathelem = namelist_get(STUFF->st_searchpath, i);
        if (!pathelem)
            break;
        sprintf(buf1, "path%d", i+1);
        sys_putpreference(buf1, pathelem);
    }
    sprintf(buf1, "%d", i);
    sys_putpreference("npath", buf1);
    sprintf(buf1, "%d", sys_usestdpath);
    sys_putpreference("standardpath", buf1);
    sprintf(buf1, "%d", sys_verbose);
    sys_putpreference("verbose", buf1);

        /* startup */
    for (i = 0; 1; i++)
    {
        const char *pathelem = namelist_get(STUFF->st_externlist, i);
        if (!pathelem)
            break;
        sprintf(buf1, "loadlib%d", i+1);
        sys_putpreference(buf1, pathelem);
    }
    sprintf(buf1, "%d", i);
    sys_putpreference("nloadlib", buf1);
    sprintf(buf1, "%d", sys_defeatrt);
    sys_putpreference("defeatrt", buf1);
    sys_putpreference("flags",
        (sys_flags ? sys_flags->s_name : ""));
        /* misc */
    sprintf(buf1, "%d", sys_zoom_open);
    sys_putpreference("zoom", buf1);
    sys_putpreference("loading", "no");

    sys_donesavepreferences();
}

    /* calls from GUI to load/save from/to a file */
void glob_loadpreferences(t_pd *dummy, t_symbol *filesym)
{
    sys_loadpreferences(filesym->s_name, 0);
    sys_close_audio();
    sys_reopen_audio();
    sys_close_midi();
    sys_reopen_midi();
}

void glob_savepreferences(t_pd *dummy, t_symbol *filesym)
{
    sys_savepreferences(filesym->s_name);
}

void glob_forgetpreferences(t_pd *dummy)
{
#if !defined(_WIN32) && !defined(__APPLE__)
    if (system("cat ~/" UNIX_CONFIG_FILENAME " >& /dev/null\n"))
        post("no Pd settings to clear");
    else if (!system("rm ~/" UNIX_CONFIG_FILENAME "\n"))
        post("removed " UNIX_CONFIG_FILENAME " file");
    else post("couldn't delete " UNIX_CONFIG_FILENAME " file");
#endif  /* !defined(_WIN32) && !defined(__APPLE__) */
#ifdef __APPLE__
    char cmdbuf[MAXPDSTRING];
    int warn = 1;
    if (!sys_getpreference("audioapi", cmdbuf, MAXPDSTRING))
        post("no Pd settings to clear"), warn = 0;
            /* do it anyhow, why not... */
    snprintf(cmdbuf, MAXPDSTRING,
        "defaults delete %s 2> /dev/null\n", MACOSX_CONFIG_NAME);
    if (system(cmdbuf) && warn)
        post("failed to erase Pd settings");
    else if(warn) post("erased Pd settings");
#endif /* __APPLE__ */
#ifdef _WIN32
    HKEY hkey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
        "Software", 0,  KEY_QUERY_VALUE, &hkey) != ERROR_SUCCESS)
            post("no Pd settings to erase");
    else
    {
        if (RegDeleteKey(hkey, WIN_CONFIG_KEYNAME) != ERROR_SUCCESS)
            post("no Pd settings to erase");
        else post("erased Pd settings");
        RegCloseKey(hkey);
    }
#endif /* _WIN32 */
}

int sys_oktoloadfiles(int done)
{
#if defined(_WIN32) || defined(__APPLE__)
    if (done)
    {
        sys_putpreference("loading", "no");
        return (1);
    }
    else
    {
        char prefbuf[MAXPDSTRING];
        if (sys_getpreference("loading", prefbuf, MAXPDSTRING) &&
            strcmp(prefbuf, "no"))
        {
            post(
    "skipping loading preferences... Pd seems to have crashed on startup.");
            post("(re-save preferences to reinstate them)");
            return (0);
        }
        else
        {
            sys_putpreference("loading", "yes");
            return (1);
        }
    }
#else
    return (1);
#endif
}
