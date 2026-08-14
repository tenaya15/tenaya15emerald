#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "living_dex_reward.h"
#include "tv.h"

// doesn't need duplicating
static bool8 IsBoxMonOwnedByPlayer(struct BoxPokemon *boxMon)
{
    u32 otId;
    u8 otName[PLAYER_NAME_LENGTH + 1];

    if (GetBoxMonData(boxMon, MON_DATA_SPECIES) == SPECIES_NONE)
        return FALSE;

    if (GetBoxMonData(boxMon, MON_DATA_IS_EGG))
        return FALSE;

    otId = GetBoxMonData(boxMon, MON_DATA_OT_ID);
    if (otId != GetPlayerIDAsU32())
        return FALSE;

    GetBoxMonData(boxMon, MON_DATA_OT_NAME, otName);
    if (StringCompare(otName, gSaveBlock2Ptr->playerName) != 0)
        return FALSE;

    return TRUE;
}

// doesn't need duplicating
static bool8 PlayerOwnsSpecies(u16 species)
{
    u32 i;
    u32 j;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
            continue;

        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == species
            && IsBoxMonOwnedByPlayer(&gPlayerParty[i].box))
            return TRUE;
    }

    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            if (GetBoxMonData(&gPokemonStoragePtr->boxes[i][j], MON_DATA_SPECIES) == species
                && IsBoxMonOwnedByPlayer(&gPokemonStoragePtr->boxes[i][j]))
                return TRUE;
        }
    }

    return FALSE;
}

// doesn't need duplicating
static void SetRewardMonIv(struct Pokemon *mon, u8 stat, u8 ivConfig)
{
    u8 iv;

    if (ivConfig == USE_RANDOM_IVS)
        return;

    iv = ivConfig;
    SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
}

// doesn't need duplicating
static void ApplyRewardMonIvs(struct Pokemon *mon, u8 hp, u8 atk, u8 def, u8 speed, u8 spAtk, u8 spDef)
{
    SetRewardMonIv(mon, STAT_HP, hp);
    SetRewardMonIv(mon, STAT_ATK, atk);
    SetRewardMonIv(mon, STAT_DEF, def);
    SetRewardMonIv(mon, STAT_SPEED, speed);
    SetRewardMonIv(mon, STAT_SPATK, spAtk);
    SetRewardMonIv(mon, STAT_SPDEF, spDef);
    CalculateMonStats(mon);
}


// DUPLICATE EVERYTHING BELOW TO CREATE MORE CHALLENGES AND CHANGE REFERENCES FROM "CHALLENGE 1" TO "CHALLENGE 2"

// Living Dex Challenge 1 reward level and moves here
#define LIVING_DEX_REWARD_1_SPECIES    SPECIES_JIRACHI
#define LIVING_DEX_REWARD_1_LEVEL      60
#define LIVING_DEX_REWARD_1_MOVE_1     MOVE_REST
#define LIVING_DEX_REWARD_1_MOVE_2     MOVE_CONFUSION
#define LIVING_DEX_REWARD_1_MOVE_3     MOVE_TAIL_WHIP
#define LIVING_DEX_REWARD_1_MOVE_4     MOVE_WISH

// Use 0–31 for a fixed IV, or USE_RANDOM_IVS to leave that stat random. Change `MON_1_CUTE_RIBBON_RANK` to adjust the contest ribbon tier (`1`–`4`).
#define LIVING_DEX_REWARD_1_IV_HP      31
#define LIVING_DEX_REWARD_1_IV_ATK     31
#define LIVING_DEX_REWARD_1_IV_DEF     31
#define LIVING_DEX_REWARD_1_IV_SPEED   31
#define LIVING_DEX_REWARD_1_IV_SPATK   USE_RANDOM_IVS
#define LIVING_DEX_REWARD_1_IV_SPDEF   USE_RANDOM_IVS

#define MON_1_CUTE_RIBBON_RANK         4

// challenge 1 species
// only the specific pokemon stated here count
// evolutions must be stated here if they are to be counted
static const u16 sLivingDex1Species[] =
{
    SPECIES_MEOWTH,
    SPECIES_PERSIAN,
    SPECIES_SKITTY,
    SPECIES_DELCATTY,
    SPECIES_ZANGOOSE,
    SPECIES_ABSOL,
};


u8 CountPlayerLivingDex1Species(void)
{
    u32 i;
    u8 count = 0;

    for (i = 0; i < ARRAY_COUNT(sLivingDex1Species); i++)
    {
        if (PlayerOwnsSpecies(sLivingDex1Species[i]))
            count++;
    }

    return count;
}

static void ApplyMon1RewardTraits(struct Pokemon *mon)
{
    u8 cuteRibbon = MON_1_CUTE_RIBBON_RANK;

    ApplyRewardMonIvs(mon,
        LIVING_DEX_REWARD_1_IV_HP,
        LIVING_DEX_REWARD_1_IV_ATK,
        LIVING_DEX_REWARD_1_IV_DEF,
        LIVING_DEX_REWARD_1_IV_SPEED,
        LIVING_DEX_REWARD_1_IV_SPATK,
        LIVING_DEX_REWARD_1_IV_SPDEF);
    SetMonData(mon, MON_DATA_CUTE_RIBBON, &cuteRibbon);
}

u16 GiveLivingDex1Reward(void)
{
    struct Pokemon mon;
    u8 result;
    u16 nationalDexNum;

    CreateMon(&mon, LIVING_DEX_REWARD_1_SPECIES, LIVING_DEX_REWARD_1_LEVEL, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    SetMonMoveSlot(&mon, LIVING_DEX_REWARD_1_MOVE_1, 0);
    SetMonMoveSlot(&mon, LIVING_DEX_REWARD_1_MOVE_2, 1);
    SetMonMoveSlot(&mon, LIVING_DEX_REWARD_1_MOVE_3, 2);
    SetMonMoveSlot(&mon, LIVING_DEX_REWARD_1_MOVE_4, 3);
    ApplyMon1RewardTraits(&mon);

    result = GiveMonToPlayer(&mon);
    nationalDexNum = SpeciesToNationalPokedexNum(LIVING_DEX_REWARD_1_SPECIES);

    if (result == MON_GIVEN_TO_PARTY || result == MON_GIVEN_TO_PC)
    {
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
    }

    return result;
}
