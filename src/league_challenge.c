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
#include "data/league_challenge_species.h"
#include "league_challenge.h"
#include "tv.h"

extern const struct Evolution gEvolutionTable[][EVOS_PER_MON];

// Edit reward level and moves here
//challenge 1
#define CHALLENGE_1_REWARD_SPECIES   SPECIES_MEW
#define CHALLENGE_1_REWARD_LEVEL     60
#define CHALLENGE_1_REWARD_MOVE_1    MOVE_PSYCHIC
#define CHALLENGE_1_REWARD_MOVE_2    MOVE_THUNDERBOLT
#define CHALLENGE_1_REWARD_MOVE_3    MOVE_HYPER_BEAM
#define CHALLENGE_1_REWARD_MOVE_4    MOVE_DIG

#define CHALLENGE_1_REWARD_IV_HP     31
#define CHALLENGE_1_REWARD_IV_ATK    31
#define CHALLENGE_1_REWARD_IV_DEF    USE_RANDOM_IVS
#define CHALLENGE_1_REWARD_IV_SPEED  31
#define CHALLENGE_1_REWARD_IV_SPATK  31
#define CHALLENGE_1_REWARD_IV_SPDEF  USE_RANDOM_IVS

static EWRAM_DATA bool8 sChallenge1SpeciesCacheBuilt = FALSE;
static EWRAM_DATA bool8 sIsChallenge1MonSpecies[NUM_SPECIES];

//this version edited from scolandrea's code
//full credit still goes to scolandrea https://github.com/scolandrea/pokeemerald
static void BuildChallenge1SpeciesCache(void)
{
	u16 queue[NUM_SPECIES];
	u16 head = 0;
	u16 tail = 0;
	u32 i;

	for (i = 0; i < NUM_SPECIES; i++)
		sIsChallenge1MonSpecies[i] = FALSE;

	for (i = 0; i < ARRAY_COUNT(sChallenge1Species); i++)
	{
		u16 species = sChallenge1Species[i];

		if (species == SPECIES_NONE || species >= NUM_SPECIES)
			continue;

		if (!sIsChallenge1MonSpecies[species])
		{
			sIsChallenge1MonSpecies[species] = TRUE;
			queue[tail++] = species;
		}
	}

	while (head < tail)
	{
		u16 current = queue[head++];
		u32 j;

		for (j = 0; j < EVOS_PER_MON; j++)
		{
			u16 evolution = gEvolutionTable[current][j].targetSpecies;

			if (evolution == SPECIES_NONE || evolution >= NUM_SPECIES)
				continue;

			if (!sIsChallenge1MonSpecies[evolution])
			{
				sIsChallenge1MonSpecies[evolution] = TRUE;
				queue[tail++] = evolution;
			}
		}
	}

	sChallenge1SpeciesCacheBuilt = TRUE;
}

bool8 IsChallenge1MonSpecies(u16 species)
{
	if (species == SPECIES_NONE || species == SPECIES_EGG || species >= NUM_SPECIES)
	{
		return FALSE;
	}

	if (!sChallenge1SpeciesCacheBuilt)
		BuildChallenge1SpeciesCache();

	return sIsChallenge1MonSpecies[species];
}

void CheckLeagueWonWithChallenge1MonsOnly(void)
{
	u32 i;
	bool8 hasMon = FALSE;

	// Reset first so a failed check can never leave a stale TRUE flag set.
	FlagClear(FLAG_LCR_WON_WITH_CH1_MONS_ONLY);

	for (i = 0; i < PARTY_SIZE; i++)
	{
		u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

		if (species == SPECIES_NONE)
			continue;

		hasMon = TRUE;

		if (species == SPECIES_EGG || !IsChallenge1MonSpecies(species))
			return;
	}

	if (hasMon)
		FlagSet(FLAG_LCR_WON_WITH_CH1_MONS_ONLY);
}

// doesn't need duplicated
static void SetRewardMonIv(struct Pokemon *mon, u8 stat, u8 ivConfig)
{
	u8 iv;

	if (ivConfig == USE_RANDOM_IVS)
		return;

	iv = ivConfig;
	SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
}

// doesn't need duplicated
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

static void ApplyChallenge1RewardTraits(struct Pokemon *mon)
{
	u8 ribbon = TRUE;

	ApplyRewardMonIvs(mon,
		CHALLENGE_1_REWARD_IV_HP,
		CHALLENGE_1_REWARD_IV_ATK,
		CHALLENGE_1_REWARD_IV_DEF,
		CHALLENGE_1_REWARD_IV_SPEED,
		CHALLENGE_1_REWARD_IV_SPATK,
		CHALLENGE_1_REWARD_IV_SPDEF);
	SetMonData(mon, MON_DATA_WINNING_RIBBON, &ribbon);
}

u16 GiveLeagueChallenge1Reward(void)
{
	struct Pokemon mon;
	u8 result;
	u16 nationalDexNum;

	CreateMon(&mon, CHALLENGE_1_REWARD_SPECIES, CHALLENGE_1_REWARD_LEVEL,
		USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
	SetMonMoveSlot(&mon, CHALLENGE_1_REWARD_MOVE_1, 0);
	SetMonMoveSlot(&mon, CHALLENGE_1_REWARD_MOVE_2, 1);
	SetMonMoveSlot(&mon, CHALLENGE_1_REWARD_MOVE_3, 2);
	SetMonMoveSlot(&mon, CHALLENGE_1_REWARD_MOVE_4, 3);
	ApplyChallenge1RewardTraits(&mon);

	result = GiveMonToPlayer(&mon);
	nationalDexNum = SpeciesToNationalPokedexNum(CHALLENGE_1_REWARD_SPECIES);

	if (result == MON_GIVEN_TO_PARTY || result == MON_GIVEN_TO_PC)
	{
		GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
		GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
	}

	return result;
}
