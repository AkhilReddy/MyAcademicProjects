﻿using System;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IIntention : IHasAssociatedID, IExecutableWorkItem, IHasParameters, IHasType 
   {      
      ISingleAction ResultingAction { get; }
      TimeSpan IntentionToActionDelay { get; }
      IIntention CreateInstance(IParameterCollection parameters);
      bool PerformIntention();
      IAbility AssociatedEntityAbility { get; set; }            
   }
}
