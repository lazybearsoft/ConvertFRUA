#include "stdafx.h"
#include "Translate.h"
#include "specAb.h"
#include "NPC.h"
#include "Monster.h"

//
extern FILE *f;
extern CString FRUAExportDate, FRUAExportTime;
extern CString ConvertFRUAVersion;
extern CString binPath;
void Line(const char *name, const char *value);
void Line(const char *name, int value);
CString CapitalizeMonster(const CString& monsterName);
CString CapitalizeRace(const CString& raceName);
CString CapitalizeClass(const CString& className);
CString CapitalizeItem(const CString& itemName);
CString UniqueItemName(const CString& name);
ARTMAP *SearchFRUAArtMap(const CString& name, const CString& type);
CString CamelCap(const CString&src);

#define Str(a) monster.Fetch_String(a)
#define Int(a) monster.Fetch_Int(a)

CString tag, leftTag, rightTag, tagValue;
int instance;
JReader *mon;

//CArray<CString, CString&> monsterList;
CArray<MONSTER_DATA, MONSTER_DATA&> monsterData;



MONSTER_DATA *pMonster;
CString defaultMonsters[] = {
  "KOBOLD",
  "GOBLIN",
  "ORC",
  "HOBGOBLIN",
  "ORC CHIEFTAIN",
  "HOBGOBLIN LDR",
  "GNOLL",
  "OGRE",
  "TROLL",
  "HILL GIANT",
  "FIRE GIANT",
  "FROST GIANT",
  "CLOUD GIANT",
  "STORM GIANT",
  "GIANT RAT",
  "CARRION CRAWLER",
  "ENORMOUS SPIDER",
  "SKELETON",
  "ZOMBIE",
  "GHOUL",
  "GHAST",
  "WIGHT",
  "WRAITH",
  "MUMMY",
  "SPECTRE",
  "VAMPIRE",
  "LICH",
  "LIZARD MAN",
  "LIZARD MAN KING",
  "MINOTAUR",
  "DISPLACER BEAST",
  "BORING BEETLE",
  "GRIFFON",
  "HYDRA",
  "WYVERN",
  "BLACK DRAGON",
  "BLUE DRAGON",
  "GREEN DRAGON",
  "RED DRAGON",
  "WHITE DRAGON",
  "DRACOLICH",
  "BASILISK",
  "GORGON",
  "COCKATRICE",
  "BEHOLDER",
  "OGRE MAGE",
  "BULETTE",
  "SHAMBLING MOUND",
  "MARGOYLE",
  "DRACOLISK",
  "MOBAT",
  "BLACK PUDDING",
  "OTYUGH",
  "NEO OTYUGH",
  "SALAMANDER",
  "EFREETI",
  "EARTH ELEMENTAL",
  "FIRE ELEMENTAL",
  "UMBER HULK",
  "ETTIN",
  "OWL BEAR",
  "BUGBEAR",
  "MEDUSA",
  "GIANT SPIDER",
  "PHASE SPIDER",
  "POISONOUS SNAKE",
  "HELL HOUND",
  "GIANT CROCODILE",
  "DRIDER",
  "IRON GOLEM",
  "RAKSHASA",
  "PURPLE WORM",
  "DROW CHAMPION",
  "DROW PRIEST",
  "DROW SORCERESS",
  "DROW PRIESTESS",
  "WARRIOR",
  "CONJURER",
  "ACOLYTE",
  "GOON",
  "ARCHER",
  "THEURGIST",
  "PRIEST",
  "THUG",
  "EVIL CHAMPION",
  "MAGICIAN",
  "DARK CLERIC",
  "ROGUE",
  "DARK KNIGHT",
  "NECROMANCER",
  "HIGH PRIEST",
  "THIEF",
  "DARK WARLORD",
  "WIZARD",
  "ARCHPRIEST",
  "MASTER THIEF",
  "DARK OVERLORD",
  "MASTER WIZARD",
  "DARK DISCIPLE",
  "HIGH THIEF",
  "VAMPIRE LORD",
  "VAMPIRESS",
  "DAZMILAR",
  "OGRE SHAMAN",
  "SIR DUTIOCS",
  "VIDRUAND",
  "HILL GNT SHAMAN",
  "VAMPIRE PRIEST",
  "DROW AMAZON",
  "RAKSHASA RUKH",
  "ROAD GUARD",
  "KALLITHREA",
  "YEMANDRA",
  "KRONDASZ",
  "ARDERIEL",
  "TORNILEE",
  "ALIAS",
  "DRAGONBAIT",
  "NACACIA",
  "NPC ONE",
  "VALA",
  "SILK",
  "CAPTAIN DAENOR",
  "GRUNSCHKA",
  "STORM",
  "SHAL",
  "RAIZEL",
  ""
};



int GetIntVal(const CString& tag)
{
  return mon->Fetch_Int(tag);
}


int MONSTER_DATA::FindLine(const CString& tag, int index)
{
  int i, n;
  n = key.GetSize();
  for (i=0; i<n; i++)
  {
    if (key[i] == tag)
    {
      if (index == 0) return i;
      index--;
    };
  };
  return -1;
}

CString MONSTER_DATA::GetStringValue(const CString& tag, int index)
{
  int j; 
  j = FindLine(tag, index);
  if (j < 0) return "???";
  return value[j];
}



CString MONSTER_DATA::GetStringValue(const CString& tag)
{
  return GetStringValue(tag, 0);
}

int MONSTER_DATA::GetIntegerValue(const CString& tag, int index)
{
  CString str;
  str = GetStringValue(tag, index);
  if (str == "???")
  {
    return -1;
  }
  else
  {
    int i;
#pragma warning (suppress:4996)
    sscanf((LPCSTR)str, "%d", &i);
    return i;
  };
}

int MONSTER_DATA::GetIntegerValue(const CString& tag)
{
  return GetIntegerValue(tag, 0);
}


void InsertLine(const CString& tag, const CString& value)
{
  int n;
  n = pMonster->key.GetSize();
  pMonster->key.SetSize(n+1);
  pMonster->value.SetSize(n+1);
  pMonster->key[n] = tag;
  pMonster->value[n] = value;
}

void MONSTER_DATA::UpdateLine(const CString& tag, const CString& value)
{
  int i;
  i = FindLine(tag);
  if (i < 0)
  {
    InsertLine(tag, value);
  }
  else
  {
    pMonster->value[i] = value;
  };
}
void MONSTER_DATA::UpdateLine(const CString& tag, int value)
{
  CString text;
  text.Format("%d", value);
  UpdateLine(tag, text);
}

void MONSTER_DATA::RenameLine(const CString& tag, const CString& newTag)
{
  int i;
  while ((i = FindLine(tag)) >= 0)
  {
    pMonster->key[i] = newTag;
  };
}

void MONSTER_DATA::AddImmunity(const char *immunity)
{
  int i;
  i = FindLine("immunity");
  if (i < 0) InsertLine("immunity", immunity);
  else UpdateLine("immunity", pMonster->value[i] + "+" + immunity);
}

void MONSTER_DATA::UpdateSpecialAbility(const char *saName, const char *v)
{
  int i, n, comma;
  n = key.GetSize();
  for (i=0; i<n; i++)
  {
    if (key[i] == "Special Ability")
    {
      CString name;
      comma = value[i].Find(',');
      if (comma < 0) comma = value[i].GetLength();
      name = value[i].Left(comma);
      if (name == saName)
      {
        value[i] = name + "," + v;
        return;
      };
    };
  };
  //InsertLine("Special Ability", CString("monster_Race,") + v);
}


void NOP(void)
{
}
void HandleAbilityCharisma(void)
{
  pMonster->UpdateLine("//charisma", tagValue);
}
void HandleAbilityConstitution(void)
{
  pMonster->UpdateLine("//constitution", tagValue);
}
void HandleAbilityIntelligence(void)
{
  pMonster->UpdateLine("intelligence", tagValue);
}
void HandleAbilityStrength(void)
{
  pMonster->UpdateLine("//strength", tagValue);
}
void HandleAbilityWisdom(void)
{
  pMonster->UpdateLine("//wisdom", tagValue);
}
void HandleAbilityDexterity(void)
{
  pMonster->UpdateLine("//dexterity", tagValue);
}
void HandleAge(void)
{
  pMonster->UpdateLine("//age", tagValue);
}
void HandleAlignment(void)
{
  pMonster->UpdateLine("//alignment", tagValue);
}
void HandleArmorClass(void)
{
  int value;
  value = GetIntVal("armor_class_adjusted") + GetIntVal("armor_class_base");
  pMonster->UpdateLine("armor class", value);
}

int Attack_Int(const char *tag)
{
  CString temp;
  temp.Format("attack_%d_%s", instance, tag);
  return mon->Fetch_Int(temp);
};
void HandleAttack(void)
{
  //DEFID( "attack"                  ,string ,Attack),
  //                                 sides, number, bonus, attackMessage, spellID
  int damageBonus, damageDiceSides, nbrAttackPer2Rounds;
  int numDamageDice, unarmedDamageBonus, unarmedDamageDiceSides;
  int unarmedNbrAttacksPer2Rounds, unarmedNumDamageDice;
  CString attack;
  damageBonus = Attack_Int("damage_bonus");
  damageDiceSides = Attack_Int("damage_dice_sides");
  nbrAttackPer2Rounds = Attack_Int("nbr_attacks_per_2_rounds");
  numDamageDice = Attack_Int("num_damage_dice");
  unarmedDamageBonus = Attack_Int("unarmed_damage_bonus");
  unarmedDamageDiceSides = Attack_Int("unarmed_damage_dice_sides");
  unarmedNbrAttacksPer2Rounds = Attack_Int("unarmed_nbr_attacks_per_2_rounds");
  unarmedNumDamageDice = Attack_Int("unarmed_num_damage_dice");
  if (    (unarmedDamageDiceSides == 0)
       && (unarmedNumDamageDice == 0)
       && (unarmedDamageBonus == 0)
     ) return;
  attack.Format("%d, %d, %d, Attacks,",
                 unarmedDamageDiceSides,
                 unarmedNumDamageDice,
                 unarmedDamageBonus);
  InsertLine("attack", attack);
}
void HandleClass(void)
{
  pMonster->UpdateLine("Class", tagValue);
}
void HandleCombatMode(void)
{
  pMonster->UpdateLine("//combat mode", tagValue);
}
void HandleCombatStatus(void)
{
  pMonster->UpdateLine("//combat status", tagValue);
}
void HandleCureDiseaseAllowed(void)
{
  pMonster->UpdateLine("//cure disease allowed", tagValue);
}
void HandleCurrentStatus(void)
{
  pMonster->UpdateLine("//current status", tagValue);
}

CString Equip_Str(const char *tag)
{
  CString temp;
  temp.Format("equip_item_%02d_%s", instance, tag);
  return mon->Fetch_String(temp);
}
int Equip_Int(const char *tag)
{
  CString temp;
  temp.Format("equip_item_%02d_%s", instance, tag);
  return mon->Fetch_Int(temp);
}

void HandleEquipItem(void)
{
  CString item, id, equip;
  int count;
  item = tagValue;
  if (item.CompareNoCase("Plate Mail +1") == 0)
  {
    int kkk = 1;
  }
  count = Equip_Int("count");
  id =    Equip_Str("id");
  {
    // Make sure the item exists.
    // Rename it if that makes sense.
    {
      LINE_DATA *pItemData;
      pItemData = defaultItemData.Find("name", item);
      if (pItemData == NULL)
      {
        // Perhaps we can rename this item.
        // Search the default list for the 'identified name"
        pItemData = defaultItemData.Find("id name", item);
        if (pItemData == NULL)
        {
          pItemData = jsonItemData.Find("name", item);
          if (pItemData == NULL)
          {
            pItemData = jsonItemData.Find("id name", item);
          };
        };
      };
      if (pItemData != NULL)
      {
        // Rename this monster's item to agree with the defaultItemDatabase.
        LINE_ENTRY *pDefaultLine;
        pDefaultLine = (*pItemData)["name"];
        if (pDefaultLine != NULL)
        {
          item = pDefaultLine->value;
        };
      };
    };
  };
  if (count == 0) count = 1;
  equip.Format("%s, %d", item, count);
  InsertLine("item", equip);
}
void HandleExperiencePredrain(void)
{
  pMonster->UpdateLine("//experience predrain", tagValue);
}
void HandleGender(void)
{
  pMonster->UpdateLine("//gender", tagValue);
}
void HandleEncumbranceInCoins(void)
{
  pMonster->UpdateLine("//encumbrance in coins", tagValue);
}
void HandleHitpoints(void)
{
  int hitpointsBase, hitpointsAdjusted, hitpointsMaximum, hitpointsPredrain;
  hitpointsBase = mon->Fetch_Int("hitpoints_base");
  hitpointsAdjusted = mon->Fetch_Int("hitpoints_adjusted");
  hitpointsMaximum = mon->Fetch_Int("hitpoints_maximum");
  hitpointsPredrain = mon->Fetch_Int("hitpoints_predrain");
  pMonster->UpdateLine("hit dice", hitpointsMaximum);
  pMonster->UpdateLine("//hitpoints adjusted", hitpointsAdjusted);
  pMonster->UpdateLine("//hitpoints predrain", hitpointsPredrain);
  pMonster->UpdateLine("//hitpoints base", hitpointsBase);
}
void HandleEquipNumHandsFull(void)
{
  pMonster->UpdateLine("//equip num hands full", tagValue);
}
void HandleExperienceCurrent(void)
{
  pMonster->UpdateLine("//experience current", tagValue);
}
void HandleExperienceGrantedForKilling(void)
{
  pMonster->UpdateLine("experience point value", tagValue);
}
void HandleIconIndex(void)
{
  pMonster->UpdateLine("//icon index", tagValue);
}
void HandleIconId(void)
{
  pMonster->UpdateLine("//icon id", tagValue);
}
void HandleItemBundlesCarried(void)
{
  pMonster->UpdateLine("//bundles carried", tagValue);
}
void HandleItemMaskCanEquipCleric(void)
{
  pMonster->UpdateLine("//can equip cleric", tagValue);
}
void HandleItemMaskCanEquipFighter(void)
{
  pMonster->UpdateLine("//can equip fighter", tagValue);
}
void HandleItemMaskCanEquipKnight(void)
{
  pMonster->UpdateLine("//can equip knight", tagValue);
}
void HandleItemMaskCanEquipMagicUser(void)
{
  pMonster->UpdateLine("//can equip magic user", tagValue);
}
void HandleItemMaskCanEquipPaladinRanger(void)
{
  pMonster->UpdateLine("//can equip paladin ranger", tagValue);
}
void HandleItemMaskCanEquipThief(void)
{
  pMonster->UpdateLine("//can equip thief", tagValue);
}
void HandleLevelCurrent(void)
{
  pMonster->UpdateLine("//level current", tagValue);
}
void HandleLevelCurrentCleric(void)
{
  pMonster->UpdateLine("//level current cleric", tagValue);
}
void HandleLevelCurrentFighter(void)
{
  pMonster->UpdateLine("//level current fighter", tagValue);
}
void HandleLevelCurrentKnight(void)
{
  pMonster->UpdateLine("//level current knight", tagValue);
}
void HandleLevelCurrentMage(void)
{
  pMonster->UpdateLine("//level current mage", tagValue);
}
void HandleLevelCurrentPaladin(void)
{
  pMonster->UpdateLine("//level current paladin", tagValue);
}
void HandleLevelCurrentRanger(void)
{
  pMonster->UpdateLine("//level current ranger", tagValue);
}
void HandleLevelCurrentThief(void)
{
  pMonster->UpdateLine("//level current thief", tagValue);
}
void HandleLevelFighterSweep(void)
{
  pMonster->UpdateLine("//level fighter sweep", tagValue);
}
void HandleLevelFormerClass(void)
{
  pMonster->UpdateLine("//level former class", tagValue);
}
void HandleLevelPreClassChangeCleric(void)
{
  pMonster->UpdateLine("//level pre class change cleric", tagValue);
}
void HandleLevelPreClassChangeFighter(void)
{
  pMonster->UpdateLine("//level pre class change fighter", tagValue);
}
void HandleLevelPreClassChangeKnight(void)
{
  pMonster->UpdateLine("//level pre class change knight", tagValue);
}
void HandleLevelPreClassChangeMage(void)
{
  pMonster->UpdateLine("//level pre class change mage", tagValue);
}
void HandleLevelPreClassChangePaladin(void)
{
  pMonster->UpdateLine("//level pre class change paladin", tagValue);
}
void HandleLevelPreClassChangeRanger(void)
{
  pMonster->UpdateLine("//level pre class change ranger", tagValue);
}
void HandleLevelPreClassChangeThief(void)
{
  pMonster->UpdateLine("//level pre class change thief", tagValue);
}
void HandleLevelPreDrainCleric()
{
  pMonster->UpdateLine("//level pre drain cleric", tagValue);
}
void HandleLevelPreDrainFighter()
{
  pMonster->UpdateLine("//level pre drain fighter", tagValue);
}
void HandleLevelPreDrainKnight()
{
  pMonster->UpdateLine("//level pre drain knight", tagValue);
}
void HandleLevelPreDrainMage()
{
  pMonster->UpdateLine("//level pre drain mage", tagValue);
}
void HandleLevelPreDrainPaladin()
{
  pMonster->UpdateLine("//level pre drain paladin", tagValue);
}
void HandleLevelPreDrainRanger()
{
  pMonster->UpdateLine("//level pre drain ranger", tagValue);
}
void HandleLevelPreDrainThief()
{
  pMonster->UpdateLine("//level pre drain thief", tagValue);
}
void HandleLevelReadyToTrain()
{
  pMonster->UpdateLine("//level ready to train", tagValue);
}
void HandleMagicResist()
{
  int base, bonus;
  base = mon->Fetch_Int("magic_resist_base_percent");
  bonus = mon->Fetch_Int("magic_resist_bonus");
  pMonster->UpdateLine("magic resistance", base);
}
void HandleMorale()
{
  pMonster->UpdateLine("morale", tagValue);
}
void HandleMovement()
{
  pMonster->UpdateLine("movement rate", tagValue);
}
void HandleRace()
{
  pMonster->UpdateSpecialAbility("monster_Race", tagValue);
  pMonster->UpdateLine("Race", tagValue);
}
void HandleSaveVsBreathWeapon(void)
{
}
void HandleSaveVsParalysisPoisonDeathmagic(void)
{
}
void HandleSaveVsPetrificationPolymorph(void)
{
}
void HandleSaveVsRodStaffWand(void)
{
}
void HandleSaveVsSpell(void)
{
}
void HandleSizeIcon(void)
{
}
void HandleSizeLargeEvenIfIcon1x1(void)
{
}
void HandleSpecialFlagAffectedByDispelEvil(void)
{
}
void HandleSpecialFlagCanBeHeldOrCharmed(void)
{
}
void HandleSpecialFlagDwarfHasHitBonus(void)
{
}
void HandleSpecialFlagExtraDmgFromRanger(void)
{
}
void HandleSpecialFlagGnomeHasHitBonus(void)
{
}
void HandleSpecialFlagImmuneToConfusion(void)
{
}
void HandleSpecialFlagImmuneToDeathMagic(void)     
{
}
void HandleSpecialFlagImmuneToDecapitationFromVorpalSword(void)
{
}
void HandleSpecialFlagImmuneToPoison(void)
{
}
void HandleSpecialFlagIsAAnimal(void)
{
}
void HandleSpecialFlagIsAMammal(void)
{
}
void HandleSpecialFlagIsASnake(void)
{
}
void HandleSpecialFlagIsATrueGiant(void)
{
}
void HandleSpecialFlagPenaltyToHitDwarf(void)
{
}
void HandleSpecialFlagPenaltyToHitGnome(void)
{
}
void HandleNumSpellCleric(void)
{
}
void HandleNumSpellDruid(void)
{
}
void HandleNumSpellMagicUser(void)
{
}
void HandleTHAC0(void)
{
}
void HandleThievingSkillClimbWalls(void)
{
}
void HandleThievingSkillFindRemoveTrap(void)
{
}
void HandleThievingSkillHearNoise(void)
{
}
void HandleThievingSkillHideInShadows(void)
{
}
void HandleThievingSkillMoveSilent(void)
{
}
void HandleThievingSkillOpenLock(void)
{
}
void HandleThievingSkillPickpocket(void)
{
}
void HandleThievingSkillReadLanguages(void)
{
}
void HandleUndeadType(void)
{
}
void HandleWealthGems(void)
{
}
void HandleWealthJewelry(void)
{
}
void HandleWealthPlatinum(void)
{
}
void HandleSpecialAbility01(void)
{
}
void HandleSpecialAbility02(void)
{
}
void HandleSpecialAbility03(void)
{
}
void HandleSpecialAbility04(void)
{
}
void HandleSpecialAbility05(void)
{
}
void HandleSpecialAbility06(void)
{
}
void HandleSpecialAbility07(void)
{
}
void HandleSpecialAbility08(void)
{
}
void HandleSpecialAbility09(void)
{
}
void HandleSpecialAbility10(void)
{
}
void HandleSpellsMemorized(void)
{
}


struct TAG_ENTRY
{
  const char *tag;
  void (*function)(void);
};

#define PROCESS_TAG(tag,func)  {tag, func},

TAG_ENTRY tagTable[] =
{
    PROCESS_TAG("ability_charisma_adjusted"                  ,HandleAbilityCharisma)
    PROCESS_TAG("ability_charisma_base"                      ,NOP)
    PROCESS_TAG("ability_constitution_adjusted"              ,HandleAbilityConstitution)
    PROCESS_TAG("ability_constitution_base"                  ,NOP)
    PROCESS_TAG("ability_intelligence_adjusted"              ,HandleAbilityIntelligence)
    PROCESS_TAG("ability_intelligence_base"                  ,NOP)
    PROCESS_TAG("ability_strength_adjusted"                  ,HandleAbilityStrength)
    PROCESS_TAG("ability_strength_base"                      ,NOP)
    PROCESS_TAG("ability_strength_extraordinary_adjusted"    ,NOP)
    PROCESS_TAG("ability_strength_extraordinary_percentage"  ,NOP)
    PROCESS_TAG("ability_wisdom_adjusted"                    ,HandleAbilityWisdom)
    PROCESS_TAG("ability_wisdom_base"                        ,NOP)
    PROCESS_TAG("ability_dexterity_adjusted"                 ,HandleAbilityDexterity)
    PROCESS_TAG("ability_dexterity_base"                     ,NOP)
    PROCESS_TAG("age_years"                                  ,HandleAge)
    PROCESS_TAG("alignment"                                  ,HandleAlignment)
    PROCESS_TAG("armor_class_adjusted"                       ,HandleArmorClass)
    PROCESS_TAG("armor_class_base"                           ,NOP)
    PROCESS_TAG("attack_%i_damage_bonus"                     ,HandleAttack)
    PROCESS_TAG("attack_%i_damage_dice_sides"                ,NOP)
    PROCESS_TAG("attack_%i_nbr_attacks_per_2_rounds"         ,NOP)
    PROCESS_TAG("attack_%i_num_damage_dice"                  ,NOP)
    PROCESS_TAG("attack_%i_unarmed_damage_bonus"             ,NOP)
    PROCESS_TAG("attack_%i_unarmed_damage_dice_sides"        ,NOP)
    PROCESS_TAG("attack_%i_unarmed_nbr_attacks_per_2_rounds" ,NOP)
    PROCESS_TAG("attack_%i_unarmed_num_damage_dice"          ,NOP)
    PROCESS_TAG("class"                                      ,HandleClass)
    PROCESS_TAG("combat_mode"                                ,HandleCombatMode)
    PROCESS_TAG("combat_status"                              ,HandleCombatStatus)
    PROCESS_TAG("cure_disease_allowed"                       ,HandleCureDiseaseAllowed)
    PROCESS_TAG("cure_disease_count"                         ,NOP)
    PROCESS_TAG("current_status"                             ,HandleCurrentStatus)
    PROCESS_TAG("encumbrance_in_coins"                       ,HandleEncumbranceInCoins)
    PROCESS_TAG("equip_item_%i"                              ,HandleEquipItem)
    PROCESS_TAG("equip_item_%i_count"                        ,NOP)
    PROCESS_TAG("equip_item_%i_id"                           ,NOP)
    PROCESS_TAG("equip_num_hands_full"                       ,HandleEquipNumHandsFull)
    PROCESS_TAG("experience_current"                         ,HandleExperienceCurrent)
    PROCESS_TAG("experience_granted_for_killing"             ,HandleExperienceGrantedForKilling)
    PROCESS_TAG("experience_predrain"                        ,HandleExperiencePredrain)
    PROCESS_TAG("gender"                                     ,HandleGender)
    PROCESS_TAG("hitpoints_adjusted"                         ,HandleHitpoints)
    PROCESS_TAG("hitpoints_base"                             ,NOP)
    PROCESS_TAG("hitpoints_maximum"                          ,NOP)
    PROCESS_TAG("hitpoints_predrain"                         ,NOP)
    PROCESS_TAG("icon_index"                                 ,HandleIconIndex)
    PROCESS_TAG("id"                                         ,HandleIconId)
    PROCESS_TAG("item_bundles_carried"                       ,HandleItemBundlesCarried)
    PROCESS_TAG("item_mask_can_equip_cleric"                 ,HandleItemMaskCanEquipCleric)
    PROCESS_TAG("item_mask_can_equip_fighter"                ,HandleItemMaskCanEquipFighter)
    PROCESS_TAG("item_mask_can_equip_knight"                 ,HandleItemMaskCanEquipKnight)
    PROCESS_TAG("item_mask_can_equip_magic_user"             ,HandleItemMaskCanEquipMagicUser)
    PROCESS_TAG("item_mask_can_equip_paladin_ranger"         ,HandleItemMaskCanEquipPaladinRanger)
    PROCESS_TAG("item_mask_can_equip_thief"                  ,HandleItemMaskCanEquipThief)
    PROCESS_TAG("level_current"                              ,HandleLevelCurrent)
    PROCESS_TAG("level_current_cleric"                       ,HandleLevelCurrentCleric)
    PROCESS_TAG("level_current_fighter"                      ,HandleLevelCurrentFighter)
    PROCESS_TAG("level_current_knight"                       ,HandleLevelCurrentKnight)
    PROCESS_TAG("level_current_mage"                         ,HandleLevelCurrentMage)
    PROCESS_TAG("level_current_paladin"                      ,HandleLevelCurrentPaladin)
    PROCESS_TAG("level_current_ranger"                       ,HandleLevelCurrentRanger)
    PROCESS_TAG("level_current_thief"                        ,HandleLevelCurrentThief)
    PROCESS_TAG("level_fighter_sweep"                        ,HandleLevelFighterSweep)
    PROCESS_TAG("level_former_class"                         ,HandleLevelFormerClass)
    PROCESS_TAG("level_preclasschange_cleric"                ,HandleLevelPreClassChangeCleric)
    PROCESS_TAG("level_preclasschange_fighter"               ,HandleLevelPreClassChangeFighter)
    PROCESS_TAG("level_preclasschange_knight"                ,HandleLevelPreClassChangeKnight)
    PROCESS_TAG("level_preclasschange_mage"                  ,HandleLevelPreClassChangeMage)
    PROCESS_TAG("level_preclasschange_paladin"               ,HandleLevelPreClassChangePaladin)
    PROCESS_TAG("level_preclasschange_ranger"                ,HandleLevelPreClassChangeRanger)
    PROCESS_TAG("level_preclasschange_thief"                 ,HandleLevelPreClassChangeThief)
    PROCESS_TAG("level_predrain_cleric"                      ,HandleLevelPreDrainCleric)
    PROCESS_TAG("level_predrain_fighter"                     ,HandleLevelPreDrainFighter)
    PROCESS_TAG("level_predrain_knight"                      ,HandleLevelPreDrainKnight)
    PROCESS_TAG("level_predrain_mage"                        ,HandleLevelPreDrainMage)
    PROCESS_TAG("level_predrain_paladin"                     ,HandleLevelPreDrainPaladin)
    PROCESS_TAG("level_predrain_ranger"                      ,HandleLevelPreDrainRanger)
    PROCESS_TAG("level_predrain_thief"                       ,HandleLevelPreDrainThief)
    PROCESS_TAG("level_ready_to_train"                       ,HandleLevelReadyToTrain)
    PROCESS_TAG("magic_resist_base_percent"                  ,HandleMagicResist)
    PROCESS_TAG("magic_resist_bonus"                         ,NOP)
    PROCESS_TAG("morale_base"                                ,HandleMorale)
    PROCESS_TAG("movement_adjusted"                          ,NOP)
    PROCESS_TAG("movement_base"                              ,HandleMovement)
    PROCESS_TAG("name"                                       ,NOP)
    PROCESS_TAG("party_index"                                ,NOP)
    PROCESS_TAG("race"                                       ,HandleRace)
    PROCESS_TAG("save_vs_breathweapon"                       ,HandleSaveVsBreathWeapon)
    PROCESS_TAG("save_vs_paralysis_poison_deathmagic"        ,HandleSaveVsParalysisPoisonDeathmagic)
    PROCESS_TAG("save_vs_petrification_polymorph"            ,HandleSaveVsPetrificationPolymorph)
    PROCESS_TAG("save_vs_rod_staff_wand"                     ,HandleSaveVsRodStaffWand)
    PROCESS_TAG("save_vs_spell"                              ,HandleSaveVsSpell)
    PROCESS_TAG("size_icon"                                  ,HandleSizeIcon)
    PROCESS_TAG("size_large_even_if_icon_1x1"                ,HandleSizeLargeEvenIfIcon1x1)
    PROCESS_TAG("special_flag_affected_by_dispel_evil"       ,HandleSpecialFlagAffectedByDispelEvil)
    PROCESS_TAG("special_flag_can_be_held_or_charmed"        ,HandleSpecialFlagCanBeHeldOrCharmed)
    PROCESS_TAG("special_flag_dwarf_has_hit_bonus"           ,HandleSpecialFlagDwarfHasHitBonus)
    PROCESS_TAG("special_flag_extra_dmg_from_ranger"         ,HandleSpecialFlagExtraDmgFromRanger)
    PROCESS_TAG("special_flag_gnome_has_hit_bonus"           ,HandleSpecialFlagGnomeHasHitBonus)
    PROCESS_TAG("special_flag_immune_to_confusion"           ,HandleSpecialFlagImmuneToConfusion)
    PROCESS_TAG("special_flag_immune_to_death_magic"         ,HandleSpecialFlagImmuneToDeathMagic)
    PROCESS_TAG("special_flag_immune_to_decapitation_from_vorpal_sword"       
                                                             ,HandleSpecialFlagImmuneToDecapitationFromVorpalSword)
    PROCESS_TAG("special_flag_immune_to_poison"              ,HandleSpecialFlagImmuneToPoison)
    PROCESS_TAG("special_flag_is_a_animal"                   ,HandleSpecialFlagIsAAnimal)
    PROCESS_TAG("special_flag_is_a_mammal"                   ,HandleSpecialFlagIsAMammal)
    PROCESS_TAG("special_flag_is_a_snake"                    ,HandleSpecialFlagIsASnake)
    PROCESS_TAG("special_flag_is_a_true_giant"               ,HandleSpecialFlagIsATrueGiant)
    PROCESS_TAG("special_flag_penalty_to_hit_dwarf"          ,HandleSpecialFlagPenaltyToHitDwarf)
    PROCESS_TAG("special_flag_penalty_to_hit_gnome"          ,HandleSpecialFlagPenaltyToHitGnome)
    PROCESS_TAG("spells_num_cleric_level_1"                  ,HandleNumSpellCleric)
    PROCESS_TAG("spells_num_cleric_level_2"                  ,NOP)
    PROCESS_TAG("spells_num_cleric_level_3"                  ,NOP)
    PROCESS_TAG("spells_num_cleric_level_4"                  ,NOP)
    PROCESS_TAG("spells_num_cleric_level_5"                  ,NOP)
    PROCESS_TAG("spells_num_cleric_level_6"                  ,NOP)
    PROCESS_TAG("spells_num_cleric_level_7"                  ,NOP)
    PROCESS_TAG("spells_num_druid_level_1"                   ,HandleNumSpellDruid)
    PROCESS_TAG("spells_num_druid_level_2"                   ,NOP)
    PROCESS_TAG("spells_num_druid_level_3"                   ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_1"               ,HandleNumSpellMagicUser)
    PROCESS_TAG("spells_num_magicuser_level_2"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_3"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_4"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_5"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_6"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_7"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_8"               ,NOP)
    PROCESS_TAG("spells_num_magicuser_level_9"               ,NOP)
    PROCESS_TAG("thaco_adjusted"                             ,HandleTHAC0)
    PROCESS_TAG("thaco_base"                                 ,NOP)
    PROCESS_TAG("thieving_skill_climb_walls"                 ,HandleThievingSkillClimbWalls)
    PROCESS_TAG("thieving_skill_find_remove_trap"            ,HandleThievingSkillFindRemoveTrap)
    PROCESS_TAG("thieving_skill_hear_noise"                  ,HandleThievingSkillHearNoise)
    PROCESS_TAG("thieving_skill_hide_in_shadows"             ,HandleThievingSkillHideInShadows)
    PROCESS_TAG("thieving_skill_move_silent"                 ,HandleThievingSkillMoveSilent)
    PROCESS_TAG("thieving_skill_openlock"                    ,HandleThievingSkillOpenLock)
    PROCESS_TAG("thieving_skill_pickpocket"                  ,HandleThievingSkillPickpocket)
    PROCESS_TAG("thieving_skill_read_languages"              ,HandleThievingSkillReadLanguages)
    PROCESS_TAG("undead_type"                                ,HandleUndeadType)
    PROCESS_TAG("wealth_num_gems"                            ,HandleWealthGems)
    PROCESS_TAG("wealth_num_jewelry"                         ,HandleWealthJewelry)
    PROCESS_TAG("wealth_num_platinum"                        ,HandleWealthPlatinum)
    PROCESS_TAG("special_ability_01"                         ,HandleSpecialAbility01)
    PROCESS_TAG("special_ability_02"                         ,HandleSpecialAbility02)
    PROCESS_TAG("special_ability_03"                         ,HandleSpecialAbility03)
    PROCESS_TAG("special_ability_04"                         ,HandleSpecialAbility04)
    PROCESS_TAG("special_ability_05"                         ,HandleSpecialAbility05)
    PROCESS_TAG("special_ability_06"                         ,HandleSpecialAbility06)
    PROCESS_TAG("special_ability_07"                         ,HandleSpecialAbility07)
    PROCESS_TAG("special_ability_08"                         ,HandleSpecialAbility08)
    PROCESS_TAG("special_ability_09"                         ,HandleSpecialAbility09)
    PROCESS_TAG("special_ability_10"                         ,HandleSpecialAbility10)
    PROCESS_TAG("spells_memorized_%i"                        ,HandleSpellsMemorized)
    {"", NOP}
};

bool TagMatch(const char *pattern, const char *tag)
{
  // Pattern can have up to three parts.
  // [leftTag [+ %i]] + rightTag
  // The integer is placed in 'instance'
  int i, j, startCol;
  i = 0;
  j = 0;
  startCol = 0;
  leftTag.Empty();
  rightTag.Empty();
  for (;;)
  {
    if (tag[j] == pattern[i])
    {
      if (pattern[i] == 0)
      {
        rightTag = CString(tag+startCol, i-startCol);
        return true;
      };
      i++;
      j++;
    }
    else
    {
      if (pattern[i] == '%')
      {
        i++;
        if (pattern[i] == 'i')
        {
          instance = 0;
          while ((tag[j] >= '0') && (tag[j] <= '9'))
          {
            instance = 10*instance + tag[j] - '0';
            j++;
          };
          i++;
        }
        else
        {
          return false;
        };
      }
      else
      {
        return false;
      };
    };
  };
}

void DeleteDuplicateItems(JReader& monster, MONSTER_DATA *pMonster)
{
  // **********************************************************
  //      
  //         Remove duplicate items
  //         For each item in json file (monster), delete a 
  //         matching item in default monsters file (pMonster)
  //
  // **********************************************************
  int i, j, n;
  n = pMonster->key.GetSize();
  for (j = 0; j < 10; j++)
  {
    CString tag, val;
    tag.Format("equip_item_%02d", j);
    val = monster.Fetch_String(tag);
    if (val.IsEmpty()) continue;
    if (val == "Plate Mail +1")
    {
      int kkk = 1;
    };
    val = UniqueItemName(val);
    for (i = 0; i < n; i++)
    {
      if (pMonster->key[i] == "item")
      {
        if (pMonster->value[i] == val)
        {
          pMonster->key[i] = "//item (duplicate)";
          break;
        };
      };
    };
  };
}


void ConvertOneMonster(JReader& monster)
{
  int i, n;
  CString monsterName;
  mon = &monster;
  monster.StartList(DBGID_oneMonster);

  monsterName = monster.Fetch_String("name");
  if (monsterName == "VALA")
  {
    int kkk = 1;
  };
  n = monsterData.GetSize();
  for (i=0; i<n; i++)
  {
    int j, m;
    pMonster = &monsterData[i];
    m = pMonster->key.GetSize();
    for (j=0; j<m; j++)
    {
      if (pMonster->key[j] == "name")
      {
        if (pMonster->value[j].CompareNoCase(monsterName) == 0)
        {
          break;
        };
      };
    };
    if (j != m) break;
  }
  if (i == n)
  {
    CString msg;
    msg.Format("JSON file references non-existent default monster \"%s\"", monsterName);
    monster.PrintError(msg);
    if (n > 1) // Skip template
    {
      int m, j;
      m = monsterData[1].key.GetSize();
      for (j=0; j<m; j++)
      {
        if (monsterData[1].key[j] == "name")
        {
          monsterData.SetSize(n+1);
          monsterData[n].key.Append(monsterData[1].key);
          monsterData[n].value.Append(monsterData[1].value);
          monsterData[n].value[j] = monsterName;
          pMonster = &monsterData[i];
          n++;
          pMonster->UpdateLine("icon file", "");
          pMonster->UpdateLine("treat HD as hit points", "no");
          break;
        };
      };
    };
  };
  if (i == n)
  {
    monster.EndList(DBGID_oneMonster);
    return;
  };

  // **********************************************************
  //      
  //         Remove duplicate items
  //         For each item in json file, delete a matching item in default monsters file
  //
  // **********************************************************
  DeleteDuplicateItems(monster, pMonster);



  {
    CString line;
    line.Format("%d", monster.LineNum());
    pMonster->UpdateLine("//JSON Line", CString(line));
  };

  pMonster->RenameLine("attack", "//attack");
  //pMonster->RenameLine("immunity", "//immunity");
  for (; 
       !monster.CurrentTag().IsEmpty();
       monster.NextTag())
  {
    tag   = monster.CurrentTag();
    if ((monsterName == "TIBERUS") && (tag == "race"))
    {
      int kkk = 1;
    };
    tagValue = monster.CurrentValue();
    for (i=0; tagTable[i].tag[0]!=0; i++)
    {
      if (TagMatch(tagTable[i].tag, tag))
      {
        (*tagTable[i].function)();
        break;
      };
    };
    if (tagTable[i].tag[0] == 0)
    {
      CString msg;
      msg.Format("Unrecognized tag in JSON monster data = \"%s\"", tag);
      monster.PrintError(msg);
    };
  };
  monster.EndList(DBGID_oneMonster);
};


void ReadDCDefaultMonsters(FILE *out)
{
  FILE *f;
  char *line;
  int len;
  bool copyComments = true;
#pragma warning (suppress:4996)
  f = fopen(binPath + "FRUA_Conversion_monsters.txt", "r");
  if (f == NULL)
  {
    char line[200];
    printf("Cannot open \"FRUA_Conversion_monsters.txt\"\n");
    printf("Press Enter ---->");
    fgets(line,199,stdin);
    printf("\n");
    return;
  };
  line = (char *)malloc(100000);
  while (fgets(line, 99999, f) != NULL)
  {
    len = strlen(line);
    while ( (len > 0) && (line[len-1] == '\n'))
    {
      len--;
      line[len] = 0;
    };
    if (len < 2) continue;
    if ((line[0] == '/') && (line[1] == '/'))
    {
      if (copyComments)
      {
        fprintf(out, "%s\n", line);
      };
      continue;
    }
    else
    {
      copyComments = false;
    };
    if (len < 8) continue;
    if (memcmp(line, "\\(BEGIN)", 8) == 0)
    {
      int i;
      i = monsterData.GetSize();
      monsterData.SetSize(i + 1);
      monsterData[i].key.SetSize(1);
      monsterData[i].value.SetSize(1);
      monsterData[i].key[0] = "//JSON Line";
      monsterData[i].value[0] = "????";
      while (fgets(line, 99999, f) != NULL)
      {
        int col, len, n;
        char *equal;
        CString strEqual;
        len = strlen(line);
        while ((len > 0) && ((line[len-1] == '\n')||(line[len-1] == ' ')))
        {
          len--;
          line[len] = 0;
        };
        if ( (len == 6) && (memcmp(line, "\\(END)", 6) == 0)) 
        {
          break;
        };
        equal = strchr(line, '=');
        if (equal == NULL) continue;
        col = equal - line ;
        line[col] = 0;
        equal++;
        while ((col > 0) && (line[col-1] == ' ')) line[--col] = 0;
        if (col < 2) continue;
        n = monsterData[i].key.GetSize();
        monsterData[i].value.SetSize(n+1);
        monsterData[i].key.SetSize(n+1);
        while (*equal == ' ') equal++;
        while (*line == ' ') line++;
        strEqual = equal;
        if (strcmp(line,"item")== 0)
        {
          // Make sure the item exists.
          // Rename it if that makes sense.
            strEqual = UniqueItemName(strEqual);
        };
        monsterData[i].key[n] = CString(line);
        monsterData[i].value[n] = CString(strEqual);
      };
      pMonster = &monsterData[i];
      pMonster->RenameLine("classes", "gclass");
    };
  };
  free(line);
};


void ConvertMonsters(JReader& jr)
{
  if ( f != NULL)
  {
    die("Internal error in Monsters.cpp.  f not null");
  };
#pragma warning (suppress:4996)
  f = fopen(jsonPath + "monsters.txt", "w");
  fprintf(f,"// Monster database file\n");
  fprintf(f,"// The line above **must** be the first line of the monsters file!!!\n\n");

  fprintf(f,"// FRUA Export Version %s:%s\n", (LPCSTR)FRUAExportDate, (LPCSTR)FRUAExportTime);
  fprintf(f,"// ConvertFRUA version %s\n", (LPCSTR)ConvertFRUAVersion);
  //monsterList.RemoveAll();
  ReadDCDefaultMonsters(f);
  while (jr.Optional(), jr.NextEntry())
  {
    JReader monster(jr);
    ConvertOneMonster(monster);
  };
  {
    int i, n;
    n = monsterData.GetSize();
    for (i=0; i<n; i++)
    {
      int j, m;
      CString monsterName;
      pMonster = &monsterData[i];
      j = pMonster->FindLine("//combat mode");
      if ((j >= 0) && (pMonster->value[j] == "npc"))
      {
        continue; //Skip NPC. Do them later.
      };
      fprintf(f,"\n\\(BEGIN)\n");
      m = monsterData[i].key.GetSize();
      for (j = 0; j < m; j++)
      {
        if (monsterData[i].key[j] == "name")
        {
          monsterName = monsterData[i].value[j];
          if (monsterName == "DROW CHAMPION")
          {
            int kkk = 1;
          };
          break;
        };
      };
      for (j = 0; j < m; j++)
      {
        if (monsterData[i].key[j] == "icon file")
        {
          ARTMAP *pArt;
          CString iconFilename;
          pArt = SearchFRUAArtMap(monsterName, "Icon");
          if (pArt != NULL)
          {
            iconFilename = pArt->strings[1] + ',' + pArt->strings[3];
          }
          else
          {
            iconFilename = monsterData[i].value[j];
            if (iconFilename.IsEmpty())
            {
              // Our last hope of providing a proper filename
              iconFilename = CamelCap(monsterName);
              iconFilename.Remove(' ');
              iconFilename = CString("icon_") + iconFilename + ".png,0,2,48,48,0,1,2";
            };
          };
          Line("icon file", iconFilename);
          continue;
        }
        if (monsterData[i].key[j] == "name")
        {
          Line(monsterData[i].key[j], CapitalizeMonster(monsterData[i].value[j]));
        }
        else if (monsterData[i].key[j] == "Race")
        {
          Line(monsterData[i].key[j], CapitalizeRace(monsterData[i].value[j]));
        }
        else if (monsterData[i].key[j] == "Class")
        {
          Line(monsterData[i].key[j], CapitalizeClass(monsterData[i].value[j]));
        }
        else if (monsterData[i].key[j] == "item")
        {
          Line(monsterData[i].key[j], CapitalizeItem(monsterData[i].value[j]));
        }
        else
        {
          Line(monsterData[i].key[j], monsterData[i].value[j]);
        }
      };
    fprintf(f,"\\(END)\n");
    };
  };
  fclose(f);
  f = NULL;
  // *****************************************************
  // **************  Time to do the NPCs *****************
  // *****************************************************
  {
    int i, n;
    n = monsterData.GetSize();
    for (i = 0; i<n; i++)
    {
      int j;
      pMonster = &monsterData[i];
      j = pMonster->FindLine("//combat mode");
      if ((j < 0) || (pMonster->value[j] != "npc"))
      {
        continue; //Skip non-NPC. We already did them.
      };
      {
        CHARACTER ch;
        ch.ExportNPC(pMonster);
      }
    };
  };
}
