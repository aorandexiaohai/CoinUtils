// Copyright (C) 2005, International Business Machines
// Corporation and others.  All Rights Reserved.
#ifndef CoinModelUseful_H
#define CoinModelUseful_H


#include <cmath>
#include <cassert>
#include <cfloat>
#include <string>
#include <cstdio>
#include <iostream>


#include "CoinPragma.hpp"
#include "CoinFinite.hpp"

/**
   This is for various structures/classes needed by CoinModel.

   CoinModelLink
   CoinModelLinkedList
   CoinModelHash
*/
/// for going through row or column

class CoinModelLink {
  
public:
  /**@name Constructors, destructor */
   //@{
   /** Default constructor. */
   CoinModelLink();
   /** Destructor */
   ~CoinModelLink();
   //@}

   /**@name Copy method */
   //@{
   /** The copy constructor. */
   CoinModelLink(const CoinModelLink&);
  /// =
   CoinModelLink& operator=(const CoinModelLink&);
   //@}

   /**@name Sets and gets method */
   //@{
  /// Get row
  inline int row() const
  { return row_;};
  /// Get column
  inline int column() const
  { return column_;};
  /// Get value
  inline double value() const
  { return value_;};
  /// Get value
  inline double element() const
  { return value_;};
  /// Get position
  inline int position() const
  { return position_;};
  /// Get onRow
  inline bool onRow() const
  { return onRow_;};
  /// Set row
  inline void setRow(int row)
  { row_=row;};
  /// Set column
  inline void setColumn(int column)
  { column_=column;};
  /// Set value
  inline void setValue(double value)
  { value_=value;};
  /// Set value
  inline void setElement(double value)
  { value_=value;};
  /// Set position
  inline void setPosition(int position)
  { position_=position;};
  /// Set onRow
  inline void setOnRow(bool onRow)
  { onRow_=onRow;};
   //@}

private:
  /**@name Data members */
  //@{
  /// Row
  int row_;
  /// Column
  int column_;
  /// Value as double
  double value_;
  /// Position in data
  int position_;
  /// If on row chain
  bool onRow_;
  //@}
};

/// for linked lists
// for specifying triple
typedef struct {
  unsigned int string:1; // nonzero if string
  unsigned int row:31;
  //CoinModelRowIndex row;
  int column;
  double value; // If string then index into strings
} CoinModelTriple;

/// for names and hashing
// for hashing
typedef struct {
  int index, next;
} CoinModelHashLink;

class CoinModelHash {
  
public:
  /**@name Constructors, destructor */
  //@{
  /** Default constructor. */
  CoinModelHash();
  /** Destructor */
  ~CoinModelHash();
  //@}
  
  /**@name Copy method */
  //@{
  /** The copy constructor. */
  CoinModelHash(const CoinModelHash&);
  /// =
  CoinModelHash& operator=(const CoinModelHash&);
  //@}

  /**@name sizing (just increases) */
  //@{
  /// Resize hash (also re-hashs)
  void resize(int maxItems);
  /// Number of items i.e. rows if just row links
  inline int numberItems() const
  { return numberItems_;};
  /// Maximum number of items
  inline int maximumItems() const
  { return maximumItems_;};
  /// Names
  inline const char *const * names() const
  { return names_;};
  //@}

  /**@name hashing */
  //@{
  /// Returns index or -1
  int hash(const char * name) const;
  /// Adds to hash
  void addHash(int index, const char * name);
  /// Deletes from hash
  void deleteHash(int index);
  /// Returns name at position (or NULL)
  const char * name(int which) const;
private:
  /// Returns a hash value
  int hashValue(const char * name) const;
public:
  //@}
private:
  /**@name Data members */
  //@{
  /// Names
  char ** names_;
  /// hash
  CoinModelHashLink * hash_;
  /// Number of items 
  int numberItems_;
  /// Maximum number of items
  int maximumItems_;
  /// Last slot looked at
  int lastSlot_;
  //@}
};
/// For int,int hashing
class CoinModelHash2 {
  
public:
  /**@name Constructors, destructor */
  //@{
  /** Default constructor. */
  CoinModelHash2();
  /** Destructor */
  ~CoinModelHash2();
  //@}
  
  /**@name Copy method */
  //@{
  /** The copy constructor. */
  CoinModelHash2(const CoinModelHash2&);
  /// =
  CoinModelHash2& operator=(const CoinModelHash2&);
  //@}

  /**@name sizing (just increases) */
  //@{
  /// Resize hash (also re-hashs)
  void resize(int maxItems, const CoinModelTriple * triples);
  /// Number of items i.e. rows if just row links
  inline int numberItems() const
  { return numberItems_;};
  /// Maximum number of items
  inline int maximumItems() const
  { return maximumItems_;};
  //@}

  /**@name hashing */
  //@{
  /// Returns index or -1
  int hash(int row, int column, const CoinModelTriple * triples) const;
  /// Adds to hash
  void addHash(int index, int row, int column, const CoinModelTriple * triples);
  /// Deletes from hash
  void deleteHash(int index, int row, int column);
private:
  /// Returns a hash value
  int hashValue(int row, int column) const;
public:
  //@}
private:
  /**@name Data members */
  //@{
  /// hash
  CoinModelHashLink * hash_;
  /// Number of items 
  int numberItems_;
  /// Maximum number of items
  int maximumItems_;
  /// Last slot looked at
  int lastSlot_;
  //@}
};
class CoinModelLinkedList {
  
public:
  /**@name Constructors, destructor */
  //@{
  /** Default constructor. */
  CoinModelLinkedList();
  /** Destructor */
  ~CoinModelLinkedList();
  //@}
  
  /**@name Copy method */
  //@{
  /** The copy constructor. */
  CoinModelLinkedList(const CoinModelLinkedList&);
  /// =
  CoinModelLinkedList& operator=(const CoinModelLinkedList&);
  //@}

  /**@name sizing (just increases) */
  //@{
  /** Resize list - for row list maxMajor is maximum rows.
  */
  void resize(int maxMajor,int maxElements);
  /** Create list - for row list maxMajor is maximum rows.
      type 0 row list, 1 column list
  */
  void create(int maxMajor,int maxElements,
              int numberMajor, int numberMinor,
              int type,
              int numberElements, const CoinModelTriple * triples);
  /// Number of major items i.e. rows if just row links
  inline int numberMajor() const
  { return numberMajor_;};
  /// Maximum number of major items i.e. rows if just row links
  inline int maximumMajor() const
  { return maximumMajor_;};
  /// Number of elements
  inline int numberElements() const
  { return numberElements_;};
  /// Maximum number of elements
  inline int maximumElements() const
  { return maximumElements_;};
  /// First on free chain
  inline int firstFree() const
  { return first_[maximumMajor_];};
  /// Last on free chain
  inline int lastFree() const
  { return last_[maximumMajor_];};
  /// First on  chain
  inline int first(int which) const
  { return first_[which];};
  /// Last on  chain
  inline int last(int which) const
  { return last_[which];};
  /// Next array
  inline const int * next() const
  { return next_;};
  /// Previous array
  inline const int * previous() const
  { return previous_;};
  //@}

  /**@name does work */
  //@{
  /** Adds to list - easy case i.e. add row to row list
      Returns where chain starts
  */
  int addEasy(int majorIndex, int numberOfElements, const int * indices,
              const double * elements, CoinModelTriple * triples,
              CoinModelHash2 & hash);
  /** Adds to list - hard case i.e. add row to column list
  */
  void addHard(int minorIndex, int numberOfElements, const int * indices,
               const double * elements, CoinModelTriple * triples,
               CoinModelHash2 & hash);
  /** Adds to list - hard case i.e. add row to column list
      This is when elements have been added to other copy
  */
  void addHard(int first, const CoinModelTriple * triples,
               int firstFree, int lastFree,const int * nextOther);
  /** Deletes from list - same case i.e. delete row from row list
  */
  void deleteSame(int which, CoinModelTriple * triples,
                 CoinModelHash2 & hash);
  /** Deletes from list - hard case i.e. delete row from column list
  */
  void deleteOther(int which, CoinModelTriple * triples,
                   CoinModelHash2 & hash);
  /** Deletes from list - hard case i.e. delete row from column list
      This is when elements have been deleted from other copy
  */
  void updateDeleted(int which, const CoinModelTriple * triples,
                  int firstFree, int lastFree,const int * nextOther);
  //@}
private:
  /**@name Data members */
  //@{
  /// Previous - maximumElements long
  int * previous_;
  /// Next - maximumElements long
  int * next_;
  /// First - maximumMajor+1 long (last free element chain)
  int * first_;
  /// Last - maximumMajor+1 long (last free element chain)
  int * last_;
  /// Number of major items i.e. rows if just row links
  int numberMajor_;
  /// Maximum number of major items i.e. rows if just row links
  int maximumMajor_;
  /// Number of elements
  int numberElements_;
  /// Maximum number of elements
  int maximumElements_;
  /// 0 row list, 1 column list
  int type_;
  //@}
};

#endif