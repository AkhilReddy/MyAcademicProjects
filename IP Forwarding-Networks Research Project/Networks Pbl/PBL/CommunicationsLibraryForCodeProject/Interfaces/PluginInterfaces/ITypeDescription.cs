using System;
using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ITypeDescription
   {
      Type ClassType { get; }
      string SourceDLL { get; }
   }
}
