using System.Collections.Generic;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
	public interface IAllEntities : ISupportsAdd<IEntity>, ISupportsRemove<long>, ISupportsFind<long, IEntity>, IMultipleItems<IEntity>
   {
      List<long> AllEntityIDs { get; }
   }
}
