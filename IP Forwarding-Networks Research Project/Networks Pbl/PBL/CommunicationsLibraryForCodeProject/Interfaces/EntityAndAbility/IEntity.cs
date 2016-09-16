using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IEntity : IHasAssociatedID, IControlReceiver, IHasSize, IHasLocation, ICanHaveIntent, IHasAbilities, IHasStates, IOwnsObjects, ISuppliesID  
   {
      IPosition Position { get; }
      IOccupySpace OccupySpace { get; }
      void NotifyLocationChanged();
      bool NoLocation { get; }
      ITerrainCollection Terrains { get; }
      IChangeMessageReceiver ChangeMessageReceiver { get; }
      IChangeNotifier ChangeNotifier { get; }
   }
}
