/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 0;            /* 0 means bottom bar */
static const char *fonts[] = {
    "Liberation Mono:size=12",
    "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[] = "Liberation Mono:size=12";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Firefox", NULL, NULL, 1 << 3, 0, -1},
    {"firefox", NULL, NULL, 1 << 3, 0, -1},
    {"discord", NULL, NULL, 1 << 1, 0, -1},
};

/* layout(s) */
static const float mfact = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */

static const char *shutdowncmd[] = {"sudo", "/usr/sbin/poweroff", NULL};
static const char *rebootcmd[] = {"sudo", "/usr/sbin/reboot", "now", NULL};

static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *dmenupasscmd[] = {
    "passmenu", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",      col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *brightnessupcmd[] = {"blmgr", "+5%", NULL};
static const char *brightnessdowncmd[] = {"blmgr", "-5%", NULL};
static const char *raisevolumecmd[] = {"pactl", "set-sink-volume",
                                       "@DEFAULT_SINK@", "+5%", NULL};
static const char *lowervolumecmd[] = {"pactl", "set-sink-volume",
                                       "@DEFAULT_SINK@", "-5%", NULL};
static const char *mutevolumecmd[] = {"pactl", "set-sink-mute",
                                      "@DEFAULT_SINK@", "toggle", NULL};
static const char *nextcmd[] = {"playerctl", "next", NULL};
static const char *prevcmd[] = {"playerctl", "prev", NULL};
static const char *ppcommand[] = {"playerctl", "play-pause", NULL};
static const char *webcmd[] = {"firefox", NULL};
static const char *screencapcmd[] = {"/home/lajp/.local/scripts/screencap.sh",
                                     NULL};
static const char *screenshotcmd[] = {"flameshot", "gui", NULL};
static const char *playclipboardcmd[] = {
    "/home/lajp/.local/scripts/playclipboard.sh", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY | ShiftMask, XK_c, spawn, {.v = shutdowncmd}},
    {MODKEY | ShiftMask, XK_r, spawn, {.v = rebootcmd}},

    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_a, spawn, {.v = dmenupasscmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = webcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_h, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_l, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_space, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_s, setlayout, {.v = &layouts[0]}}, // default
    {MODKEY, XK_y, setlayout, {.v = &layouts[1]}}, // floating
    {MODKEY, XK_f, setlayout, {.v = &layouts[2]}}, // fullscreen stack
    //{ MODKEY,                       XK_space,  setlayout,      {0} },
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_n, focusmon, {.i = -1}},
    {MODKEY, XK_m, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_n, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_m, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY, XK_Up, spawn, {.v = brightnessupcmd}},
    {MODKEY, XK_Down, spawn, {.v = brightnessdowncmd}},
    {MODKEY, XK_Right, spawn, {.v = nextcmd}},
    {MODKEY, XK_Left, spawn, {.v = prevcmd}},
    {MODKEY, XK_p, spawn, {.v = ppcommand}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = raisevolumecmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = lowervolumecmd}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevolumecmd}},
    {0, XK_F7, spawn, {.v = screencapcmd}},
    {0, XK_Print, spawn, {.v = screenshotcmd}},
    {MODKEY | ShiftMask, XK_w, spawn, {.v = playclipboardcmd}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
