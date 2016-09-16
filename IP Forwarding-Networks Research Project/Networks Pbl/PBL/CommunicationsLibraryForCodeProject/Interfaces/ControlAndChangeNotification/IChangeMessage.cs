using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IChangeMessage : IMessage 
   {
      IMessage Message { get; set; }
      string MessageType { get; }
      long From { get; }
      long To { get; }
   }
}
