#pragma once

struct MONSTER_DATA
{
  CArray<CString, CString&> key;
  CArray<CString, CString&> value;

  int FindLine(const CString& tag, int index = 0);
  CString GetStringValue(const CString& tag, int index);
  CString GetStringValue(const CString& tag);
  int GetIntegerValue(const CString& tag, int index);
  int GetIntegerValue(const CString& tag);
  void UpdateLine(const CString& tag, const CString& value);
  void UpdateLine(const CString& tag, int value);
  void AddImmunity(const char *immunity);
  void RenameLine(const CString& tag, const CString& newTag);
  void UpdateSpecialAbility(const char *saName, const char *value);
};

