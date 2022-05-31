#include "StdAfx.h"

CString StandardCapitalize(const CString& str)
{
  CString result;
  result = str;
  result.MakeUpper();
  return result;
}

CString CapitalizeItem(const CString& itemName)
{
  return StandardCapitalize(itemName);
}

CString CapitalizeMonster(const CString& monsterName)
{
  return StandardCapitalize(monsterName);
}

CString CapitalizeRace(const CString& raceName)
{
  return StandardCapitalize(raceName);
}

CString CapitalizeCharacterID(const CString& characterID)
{
  return StandardCapitalize(characterID);
}

CString CapitalizeNPC(const CString& NPCName)
{
  return StandardCapitalize(NPCName);
}

CString CapitalizeClass(const CString& className)
{
  return StandardCapitalize(className);
}

CString CapitalizePassword(const CString& password)
{
  return StandardCapitalize(password);
}

CString CapitalizeZoneName(const CString& zoneName)
{
  return StandardCapitalize(zoneName);
}

CString CapitalizeBaseclass(const CString& baseclassName)
{
  return StandardCapitalize(baseclassName);
}

CString CapitalizeSchool(const CString& school)
{
  return StandardCapitalize(school);
}

CString CapitalizeSpell(const CString& spell)
{
  return StandardCapitalize(spell);
}

