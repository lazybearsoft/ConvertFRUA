#include "stdafx.h"
#include "Translate.h"
#include "specAb.h"
#include "NPC.h"
#include "Monster.h"


CString CapitalizeRace(const CString& raceName);
CString CapitalizeClass(const CString& raceName);
CString CapitalizeNPC(const CString& raceName);
CString CapitalizeCharacterID(const CString& raceName);

const int CHARACTER_VERSION = 0x80000001;  // Not to be confused with index values


void BASECLASS_STATS::Export(JWriter& jw)
{
  jw.StartList();
  jw.NameAndValue(JKEY_BASECLASSID, baseclassID);
  jw.NameAndValue(JKEY_CURRENTLEVEL, currentLevel);
  jw.NameAndValue(JKEY_PREVIOUSLEVEL, previousLevel);
  jw.NameAndValue(JKEY_PREDRAINLEVEL, preDrainLevel);
  jw.NameAndValue(JKEY_EXPERIENCE, experience);
  jw.EndList();
}

BASECLASS_STATS::BASECLASS_STATS(void)
{
  NotImplemented(0xbbd, false);
}

void SPECIAL_ABILITIES::Export(JWriter& jw)
{
  m_specialAbilities.Export(jw);
};

void SPECIAL_ABILITIES::InsertAbility_RO(const CString& name, const CString& param, LPCSTR d1, LPCSTR d2)
{
  m_specialAbilities.Insert(name, param);
}


void SPECIAL_ABILITIES::InsertAbility(const CString& name, const CString& param, LPCSTR d1, LPCSTR d2)
{
  InsertAbility_RO(name, param, d1, d2);
}



void SPECIAL_ABILITIES::InsertAbility(const CString& str)
{
  InsertAbility(str, "0", "", "");
}


SPECIAL_ABILITIES::SPECIAL_ABILITIES(bool readOnly)
{
  m_readOnly = readOnly;
}

SPECIAL_ABILITIES::~SPECIAL_ABILITIES(void)
{
  m_specialAbilities.Clear();
}



void SPECIAL_ABILITIES::Clear(void)
{
  m_specialAbilities.Clear();
}


BTree::~BTree(void)
{
  if (m_root != NULL)
  {
    NotImplemented(0xadabc, false);  // Should not happen
  }
}

int BTree::GetNextAssoc(POSITION& pos) const
{
  int n;
  WORD more;
  more = 0;
  BTreeNode *pNode;
  pNode = m_root;
  n = (int)pos - 1;
  for (;;)
  {
    if (n == pNode->m_cntL)
    {
      pos++;
      more += pNode->m_cntR;
      if (!more) pos = NULL;
      return pNode->m_data;
    };
    if (n < pNode->m_cntL)
    {
      if (pNode->m_cntL == 1)
      {
        pos++;
        return pNode->m_left.data;
      };
      more++;
      pNode = pNode->m_left.pNode;
    }
    else
    {
      if (pNode->m_cntR == 1)
      {
        pos++;
        if (more == 0) pos = NULL;
        return pNode->m_right.data;
      };
      n -= pNode->m_cntL + 1;
      pNode = pNode->m_right.pNode;
    };
  };
}



struct BTREE_ENVIRONMENT
{
  BOOL(*bTreeKeyCompare)(int a);          // Compare bTreeKey to entry a.
  BOOL(*bTreeEntryCompare)(int a, int b); // Compare entry a to entry b.
  void(*bTreeDeleteData)(int a);
  int     bTreeNoData;
  LPCTSTR bTreeKey;
  int     bTreeData;
};

void CStringPAIR_DELETE(int a);
int CStringPAIR_COMPARE_KEY(int a);  // sign(a-key)
int CStringPAIR_COMPARE_ENTRY(int a, int b);  // sign(a-b)

void BTree::ClearNode(BTreeNode *pNode, BTREE_ENVIRONMENT *pEnv)
{
  if (pNode->m_cntL != 0)
  {
    if (pNode->m_cntL == 1)
    {
      (*pEnv->bTreeDeleteData)(pNode->m_left.data);
    }
    else
    {
      ClearNode(pNode->m_left.pNode, pEnv);
    };
  };
  if (pNode->m_cntR != 0)
  {
    if (pNode->m_cntR == 1)
    {
      (*pEnv->bTreeDeleteData)(pNode->m_right.data);
    }
    else
    {
      ClearNode(pNode->m_right.pNode, pEnv);
    };
  };
  (*pEnv->bTreeDeleteData)(pNode->m_data);
  delete pNode;
}


void BTree::Clear(BTREE_ENVIRONMENT *pEnv)
{
  if (m_root != NULL) ClearNode(m_root, pEnv);
  m_root = NULL;
}


#define BALANCE_RIGHT(p, e) if((p)->m_cntL > (p)->m_cntR+2+(p)->m_cntL/8)PushRight(p,e);
#define BALANCE_LEFT(p, e)  if((p)->m_cntR > (p)->m_cntL+2+(p)->m_cntR/8)PushLeft(p,e);

void BTree::Swap(BTree& tree)
{
  BTreeNode *temp;
  temp = m_root;
  m_root = tree.m_root;
  tree.m_root = temp;
}

void BTree::PushLeft(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv)
{
  int temp;
  BTreeNode *C, *D;
  ASSERT(pTop->m_cntR > 1);
  C = pTop->m_right.pNode;
  D = C->m_left.pNode;
  if (D == NULL)
  {
    temp = C->m_data;
    C->m_data = pTop->m_data;
    pTop->m_data = temp;

    pTop->m_cntR = C->m_cntR;
    pTop->m_right.pNode = C->m_right.pNode;
    C->m_cntL = pTop->m_cntL;
    C->m_left.pNode = pTop->m_left.pNode;
    C->m_cntR = 0;
    C->m_right.pNode = NULL;
    if (pTop->m_cntL == 0)
    {
      pTop->m_left.data = C->m_data;
      delete C;
    }
    else
    {
      pTop->m_left.pNode = C;
    };
    pTop->m_cntL++;
    return;
  }
  else
  {
    if (C->m_cntL == 1)
    {
      temp = C->m_data;
      C->m_data = pTop->m_data;
      pTop->m_data = temp;

      pTop->m_cntR = C->m_cntR;
      pTop->m_right.pNode = C->m_right.pNode;

      C->m_cntR = 1;
      C->m_right.data = C->m_left.data;

      C->m_cntL = pTop->m_cntL;
      C->m_left.pNode = pTop->m_left.pNode;

      pTop->m_cntL += 2;
      pTop->m_left.pNode = C;

      BALANCE_RIGHT(C, pEnv);
      return;
    }
    else
    {
      temp = D->m_data;
      D->m_data = pTop->m_data;
      pTop->m_data = temp;

      C->m_cntL = D->m_cntR;
      C->m_left.pNode = D->m_right.pNode;

      D->m_cntR = D->m_cntL;
      D->m_right.pNode = D->m_left.pNode;

      D->m_cntL = pTop->m_cntL;
      D->m_left.pNode = pTop->m_left.pNode;

      pTop->m_cntL += 1 + D->m_cntR;
      pTop->m_left.pNode = D;
      pTop->m_cntR -= 1 + D->m_cntR;

      if (pTop->m_cntR == 1)
      {
        BTreeNode *rightNode;
        rightNode = pTop->m_right.pNode;
        pTop->m_right.data = rightNode->m_data;
        delete rightNode;
      };

      if (pTop->m_cntL == 1)
      {
        BTreeNode *leftNode;
        leftNode = pTop->m_left.pNode;
        pTop->m_left.data = leftNode->m_data;
        delete leftNode;
      };

      BALANCE_LEFT(C, pEnv)
        BALANCE_RIGHT(D, pEnv)
        return;
    };
  };
}

void BTree::PushRight(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv)
{
  int temp;
  BTreeNode *C, *D;
  ASSERT(pTop->m_cntL > 1);
  C = pTop->m_left.pNode;
  D = C->m_right.pNode;
  if (D == NULL)
  {
    temp = C->m_data;
    C->m_data = pTop->m_data;
    pTop->m_data = temp;

    pTop->m_cntL = C->m_cntL;
    pTop->m_left.pNode = C->m_left.pNode;
    C->m_cntR = pTop->m_cntR;
    C->m_right.pNode = pTop->m_right.pNode;
    C->m_cntL = 0;
    C->m_left.pNode = NULL;
    if (pTop->m_cntR == 0)
    {
      pTop->m_right.data = C->m_data;
      delete C;
    }
    else
    {
      pTop->m_right.pNode = C;
    };
    pTop->m_cntR++;
    return;
  }
  else
  {
    if (C->m_cntR == 1)
    {
      temp = C->m_data;
      C->m_data = pTop->m_data;
      pTop->m_data = temp;

      pTop->m_cntL = C->m_cntL;
      pTop->m_left.pNode = C->m_left.pNode;

      C->m_cntL = 1;
      C->m_left.data = C->m_right.data;

      C->m_cntR = pTop->m_cntR;
      C->m_right.pNode = pTop->m_right.pNode;

      pTop->m_cntR += 2;
      pTop->m_right.pNode = C;

      BALANCE_LEFT(C, pEnv);
      return;
    }
    else
    {
      temp = D->m_data;
      D->m_data = pTop->m_data;
      pTop->m_data = temp;

      C->m_cntR = D->m_cntL;
      C->m_right.pNode = D->m_left.pNode;

      D->m_cntL = D->m_cntR;
      D->m_left.pNode = D->m_right.pNode;

      D->m_cntR = pTop->m_cntR;
      D->m_right.pNode = pTop->m_right.pNode;

      pTop->m_cntR += 1 + D->m_cntL;
      pTop->m_right.pNode = D;
      pTop->m_cntL -= 1 + D->m_cntL;

      if (pTop->m_cntL == 1)
      {
        BTreeNode *leftNode;
        leftNode = pTop->m_left.pNode;
        pTop->m_left.data = leftNode->m_data;
        delete leftNode;
      };

      if (pTop->m_cntR == 1)
      {
        BTreeNode *rightNode;
        rightNode = pTop->m_right.pNode;
        pTop->m_right.data = rightNode->m_data;
        delete rightNode;
      };

      BALANCE_RIGHT(C, pEnv)
        BALANCE_LEFT(D, pEnv)
        return;
    };
  };
}


int BTree::AddNode(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv)
{ // *ppTop != NULL
  // Update *ppTop if tree is adjusted.
  // If (matching key already exists)
  // {
  //     return data from existing node;
  // }
  // else
  // {
  //     return NULL;
  // };
  int diff;
  diff = (*(pEnv->bTreeEntryCompare))(pTop->m_data, pEnv->bTreeData);
  //diff = pTop->m_data->Compare(bTreeData);
  if (diff == 0)
  {
    return pTop->m_data;
  };
  if (diff < 0)
  {
    // Add to right side
    if (pTop->m_cntR == 0)
    {
      pTop->m_right.data = pEnv->bTreeData;
      pTop->m_cntR = 1;
    }
    else
    {
      int foundData;
      if (pTop->m_cntR == 1)
      {
        diff = (*pEnv->bTreeEntryCompare)(pTop->m_right.data, pEnv->bTreeData);
        //diff = pTop->m_right.pData->Compare(bTreeData);
        if (diff == 0)
        {
          return pTop->m_right.data;
        };
        BTreeNode *pNewNode;
        pNewNode = new BTreeNode;
        pNewNode->m_data = pTop->m_right.data;
        pTop->m_right.pNode = pNewNode;
        if (diff < 0)
        {
          // Put on right side
          pNewNode->m_cntR = 1;
          pNewNode->m_cntL = 0;
          pNewNode->m_left.data = pEnv->bTreeNoData;
          pNewNode->m_right.data = pEnv->bTreeData;
        }
        else
        {
          // Put on left side
          pNewNode->m_cntR = 0;
          pNewNode->m_cntL = 1;
          pNewNode->m_left.data = pEnv->bTreeData;
          pNewNode->m_right.data = pEnv->bTreeNoData;
        };
        pTop->m_cntR++;
        return pEnv->bTreeNoData;
      };
      foundData = AddNode(pTop->m_right.pNode, pEnv);
      if (foundData != pEnv->bTreeNoData) return foundData;
      pTop->m_cntR++;
      BALANCE_LEFT(pTop, pEnv);
    };
  }
  else
  {
    // Add to left side
    if (pTop->m_cntL == 0)
    {
      pTop->m_left.data = pEnv->bTreeData;
      pTop->m_cntL = 1;
    }
    else
    {
      int foundData;
      if (pTop->m_cntL == 1)
      {
        diff = (*pEnv->bTreeEntryCompare)(pTop->m_left.data, pEnv->bTreeData);
        //diff = pTop->m_left.pData->Compare(bTreeData);
        if (diff == 0)
        {
          return pTop->m_left.data;
        };
        BTreeNode *pNewNode;
        pNewNode = new BTreeNode;
        pNewNode->m_data = pTop->m_left.data;
        pTop->m_left.pNode = pNewNode;
        if (diff < 0)
        {
          // Put on right side
          pNewNode->m_cntR = 1;
          pNewNode->m_cntL = 0;
          pNewNode->m_left.data = pEnv->bTreeNoData;
          pNewNode->m_right.data = pEnv->bTreeData;
        }
        else
        {
          // Put on left side
          pNewNode->m_cntR = 0;
          pNewNode->m_cntL = 1;
          pNewNode->m_left.data = pEnv->bTreeData;
          pNewNode->m_right.data = pEnv->bTreeNoData;
        };
        pTop->m_cntL++;
        return pEnv->bTreeNoData;
      };
      foundData = AddNode(pTop->m_left.pNode, pEnv);
      if (foundData != pEnv->bTreeNoData) return foundData;
      pTop->m_cntL++;
      BALANCE_RIGHT(pTop, pEnv);
    };
  };
  return pEnv->bTreeNoData;
}


int BTree::Insert(BTREE_ENVIRONMENT *pEnv)
{
  // Return matching data if matching key already exists; else zero.
  if (m_root == NULL)
  {
    m_root = new BTreeNode;
    //    m_root->id = NodeID++;
    m_root->m_cntL = 0;
    m_root->m_cntR = 0;
    m_root->m_left.pNode = NULL;
    m_root->m_right.pNode = NULL;
    m_root->m_data = pEnv->bTreeData;
    return pEnv->bTreeNoData;
  }
  else
  {
    return AddNode(m_root, pEnv);
  };
}


BTREE_ENVIRONMENT CStringPAIREnvironment =
{
  CStringPAIR_COMPARE_KEY,
  CStringPAIR_COMPARE_ENTRY,
  CStringPAIR_DELETE,
  0
};


int CStringPAIR::Compare(LPCSTR str) const
{
  return m_key.Compare(str);
}

int CStringPAIR::Compare(const CStringPAIR *p) const
{
  return m_key.Compare(p->m_key);
}


int CStringPAIR_COMPARE_KEY(int a)  // sign(a-key)
{
  return ((CStringPAIR *)a)->Compare(CStringPAIREnvironment.bTreeKey);
}


void CStringPAIR_DELETE(int a)
{
  delete (CStringPAIR *)a;
}



int CStringPAIR_COMPARE_ENTRY(int a, int b)  // sign(a-b)
{
  return ((CStringPAIR *)a)->Compare((CStringPAIR *)b);
}

CStringPAIR::CStringPAIR(const CString& key, const CString& value)
{
  m_key = key;
  m_value = value;
};

CStringPAIR& CStringPAIR::operator =(const CStringPAIR& p)
{
  m_key = p.m_key; m_value = p.m_value;
  return *this;
}

CStringPAIR::CStringPAIR(void)
{
  Clear();
}


void A_CStringPAIR_L::GetNextAssoc(POSITION& pos, const CStringPAIR **ppEntry) const
{
  *ppEntry = (CStringPAIR *)BTree::GetNextAssoc(pos);
}

A_CStringPAIR_L::~A_CStringPAIR_L(void)
{
  Clear();
}

void A_CStringPAIR_L::Clear(void)
{
  BTree::Clear(&CStringPAIREnvironment);
}


BOOL A_CStringPAIR_L::Insert(const CString& key, const CString& value)
{

  CStringPAIR *pEntry, *foundData;
  pEntry = new CStringPAIR;
  pEntry->m_key = key;
  pEntry->m_value = value;
  CStringPAIREnvironment.bTreeData = (int)pEntry;
  foundData = (CStringPAIR *)(BTree::Insert(&CStringPAIREnvironment));
  if (foundData != NULL)
  {
    *foundData = *pEntry;
    delete pEntry;
    return TRUE;
  };
  return FALSE;
}

BOOL A_CStringPAIR_L::Insert(const CStringPAIR& pEntry)
{
  return Insert(pEntry.Key(), pEntry.Value());
}


void A_CStringPAIR_L::Export(JWriter& jw)
{
  POSITION pos;
  const CStringPAIR *pEntry;
  jw.StartArray(JKEY_SPECIALABILITIES);
  jw.Linefeed(true);
  pos = GetStartPosition();
  while (pos != NULL)
  {
    jw.NextEntry();
    jw.StartList();
    GetNextAssoc(pos, &pEntry);
    jw.Linefeed(false);
    jw.NameAndValue(JKEY_NAME, pEntry->m_key);
    jw.NameAndValue(JKEY_VALUE, pEntry->m_value);
    jw.EndList();
    jw.Linefeed(true);
  };
  jw.EndArray();
  jw.Linefeed(true);
}

CHARACTER::CHARACTER(void) :
  // ASL named "CHARACTER_ATTRIBUTES"
  //char_asl(),
  TalkEvent(0),
  ExamineEvent(0),
  specAbs(false)
{
  //m_traits = new TRAITS;
  Clear(TRUE);
}

CHARACTER::~CHARACTER(void)
{
  Clear(TRUE);
  //if (m_traits != NULL) delete m_traits;
  //m_traits = NULL;
}

void CHARACTER::Clear(BOOL IsConstructor)
{
  //if (TalkEvent > 0)
  //  globalData.eventData.DeleteEvents(TalkEvent);
  DisableTalkIfDead = TRUE;
  TalkEvent = 0;
  TalkLabel = "TALK";
  //if (ExamineEvent > 0)
  //  globalData.eventData.DeleteEvents(ExamineEvent);
  ExamineEvent = 0;
  ExamineLabel = "EXAMINE";
  //uniqueKey = 0;
  type = CHAR_TYPE;
  //race(Human);
  race = "";
  gender = Male;
  //charClass = Fighter;
  classID = "";
  alignment = ChaoticNeutral;
  allowInCombat = TRUE;
  status = Unconscious;
  //undead = NotUndead;
  undeadType.Empty();
  creatureSize = Medium;
  name = "";
  THAC0 = 20;
  morale = 50; // 0.100%
  encumbrance = 0;
  maxEncumbrance = 0;
  m_AC = 10;
  hitPoints = 0;
  maxHitPoints = 0;
  nbrHitDice = 0;
  age = 0;
  maxAge = 0;
  //SetBirthday(1);
  m_iMaxCureDisease = 0;
  m_iUsedCureDisease = 0;
  unarmedDieS = 0;
  unarmedNbrDieS = 0;
  unarmedBonus = 0;
  unarmedDieL = 0;
  unarmedNbrDieL = 0;
  //ItemMask = 0;
  maxMovement = 0;
  readyToTrain = FALSE;
  canTradeItems = TRUE;
  strength = 0;
  strengthMod = 0;
  intelligence = 0;
  wisdom = 0;
  dexterity = 0;
  constitution = 0;
  charisma = 0;
  strength_adjustment = 0x7fffffff;
  strengthMod_adjustment = 0x7fffffff;
  intelligence_adjustment = 0x7fffffff;
  wisdom_adjustment = 0x7fffffff;
  dexterity_adjustment = 0x7fffffff;
  constitution_adjustment = 0x7fffffff;
  charisma_adjustment = 0x7fffffff;
  spellAbility.valid = FALSE;
  openDoors = 0;
  openMagicDoors = 0;
  BB_LG = 0;
  automatic = FALSE;
  allowPlayerControl = TRUE;
  //detectingMagic=FALSE;
  detectingInvisible = FALSE;
  detectingTraps = FALSE;
  hitBonus = 0;
  dmgBonus = 0;
  magicResistance = 0;
  baseclassStats.RemoveAll();

  IsPreGen = FALSE;
  CanBeSaved = TRUE;
  HasLayedOnHandsToday = FALSE;
  money.Clear();
  NbrAttacks = 0.0;
  icon.Clear();
  iconIndex = 1;
  smallPic.Clear();
  origIndex = -1;
  monsterID.Empty();
  characterID.Empty();
  uniquePartyID = 0xff;
  specAbs.Clear();
  //specAbQueue.RemoveAll();
  //blockageData.Clear();
  m_spellbook.Clear();
  myItems.Clear();
  //char_asl.Clear();
  m_spellCastingLevel = -1;
  //m_spellEffects.RemoveAll();
  //spellAdjustments.RemoveAll();
  //m_pCombatant = NULL;
  temp__canUsePrevClass = -1;
}

void CHARACTER::ExportNPC(MONSTER_DATA *pNPC)
{
  CString str;
  int i;
  preSpellNamesKey = -1;    // Just for conversion of old designs.
  int origIndex = -1;       // id for npc or monster if added to party or combatData tables
  monsterID = "";   // If this character is a monster
  characterID = pNPC->GetStringValue("name"); // If this character is an NPC
  BYTE uniquePartyID = 0;       // 0-7 party id, never changes, even when party order changes
  BOOL IsPreGen = TRUE;     // means NPC is available to add to party at start
  BOOL CanBeSaved = TRUE;   // allow saving NPC for later restore?
  BOOL HasLayedOnHandsToday = FALSE; // Paladins allowed to heal self/others once per day
  int unarmedDieS = 0;   // if not using a weapon
  int unarmedNbrDieS = -1;
  int unarmedBonus = -1;
  int unarmedDieL = -1;
  int unarmedNbrDieL = -1;
  BOOL DisableTalkIfDead = TRUE;
  DWORD TalkEvent = 0; // event chain used for 'Talk' menu 
  CString TalkLabel = "???"; // text used in menu to trigger talk event
  DWORD ExamineEvent = 0;
  CString ExamineLabel = "???";
  int iconIndex = 1; // which icon to use - default is 1
  icon = pNPC->GetStringValue("icon file");
  smallPic.Clear();
  for (i = 0; (str = pNPC->GetStringValue("Special Ability", i)) != "???"; i++)
  {
    specAbs.InsertAbility(str);
  };
  m_spellbook.Clear();
  spellAbility.Clear();
  for (i = 0; (str = pNPC->GetStringValue("item", i)) != "???"; i++)
  {
    myItems.InsertItem(str);
  };
  money.Clear();
  name = pNPC->GetStringValue("name");
  if (name == "TIBERUS")
  {
    int kkk = 1;
  };
  race = pNPC->GetStringValue("Race");
  THAC0 = pNPC->GetIntegerValue("THAC0");
  m_AC = pNPC->GetIntegerValue("armor class");
  // Renamed 28 Feb 2010 PRS
  // The meaning of this variable is changing.  Therefore the name change.
  // We used to change AC as a PC readied armor and such.  But
  // it was not changed for enemies who wore armor.  This made
  // things very confusing.  So now this variable will be a
  // constant and we will always make adjustments to the 
  // effective armor class that includes readied items.  And we
  // provide a function GetEffectiveAC() to do this easily.
  // m_AC DOES include any skill-based adjustments (Dexterity?)
  hitPoints = pNPC->GetIntegerValue("//hitpoints base");
  maxHitPoints = pNPC->GetIntegerValue("//hitpoints base");
  BOOL readyToTrain = FALSE;
  BOOL canTradeItems = TRUE; // can restrict player from taking NPC items
  BOOL automatic = TRUE;  // combat only, true means control with AI instead of player control
  BOOL allowPlayerControl = TRUE; // combat only, if true plyr can control actions
  BOOL detectingInvisible = FALSE;
  BOOL detectingTraps = FALSE;
  age = pNPC->GetIntegerValue("//age");
  maxAge = 99;
  int birthday = 0;
  maxMovement = pNPC->GetIntegerValue("movement rate");
  // low 7 bits indicate pc, npc, or even monster during combat
  // high-bit indicates member of party: 1=inparty,0=notinparty
  type = 2;
  strength = pNPC->GetIntegerValue("//strength");
  strengthMod = 0;
  intelligence = pNPC->GetIntegerValue("intelligence");
  wisdom = pNPC->GetIntegerValue("//wisdom");
  dexterity = pNPC->GetIntegerValue("//dexterity");
  constitution = pNPC->GetIntegerValue("//constitution");
  charisma = pNPC->GetIntegerValue("//charisma");
  int encumbrance = 0;
  int maxEncumbrance = 0;
  hitBonus = pNPC->GetIntegerValue("hit dice bonus");
  dmgBonus = 0;
  double nbrHitDice = pNPC->GetIntegerValue("hit dice");
  NbrAttacks = 1.0; // per round
  magicResistance = pNPC->GetIntegerValue("magic resistance");  // only monsters have non-zero mr
  morale = pNPC->GetIntegerValue("morale");	 // 0-100, higher is better
  m_iMaxCureDisease = 0; // uses per day, 0=none
  m_iUsedCureDisease = 0; // times used this day (not serialized or used yet!)
  openDoors = 0;      // locked doors
  openMagicDoors = 0; // wizard locked doors
  BB_LG = 0;	         // bend bars - lift gates
  baseclassStats.RemoveAll();
  skillAdjustments.RemoveAll();
  str = pNPC->GetStringValue("//gender");
  gender = Bishop;
  if (str == "male")  gender = Male;
  if (str == "female") gender = Female;
  classID = pNPC->GetStringValue("Class");
  str = pNPC->GetStringValue("//alignment");
  if (str == "lawful good")     alignment = LawfulGood;
  if (str == "neutral good")    alignment = NeutralGood;
  if (str == "chaotic good")    alignment = ChaoticGood;
  if (str == "lawful neutral")  alignment = LawfulNeutral;
  if (str == "true neutral")    alignment = TrueNeutral;
  if (str == "chaotic neutral") alignment = ChaoticNeutral;
  if (str == "lawful evil")     alignment = LawfulEvil;
  if (str == "neutral evil")    alignment = NeutralEvil;
  if (str == "chaotic evil")    alignment = ChaoticEvil;
  status = Okay;
  undeadType = pNPC->GetStringValue("undead"); // monsters only
  str = pNPC->GetStringValue("size");
  if (str == "small")  creatureSize = Small;
  if (str == "medium") creatureSize = Medium;
  if (str == "large")  creatureSize = Large;
  allowInCombat = TRUE; // for NPC's, if false it won't appear in combat events


  {
    CFile cf;
    CString path;
    CString filename;
    CString importText;
    filename.Format("%s.CHAR", name);
    path = jsonPath + filename;
    if (!cf.Open(path, CFile::modeCreate | CFile::modeWrite))
    {
      CString msg;
      msg.Format("Cannot open output file '%s'", path);
      die(msg);
    };
    JWriter jw(&cf);
    Export(jw);
  }
};


void CHARACTER::Export(JWriter& jw)
{
  // This data can be serialized along with the globalData, and
  // also separately as a 'CharName.CHR' file.
  // The version specified distinguishes between saved char file 
  // version and game.dat file version
  //
  jw.StartList();
  jw.NameAndValue(JKEY_CHARVERSION, CHARACTER_VERSION);
  //ar << uniqueKey;
  jw.NameAndValue(JKEY_TYPE, type);
  //temp = m_race;
  //ar << temp;
  jw.NameAndValue(JKEY_RACE, CapitalizeRace(race));
  jw.NameAndEnum(JKEY_GENDER, gender);
  //ar << temp;
  //temp = charClass;
  jw.NameAndValue(JKEY_CLASS, CapitalizeClass(classID));
  //car << temp;
  jw.NameAndEnum(JKEY_ALIGNMENT, alignment);
  jw.NameAndValue(JKEY_ALLOWINCOMBAT, allowInCombat);
  //temp = undead;
  //temp = undeadLevel;
  //car << temp;
  jw.NameAndValue(JKEY_UNDEADTYPE, undeadType);
  jw.NameAndEnum(JKEY_SIZE, creatureSize);

  jw.NameAndValue(JKEY_NAME, CapitalizeNPC(name));
  jw.NameAndValue(JKEY_CHARACTERID, CapitalizeCharacterID(characterID));
  jw.NameAndValue(JKEY_THAC0, THAC0);
  jw.NameAndValue(JKEY_MORALE, morale);
  jw.NameAndValue(JKEY_ENCUMBRANCE, encumbrance);
  jw.NameAndValue(JKEY_MAXENCUMBRANCE, maxEncumbrance);
  jw.NameAndValue(JKEY_AC, m_AC);
  jw.NameAndValue(JKEY_HP, hitPoints);
  jw.NameAndEnum(JKEY_STATUS, status);
  jw.NameAndValue(JKEY_MAXHP, maxHitPoints);
  jw.NameAndValue(JKEY_NBRHITDICE, nbrHitDice);
  jw.NameAndValue(JKEY_AGE, age);
  jw.NameAndValue(JKEY_MAXAGE, maxAge);
  jw.NameAndValue(JKEY_BIRTHDAY, birthday);
  jw.NameAndValue(JKEY_MAXCUREDISEASE, m_iMaxCureDisease);
  jw.NameAndValue(JKEY_UNARMEDDICESIDES, unarmedDieS);
  jw.NameAndValue(JKEY_UNARMEDNBRDICES, unarmedNbrDieS);
  jw.NameAndValue(JKEY_UNARMEDDICEBONUS, unarmedBonus);
  jw.NameAndValue(JKEY_UNARMEDDICEL, unarmedDieL);
  jw.NameAndValue(JKEY_UNARMEDNBRDICEL, unarmedNbrDieL);
  //ar << ItemMask;
  jw.NameAndValue(JKEY_MAXMOVEMENT, maxMovement);
  jw.NameAndValue(JKEY_READYTOTRAIN, readyToTrain);
  jw.NameAndValue(JKEY_CANTRADEITEMS, canTradeItems);

  jw.NameAndValue(JKEY_STR, GetPermStr());
  jw.NameAndValue(JKEY_STRMOD, GetPermStrMod());
  jw.NameAndValue(JKEY_INT, GetPermInt());
  jw.NameAndValue(JKEY_WIS, GetPermWis());
  jw.NameAndValue(JKEY_DEX, GetPermDex());
  jw.NameAndValue(JKEY_CON, GetPermCon());
  jw.NameAndValue(JKEY_CHA, GetPermCha());

  jw.NameAndValue(JKEY_OPENDOORS, openDoors);
  jw.NameAndValue(JKEY_OPENMAGICDOORS, openMagicDoors);
  jw.NameAndValue(JKEY_BBLG, BB_LG);
  jw.NameAndValue(JKEY_HITBONUS, hitBonus);
  jw.NameAndValue(JKEY_DMGBONUS, dmgBonus);
  jw.NameAndValue(JKEY_MAGICRESISTANCE, magicResistance);
  {
    //CString version = "BS0";
    int i, count;
    //car << version;
    count = GetBaseclassStatsCount();
    //car << count;
    jw.StartArray(JKEY_BASECLASSSTATS);
    for (i = 0; i<count; i++)
    {
      jw.NextEntry();
      GetBaseclassStats(i)->Export(jw);
      //baseclassStats[i].Export(jw);
    };
    jw.EndArray();
  }
  {
    //CString version = "SA0";
    int i, count;
    count = 0; // GetSkillAdjCount();
    //car << version;
    //car << count;
    jw.StartArray(JKEY_SKILLADJUSTMENTS);
    for (i = 0; i<count; i++)
    {
      jw.NextEntry();
      //GetSkillAdj(i)->Export(jw);
    };
    jw.EndArray();
  };
  {
    //CString version = "SA0";
    int i, count;
    count = 0; // GetSpellAdjCount();
    //car << version;
    //car << count;
    jw.StartArray(JKEY_SPELLADJUSTMENTS);
    for (i = 0; i<count; i++)
    {
      jw.NextEntry();
      //GetSpellAdj(i)->Export(jw);
    };
    jw.EndArray();
  };
  jw.NameAndValue(JKEY_ISPREGEN, IsPreGen);
  jw.NameAndValue(JKEY_CANBESAVED, CanBeSaved);
  jw.NameAndValue(JKEY_HASLAYEDONHANDSTODAY, HasLayedOnHandsToday);
  money.Export(jw);
  jw.NameAndValue(JKEY_NBRATTACKS, NbrAttacks);
  icon.Export(jw, JKEY_ICON);
  jw.NameAndValue(JKEY_ICONINDEX, iconIndex);
  jw.NameAndValue(JKEY_ORIGINDEX, origIndex);
  jw.NameAndValue(JKEY_UNIQUEPARTYID, uniquePartyID);
  jw.NameAndValue(JKEY_DISABLETALKIFDEAD, DisableTalkIfDead);
  jw.NameAndValue(JKEY_TALKEVENT, TalkEvent);
  jw.NameAndValue(JKEY_TALKLABEL, TalkLabel);
  jw.NameAndValue(JKEY_EXAMINEEVENT, ExamineEvent);
  jw.NameAndValue(JKEY_EXAMINELABEL, ExamineLabel);

  m_spellbook.Export(jw);

  //ar << detectingMagic;
  jw.NameAndValue(JKEY_DETECTINGINVISIBLE, detectingInvisible);
  jw.NameAndValue(JKEY_DETECTINGTRAPS, detectingTraps);
  jw.StartArray(JKEY_BLOCKAGESTATUS);
  jw.EndArray();
  //car << m_spellEffects.GetCount();
  {
    POSITION pos = NULL; // m_spellEffects.GetHeadPosition();
    jw.StartArray(JKEY_SPELLEFFECTS);
    while (pos != NULL)
    {
      jw.NextEntry();
      //m_spellEffects.GetNext(pos)->Export(jw);
    };
    jw.EndArray();
  };


  //blockageData.Export(jw);

  smallPic.Export(jw, JKEY_SMALLPIC);
  myItems.Export(jw, JKEY_POSSESSIONS);
  specAbs.Export(jw);
  // specAbQueue: no need to save this data
  //char_asl.Export(jw);


  //m_Properties.Serialize(ar, version);

  // just to make sure we catch this for some older
  // character's that might come from saved games
  //strengthKey     = abilityData.GetKeyByIndex(0);
  //intelligenceKey = abilityData.GetKeyByIndex(1);
  //wisdomKey       = abilityData.GetKeyByIndex(2);
  //dexterityKey    = abilityData.GetKeyByIndex(3);
  //constitutionKey = abilityData.GetKeyByIndex(4);
  //charismaKey     = abilityData.GetKeyByIndex(5);

  // design settings that affect encumbrance might
  // have changed since character was last saved

  //DisplayCurrSpellEffects("Serialize");
  jw.EndList();
}
