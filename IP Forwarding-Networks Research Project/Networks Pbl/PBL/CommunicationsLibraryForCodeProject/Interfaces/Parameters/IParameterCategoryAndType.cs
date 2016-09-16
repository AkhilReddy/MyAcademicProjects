using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IParameterCategoryAndType 
   {
      IDynamicEnumEntry ParameterType { get; set; }
      IDynamicEnumEntry ParameterCategory { get; set; }      
   }
}
