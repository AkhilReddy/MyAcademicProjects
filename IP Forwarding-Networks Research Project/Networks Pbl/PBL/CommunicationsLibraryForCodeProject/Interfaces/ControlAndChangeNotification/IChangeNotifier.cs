using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IChangeNotifier : IHasAssociatedID 
   {
      void NotifyChanged(IChangeMessage message);      
      void AddBroadcaster(IChangeMessageBroadcaster broadcaster);
      void RemoveBroadcaster(IChangeMessageBroadcaster broadcaster);
      void ClearBroadcasters();
   }
}
