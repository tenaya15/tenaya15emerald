EverGrandeCity_HallOfFame_EventScript_SetGameClearFlags::
	special SetChampionSaveWarp
	setflag FLAG_IS_CHAMPION
	special CheckLeagueWonWithChallenge1MonsOnly
	call EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries
	call_if_eq VAR_FOSSIL_MANIAC_STATE, 0, EverGrandeCity_HallOfFame_EventScript_SetDesertUnderpassCommentReady
	clearflag FLAG_HIDE_LILYCOVE_MOTEL_GAME_DESIGNERS
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	setflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_HIDE_SS_TIDAL_CORRIDOR_MR_BRINEY
	clearflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY
	setvar VAR_STEVENS_HOUSE_STATE, 2
	setflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	clearflag FLAG_HIDE_VICTORY_ROAD_EXIT_WALLY
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SS_TIDAL
	clearflag FLAG_HIDE_LILYCOVE_HARBOR_SSTIDAL
	setflag FLAG_HIDE_SAFARI_ZONE_SOUTH_CONSTRUCTION_WORKERS
	clearflag FLAG_HIDE_SAFARI_ZONE_SOUTH_EAST_EXPANSION
	setflag FLAG_HIDE_LILYCOVE_CITY_RIVAL
	special UpdateTrainerFanClubGameClear
	call_if_unset FLAG_RECEIVED_SS_TICKET, EverGrandeCity_HallOfFame_EventScript_ReadyReceiveSSTicketEvent
	call_if_unset FLAG_RECEIVED_BELDUM, EverGrandeCity_HallOfFame_EventScript_ShowStevensHouseBeldum
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 0, EverGrandeCity_HallOfFame_EventScript_ReadyDexUpgradeEvent
	return

EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries::
	clearflag FLAG_DEFEATED_MEW
	clearflag FLAG_DEFEATED_LATIAS_OR_LATIOS
	clearflag FLAG_DEFEATED_DEOXYS
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_DEFEATED_HO_OH
	return

EverGrandeCity_HallOfFame_EventScript_SetDesertUnderpassCommentReady::
	setvar VAR_FOSSIL_MANIAC_STATE, 1
	return

EverGrandeCity_HallOfFame_EventScript_ShowStevensHouseBeldum::
	clearflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	return

EverGrandeCity_HallOfFame_EventScript_ReadyReceiveSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 3
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 3
	clearflag FLAG_HIDE_PLAYERS_HOUSE_DAD
	return

EverGrandeCity_HallOfFame_EventScript_ReadyDexUpgradeEvent::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1
	return

LCR_Challenge1_EventScript_NPC_Start::
	lock
	faceplayer
	goto_if_set FLAG_LCR_CHALLENGE1_REWARD, LCR_Challenge1_EventScript_AlreadyReceived
	goto_if_set FLAG_LCR_WON_WITH_CH1_MONS_ONLY, LCR_Challenge1_EventScript_GiveReward

/* use if you want the challenge on the first attempt only (before becoming champion for the first time)
	goto_if_set FLAG_IS_CHAMPION, LCR_Challenge1_EventScript_ChampionNotEligible
*/
	msgbox LCR_Challenge1_Text_WaitingForTrainer, MSGBOX_NPC
	release
	end

/* use if you want the challenge on the first attempt only (before becoming champion for the first time)
LCR_Challenge1_EventScript_ChampionNotEligible::
	msgbox LCR_Challenge1_Text_ChampionNotEligible, MSGBOX_NPC
	release
	end
*/

LCR_Challenge1_EventScript_GiveReward::
	bufferspeciesname STR_VAR_2, SPECIES_MEW
	msgbox LCR_Challenge1_Text_EligibleIntro, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MEW
	specialvar VAR_RESULT, GiveLeagueChallenge1Reward
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LCR_Challenge1_EventScript_ReceiveMonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LCR_Challenge1_EventScript_ReceiveMonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LCR_Challenge1_EventScript_ReceiveMonParty::
	call LCR_Challenge1_EventScript_ReceiveMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LCR_Challenge1_EventScript_FinishReward
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LCR_Challenge1_EventScript_FinishReward
	end

LCR_Challenge1_EventScript_ReceiveMonPC::
	call LCR_Challenge1_EventScript_ReceiveMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LCR_Challenge1_EventScript_TransferMonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LCR_Challenge1_EventScript_TransferMonToPC
	end

LCR_Challenge1_EventScript_TransferMonToPC::
	call Common_EventScript_TransferredToPC
	goto LCR_Challenge1_EventScript_FinishReward
	end

LCR_Challenge1_EventScript_ReceiveMonFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_MEW
	playfanfare MUS_OBTAIN_ITEM
	message LCR_Challenge1_Text_ObtainedMon
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MEW
	return

LCR_Challenge1_EventScript_FinishReward::
	setflag FLAG_LCR_CHALLENGE1_REWARD
	msgbox LCR_Challenge1_Text_AfterReward, MSGBOX_DEFAULT
	release
	end

LCR_Challenge1_EventScript_AlreadyReceived::
	msgbox LCR_Challenge1_Text_AlreadyReceived, MSGBOX_NPC
	release
	end

LCR_Challenge1_Text_WaitingForTrainer:
	.string "Ah, a young TRAINER!\p"
	.string "I've been waiting here for a feline\n"
	.string "TRAINER who would conquer the\l"
	.string "POKéMON LEAGUE.\p"
	.string "Only a team of cats, from start to\n"
	.string "finish, would prove worthy.\p"
	.string "When that day comes, I have a very\n"
	.string "special gift waiting…$"

/* use if you want the challenge on the first attempt only (before becoming champion for the first time)
LCR_Challenge1_Text_ChampionNotEligible:
	.string "So you became CHAMPION!\n"
	.string "Congratulations, truly.\p"
	.string "But the gift I keep is not for any\n"
	.string "champion.\p"
	.string "It belongs to one who entered the\n"
	.string "HALL OF FAME with nothing but\l"
	.string "feline partners at their side.$"
*/

LCR_Challenge1_Text_EligibleIntro:
	.string "Incredible…!\p"
	.string "You conquered the LEAGUE with a team\n"
	.string "of cats, just as I dreamed!\p"
	.string "Please, accept this {STR_VAR_2}.\n"
	.string "It has earned its place beside you!$"

LCR_Challenge1_Text_ObtainedMon:
	.string "{PLAYER} received a {STR_VAR_2}!$"

LCR_Challenge1_Text_AfterReward:
	.string "Raise that {STR_VAR_2} with pride.\n"
	.string "The feline spirit runs in your team!$"

LCR_Challenge1_Text_AlreadyReceived:
	.string "My gift is already in your care.\p"
	.string "May your cats keep prowling\n"
	.string "victoriously across HOENN!$"
