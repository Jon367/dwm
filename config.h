/* See LICENSE file for copyright and license details. */
#define TERMINAL "alacritty"
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel size of windows */
static const unsigned int gappx     = 5;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"monospace:size=12","JoyPixels:pixelsize=12:antialias=true:autohint=true","fontawesome:size=12"};
static const char dmenufont[]       = {"monospace:size=11"};
//background color
static const char col_gray1[]       = "#282a36";
//inactive window border color
static const char col_gray2[]       = "#4d4d4d";
//font color
static const char col_gray3[]       = "#f8f8f2";
//current tag and current window font color
static const char col_gray4[]       = "#f1fa8c";
//Top bar second color (blue) and active window border color
static const char col_cyan[]        = "#bd93f9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
/* tagging */
//tag names (upper left)
static const char *tags[] = { "", "", "", "4", "5",  "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *filemanager[] = { "
//launches htop
static const char *monitor[] = { "/usr/bin/htop", NULL };
//sets st as the default terminal
//static const char *termcmd[]  = { "st", NULL };
//sets urxvt as the default terminal
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static char *endx[] = { "/bin/sh", "-c", "endx", "externalpipe", NULL };
static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_o,       spawn,      SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
    { MODKEY,                       XK_w,       spawn,      SHCMD("librewolf") },
    { MODKEY,                       XK_Print,   spawn,      SHCMD("maim -s -u | xclip -selection clipboard -t image/png -i.png") },
    { MODKEY,                       XK_F3,      spawn,          SHCMD(TERMINAL " -e pulsemixer") },
    { MODKEY,                       XK_p,      spawn,          SHCMD("passmenu") },
    { MODKEY,                       XK_F4,      spawn,          SHCMD(TERMINAL " -e curl wttr.in") },
    { MODKEY,                       XK_F11,     spawn,      SHCMD("mpv --no-input-default-bindings av://v4l2:/dev/video0 --profile=low-latency --untimed)") },
    { MODKEY|ShiftMask,		    XK_w,	spawn,		SHCMD("networkmanager_dmenu") },
	{ MODKEY,                       XK_s,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_g,      togglebar,      {0} },
	{ MODKEY,                       XK_n,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_e,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,       SHCMD("slock") },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,              		    XK_k,      shiftview,  	   { .i = +1 } },
	{ MODKEY,              		    XK_b,      shiftview,      { .i = -1 } },
    //{ MODKEY,			XK_f,		togglefullscr,	{0} },
    { 0, XF86XK_AudioMute,		spawn,      SHCMD("amixer -q set Master toggle") },
    { 0, XF86XK_AudioRaiseVolume,	spawn,  SHCMD("amixer -q set Master 2%+ unmute") },
    { 0, XF86XK_AudioLowerVolume,     spawn,SHCMD("amixer -q set Master 2%- unmute") },
    { 0, XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous") },
    { 0, XF86XK_AudioNext,		spawn,		SHCMD("playerctl next") },
    { 0, XF86XK_AudioPause,		spawn,		SHCMD("playerctl pause") },
    { 0, XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play") },
    { 0, XF86XK_AudioStop,		spawn,		SHCMD("playerctl stop") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ShiftMask,                       XK_l,      spawn,          SHCMD("slock") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

