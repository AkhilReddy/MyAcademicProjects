using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IChangeMessageReceiver : IHasAssociatedID 
   {      
      bool WantNotifications { get; set; }
      void EnqueueChangeMessage(IChangeMessage message);
      bool DequeueChangeMessage(out IChangeMessage message);
   }
}
