﻿using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ILocation : IVector4
   {
      ILocation LocationVector { get; }
      bool NoLocation { get; }      
   }
}
