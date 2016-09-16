using System.Collections.Generic;
using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IMultipleItems<T> 
   {
      List<T> AllItems { get; }
      T[] ArrayOfItems { get; }
   }
}
