#pragma once

enum IF_KEYWORD_INDEX
{
  /* character keywords */
  CHAR_BASE = 0,
  CHAR_NAME = 1,
  CHAR_AC = 2,
  CHAR_HITPOINTS = 3,
  CHAR_THAC0 = 4,
  CHAR_ADJTHAC0 = 5,
  CHAR_RDYTOTRAIN = 6,
  //CHAR_CLERICEXP=6,
  //CHAR_MAGICUSEREXP=7,
  CHAR_ADJAC = 7,
  CHAR_EFFAC = 8,
  //CHAR_FIGHTEREXP=8,
  //CHAR_RANGEREXP=9,
  //CHAR_THIEFEXP=10,
  //CHAR_DRUIDEXP=11,
  //CHAR_PALADINEXP=12,
  CHAR_AGE = 9,
  CHAR_MAXAGE = 10,
  CHAR_MAXMOVE = 11,
  CHAR_ADJUSTED_STR = 12,
  CHAR_STR = 12,
  CHAR_ADJUSTED_STRMOD = 13,
  CHAR_STRMOD = 13,
  CHAR_ADJUSTED_INT = 14,
  CHAR_INT = 14,
  CHAR_ADJUSTED_WIS = 15,
  CHAR_WIS = 15,
  CHAR_ADJUSTED_DEX = 16,
  CHAR_DEX = 16,
  CHAR_ADJUSTED_CON = 17,
  CHAR_CON = 17,
  CHAR_ADJUSTED_CHA = 18,
  CHAR_CHA = 18,
  CHAR_MAXENC = 19,
  CHAR_ENC = 20,
  CHAR_GENDER = 21,
  CHAR_CLASS = 22,
  CHAR_ALIGNMENT = 23,
  CHAR_STATUS = 24,
  CHAR_UNDEAD = 25,
  CHAR_SIZE = 26,
  CHAR_MAGICRESIST = 27,
  CHAR_NBRHITDICE = 28,
  CHAR_NBRATTACKS = 29,
  CHAR_MORALE = 30,
  CHAR_ALLOWPLAYERCONTROL = 31,
  CHAR_DETECTINVISIBLE = 32,
  CHAR_DETECTTRAPS = 33,
  CHAR_DAMAGEBONUS = 34,
  CHAR_CHARTYPE = 35,
  CHAR_COINAMOUNT1 = 36,
  CHAR_COINAMOUNT2 = 37,
  CHAR_COINAMOUNT3 = 38,
  CHAR_COINAMOUNT4 = 39,
  CHAR_COINAMOUNT5 = 40,
  CHAR_COINAMOUNT6 = 41,
  CHAR_COINAMOUNT7 = 42,
  CHAR_COINAMOUNT8 = 43,
  CHAR_COINAMOUNT9 = 44,
  CHAR_COINAMOUNT10 = 45,
  CHAR_GEMAMOUNT = 46,
  CHAR_JEWELRYAMOUNT = 47,
  CHAR_ISMAMMAL = 48,
  CHAR_ISANIMAL = 49,
  CHAR_ISSNAKE = 50,
  CHAR_ISGIANT = 51,
  CHAR_ISALWAYSLARGE = 52,
  CHAR_HASDWARFACPENALTY = 53,
  CHAR_HASGNOMEACPENALTY = 54,
  CHAR_HASDWARFTHAC0PENALTY = 55,
  CHAR_HASGNOMETHAC0PENALTY = 56,
  CHAR_HASRANGERDMGPENALTY = 57,
  CHAR_HASPOISONIMMUNITY = 58,
  CHAR_HASDEATHIMMUNITY = 59,
  CHAR_HASCONFUSIONIMMUNITY = 60,
  CHAR_HASVORPALIMMUNITY = 61,
  CHAR_CANBEHELDORCHARMED = 62,
  CHAR_AFFECTEDBYDISPELEVIL = 63,
  CHAR_HITBONUS = 64,
  CHAR_MIRRORIMAGE = 65,

  /* party values */
  PARTY_BASE = 512,
  PARTY_FACING = 513,
  PARTY_DAYS = 514,
  PARTY_HOURS = 515,
  PARTY_MINUTES = 516,
  PARTY_ACTIVECHAR = 517,
  PARTY_MONEYAVAILABLE = 518,
  PARTY_TIME = 519,
  PARTY_LOCATION = 520,

  /* game values */
  GAME_BASE = 1024,
  GAME_CURRLEVEL = 1025,
  GAME_VERSION = 1026,
  GAME_COINNAME1 = 1027,
  GAME_COINNAME2 = 1028,
  GAME_COINNAME3 = 1029,
  GAME_COINNAME4 = 1030,
  GAME_COINNAME5 = 1031,
  GAME_COINNAME6 = 1032,
  GAME_COINNAME7 = 1033,
  GAME_COINNAME8 = 1034,
  GAME_COINNAME9 = 1035,
  GAME_COINNAME10 = 1036,
  GAME_GEMNAME = 1037,
  GAME_JEWELRYNAME = 1038,
  GAME_VAULTMONEYAVAILABLE = 1039
};


enum charStatusType
{
  Okay,        // 0
  Unconscious, // 1  less than one hp, but not losing hp (dying)
  Dead,        // 2  <= -10 hp
  Fled,        // 3 
  Petrified,   // 4
  Gone,        // 5
  Animated,    // 6
  TempGone,    // 7
  Running,     // 8
  Dying        // 9 less than one hp, and losing 1 hp per round (combat only)
};



const int MAX_SPELL_LEVEL = 9;

typedef LPCSTR specialAbilitiesType;
typedef DWORD ABILITYLIMITS;
typedef CString CHARACTER_ID;
typedef CString ITEM_ID;
typedef CString BASECLASS_ID;
typedef CString CLASS_ID;
typedef CString SPELL_ID;
typedef CString ABILITY_ID;
typedef CString RACE_ID;
typedef CString MONSTER_ID;
typedef CString SCHOOL_ID;
typedef CString SKILL_ID;
typedef CString BASECLASS_ID;

class SPELL_DATA;
class TRAITS;

class SKILL_ADJ
{
public:
  SKILL_ID skillID;
  CString  adjID;
  int      value;
  char     type;

  void Export(JWriter& jw);
  void Import(JReader& jr);
  BOOL operator ==(const SKILL_ADJ& sa) const
  {
    if (skillID != sa.skillID) return FALSE;
    if (adjID != sa.adjID)   return FALSE;
    if (value != sa.value)   return FALSE;
    if (type != sa.type)    return FALSE;
    return TRUE;
  };
  BOOL operator >(const SKILL_ADJ& sa) const
  {
    if (skillID > sa.skillID) return TRUE;
    if (skillID < sa.skillID) return FALSE;
    if (adjID   > sa.adjID)   return TRUE;
    return FALSE;
  };
};


class BASECLASS_STATS
{
public:
  BASECLASS_STATS(void);

  BASECLASS_ID baseclassID;
  int currentLevel;
  int temp__origLevel; // Temporary....not serialized
  int previousLevel;
  int preDrainLevel;
  int experience;

  void Export(JWriter& jw);
  void Import(JReader& jr);

  BOOL operator ==(const BASECLASS_STATS& bcs) const
  {
    if (baseclassID != bcs.baseclassID)   return FALSE;
    if (currentLevel != bcs.currentLevel)  return FALSE;
    if (previousLevel != bcs.previousLevel) return FALSE;
    if (preDrainLevel != bcs.preDrainLevel) return FALSE;
    if (experience != bcs.experience)    return FALSE;
    return TRUE;
  };
};


class SCHOOL_ABILITY
{
public:
  SCHOOL_ABILITY(void) { Clear(); };
  void Clear(void)
  {
    int i;
    for (i = 0; i<MAX_SPELL_LEVEL; i++)
    {
      base[i] = 0;
      bonus[i] = 0;
      baseclassLevel[i] = 0;
    };
    maxSpellLevel = 0;
    maxSpells = 0;
  };

  SCHOOL_ID schoolID;
  int maxSpellLevel; // Max spell level based on ability score.
  int maxSpells;     // Total number of spells based on ability score.
  int base[MAX_SPELL_LEVEL];
  int bonus[MAX_SPELL_LEVEL];
  int baseclassLevel[MAX_SPELL_LEVEL];
};




class SPELL_ABILITY
{
public:
  void Clear(void) { valid = FALSE; schoolAbilities.RemoveAll(); };
  void operator =(const SPELL_ABILITY& src);

  //For each spell school we will record
  // * Highest spell level
  // * Number of spells that can be memorized at each spell level
  BOOL valid;
  mCArray<SCHOOL_ABILITY, SCHOOL_ABILITY&> schoolAbilities;

  DEFINE_mCARRAY_ACCESS_FUNCTIONS(SchoolAbility,    /* array data name      */ \
    SCHOOL_ID,        /* Search variable type */ \
    schoolID,         /* search variable name */ \
    schoolAbilities,  /* array name           */ \
    SCHOOL_ABILITY,   /* array data type      */ \
    SPELL_ABILITY)    /* type of *this        */

};


struct MONSTER_DATA;
class CHARACTER //: public CObject
{
public:

  friend class CCharacter;
public:
  //  DECLARE_SERIAL( CHARACTER )

  CHARACTER(void);
  CHARACTER(const CHARACTER& src);
  ~CHARACTER(void);
  CHARACTER& operator=(const CHARACTER& src);
  BOOL operator==(const CHARACTER& src);
  BOOL IsSameCharacter(const CHARACTER& dude) const; // doesn't compare all member vars

  void Clear(BOOL IsConstructor = FALSE);
//#ifdef UAFEDITOR
  void Export(JWriter& jw);
  void Import(JReader& jr);
  void ExportNPC(MONSTER_DATA *pNPC);
    //#endif


  void getCharWeaponText(CString &wpn, CString &dmg);
  void getCharArmorText(CString &armor);
  CString getInfo(void);
  CString getItemList(int id);
  //int GetUniqueId(); 
  CHARACTER_ID CharacterID(void) const { CHARACTER_ID cid; cid = name; return cid; };

  //BOOL addCharacterItem(GLOBAL_ITEM_ID giID, int qty, int charges, BOOL id, int cost);
  BOOL addCharacterItem(const ITEM_ID& itemID, int qty, int charges, BOOL id, int cost);
  BOOL delCharacterItem(int index, int qty);
  //BOOL HasItem(GLOBAL_ITEM_ID giID);
  BOOL HasItem(const ITEM_ID& itemID);
  //void buyItem(GLOBAL_ITEM_ID giID, costFactorType type);
  void buyItem(const ITEM_ID& itemID, costFactorType type);
  void payForItem(int moneyCost, itemClassType moneyType, int gems = 0, int jewelry = 0);
  int  IsIdentified(int key, int num);
  bool CanReady(int index);
  BOOL toggleReadyItem(int item);
  void ReadyBestWpn(int dist, BOOL isLargeTarget);
#ifdef UAFEngine
  void ListShields(COMBAT_SUMMARY_COMBATANT *pcsc);
#endif
  void ReadyBestShield();
  void ReadyBestArmor();
  void ReadyBestAmmo(BOOL isLargeTarget);

  int poolCharacterGold();
  BOOL enoughMoney(int moneyCost, int gemCost = 0, int jewelryCost = 0, itemClassType moneyType = PlatinumType);
  BOOL CanCastSpells();
  BOOL CanMemorizeSpells(int circumstance);  // 0 = Magic menu display "MEMORIZE"
                                             // 1 = Resting - Should character memorize spells.
                                             //BOOL CanCastAsRanger() const { return ((GetClass() == Ranger) && (RangerLevel >= 8)); }
                                             //BOOL CanCastAsPaladin() const { return ((GetClass() == Paladin) && (PaladinLevel >= 9)); }
                                             //DWORD GetBestMemorizedHealingSpell(GLOBAL_SPELL_ID& index);

  BOOL CanBeModified();
  void generateNewCharacter(DWORD StartExperience, int StartExpType);
  WORD getAllowedAlignments(void) const;

  //void SetThiefSkillDexAdjustments();
  //void SetThiefSkillRaceAdjustments();
  void SetThiefSkills();
  int  GetThiefBackstabDamageMultiplier() const;
  int  GetThiefBackstabAttackAdjustment(void) const;
  void GetThiefSkillArmorAdustments() const;

  void UpdateSkill(int *abilityModifier,
    const CString& abilityName);


//  BOOL CanChangeToClass(const CLASS_DATA *pClass);
//  int  CreateChangeClassList(CArray<CLASS_ID, CLASS_ID&> *pClassArray);
  //void HumanChangeClass(classType newClass);
  //classType GetPreviousClass() const;
  BASECLASS_ID GetPreviousBaseclass(void) const;
  void HumanChangeClass(const CLASS_ID& classID);
  CLASS_ID GetPreviousClass() const;
  BYTE GetPreviousClassLevel() const;
  BOOL CanUsePrevClass() const;
  mutable int  temp__canUsePrevClass; // Not serialiized
                                      // -1=unknown;  0=FLASE;  1=TRUE
  BOOL IsDualClass() const;
  /*
  BOOL CanDualClassCleric() const;
  BOOL CanDualClassFighter() const;
  BOOL CanDualClassMagicUser() const;
  BOOL CanDualClassThief() const;
  BOOL CanDualClassDruid() const;
  BOOL CanDualClassRanger() const;
  BOOL CanDualClassPaladin() const;
  */

  //BOOL IsUsingClass(WORD ClassFlag);  
  BOOL IsUsingBaseclass(const BASECLASS_ID& baseclassID) const;

  //BOOL IsAlive()
  //{
  //  charStatusType stype = GetAdjStatus();
  //  return ((stype == Okay) || (stype == Unconscious) || (stype == Running) || (stype == Dying));
  //}

  //void GetContext(ActorType *pActor, WORD ClassFlag=0) const;

#ifdef UAFEngine
  void ClearAllItemCursedFlags();
  int RemoveAllSpellEffectsByLevel(int lvl); // removes all that match lvl
  int DispelSpellEffectsByLevel(int lvl); // checks dispel flag, removes all <= lvl
                                          //BOOL CastSpell(GLOBAL_SPELL_ID spell, bool abortIfSetPartyXY);
  BOOL CastSpell(const SPELL_ID& spellID, bool abortIfSetPartyXY, bool LayOrCureOrWhatever);
  void SpellActivate(const PENDING_SPELL &data,
    InvokeSpellOptions *invokeOptions,
    bool abortIfSetPartyXY,
    ToHitComputation *pToHitComputation);
  int InvokeSpellOnTarget(CHARACTER& targ,
    int activeSpellKey,
    //GLOBAL_SPELL_ID spellDbKey,
    const SPELL_ID& spellID,
    CString *displayText,
    BOOL *spellSucceeded,
    InvokeSpellOptions *invokeOptions,
    bool abortIfSetPartyXY,
    ToHitComputation *pToHitComputation);
  int InvokeLingerSpellOnTarget(CHARACTER& targ,
    int activeSpellKey,
    //GLOBAL_SPELL_ID spellDbKey,
    const SPELL_ID& spellID,
    CString *displayText,
    BOOL *spellSucceeded,
    InvokeSpellOptions *invokeOptions,
    bool abortIfSetPartyXY,
    ToHitComputation *pToHitComputation);

  void ApplySpellEffectAdjustments(DWORD /*flags*/, IF_KEYWORD_INDEX key, int &val) const;
  double ModifyByDouble(IF_KEYWORD_INDEX ifKey, double modifiecation);
  BOOL AddSpellEffect(SPELL_EFFECTS_DATA &data,
    const CHARACTER *pAttacker,
    InvokeSpellOptions *pInvokeOptions);
  BOOL AddLingeringSpellEffect(SPELL_EFFECTS_DATA &data, const CHARACTER *pAttacker);
  BOOL AddSpecAb(SPELL_EFFECTS_DATA &data);
  BOOL AddTemporaryEffect(const CString& attrName,
    const CString& timeUnits,
    int            duration,
    int            delta,
    const CString& text,
    const CString& source);
  BOOL RemoveTemporaryEffect(const CString& mask);
  BOOL CHARACTER::DoesSavingThrowSucceed(SPELL_DATA *pSdata,
    SAVING_THROW_DATA &stData,
    BOOL friendlyFire,
    CHARACTER *pCaster,
    CString *displayText);

  void CalcSpellEffectChangeValue(SPELL_DATA *spData,
    SPELL_EFFECTS_DATA &seData,
    BOOL friendlyFire,
    CHARACTER *pCaster);
  BOOL RemoveSpellByName(const CString &sname);

  BOOL RemoveSpellEffect(DWORD parent, SPELL_DATA *pSpell, bool endSpell);

  CString RemoveSpellEffect(const CString& SEIdentifier);
  void CheckForExpiredSpellEffects();

  CString RunSEScripts(const CString& scriptName);
  CString ForEachPossession(const CString& scriptName);
  void RemoveAllEffectsFor(const CString &AttrName);
  void RemoveSpecAb(SPELL_EFFECTS_DATA &data);
  DWORD CalcRestTime(void);
  void RemoveAllTargets();
  void InitTargeting(spellTargetingType type,
    BOOL canTargetFriend,
    BOOL canTargetEnemy,
    BOOL partyfriend,
    DWORD targs,
    DWORD range,
    DWORD width,
    DWORD height,
    BOOL  lingering);
  BOOL AddTarget(CHARACTER &targ, int range = 0);
  BOOL AddTargetSelf();
  BOOL IsAffectedBySpell(const SPELL_ID& SpellID);
  BOOL IsAffectedBySpellAttribute(const CString& SpellAttribName);
  void UpdateSpellForDamage(int DamageTaken);
  void UpdateSpellForAttacks(int AttacksTaken);
  SPELL_TARGETING_DATA targets;
#endif

#ifdef UAFEDITOR
  CString GetNPCEventText();
#endif

  // functions that access the attributes
  const CString& GetName() const { return name; }
  void SetName(const char *val);

  //  int GetPickPockets() const { return pickPockets; }
  //  int GetOpenLocks() const { return openLocks; }
  //  int GetFindTraps() const { return findRemoveTrap; }
  //  int GetMoveSilent() const { return moveSilent; }
  //  int GetHideInShadows() const { return hideInShadows; }
  //  int GetHearNoise() const { return hearNoise; }
  //  int GetClimbWalls() const { return climbWalls; }
  //  int GetReadLanguages() const { return readLanguages; }
  //  int GetAdjPickPockets(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjOpenLocks(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjFindTraps(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjMoveSilent(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjHideInShadows(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjHearNoise(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjClimbWalls(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  int GetAdjReadLanguages(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  void SetPickPockets(int val) { val=min(100,val);val=max(0,val);pickPockets=val; }
  //  void SetOpenLocks(int val) { val=min(100,val);val=max(0,val);openLocks=val; }
  //  void SetFindTraps(int val) { val=min(100,val);val=max(0,val); findRemoveTrap=val; }
  //  void SetMoveSilent(int val) { val=min(100,val);val=max(0,val);moveSilent=val; }
  //  void SetHideInShadows(int val) { val=min(100,val);val=max(0,val);hideInShadows=val; }
  //  void SetHearNoise(int val) { val=min(100,val);val=max(0,val);hearNoise=val; }
  //  void SetClimbWalls(int val) { val=min(100,val);val=max(0,val);climbWalls=val; }
  //  void SetReadLanguages(int val) { val=min(100,val);val=max(0,val);readLanguages=val; }

  //  BYTE GetOpenDoors() const { return openDoors; }
  //  BYTE GetOpenMagicDoors() const { return openMagicDoors; }
  //  BYTE GetBendBarsLiftGates() const { return BB_LG; }
  //  BYTE GetAdjOpenDoors(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  BYTE GetAdjOpenMagicDoors(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  BYTE GetAdjBendBarsLiftGates(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //  void SetOpenDoors(BYTE val) { val=min(100,val);openDoors=val; }
  //  void SetOpenMagicDoors(BYTE val) { val=min(100,val);openMagicDoors=val; }
  //  void SetBendBarsLiftGates(BYTE val) { val=min(100,val);BB_LG=val; }

  int DetermineMaxCureDisease() { m_iMaxCureDisease = 0; return m_iMaxCureDisease;/* not used yet */ }
  int GetMaxCureDisease() const { return m_iMaxCureDisease; }
  void SetMaxCureDisease(int val) { val = max(0, val); m_iMaxCureDisease = val; }
  int GetCureDisease() const { return m_iUsedCureDisease; }
  void SetCureDisease(int val) { val = max(0, val); val = min(m_iMaxCureDisease, val); m_iUsedCureDisease = val; }
  int IncCureDisease() { m_iUsedCureDisease++; m_iUsedCureDisease = min(m_iMaxCureDisease, m_iUsedCureDisease); return m_iUsedCureDisease; }
  BOOL HaveCureDisease() const { return ((m_iMaxCureDisease>0) && (m_iUsedCureDisease<m_iMaxCureDisease)); }

  int GetMorale() const { return morale; }
  //int GetAdjMorale(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetMorale(int val) { val = max(0, val); val = min(100, val); morale = val; }

  void DetermineUnarmedHitDice(); // for attacks without weapons
  void DetermineCharHitDice();
  int DetermineHitDiceBonus(const BASECLASS_ID& baseclassID);
  double GetNbrHD() const { return nbrHitDice; }
  void SetNbrHD(double val) { val = max(0, val); nbrHitDice = val; }

  float determineNbrAttacks();
  float GetNbrAttacks() const { return NbrAttacks; }
  void SetNbrAttacks(float val) { val = max(0, val); NbrAttacks = val; }

  //BYTE GetCurrentLevel(WORD ClassFlag=0) const;// 0 means return max level for all class types
  BYTE GetCurrentLevel(const BASECLASS_ID& baseclassID) const;// ID="" means return max level for all class types
                                                              //int  CurrentBaseclassLevel(unsigned int baseClass) const;
  int  CurrentBaseclassLevel(const BASECLASS_ID& baseclassID) const;
  /*
  BYTE GetPrevLevel(WORD ClassFlag) const;
  BYTE GetPreDrainLevel(WORD ClassFlag) const;
  void SetCurrentLevel(WORD ClassFlag, int lvl);
  void SetPrevLevel(WORD ClassFlag, int lvl);
  void SetPreDrainLevel(WORD ClassFlag, int lvl);
  int IncCurrentLevel(WORD ClassFlag, int inc=1);
  int IncPrevLevel(WORD ClassFlag, int inc=1);
  int IncPreDrainLevel(WORD ClassFlag, int inc=1);
  */
  BYTE GetPrevLevel(const BASECLASS_ID& baseclassID) const;
  BYTE GetPreDrainLevel(const BASECLASS_ID& baseclassID) const;
  void SetCurrentLevel(const BASECLASS_ID& baseclassID, int lvl);
  void SetPrevLevel(const BASECLASS_ID& baseclassID, int lvl);
  void SetPreDrainLevel(const BASECLASS_ID& baseclassID, int lvl);
  int IncCurrentLevel(const BASECLASS_ID& baseclassID, int inc = 1);
  int IncPrevLevel(const BASECLASS_ID& baseclassID, int inc = 1);
  int IncPreDrainLevel(const BASECLASS_ID& baseclassID, int inc = 1);


  int GetHitBonus() const { return hitBonus; }
  //int GetAdjHitBonus(GLOBAL_ITEM_ID weaponID, int distance, DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjHitBonus(const ITEM_ID& weaponID, int distance, DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //void SetHitBonus(int val);
  //int GetDmgBonus() const { return dmgBonus; }
  //int GetAdjDmgBonus(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //void SetDmgBonus(int val);

  void ComputeCharSavingThrows();
  int GetMagicResistance() const { return magicResistance; }
  //int GetAdjMagicResistance(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //void SetMagicResistance(int val);
  genderType GetGender() const { return gender; }
  //classType GetClass() const { return charClass; }
  CLASS_ID GetClass() const { return classID; }
  CString GetHighestLevelBaseclass(void);
  alignmentType GetAlignment() const { return alignment; }
  charStatusType GetStatus() const { return status; }
  //undeadType GetUndeadType() const { return undead; }
  CString GetUndeadType() const { return undeadType.IsEmpty() ? "none" : undeadType; }
  creatureSizeType GetSize() const { return creatureSize; }
  BOOL GetAllowInCombat() const { return allowInCombat; }

  //genderType GetAdjGender(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //classType GetAdjClass(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //CLASS_ID GetAdjClass(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //alignmentType GetAdjAlignment(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //charStatusType GetAdjStatus(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //undeadType GetAdjUndeadType(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
  //creatureSizeType GetAdjSize(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  BOOL GetIsFriendly() const;

  void SetGender(genderType val) { gender = val; }
  void SetGender(const CString& gender);
  //void SetClass(classType val);
  void SetClass(const CLASS_ID& classID);
  void SetAlignment(alignmentType val) { alignment = val; }
//  void SetStatus(charStatusType val) { status = val; if (status == Dead) m_spellEffects.RemoveAll(); }
  //void SetUndead(undeadType val) { undead=val; }
  void SetUndead(const CString& uType) { undeadType = uType; }
  void SetSize(creatureSizeType val) { creatureSize = val; }
  void SetAllowInCombat(BOOL allow) { allowInCombat = allow; }

  BOOL IsAlignmentEvil() const;
  BOOL IsAlignmentGood() const;

  int GetEncumbrance() const { return encumbrance; }
  void SetEncumbrance(int val) { val = max(0, val); encumbrance = val; }
  int determineEffectiveEncumbrance(); // compute enc for all non-magical inventory
  int determineEncumbrance();       // compute enc for all inventory
  int determineNormalEncumbrance(); // compute standard enc based on str (no penalty enc)
  int determineMaxEncumbrance();    // compute max enc allowed
  int GetMaxEncumbrance() const { return maxEncumbrance; }
  void SetMaxEncumbrance(int val) { val = max(0, val); maxEncumbrance = val; }
  //int GetAdjMaxEncumbrance(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;



 
 
  int GetPermStr()    const {return strength;};
  int GetPermStrMod() const {return strengthMod;};
  int GetPermInt()    const {return intelligence;};
  int GetPermWis()    const {return wisdom;};
  int GetPermDex()    const {return dexterity;};
  int GetPermCon()    const {return constitution;};
  int GetPermCha()    const {return charisma;};
  //int GetAdjStr(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjStrMod(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjInt(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjWis(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjDex(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjCon(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetAdjCha(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  int GetLimitedStr() const;
  int GetLimitedStrMod() const;
  int GetLimitedInt() const;
  int GetLimitedWis() const;
  int GetLimitedDex() const;
  int GetLimitedCon() const;
  int GetLimitedCha() const;
  void SetPermStr(int val);
  void SetPermStrMod(int val);
  void SetPermInt(int val);
  void SetPermWis(int val);
  void SetPermDex(int val);
  void SetPermCon(int val);
  void SetPermCha(int val);
  //int AddAdjStr     (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjStrMod  (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjInt     (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjWis     (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjDex     (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjCon     (int val, DELAY_TYPE delayType, int delayTime);
  //int AddAdjCha     (int val, DELAY_TYPE delayType, int delayTime);


  //BYTE GetAbility(abilityType type);
  BYTE GetAbilityScore(const CString& abilityName) const;

  int      GetSpellBookIndex(const SPELL_ID& spellID, BOOL checkMemorized) const;

  //ABILITYLIMITS GetAbilityLimits(abilityType abType) const; 
  ABILITYLIMITS GetAbilityLimits(const ABILITY_ID& abilityID) const;
  // Min/Max for this character
  // Four bytes packed into DWORD

  BOOL IsPartyMember() const { return ((type&IN_PARTY_TYPE)>0); }
  void SetPartyMember(BOOL flag = TRUE) { if (flag) type |= IN_PARTY_TYPE; else type &= (~IN_PARTY_TYPE); }

  BYTE GetType() const { return (type&(~IN_PARTY_TYPE)); }
  void SetType(BYTE flag)
  {
    /*remove high-bit first*/
    BOOL inparty = IsPartyMember();
    flag &= (~IN_PARTY_TYPE);
    type = flag;
    if (inparty) SetPartyMember(TRUE);
  }
#ifdef UAFEngine
  // These ModifyXXX functions dynamically alter character
  // values based on spell effects or special abilities.
  BOOL ModifyAttackRollDice(const CHARACTER *pTarget, const int num, const int  sides, int *pBonus) const;
  //BOOL ModifyAttackRollDiceForItem          (const CHARACTER *pTarget,  GLOBAL_ITEM_ID giID,const int num, const int  sides, int *pBonus, int distance) const;
  BOOL ModifyAttackRollDiceForItem(const CHARACTER *pTarget, const ITEM_ID& itemID, const int num, const int  sides, int *pBonus, int distance) const;
  BOOL ModifyAttackRollDiceAsTarget(const CHARACTER *pAttacker, const int num, const int  sides, int *pBonus) const;
  //BOOL ModifyAttackRollDiceForItemAsTarget  (const CHARACTER *pAttacker,GLOBAL_ITEM_ID giID,const int num, const int  sides, int *pBonus) const;
  BOOL ModifyAttackRollDiceForItemAsTarget(const CHARACTER *pAttacker, const ITEM_ID& itemID, const int num, const int  sides, int *pBonus) const;
  BOOL ModifyAttackDamageDice(const CHARACTER *pTarget, const int num, const int  sides, int *pBonus, BOOL *pNonLethal) const;
  //BOOL ModifyAttackDamageDiceForItem        (const CHARACTER *pTarget,  GLOBAL_ITEM_ID giID,const int num, const int  sides, int *pBonus, BOOL *pNonLethal, int distance) const;
  BOOL ModifyAttackDamageDiceForItem(const CHARACTER *pTarget, const ITEM_ID& itemID, const int num, const int  sides, int *pBonus, BOOL *pNonLethal, int distance) const;
  BOOL ModifyAttackDamageDiceAsTarget(const CHARACTER *pAttacker, const int num, const int  sides, int *pBonus, BOOL *pNonLethal) const;
  //void ModifyAttackDamageDiceForItemAsTarget(const CHARACTER *pAttacker,GLOBAL_ITEM_ID giID,const int num, const int  sides, int *pBonus, BOOL *pNonLethal) const;
  void ModifyAttackDamageDiceForItemAsTarget(const CHARACTER *pAttacker, const ITEM_ID& itemID, const int num, const int  sides, int *pBonus, BOOL *pNonLethal) const;
  BOOL ModifyAttackThac0(const CHARACTER *pTarget, int *pVal) const;
  BOOL ModifyAttackThac0AsTarget(const CHARACTER *pAttacker, int *pVal) const;
  BOOL ModifySaveRoll(const CHARACTER *pTarget, int *pRoll) const;
  BOOL ModifySaveRollAsTarget(const CHARACTER *pAttacker, int *pRoll) const;
private:
  //BOOL ModifyACAsTarget                     (const CHARACTER *pAttacker,int *pAC, GLOBAL_ITEM_ID giID) const;
  BOOL ModifyACAsTarget(const CHARACTER *pAttacker, int *pAC, const ITEM_ID& itemID) const;
public:


  CString FormatSpecAbMsg(DWORD sa_state);
#endif

  BOOL GetAutomatic() const { return automatic; }
  void SetAutomatic(BOOL flag) { automatic = flag; }
  //BOOL GetAdjAutomatic(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS);

  BOOL GetAllowPlayerControl() const { return allowPlayerControl; }
  void SetAllowPlayerControl(BOOL flag) { allowPlayerControl = flag; SetAutomatic(!allowPlayerControl); }
  //BOOL GetAdjAllowPlayerControl(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS);

  // These properties are only TRUE for a spell's
  // duration. The property will always be FALSE if a spell which
  // grants them is not active.
  //
  BOOL GetDetectingInvisible() const { return detectingInvisible; }
  void SetDetectingInvisible(BOOL flag) { detectingInvisible = flag; }
  //BOOL GetAdjDetectingInvisible(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  BOOL GetDetectingTraps() const { return detectingTraps; }
  void SetDetectingTraps(BOOL flag) { detectingTraps = flag; }
  //BOOL GetAdjDetectingTraps(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;

  // if such a spell is memorized, return char's spell book key
  //GLOBAL_SPELL_ID CanCastDetectMagic();
#ifdef SpellDetectMagic
  SPELL_ID CanCastDetectMagic();
#endif
  // if such a spell is memorized, return char's spell book key
  //GLOBAL_SPELL_ID CanCastIdentify();

  //raceType race(void) const {return m_race;};
  RACE_ID RaceID(void) const { return race; };
  //void race(raceType race);
  void RaceID(const RACE_ID& raceID) { race = raceID; };

  void getCharTHAC0();
  int GetTHAC0(void) const;
  //int GetAdjTHAC0(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetTHAC0(int val);

  // PRS 28 Feb 2010
  //int GetAC() const {return AC;};
  int GetBaseAC() const { return m_AC; };
  int GetEffectiveAC() const;  // m_AC plus adjustments for readied items.
                               //
  void SetCharBaseAC();
  //int GetAdjAC(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetAC(int val);
  int SetCharAC();

  void DetermineCharMaxHitPoints();
  void DetermineNewCharMaxHitPoints(DWORD randomSeed);
  int GetHitPoints() const;
  //int GetAdjHitPoints(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetHitPoints(int val);
  int  SetHitPoints(int val, int /*fakearoo*/, bool canFinishCasting);
  void RestoreMaxHitPoints();
  int GetMaxHitPoints() const;
  void SetMaxHitPoints(int val);
  void RestoreToBestCondition();

  int GetAge() const { return age; }
  //int GetAdjAge(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetAge(int val);
  //int GetBirthday() const { return birthday; }
  //void SetBirthday(int bday); // day 1-365
  int GetMaxAge() const { return maxAge; }
  //int GetAdjMaxAge(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void DetermineCharStartAge();
  void DetermineCharMaxAge();
  void SetMaxAge(int val) { maxAge = val; }

  int determineMaxMovement();
  BYTE GetMaxMovement() const { return maxMovement; }
  //BYTE GetAdjMaxMovement(DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  void SetMaxMovement(int val);


  int getCharExpWorth(); // total value, exp + items
  void giveCharacterExperience(int exp, BOOL UseLimits = TRUE); // split among classes
                                                                //int GetCurrExp(int classflag);
                                                                //int GetCurrExp(const CString& baseclassName);
  int GetCurrExp(const BASECLASS_ID& baseclassID);
  void ClearExperience(void);
  //void SetCurrExp(int classflag, int exp);
  //void SetCurrExp(const CString& baseclassName, int exp);
  int SetCurrExp(const BASECLASS_ID& baseclassID, int exp);

  /*
  void SetFighterExperience(int exp){FighterExperience = exp;};
  void SetClericExperience(int exp){ClericExperience = exp;};
  void SetRangerExperience(int exp){RangerExperience = exp;};
  void SetPaladinExperience(int exp){PaladinExperience = exp;};
  void SetMUExperience(int exp){FighterExperience = exp;};
  void SetThiefExperience(int exp){ThiefExperience = exp;};
  void SetDruidExperience(int exp){DruidExperience = exp;};
  */
  //void SetBaseclassExperience(const BASECLASS_ID& baseclassID, int experience);


  void ClearLevels(void);
  //void SetLevel(int classflag, int lvl);
  //void SetLevel(const CString& baseclassName, int lvl);
  void SetLevel(const BASECLASS_ID& baseclassID, int lvl);
  void SetLevel(int lvl);  // Set ALL baseclasses to this level.
                           //int  GetLevel(const CString& baseclassName);
  int  GetCurrLevel(const BASECLASS_ID& baseclassID) const;
  int  GetAllowedLevel(const BASECLASS_ID& baseclassID) const;
  //int IncCurrExp(int classflag, int exp); // +/- adjustment
  int IncCurrExp(const BASECLASS_ID& baseclassID, int exp); // +/- adjustment

                                                            /*
                                                            int GetAdjClericExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjFighterExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjMagicUserExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjThiefExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjRangerExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjPaladinExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetAdjDruidExp(DWORD flags=DEFAULT_SPELL_EFFECT_FLAGS) const;
                                                            int GetClericExp() const { return ClericExperience; }
                                                            int GetFighterExp() const { return FighterExperience; }
                                                            int GetMagicUserExp() const { return MUExperience; }
                                                            int GetThiefExp() const { return ThiefExperience; }
                                                            int GetRangerExp() const { return RangerExperience; }
                                                            int GetPaladinExp() const { return PaladinExperience; }
                                                            int GetDruidExp() const { return DruidExperience; }
                                                            */
  //int GetAdjBaseclassExp(const BASECLASS_ID& baseclassID, DWORD flags = DEFAULT_SPELL_EFFECT_FLAGS) const;
  //int GetBaseclassExp(const BASECLASS_ID& baseclassID);


  //int  GetAdjSpecAb(LPCTSTR sa, DWORD *pSource=NULL, GLOBAL_SPELL_ID *pSrcKey=NULL) const;
  //int  GetAdjSpecAb(LPCTSTR sa, DWORD *pSource = NULL, CString *pSpellName = NULL) const;
  void SetSpecAb(LPCTSTR sa, BYTE enable, DWORD flags);
  //void QueueUsedSpecAb(specialAbilitiesType sa, WORD src, GLOBAL_SPELL_ID key) const;
  void QueueUsedSpecAb(specialAbilitiesType sa, WORD src, const SPELL_ID& SpellID) const;
  void ClearQueuedSpecAb();

  //void AdjustEffectData(const char *akey, int val);
  void AdjustEffectData(const IF_KEYWORD_INDEX key, int val);

  BOOL IsMammal() const;
  BOOL IsAnimal() const;
  BOOL IsSnake() const;
  BOOL IsGiant() const;
  BOOL IsAlwaysLarge() const;

  BOOL HasDwarfACPenalty() const;
  BOOL HasGnomeACPenalty() const;
  BOOL HasDwarfTHAC0Penalty() const;
  BOOL HasGnomeTHAC0Penalty() const;
  BOOL HasRangerDmgPenalty() const;

  BOOL HasPoisonImmunity() const;
  BOOL HasDeathImmunity() const;
  BOOL HasConfusionImmunity() const;
  BOOL HasVorpalImmunity() const;

  BOOL CanBeHeldOrCharmed() const;
  BOOL AffectedByDispelEvil() const;

  //int uniqueKey;	   // unique id for NPC in NPC data table
  // Always equal to the internal key of the Ordered Queue entry.
  int preSpellNamesKey; // Just for conversion of old designs.

  int origIndex;     // id for npc or monster if added to party or combatData tables
  MONSTER_ID   monsterID;   // If this character is a monster
  CHARACTER_ID characterID; // If this character is an NPC
  void CharacterID(const CHARACTER_ID& id) { characterID = id; };

  BYTE uniquePartyID;// 0-7 party id, never changes, even when party order changes
  BOOL IsPreGen;     // means NPC is available to add to party at start
  BOOL CanBeSaved;   // allow saving NPC for later restore?

  BOOL HasLayedOnHandsToday; // Paladins allowed to heal self/others once per day

  int unarmedDieS;   // if not using a weapon
  int unarmedNbrDieS;
  int unarmedBonus;
  int unarmedDieL;
  int unarmedNbrDieL;

  BOOL DisableTalkIfDead;
  DWORD TalkEvent; // event chain used for 'Talk' menu 
  CString TalkLabel; // text used in menu to trigger talk event
  DWORD ExamineEvent;
  CString ExamineLabel;
  //BYTE ItemMask;  // determines which items can be readied
  // This is now determined by whether the character
  // has a baseclass listed in the items usableByBaseclass list.

  long unused; // was iconSurface;
  int iconIndex; // which icon to use - default is 1
  PIC_DATA icon;
  PIC_DATA smallPic;
  //const SPELL_EFFECTS_DATA *PeekAtSpellEffect(POSITION pos) const
  //{
  //  return & const_cast<CHARACTER*>(this)->m_spellEffects.GetAt(pos);
  //};
  void ProcessLingeringSpellEffects(void);
  //mCList<SPELL_EFFECTS_DATA, SPELL_EFFECTS_DATA&> m_spellEffects;
  SPECIAL_ABILITIES specAbs;
  CString RunCharacterScripts(
    LPCSTR scriptName,
  enum CBRESULT(*fnc)(enum CBFUNC func, CString *scriptResult, void *pkt),
    void *pkt
    ) const
  {
    return specAbs.RunScripts(scriptName,
      fnc,
      pkt,
      "CHARACTER",
      name);

  };

  // This character has a spellbook.
protected:
  spellBookType m_spellbook;

public:
  SPELL_ABILITY spellAbility;  // A summary of this character's spell abilities
                               // at his current baseclass levels and ability scores.
 // int     GetSpellCount(void) const { return m_spellbook.GetCount(); };
  void    ClearSpellbook(void) { m_spellbook.Clear(); };
  //   BOOL    GetSpell           (GLOBAL_SPELL_ID gsID, CHARACTER_SPELL &spell)
  //           {
  //             return m_spellbook.GetSpell(GetSpellBookKey(gsID, FALSE), spell);
  //           };
  //   BOOL    DecMemorized(GLOBAL_SPELL_ID gsID, int count)
  //           {
  //             return m_spellbook.DecMemorized(GetSpellBookKey(gsID, FALSE), count);
  //           };
  //BOOL    GetSpell           (const SPELL_ID& spellID, CHARACTER_SPELL &spell)
  //        {
  //          return m_spellbook.GetSpell(GetSpellBookID(spellID, FALSE), spell);
  //        };

 // BOOL     FetchCharacterSpell(const SPELL_ID& spellID, CHARACTER_SPELL *pCharSp) const
 // {
 //   return m_spellbook.FetchCharacterSpell(spellID, pCharSp);
 // };

  //int                     LocateCharacterSpell(const SPELL_ID& spellID) const
  //{
  //  return m_spellbook.LocateCharacterSpell(spellID);
  //};
  //const CHARACTER_SPELL *PeekCharacterSpell(int index) const
  //{
  //  return m_spellbook.PeekCharacterSpell(index);
  //};

  //CHARACTER_SPELL *GetCharacterSpell(int index)
  //{
  //  return m_spellbook.GetCharacterSpell(index);
  //};

  //BOOL     DecMemorized(const SPELL_ID& spellID, int count)
  //{
  //  //return m_spellbook.DecMemorized(GetSpellBookID(spellID, FALSE), count);
  //  return m_spellbook.DecMemorized(spellID, count);
  //};

  //int                  SpellsKnown(void) { return m_spellbook.SpellsKnown(); };
  //POSITION             GetFirstSpellPosition(void){return m_spellbook.GetHeadPosition();};
  //CHARACTER_SPELL&     GetNextSpell(POSITION& pos){return m_spellbook.GetNext(pos);};
  //CHARACTER_SPELL&     GetSpellAt(POSITION pos){return m_spellbook.GetSpellAt(pos);};
  //GLOBAL_SPELL_ID      GetSpellKeyAt(POSITION pos){return m_spellbook.GetSpellKeyAt(pos);};
  //SPELL_ID             GetSpellIDAt(POSITION pos)
  //{
  //  return m_spellbook.GetSpellIDAt(pos);
  //};
  //void                 SortSpells(void){m_spellbook.SortSpells();};
  //BOOL                 IsMemorized(GLOBAL_SPELL_ID gsID) const {return m_spellbook.IsMemorized(gsID);};
  //BOOL                 IsMemorized(const SPELL_ID& spellID) const
  //{
  //  return m_spellbook.IsMemorized(spellID);
  //};
  //BOOL                 IncAllMemorizedTime(int minuteInc, bool all)
  //{
  //  return m_spellbook.IncAllMemorizedTime(minuteInc, all);
  //};
  //   BOOL                 KnowSpell(WORD CasterClassFlag,
  //                                  WORD SpellClassFlag,
  //                                  //GLOBAL_SPELL_ID SpellDbKey,
  //                                  const SPELL_ID& spellID,
  //                                  int level,
  //                                  BOOL known)
  //                          {
  //                            return m_spellbook.KnowSpell( CasterClassFlag,
  //                                                          SpellClassFlag, 
  //                                                          //SpellDbKey,
  //                                                          spellID,
  //                                                          level, 
  //                                                          known);
  //                          };
  //BOOL                 KnowSpell(const BASECLASS_ID& baseclassID,
  //  const SCHOOL_ID& spellSchoolID,
  //  //GLOBAL_SPELL_ID SpellDbKey,
  //  const SPELL_ID& spellID,
  //  int level,
  //  BOOL known)
  //{
  //  return m_spellbook.KnowSpell(baseclassID,
  //    spellSchoolID,
  //    //SpellDbKey,
  //    spellID,
  //    level,
  //    known);
  //};
  //BOOL                 KnowSpell(const SPELL_DATA *pSpell,
  //  BOOL known)
  //{
  //  return m_spellbook.KnowSpell(pSpell, known);
  //};
  //void                 CopySpellbook(spellBookType& b) { m_spellbook = b; };
  //void                 UnselectIfNotMemorized(void) { m_spellbook.UnselectIfNotMemorized(); };
  //inline void          UseSpellLimits(BOOL b) { m_spellbook.spellLimits.UseLimits = b; };


  //BYTE MaxSpellsForLevel(WORD CharClass, int CharLevel, int SpellLevel, BYTE prime)
  //   BYTE MaxSpellsForLevel(const BASE_CLASS_DATA *pBaseclass, int CharLevel, int SpellLevel, BYTE prime)
  //   {
  //     return m_spellbook.spellLimits.MaxSpellsForLevel(pBaseclass, CharLevel, SpellLevel, prime);
  //   };

  //Added Dec 2010 - should eventually replace MaxSpellsForLevel
  //BYTE MaxSpellsForLevelAndSchool(int charBaseClass, int charLevel, int spellLevel, int prime, int spellSchool)
  //   BYTE MaxSpellsForLevelAndSchool(const BASE_CLASS_DATA *pBaseclass, 
  //                                   int baseclassLevel, 
  //                                   int spellLevel, 
  //                                   int prime, 
  //                                   const SCHOOL_ID& schoolID)
  //   {
  //     return m_spellbook.spellLimits.MaxSpellsForLevelAndSchool(pBaseclass, baseclassLevel, spellLevel, prime, schoolID);
  //   };
  //   void GetMaxMemorizePerSpellLevel(const SCHOOL_ID& schoolID, int *maxMemorizeArray) const;

  //BOOL CanKnowSpell(WORD CasterClassFlag, WORD SpellClassFlag, WORD CastMask, int SpellLevel)
  BOOL CanKnowSpell(const SCHOOL_ID& schoolID,
    int        spellLevel)
  {
    //return m_spellbook.CanKnowSpell(CasterClassFlag, SpellClassFlag, CastMask, SpellLevel);
    //return m_spellbook.CanKnowSpell(pClass, schoolID, spellAllowedBaseclasses, SpellLevel);
    int i;
    i = spellAbility.LocateSchoolAbility(schoolID);
    if (i < 0) return FALSE;
    const SCHOOL_ABILITY *pSchoolAbility;
    pSchoolAbility = spellAbility.PeekSchoolAbility(i);
    if (spellLevel <= pSchoolAbility->maxSpellLevel)
    {
      return TRUE;
    };
    return FALSE;
  };



  ITEM_LIST myItems;
  MONEY_SACK money;
  TRAITS *m_traits; // Allocated/deallocated in constructor/destructor


  //A_ASLENTRY_L char_asl;
  bool HasKnowableSpell(const CString& uniqueName) const;
  bool AddKnowableSpell(const CString& uniqueName);
  bool DelKnowableSpell(const CString& uniqueName);
  bool ClrKnowableSpell(void);


protected: // attributes of a character

  CString name;
  //raceType m_race;
  RACE_ID race;
  int THAC0;
  //
private:
  int m_AC;   // Renamed 28 Feb 2010 PRS
              // The meaning of this variable is changing.  Therefore the name change.
              // We used to change AC as a PC readied armor and such.  But
              // it was not changed for enemies who wore armor.  This made
              // things very confusing.  So now this variable will be a
              // constant and we will always make adjustments to the 
              // effective armor class that includes readied items.  And we
              // provide a function GetEffectiveAC() to do this easily.
              // m_AC DOES include any skill-based adjustments (Dexterity?)
protected:
  //
public:
  int hitPoints;
  int maxHitPoints;
  DWORD hitpointSeed; //temp....not serialized. 
  int  m_spellCastingLevel; // Not Serialized
                            // Moved here from COMBATANT to work with spells
                            // outside of combat 
                            // level of character casting m_spellIDBeingCast
  BOOL readyToTrain;
  BOOL canTradeItems; // can restrict player from taking NPC items
  BOOL automatic;  // combat only, true means control with AI instead of player control
  BOOL allowPlayerControl; // combat only, if true plyr can control actions
                           //BOOL detectingMagic;
  BOOL detectingInvisible;
  BOOL detectingTraps;

  // current exp in each class	
  /*  // Moved to baseclassStats

  int FighterExperience;
  int ClericExperience;
  int RangerExperience;
  int PaladinExperience;
  int MUExperience;
  int ThiefExperience;
  int DruidExperience;
  */
  int age;
  int maxAge;
  int birthday;
  BYTE maxMovement;

  // low 7 bits indicate pc, npc, or even monster during combat
  // high-bit indicates member of party: 1=inparty,0=notinparty
  BYTE type;
  int strength;
  int strengthMod;
  int intelligence;
  int wisdom;
  int dexterity;
  int constitution;
  int charisma;
  // The adjustments are not serializee.
  // They are compted when first needed
  //  and are updated as spellEffects are added/removed.
  // A value of 0x7fffffff means that they have not been computed
  mutable int strength_adjustment;
  mutable int strengthMod_adjustment;
  mutable int intelligence_adjustment;
  mutable int wisdom_adjustment;
  mutable int dexterity_adjustment;
  mutable int constitution_adjustment;
  mutable int charisma_adjustment;
protected:
  int encumbrance;
  int maxEncumbrance;

  int hitBonus;
  int dmgBonus;
  double nbrHitDice;
  float NbrAttacks; // per round

                    // saving throw values
  int magicResistance;  // only monsters have non-zero mr

  int morale;	 // 0-100, higher is better
  int m_iMaxCureDisease; // uses per day, 0=none
  int m_iUsedCureDisease; // times used this day (not serialized or used yet!)

                          // attributes based on strength
  BYTE openDoors;      // locked doors
  BYTE openMagicDoors; // wizard locked doors
  BYTE BB_LG;	         // bend bars - lift gates
  mCArray<BASECLASS_STATS, BASECLASS_STATS&> baseclassStats;
public:
  DEFINE_mCARRAY_ACCESS_FUNCTIONS(BaseclassStats,   /* array data name      */ \
    BASECLASS_ID,     /* Search variable type */ \
    baseclassID,      /* search variable name */ \
    baseclassStats,   /* array name           */ \
    BASECLASS_STATS,  /* array data type      */ \
    CHARACTER)        /* type of *this        */
private:
  mCArray<SKILL_ADJ, SKILL_ADJ&> skillAdjustments;
public:
  //DEFINE_mCARRAY_ACCESS_FUNCTIONS(SkillAdj,          /* array data name      */ \
  //  SKILL_ID,          /* Search variable type */ \
  //  skillID,           /* search variable name */ \
  //  skillAdjustments,  /* array name           */ \
  //  SKILL_ADJ,         /* array data type      */ \
  //  CHARACTER)         /* type of *this        */

    void DeleteSkillAdj(int indx);
  int  LocateSkillAdj(const SKILL_ID& skillId, const CString& adjName) const;
  int  InsertSkillAdj(const SKILL_ID& skillID, const CString&adjName, char type, int value);
  double UpdateSkillValue(const SKILL_ID& skillID, double val) const;
  int    GetAdjSkillValue(const SKILL_ID& skillID);

protected:

  genderType       gender;
  //classType        charClass;
  CLASS_ID         classID;
  alignmentType    alignment;
  charStatusType   status;
  //undeadType       undead; // monsters only
  CString          undeadType; // monsters only
  creatureSizeType creatureSize;

  BOOL allowInCombat; // for NPC's, if false it won't appear in combat events

  //mCList<SQueuedSpecAb, SQueuedSpecAb&> specAbQueue; // special abilities used recently
public:
  //inline int           GetSpecAbQueueCount(void) { return specAbQueue.GetCount(); };
  //inline POSITION      GetSpecAbQueueHeadPosition(void) { return specAbQueue.GetHeadPosition(); };
  //inline SQueuedSpecAb GetSpecAbQueueAt(POSITION pos) { return *specAbQueue.GetAt(pos); };
  //inline SQueuedSpecAb GetSpecAbQueueNext(POSITION& pos) { return *specAbQueue.GetNext(pos); };
  //inline void          RemoveSpecAbQueueAt(POSITION pos) { specAbQueue.RemoveAt(pos); };
protected:
  //CPropertyContainer m_Properties;

  //BYTE GetClassLevel(WORD ClassFlag) const; // curr level for specific class
  //BYTE GetClassPrevLevel(WORD ClassFlag) const; // prev level for specific class
  //BYTE GetClassPreDrainLevel(WORD ClassFlag) const; // pre-drain level for specific class
public:
  BYTE GetBaseclassLevel(const BASECLASS_ID& baseclassID) const; // curr level for specific class
  BYTE GetBaseclassPrevLevel(const BASECLASS_ID& baseclassID) const; // prev level for specific class
  BYTE GetBaseclassPreDrainLevel(const BASECLASS_ID& baseclassID) const; // pre-drain level for specific class
  void SetBaseclassLevel(const BASECLASS_ID& baseclassID, int level);
protected:
  //bool HaveEffectAttr(const SPELL_EFFECTS_DATA &src) const;
  POSITION GetFirstEffectAttributeMod(IF_KEYWORD_INDEX attr) const;
  POSITION GetNextEffectAttributeMod(IF_KEYWORD_INDEX attr, POSITION start) const;

public:
  // The 'displayValues' are computed once, before the character display, 
  // so that we don't call scripts inside of 'OnDraw()'.  Calling scripts
  // within 'OnDraw()' is bad business because:
  // 1) We call them thousands of times uselessly.
  // 2) We call them an indeterminate number of times.....what if the
  //    script contains a call to 'Random()'?  Yea!  Then what?
  //CHARACTER_DISPLAY_VALUES displayValues;
  //void ComputeCharacterViewValues(void);
  void ComputeCombatViewValues(void);  // Combatant:: Fills 'displayValues' structure.

private:
  //mCArray<SPELL_ADJ, SPELL_ADJ&> spellAdjustments;
public:
  //DEFINE_mCARRAY_ACCESS_FUNCTIONS(SpellAdj,          /* array data name      */ \
  //  SCHOOL_ID,         /* Search variable type */ \
  //  schoolID,          /* search variable name */ \
  //  spellAdjustments,  /* array name           */ \
  //  SPELL_ADJ,         /* array data type      */ \
  //  CHARACTER)         /* type of *this        */



    CString SpellAdjustment(
      const CString&  schoolID,
      const CString&  identifier,
      int             firstLevel,
      int             lastLevel,
      int             percent,
      int             bonus
      );
};


#ifdef UAFEngine
extern CHARACTER character;
#endif

class CHAR_LIST //: public CObject
{
  //CCriticalSection m_CS;
  //OrderedQueue<CHARACTER, MAX_CHARACTERS> chars;
  mCArray<CHARACTER, CHARACTER&> chars;

  //int GetNextKey();
  //int m_FindNamei (const CString& name); // case-insensitive
  BOOL m_IsTempCharList;

public:
  //  DECLARE_SERIAL( CHAR_LIST )
  CHAR_LIST();
  CHAR_LIST(const CHAR_LIST& src);
  ~CHAR_LIST();
  void Clear();
  int GetCount() const { return chars.GetSize(); };
  //int numChars();

  void SetAsTempCharList() { m_IsTempCharList = TRUE; }
  BOOL IsTempCharList() { return m_IsTempCharList; }

  DEFINE_mCARRAY_ACCESS_FUNCTIONS(Character,       /* array data name      */ \
    CHARACTER_ID,    /* Search variable type */ \
    characterID,     /* search variable name */ \
    chars,           /* array name           */ \
    CHARACTER,       /* array data type      */ \
    CHAR_LIST)       /* type of *this        */

    int LocatePreSpellNamesKey(int key);
  int LocateOrigIndex(int i);
  //POSITION GetHeadPosition() const;
  //CHARACTER& GetAt(POSITION pos);
  //CHARACTER& GetNext(POSITION &pos);
  //int LocateCharacter(const NPC_ID& npcID) const;
  //const CHARACTER *PeekCharacter(const NPC_ID& npcID) const;
  //const CHARACTER *PeekCharacter(int arrayIndex) const {return &(const_cast<CHAR_LIST*>(this)->chars[arrayIndex]);};
  //      CHARACTER *GetCharacter(const NPC_ID& npcID);
  //      CHARACTER *GetCharacter(int arrayIndex);

  CHAR_LIST& operator=(const CHAR_LIST& src);

  void Serialize(CArchive &ar, double version);
  void Serialize(CAR &ar, double version);
  //BOOL Validate(int index, FILE *pFile, WORD flags=VAL_ALL) const; // specific char
  //BOOL Validate(const CHARACTER_ID& characterID, FILE *pFile, WORD flags = VAL_ALL) const; // specific char
  //BOOL Validate(FILE *pFile, WORD flags = VAL_ALL) const; // all chars

#ifdef UAFEDITOR
  void CrossReference(CR_LIST *pCRList) const;
  void Export(void);
  void Import(BOOL quiet);
#endif
  //BOOL HaveKey(int index);
  BOOL HaveCharacter(const CHARACTER_ID& characterID) const;
  BOOL HaveNPC(const CHARACTER_ID& characterID) const;

  int FindNamei(const CString& name); // case-insensitive

#ifdef UAFEngine
                                      //void CastSpell(int index, GLOBAL_SPELL_ID spell);
  void CastSpell(int index, const SPELL_ID& spellID);
  void SpellActivate(int index, const PENDING_SPELL &data, ToHitComputation *pToHitComputation);
#endif
  // called when loading from scripts, or
  // when adding from editor GUI
  //int AddCharacter(CHARACTER &data);
  int AddCharacter(const CHARACTER *pChar);

  // called when loading binary monster data that
  // was saved with key info
  //int AddCharacterWithCurrKey(CHARACTER &data);

  //CString GetCharacterName(int index) const;
  CString GetCharacterName(const CHARACTER_ID& characterID) const;

  //BOOL SetCharacter(int index, const CHARACTER &data);
  BOOL SetCharacter(int arrayIndex, const CHARACTER *pChar);
  //BOOL RemoveCharacter(int index);
  void RemoveCharacter(int arrayIndex);
  BOOL RemoveCharacter(const CHARACTER_ID& characterID);
  BOOL DeleteCharacterEvents(int index);
  //BOOL GetCharacterData(int index, CHARACTER &data);  
  BOOL FetchCharacter(int arrayIndex, CHARACTER *pChar) const;
  BOOL FetchCharacter(const CHARACTER_ID& characterID, CHARACTER *pChar) const;
  //CHARACTER *GetCharacterData(int index);  
};

