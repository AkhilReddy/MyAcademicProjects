using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IHasParameters 
   {
      IParameterCollection Parameters { get; set; }      
   }
}
