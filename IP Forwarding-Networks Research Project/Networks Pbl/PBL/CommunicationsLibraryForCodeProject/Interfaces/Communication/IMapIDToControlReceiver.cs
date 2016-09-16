using System.ComponentModel;
using System.Net.Sockets;
using System.Net;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IMapIDToControlReceiver
   {
      IControlReceiver FindReceiver(long ID);      
   }
}
