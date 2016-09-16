using System.Collections.Generic;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IObjectCollection : ISupportsRemove<long>, ISupportsAdd<long>, IMultipleItems<long>
   {
   }
}
