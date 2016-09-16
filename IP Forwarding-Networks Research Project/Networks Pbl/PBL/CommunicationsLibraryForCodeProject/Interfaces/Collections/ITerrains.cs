using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
	public interface ITerrains : ISupportsFind<long, ITerrain>, ISupportsRemove<ITerrain>, IMultipleItems<ITerrain>, IChanged, ISupportsAdd<ITerrain> 
   {      
      ITerrainCollection FindTerrains(ILocation location);      
   }
}
