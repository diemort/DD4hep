//==========================================================================
//  AIDA Detector description implementation for LCD
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================

// Framework includes
#include "DD4hep/IOV.h"
#include "DD4hep/Handle.inl"

#include "DD4hep/World.h"
#include "DD4hep/Printout.h"
#include "DD4hep/InstanceCount.h"
#include "DD4hep/objects/DetectorInterna.h"
#include "DD4hep/objects/AlignmentsInterna.h"

using namespace std;
using namespace DD4hep::Alignments;
using namespace DD4hep::Alignments::Interna;

DD4HEP_INSTANTIATE_HANDLE_NAMED(AlignmentObject);
DD4HEP_INSTANTIATE_HANDLE_UNNAMED(AlignmentData);

/// Default constructor
AlignmentObject::AlignmentObject()
  : ConditionObject(), alignment_data(0)//, source_key(0)
{
  InstanceCount::increment(this);
  flags  = Conditions::Condition::ALIGNMENT_DERIVED;
  AlignmentData& d = data.bind<AlignmentData>();
  alignment_data   = &d;
}

/// Standard constructor
AlignmentObject::AlignmentObject(const string& nam, const string& tit, void* p, size_t len)
  : ConditionObject(nam, tit), alignment_data(0)//, source_key(0)
{
  InstanceCount::increment(this);
  flags  = Conditions::Condition::ALIGNMENT_DERIVED|Conditions::Condition::ONSTACK;
  AlignmentData& d = data.bind<AlignmentData>(p,len);
  alignment_data   = &d;
}

/// Standard Destructor
AlignmentObject::~AlignmentObject()  {
  InstanceCount::decrement(this);
}

/// Clear data content on demand.
void AlignmentObject::clear()   {
  AlignmentCondition a(this);
  AlignmentData& d = a.data();
  d.trToWorld = Transform3D();
  d.detectorTrafo.Clear();
  d.worldTrafo.Clear();
  d.nodes.clear();
  flags = Conditions::Condition::ALIGNMENT_DERIVED;
}
