using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
	public interface IGameObjects : ISupportsFind<long, IGameObject>, ISupportsAdd<IGameObject>, ISupportsRemove<IGameObject>, IMultipleItems<IGameObject>
   {      
      IObjectCollection FindObjects(ILocation location);    
   }
}
