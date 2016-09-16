using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IEnablesIntentions 
   {
      Dictionary<int, IIntention> AllowsIntentions { get; }
      List<IIntention> AllowsIntentionList { get; }            
   }
}
