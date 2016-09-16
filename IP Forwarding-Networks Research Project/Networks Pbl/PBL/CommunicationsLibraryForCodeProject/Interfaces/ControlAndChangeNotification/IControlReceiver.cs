using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IControlReceiver
   {
      IControlResponse HandleIncomingControlCommand(IControlCommand controlCommand);
   }
}
