/*
Challenge 1 gift mon = SPECIES_MEW
*/

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
