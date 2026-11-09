#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// In the Generation 3 games, Asserts were used in various debug builds.
// Ruby/Sapphire and Emerald do not have these asserts while Fire Red
// still has them in the ROM. This is because the developers forgot
// to define NDEBUG before release, however this has been changed as
// Ruby's actual debug build does not use the AGBPrint features.
#define NDEBUG

// To enable printf debugging, comment out "#define NDEBUG". This allows
// the various AGBPrint functions to be used. (See include/gba/isagbprint.h).
// See below for enabling different pretty printing versions.

#ifndef NDEBUG

#define PRETTY_PRINT_MINI_PRINTF (0)
#define PRETTY_PRINT_LIBC (1)

#define LOG_HANDLER_AGB_PRINT (0)
#define LOG_HANDLER_NOCASH_PRINT (1)
#define LOG_HANDLER_MGBA_PRINT (2)

// Use this switch to choose a handler for pretty printing.
// NOTE: mini_printf supports a custom pretty printing formatter to display preproc encoded strings. (%S)
//       some libc distributions (especially dkp arm-libc) will fail to link pretty printing.
#define PRETTY_PRINT_HANDLER (PRETTY_PRINT_MINI_PRINTF)

// Use this switch to choose a handler for printf output.
// NOTE: These will only work on the respective emulators and should not be used in a productive environment.
//       Some emulators or real hardware might (and is allowed to) crash if they are used.
//       AGB_PRINT is supported on respective debug units.

#define LOG_HANDLER (LOG_HANDLER_MGBA_PRINT)
#endif

#define ENGLISH

#ifdef ENGLISH
#define UNITS_IMPERIAL
#define CHAR_DEC_SEPARATOR CHAR_PERIOD // Period is used as a decimal separator only in the UK and the US.
#else
#define UNITS_METRIC
#define CHAR_DEC_SEPARATOR CHAR_COMMA
#endif

// Uncomment to fix some identified minor bugs
//#define BUGFIX

// Various undefined behavior bugs may or may not prevent compilation with
// newer compilers. So always fix them when using a modern compiler.
#if MODERN || defined(BUGFIX)
#ifndef UBFIX
#define UBFIX
#endif
#endif

// Alternate Ball Catch Effects

// Moon Ball catch effects
// uncomment to change Moon Ball multiplier to x4 for all family of moon stone evolvers; else default, boosted multiplier only for Nidorina / Nidorino / Clefairy / Jigglypuff / Skitty / Munna (if defined)
//#define MOON_BALL_MODIFIER

// Lure Ball catch effects
// uncomment to change Lure Ball multiplier to x5 for all fishing encounters
//#define LURE_BALL_MODIFIER

// Love Ball catch effects
// uncomment to change Love Ball to where you don't need to be the same species, only the opposite gender to the wild pokemon
//#define LOVE_BALL_MODIFIER

// Sport Ball catch effects
// uncomment to change Sport Ball to a x1 modifier that can catch pokemon anywhere (like a normal poke ball)
//#define SPORT_BALL_MODIFIER

// Heavy Ball catch effects
// uncomment to change to Gen 4 effects: if (i < 2048), ballAddition = -20; if (i < 3072), ballAddition = 20; if (i < 4096), ballAddition = 30; else ballAddition = 40;
//#define HEAVY_BALL_MODIFIER

#endif // GUARD_CONFIG_H
