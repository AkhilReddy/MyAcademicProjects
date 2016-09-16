using System.Collections.Generic;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IChangeMessageBroadcaster : IMultipleItems<IChangeMessageReceiver>
   {
      void BroadcastChange(IChangeMessage message);
      void Subscribe(IChangeMessageReceiver subscriber);
      void Unsubscribe(IChangeMessageReceiver subscriber);      
   }
}
