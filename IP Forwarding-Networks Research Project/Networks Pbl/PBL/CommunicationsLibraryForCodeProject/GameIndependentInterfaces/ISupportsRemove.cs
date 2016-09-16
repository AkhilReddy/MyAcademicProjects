﻿using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsRemove<TKeyType>
   {
      bool Remove(TKeyType key);
   }
}
