#pragma once

class BTreeNode;
class A_ASLENTRY_L;


template <class TYPE, class ARG_TYPE>
class mCArray : public CArray<TYPE, ARG_TYPE>
{
  // A private operator....illegal to use.
  // This causes a silent copy of the data!!!!  We were doing
  // thousands of these copies simply because we were peeking into
  // the array elements.
  ARG_TYPE operator[](int indx) const { die("Illegal mCArray Reference"); };
};



#define DEFINE_mCARRAY_ACCESS_FUNCTIONS(name,ID,id,array,data,container) \
  int        Locate##name (const ID& id) const;                          \
  data *Get##name    (const ID& id)                                      \
  {                                                                      \
    return Get##name(Locate##name(id));                                  \
  };                                                                     \
  const data *Peek##name   (const ID& id) const                          \
  {                                                                      \
    return Peek##name(Locate##name(id));                                 \
  };                                                                     \
  data *Get##name    (int i)                                             \
  {                                                                      \
    return (i>=0)?array.GetData()+i:NULL;                                \
  };                                                                     \
  const data *Peek##name   (int i) const                                 \
  {                                                                      \
    return const_cast<container*>(this)->Get##name(i);                   \
  };                                                                     \
  int Get##name##Count(void) const                                       \
  {                                                                      \
    return array.GetSize();                                              \
  };                                                                     \
  int Add(const data& d){return array.Add(const_cast<data&>(d));};



class CStringPAIR
{
  friend class A_CStringPAIR_L;
  friend class CChooseOptions;
  friend class CWhoTriesDlg;
  friend class A_ASLENTRY_L;
  CString m_key;
  CString m_value;
  CStringPAIR(const CStringPAIR& src);
public:
  CStringPAIR(void);
  CStringPAIR(const CString& key, const CString& value);
  CStringPAIR& operator =(const CStringPAIR& src);
  void Clear(void) { m_key = ""; m_value = ""; };
  const CString& Key(void) const { return m_key; };
  const CString& Value(void) const { return m_value; };
  void Value(const CString& value) { m_value = value; };
  int  Compare(LPCSTR key) const;
  int  Compare(const CStringPAIR *b) const;
  bool operator == (const CStringPAIR& p) const;
};


union NDPT // NodePointer/Data 
{
  int        data;
  BTreeNode *pNode;
};

class BTreeNode
{
  friend class BTree;
  friend void CheckNodes(BTreeNode *);
  //#ifdef _DEBUG
  //  int id;
  //#endif
  NDPT      m_left;
  NDPT      m_right;
  int       m_data;
  unsigned _int16 m_cntL; // Count of entries.Left/Right
  unsigned _int16 m_cntR;
  // ****** Functions ********
  int FindNode(int key);
};



struct BTREE_ENVIRONMENT;

class BTree
{
  //friend class A_ASLENTRY_L;
private:
  friend void CheckNodes(BTreeNode *);
  friend void CheckList(bool print = false);
protected:
  BTreeNode *m_root;
private:
  //mutable int m_foundData;
  //********************** FUNCTIONS **************
  int   RemoveData(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  int   AddNode(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  int   DeleteNode(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  int   RemoveSmallest(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  int   RemoveLargest(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  void  PushLeft(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  void  PushRight(BTreeNode *pTop, BTREE_ENVIRONMENT *pEnv);
  void  ClearNode(BTreeNode *pNode, BTREE_ENVIRONMENT *pEnv);
  int   FindNode(BTreeNode *pNode, BTREE_ENVIRONMENT *pEnv) const;
public:
  BTree(void) { m_root = NULL; };
  ~BTree(void);
  int         Insert(BTREE_ENVIRONMENT *pEnv);
  int         Delete(BTREE_ENVIRONMENT *pEnv);
  int         Find(BTREE_ENVIRONMENT *pEnv)const;
  inline int  GetCount(void)const { return (m_root == NULL) ? 0 : 1 + m_root->m_cntL + m_root->m_cntR; };
  void        Clear(BTREE_ENVIRONMENT *pEnv);
  POSITION    GetStartPosition(void) const { return (m_root == NULL) ? NULL : (POSITION)1; };
  int         GetNextAssoc(POSITION& pos) const;
  void        Swap(BTree& pTree);
};



class A_CStringPAIR_L :protected BTree
{
  friend class CAR;

  /****************************************************
  *  Constructors and copy operators
  ***************************************************/
private:
  // These are private because if they are made public it is FAR TOO EASY
  // to cause these CPU-intensive copies accidentally.  It is seldom necessary.
  // If you must COPY then use the Copy function explicitly and put a comment
  // justifying your actions!!!
  A_CStringPAIR_L&   operator = (const A_CStringPAIR_L& attr);
  A_CStringPAIR_L(const A_CStringPAIR_L& specDef);

public:
  A_CStringPAIR_L(void) :BTree() {};
  ~A_CStringPAIR_L(void);
  CArchive& Serialize(CArchive& ar);
  CAR&      Serialize(CAR& car);
  void Export(JWriter& jw);
  void Import(JReader& jr);

  CArchive& Save(CArchive& ar);

  void          Copy(const A_CStringPAIR_L& src);
  void          Copy(const A_ASLENTRY_L& src);
  int           GetCount(void)const { return BTree::GetCount(); };
  void          CommitRestore(const A_CStringPAIR_L *src);
  BOOL          Insert(const CString& key, const CString& data);
  BOOL          Insert(const CStringPAIR& pEntry);
#ifdef UAFEDITOR
  void          Update(LPCSTR key, LPCSTR value);
#endif
  CString       Delete(LPCSTR key);
  CStringPAIR  *Find(LPCSTR key) const;
  const         CString& Lookup(LPCSTR key) const;
  BOOL          operator == (const A_CStringPAIR_L& attr) const;
  void          Clear(void);
  int           GetDataSize(void) const;
  POSITION      GetStartPosition(void) const { return BTree::GetStartPosition(); };
  void          GetNextAssoc(POSITION &pos, const CStringPAIR **ppEntry) const;
};




class SPECIAL_ABILITIES
{
  // A list of special abilityes for an item-type, monster-type, etc. (Arrow, Dragon, etc.)
  // Each ability name is also has the name of a 'Base-Class'.

  /**************************************************
  *    The only data member
  **************************************************/
  A_CStringPAIR_L m_specialAbilities;
  bool m_readOnly; // Not serialized

                   /****************************************************
                   *  Constructors and copy operators
                   ***************************************************/
private:
  // These are private because if they are made public it is FAR TOO EASY
  // to cause these CPU-intensive copies accidentally.  It is seldom necessary.
  // If you must COPY then use the Copy function explicitly and put a comment
  // justifying your actions!!!
  SPECIAL_ABILITIES&   operator =(const SPECIAL_ABILITIES& sa);
  SPECIAL_ABILITIES(const SPECIAL_ABILITIES& sa);
public:
  //friend struct COMBATANT;
  //friend class  CHARACTER;
  //friend class  ITEM_DATA;
  //friend class  SPELL_DATA;
  //friend class  CLASS_DATA;
  //friend class  BASE_CLASS_DATA;
  //friend class  RACE_DATA;
  //friend class  MONSTER_DATA;
  //friend struct COMBAT_DATA;

  enum specialAbilitiesType;

public:
  SPECIAL_ABILITIES(bool readOnly = false);

  /****************************************************
  *    Functions
  ****************************************************/
public:
  ~SPECIAL_ABILITIES(void);

  const A_CStringPAIR_L&  SpecialAbilities(void) const { return m_specialAbilities; };
  void                    Copy(const SPECIAL_ABILITIES& spab);
  void                    Copy(const A_ASLENTRY_L& asl);
  bool                    operator == (const SPECIAL_ABILITIES& psa) const;
  void                    Clear(void);
  void                    Serialize(CAR &ar, double ver, LPCSTR objName, LPCSTR objType);
  void                    Serialize(CArchive &ar, double ver, LPCSTR objName, LPCSTR objType);
  void Export(JWriter& jw);
  void Import(JReader& jr);

  CStringPAIR            *FindAbility(specialAbilitiesType sa) const;

  //  void                InsertString(specialAbilitiesType sa, const CString& stringName, const CString& string, unsigned char type);
  void     InsertAbility(const CString& name, const CString& parameter, LPCSTR d1, LPCSTR d2);
  void     InsertAbility(const CString& str);
  CString  DeleteAbility(const CString& name);  // Returns parameter or NO_SUCH_SA
  void     InsertAbility_RO(const CString& name, const CString& parameter, LPCSTR d1, LPCSTR d2);
  CString  DeleteAbility_RO(const CString& name);  // Returns parameter or NO_SUCH_SA

  POSITION            GetHeadPosition(void) const { return m_specialAbilities.GetStartPosition(); };
  const CString&      GetAt(POSITION pos) const;
  const CString&      GetNext(POSITION &pos) const;
  const CStringPAIR  *GetNextData(POSITION& pos) const;

  void                EnableSpecAb(specialAbilitiesType sa); // adds with default activation script
  void                EnableSpecAb(specialAbilitiesType sa, const CString& script, const CString& script2);
  void                DisableSpecAb(specialAbilitiesType sa);

  const CString&      GetString(specialAbilitiesType sa) const;
  DWORD               GetMsgTypes(specialAbilitiesType sa) const;
  const CString&      GetSpecAbUserScript(specialAbilitiesType sa) const;
  //        CString       GenerateSpecAbFuncStart(specialAbilitiesType sa) const;
  //        CString       GenerateSpecAbFuncEnd(specialAbilitiesType sa) const;
  const CString&      GetSpecAbUserDAScript(specialAbilitiesType sa) const;
  CString       GenerateSpecAbFuncName(specialAbilitiesType sa) const;
  bool                HaveAtLeastOneSpecAb() const;
  void                SetMsgFormat(specialAbilitiesType sa, DWORD type, CString &format);
  CString       GetMsgFormat(specialAbilitiesType sa, DWORD type) const;
  void                SetMsgTypes(specialAbilitiesType sa, DWORD types);
  bool                HaveSpecAb(specialAbilitiesType sa) const;

  int                 GetCount(void) const { return m_specialAbilities.GetCount(); };
  int                 GetDataSize(void) const { return m_specialAbilities.GetDataSize(); };

  CString             RunScripts(LPCSTR scriptName,
  enum CBRESULT(*fnc)(enum CBFUNC func, CString *scriptResult, void *pkt),
    void *pkt,
    LPCSTR SA_Source_Type,
    LPCSTR SA_Source_Name
    ) const;

};
