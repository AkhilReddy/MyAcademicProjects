using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IEntityCollection : ISupportsRemove<long>, ISupportsAdd<long>
   {
   }
}
