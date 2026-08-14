LivingDexReward_EventScript_1_LivingDexNpc::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LIVING_DEX_1_REWARD, LivingDexReward_EventScript_1_AlreadyReceived
	specialvar VAR_RESULT, CountPlayerLivingDex1Species
	goto_if_eq VAR_RESULT, 6, LivingDexReward_EventScript_1_GiveReward
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox LivingDexReward_Text_1_InProgress, MSGBOX_NPC
	release
	end

LivingDexReward_EventScript_1_GiveReward::
	bufferspeciesname STR_VAR_2, SPECIES_JIRACHI
	msgbox LivingDexReward_Text_1_EligibleIntro, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_JIRACHI
	specialvar VAR_RESULT, GiveLivingDex1Reward
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LivingDexReward_EventScript_1_ReceiveMonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LivingDexReward_EventScript_1_ReceiveMonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LivingDexReward_EventScript_1_ReceiveMonParty::
	call LivingDexReward_EventScript_1_ReceiveMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LivingDexReward_EventScript_1_FinishReward
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LivingDexReward_EventScript_1_FinishReward
	end

LivingDexReward_EventScript_1_ReceiveMonPC::
	call LivingDexReward_EventScript_1_ReceiveMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LivingDexReward_EventScript_1_TransferMonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LivingDexReward_EventScript_1_TransferMonToPC
	end

LivingDexReward_EventScript_1_TransferMonToPC::
	call Common_EventScript_TransferredToPC
	goto LivingDexReward_EventScript_1_FinishReward
	end

LivingDexReward_EventScript_1_ReceiveMonFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_JIRACHI
	playfanfare MUS_OBTAIN_ITEM
	message LivingDexReward_Text_1_ObtainedMon
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_JIRACHI
	return

LivingDexReward_EventScript_1_FinishReward::
	setflag FLAG_RECEIVED_LIVING_DEX_1_REWARD
	msgbox LivingDexReward_Text_1_AfterReward, MSGBOX_DEFAULT
	release
	end

LivingDexReward_EventScript_1_AlreadyReceived::
	bufferspeciesname STR_VAR_2, SPECIES_JIRACHI
	msgbox LivingDexReward_Text_1_AlreadyReceived, MSGBOX_NPC
	release
	end

LivingDexReward_Text_1_InProgress:
	.string "Ah, a TRAINER with an eye for cats!\p"
	.string "I'm cataloguing every feline native\n"
	.string "to HOENN.\p"
	.string "Bring me one of each: MEOWTH, PERSIAN,\n"
	.string "SKITTY, DELCATTY, ZANGOOSE, and ABSOL.\p"
	.string "They must be yours alone, caught or\n"
	.string "raised by you. No trades.\p"
	.string "You currently have {STR_VAR_1} of\n"
	.string "those six feline companions...$"

LivingDexReward_Text_1_EligibleIntro:
	.string "Marvelous...!\p"
	.string "You have gathered every wild cat of\n"
	.string "HOENN, each one truly your own!\p"
	.string "Please, accept this {STR_VAR_2}.\n"
	.string "She has waited patiently for a\l"
	.string "collector like you!$"

LivingDexReward_Text_1_ObtainedMon:
	.string "{PLAYER} received a {STR_VAR_2}!$"

LivingDexReward_Text_1_AfterReward:
	.string "Care for that {STR_VAR_2} gently.\n"
	.string "She prefers a warm nap after a job\l"
	.string "well done!$"

LivingDexReward_Text_1_AlreadyReceived:
	.string "My {STR_VAR_2} is already with you.\p"
	.string "Keep building your bond with every\n"
	.string "cat in HOENN!$"
