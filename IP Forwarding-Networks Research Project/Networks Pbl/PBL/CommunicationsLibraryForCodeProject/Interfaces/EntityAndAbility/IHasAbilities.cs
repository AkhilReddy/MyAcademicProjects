﻿using System.ComponentModel;
using System.Collections.Generic;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IHasAbilities 
   {
      IAbilityCollection EntityAbilities { get; }
      bool AddEntityAbility(IAbility ability);      
      IIntention GetIntention(int intentionType, out IAbility ability);
   }
}
