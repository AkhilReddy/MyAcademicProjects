using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IGetSetValueByName
   {      
      string Name { get; set; }
      int Value { get; set; }      
   }
}
