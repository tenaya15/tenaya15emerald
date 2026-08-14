#ifndef GUARD_LEAGUE_CHALLENGE_H
#define GUARD_LEAGUE_CHALLENGE_H

#include "global.h"

bool8 IsChallenge1MonSpecies(u16 species);
void CheckLeagueWonWithChallenge1MonsOnly(void);
u16 GiveLeagueChallenge1Reward(void);
u8 CountPlayerLivingDex1Species(void);
u16 GiveLivingDex1Reward(void);

#endif // GUARD_LEAGUE_CHALLENGE_H
