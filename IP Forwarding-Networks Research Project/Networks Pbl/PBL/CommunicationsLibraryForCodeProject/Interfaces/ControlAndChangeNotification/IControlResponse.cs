using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IControlResponse : IMessage, IHasClassTypeName 
   {
      int ResponseType { get; set; }
      object Response { get; set; }      
   }
}
